#include "database.h"
#include "QJsonObject"
#include<QJsonDocument>



DataBase::DataBase() {}

void DataBase::SaveNewWord(QString original, QString translated)
{
    QFile file("Words.json");
    QJsonObject database = ReadFile("Words.json");

    QJsonObject newWord;
    newWord["translate"] = translated;

    database[original] = newWord;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Word added successesfully";
    } else {
        qWarning() << "Failed to open file for writing";
    }

}

void DataBase::CreateOrCreateFile()
{
    QFile file("Words.json");

    // Відкриваємо файл для читання та запису (створить, якщо не існує)
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Привіт! Це автоматично створений або відкритий файл.\n";
        file.close();
        qDebug() << "Файл створено або відкрито, запис виконано.";

    } else {
        qDebug() << "Не вдалося відкрити або створити файл!";
    }
    file.close();
}


QJsonObject DataBase::ReadFile(QString name)
{
    QFile file(name);
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

