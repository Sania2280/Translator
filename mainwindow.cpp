#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include "translator.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "quise.h"
#include <QMessageBox>
#include "enum.h"

int wordsCounter;
Quis origLeng = Quis::EN;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , translator(new Translator(this))  // Инициализация объекта Translator
{
    Ui();
    PrintAllWords();

    connect(translator, &Translator::translationReady, this, &MainWindow::onTranslationReady);
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::PrintAllWords()
{
    QJsonObject database =  ReadFile();

    ui->ALL_WORDS_listWidget->clear();

    for (const QString & key : database.keys()) {

        QJsonValue value = database.value(key);
        QJsonObject userObj = value.toObject();

        QString line = key + QChar(0x200B) ;
        int length = line.length();

        for (int i = 40 - length; i > 0; i--) {
            line += "-";
        }

        line += userObj["translate_1"].toString();

        QListWidgetItem *item = new QListWidgetItem(line);

        ui->ALL_WORDS_listWidget->addItem(item);

    }
}

void MainWindow::onTranslationReady(const QString &translatedText)
{
    // Отображение переведенного текста в UI (например, в QTextBrowser)
    ui->TRANSLATED_listWidget->addItem(translatedText);
    PrintAllWords();
}

void MainWindow::on_lineEdit_returnPressed()
{
      // Текст для перевода из текстового поля
    QString textToTranslate = ui->lineEdit->text();
    QString targetLang = "UK";  // Целевой язык для перевода (например, "EN" для английского)

    // Вызов метода translate
    translator->translate(textToTranslate, targetLang);
    ui->lineEdit->clear();

}

void MainWindow::Ui()
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "Translator");
    ui->tabWidget->setTabText(1, "All Words");
    ui->tabWidget->setTabText(2, "Quise");
    ui->tabWidget->setTabText(3, "Word");

    QFont monospaceFont("Courier New");
    monospaceFont.setStyleHint(QFont::Monospace);
    ui->tabWidget->setFont(monospaceFont);

    ui->lineEdit->setPlaceholderText("Enter a word...");
    ui->word_find->setPlaceholderText("Type word to find ...");

    ui->checkBox_2->setChecked(true);

    QFont font0 = ui->ALL_WORDS_listWidget->font();
    ui->ALL_WORDS_listWidget->setFont(font0);

    QFont font = ui->transListWidget->font();
    font.setPointSize(18);

    QFont font1("Georgia", 13);
    font1.setWeight(QFont::Light);
    ui->tabWidget->setFont(font1);

    QFont font2("Georgia", 16);
    ui->wordTextEdit->setFont(font2);
    ui->transListWidget->setFont(font2);


}

QJsonObject MainWindow::ReadFile()
{
    QFile file("Words.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Error opening DB for reading.";
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "Invalid JSON format.";
    }

    QJsonObject database = doc.object();
    return database;
}

void MainWindow::WordFinder(QString text, int stat)
{
    ui->ALL_WORDS_listWidget->clearSelection();

    if (text.isEmpty()) {
        qDebug() << "No element";
        return;
    }

    if(lastSearched != text){
        foundItems = ui->ALL_WORDS_listWidget->findItems(text, Qt::MatchContains);
        lastSearched = text;
        listIt = 0;

    }
    if (foundItems.isEmpty()) {
        qDebug() << "Nothing found";
        return;
    }

    // контролюємо індекс
    if (stat == 1) { // вниз
        if (listIt + 1 < foundItems.size())
            listIt++;
    } else if (stat == 2) { // вгору
        if (listIt - 1 >= 0)
            listIt--;
    } else { // перший пошук
        listIt = 0;
    }

    QListWidgetItem* item = foundItems[listIt];
    item->setSelected(true);
    ui->ALL_WORDS_listWidget->setCurrentItem(item);
    ui->ALL_WORDS_listWidget->scrollToItem(item);
}

void MainWindow::SetAllWordsSize()
{
    QFont font2 = ui->ALL_WORDS_listWidget->font();
    font2.setPointSize(14);
    ui->ALL_WORDS_listWidget->setFont(font2);
}




void MainWindow::on_spinBox_valueChanged()
{    
    QJsonObject database = ReadFile();

    wordsCounter = database.size();

    if(ui->spinBox->value() > wordsCounter) return;

    ui->tableWidget->setRowCount(ui->spinBox->value());
    ui->tableWidget->setColumnCount(3);

    if(origLeng == Quis::EN){
        ui->tableWidget->setHorizontalHeaderLabels({"English", "Translation", "Result"});
    }
    else if(origLeng == Quis::UK){
        ui->tableWidget->setHorizontalHeaderLabels({"Ukrain", "Translation", "Result"});
    }
    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->setColumnWidth(1, 300);


    Quise quise;
    QVector<QString> words = quise.QuiseStr(ui->spinBox->value(), wordsCounter, origLeng);


    int row = 0;
    int allrow = ui->spinBox->value();
    for (const auto& key : words) {
        QTableWidgetItem* englishItem = new QTableWidgetItem(key);
        ui->tableWidget->setItem(row, 0, englishItem);

        QTableWidgetItem* answerItem = new QTableWidgetItem("");
        ui->tableWidget->setItem(row, 1, answerItem);

        QTableWidgetItem* empty = new QTableWidgetItem("");
        ui->tableWidget->setItem(row, 2, empty);

        row++;

        if(row == allrow) break;
    }

}


void MainWindow::on_pushButton_clicked()
{
    int rows = ui->tableWidget->rowCount();
    qDebug() << rows;

    QVector<QVector<QString>> data;

    for (int i = 0; i < rows; ++i) {
        QTableWidgetItem* itemsEng = ui->tableWidget->item(i, 0);
        QTableWidgetItem* itemsUkr = ui->tableWidget->item(i, 1);

        if(itemsEng && itemsUkr){
            data.push_back({itemsEng->text(), itemsUkr->text()});
        }
        else qDebug() << "Error";
    }


    Quise quise;
    QVector<bool> results = quise.QuiseResult(data, origLeng);


    for (auto row = 0 ; row < results.size(); row++) {
        QString res ;
        if(results[row] == false){
            res = "false ❌";
        }
        else res = "true ✅";
        QTableWidgetItem* resultItem = new QTableWidgetItem(res);
        qDebug() << results[row];
        ui->tableWidget->setItem(row, 2, resultItem);
    }
}


void MainWindow::on_pushButton_2_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you shure that you whant to delete this?",
                                  QMessageBox::Yes| QMessageBox::No);

    if(reply == QMessageBox::Yes){

        QString text = ui->ALL_WORDS_listWidget->currentItem()->text();
        QListWidgetItem* item = ui->ALL_WORDS_listWidget->currentItem();

        int row = ui->ALL_WORDS_listWidget->row(item);
        ui->ALL_WORDS_listWidget->takeItem(row);
        QVector<QString> str = text.split(QChar(0x200B));
        delete item;

        DataBase db;
        db.DeleteWord(str[0]);
    }

}


void MainWindow::on_checkBox_2_clicked()
{
    origLeng = Quis::EN;

    on_spinBox_valueChanged();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(true);
}


void MainWindow::on_checkBox_clicked()
{
    origLeng = Quis::UK;

    on_spinBox_valueChanged();
    ui->checkBox_2->setChecked(false);
    ui->checkBox->setChecked(true);
}



void MainWindow::on_word_find_textChanged(const QString &arg1)
{
    listIt = 0;
    WordFinder(arg1, 0);
}


void MainWindow::on_downButon_clicked()
{
    WordFinder(ui->word_find->text(), 1);
}


void MainWindow::on_upButton_clicked()
{
    WordFinder(ui->word_find->text(), 2);
}


void MainWindow::on_pushButton_3_clicked()
{
    auto selectedItems = ui->ALL_WORDS_listWidget->selectedItems();
    ui->transListWidget->clear();

    if (!selectedItems.isEmpty()) {

        ui->tabWidget->setCurrentIndex(3);
        DataBase DB;

        QListWidgetItem* item = selectedItems.first();
        QString word = item->text().split('-').first().trimmed();

        ui->wordTextEdit->setFontPointSize(18);
        ui->wordTextEdit->setText(word);

        QStringList translation = DB.GetAllTranslation(word);

        for (const QString &tr : translation) {
            ui->transListWidget->addItem(tr);
        }
    }

}


void MainWindow::on_addTransButton_clicked()
{
    if(!ui->lineEdit_2->text().isEmpty()){
        DataBase DB;
        DB.AddNewWord(ui->wordTextEdit->toPlainText(), ui->lineEdit_2->text());
        on_pushButton_3_clicked();
        ui->lineEdit_2->clear();
    }
}


void MainWindow::on_transListWidget_itemClicked(QListWidgetItem *item)
{
    ui->lineEdit_2->setText(item->text());
}


void MainWindow::on_editTransButon_clicked()
{
    if(!ui->lineEdit_2->text().isEmpty() && !ui->transListWidget->selectedItems().isEmpty()){
        DataBase DB;
        QListWidgetItem *item = ui->transListWidget->currentItem();
        DB.EditTranslaton(ui->wordTextEdit->placeholderText(), item->text(), ui->lineEdit_2->text());
        ui->lineEdit->clear();
        on_pushButton_3_clicked();
        ui->lineEdit_2->clear();

    }
}




void MainWindow::on_delTransButon_clicked()
{
    if(!ui->transListWidget->selectedItems().isEmpty()){

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete", "Are you shure that you whant to delete this?",
                                      QMessageBox::Yes| QMessageBox::No);

        if(reply == QMessageBox::Yes){
            DataBase DB;
            QListWidgetItem *item = ui->transListWidget->currentItem();
            DB.DeleteTranslation(ui->wordTextEdit->placeholderText(), item->text());

            if (item) {
                int row = ui->transListWidget->row(item);
                delete ui->transListWidget->takeItem(row);
            }

            ui->lineEdit_2->clear();
        }
    }
}

