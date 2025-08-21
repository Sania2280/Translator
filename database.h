#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include<QFile>

class DataBase
{
public:
    DataBase();
    void SaveNewWord(QString original, QString translated);
    void CreateOrCreateFile();
    QJsonObject ReadFile(QString name);
};

#endif // DATABASE_H
