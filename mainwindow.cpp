#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include "translator.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "quise.h"

int wordsCounter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , translator(new Translator(this))  // Инициализация объекта Translator
{
    Ui();

    PrintAllWords();

    // Подключение сигнала от Translator к слоту для обработки перевода
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

        QString line = key ;
        int length = line.length();

        for (int i = 50 - length; i > 0; i--) {
            line += "-";
        }

        line += userObj["translate"].toString();

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

}

void MainWindow::Ui()
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0, "Translator");
    ui->tabWidget->setTabText(1, "All Words");
    ui->tabWidget->setTabText(2, "Quise");

    QFont monospaceFont("Courier New");
    monospaceFont.setStyleHint(QFont::Monospace);
    ui->tabWidget->setFont(monospaceFont);



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


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    QJsonObject database = ReadFile();

    wordsCounter = database.size();

    if(ui->spinBox->value() > wordsCounter) return;

    ui->tableWidget->setRowCount(ui->spinBox->value());
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"English", "Translation"});
    ui->tableWidget->setColumnWidth(0, 300);
    ui->tableWidget->setColumnWidth(1, 300);

    Quise quise;
    QVector<QString> words = quise.QuiseStr(ui->spinBox->value(), wordsCounter);


    int row = 0;
    int allrow = ui->spinBox->value();
    for (const auto& key : words) {
        QTableWidgetItem* englishItem = new QTableWidgetItem(key);
        ui->tableWidget->setItem(row, 0, englishItem);

        QLineEdit* answerField = new QLineEdit();
        ui->tableWidget->setCellWidget(row, 1, answerField);
        row++;

        if(row == allrow) break;
    }

}

