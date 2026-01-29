#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTextBrowser>
#include <qlistwidget.h>
#include "translator.h"  // Подключаем заголовочный файл Translator

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void PrintAllWords();

private slots:
    void onTranslationReady(const QString &translatedText);  // Слот для получения переведённого текста

    void on_lineEdit_returnPressed();

    void on_spinBox_valueChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_clicked();

    void on_word_find_textChanged(const QString &arg1);

    void on_downButon_clicked();

    void on_upButton_clicked();

    void on_pushButton_3_clicked();

    void on_addTransButton_clicked();

    void on_transListWidget_itemClicked(QListWidgetItem *item);

    void on_editTransButon_clicked();


    void on_delTransButon_clicked();

private:
    Ui::MainWindow *ui;
    Translator *translator;  // Указатель на объект Translator
    void Ui();
    QJsonObject ReadFile();
    void WordFinder(QString text, int stat);

    int listIt;
    QString lastSearched;
    QList<QListWidgetItem*> foundItems;
    void SetAllWordsSize();
};

#endif // MAINWINDOW_H
