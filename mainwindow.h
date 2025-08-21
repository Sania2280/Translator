#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTextBrowser>
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

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Translator *translator;  // Указатель на объект Translator
    void Ui();
    QJsonObject ReadFile();
};

#endif // MAINWINDOW_H
