#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include<QFile>

class DataBase
{
public:
    DataBase();
    void SaveNewWord(QString original, QString translated);
    void RewriteFile(QJsonObject db);
    void CreateOrCreateFile();
    void extracted(QString &word, QJsonObject &DB);
    void DeleteWord(QString word);
    void AddNewWord(QString orig, QString translte);
    void extracted(QString &cleanWord, const QString &key,
                   QString &keyLowClean);
    void EditTranslaton(QString orig, QString transOld, QString tranlNew);
    void DeleteTranslation(QString orig, QString toDel);
    QStringList GetAllTranslation(QString word);
    QJsonObject ReadFile(QString name);
};

#endif // DATABASE_H
