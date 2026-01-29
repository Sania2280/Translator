#include "database.h"
#include "QJsonObject"
#include <QJsonDocument>



DataBase::DataBase() {}

void DataBase::SaveNewWord(QString original, QString translated)
{
    QFile file("Words.json");
    QJsonObject database = ReadFile("Words.json");

    if(translated.back() ==  '.' && !translated.isEmpty()){
        translated.chop(1);
    }

    QJsonObject newWord;
    if(translated[0].isLower()){
        QString temp = translated.mid(1);
        translated = translated[0].toUpper() + temp;
    }

    QString origLow = original.toLower();
    newWord["keyLow"] = origLow;
    newWord["translate_1"] = translated;
    newWord["translate_2"] = translated.toLower();

    database[original] = newWord;

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Word added successesfully";
    } else {
        qWarning() << "Failed to open file for writing";
    }

}

void DataBase::RewriteFile(QJsonObject db)
{
    QJsonDocument doc(db);
    QFile file("Words.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи" ;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); // Записываем с отступами
    file.close();
}

void DataBase::CreateOrCreateFile()
{
    QFile file("Words.json");

    // Відкриваємо файл для читання та запису (створить, якщо не існує)
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);
        file.close();

    } else {
        qDebug() << "Не вдалося відкрити або створити файл!";
    }
    file.close();
}

void DataBase::DeleteWord(QString word)
{
    QJsonObject DB = ReadFile("Words.json");

    if (DB.contains(word)) {
        DB.remove(word);
    }
    RewriteFile(DB);
}

void DataBase::AddNewWord(QString orig, QString translte)
{
    orig = orig.trimmed();
    orig.remove(QChar(0x200B));
    orig.remove(QChar(0xFEFF));
    if (orig.isEmpty()) {
        qWarning() << "Empty original word — abort";
        return;
    }

    QFile file("Words.json");
    QJsonObject database = ReadFile("Words.json");
    QJsonObject obj;
    QString mainKey = QString();

    if (database.contains(orig)) {
        mainKey = orig;
        obj = database.value(mainKey).toObject();
    } else {
        QString searchKeyLow = orig.toLower();
        for (const QString &k : database.keys()) {
            QJsonObject candidate = database.value(k).toObject();
            QString keyLow = candidate.value("keyLow").toString();
            keyLow.remove(QChar(0x200B));
            keyLow.remove(QChar(0xFEFF));
            if (keyLow == searchKeyLow) {
                mainKey = k;
                obj = candidate;
                break;
            }
        }
    }


    if (mainKey.isEmpty()) {
        mainKey = orig;
        obj = QJsonObject();
        obj.insert("keyLow", orig.toLower());
    }

    // Ищем максимальный индекс translate_N корректно (toInt(&ok))
    int maxIndex = 0;
    for (const QString &key : obj.keys()) {
        if (key.startsWith("translate_")) {
            bool ok = false;
            int index = key.mid(QString("translate_").length()).toInt(&ok);
            if (ok && index > maxIndex) {
                maxIndex = index;
            }
        }
    }

    int newInd = maxIndex + 1;
    QString newKey = QString("translate_%1").arg(newInd);

    obj.insert(newKey, translte);
    database.insert(mainKey, obj);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Word added successfully to key:" << mainKey << "as" << newKey;
    } else {
        qWarning() << "Failed to open file for writing";
    }
}

void DataBase::EditTranslaton(QString orig, QString transOld, QString tranlNew)
{
    QFile file("Words.json");
    QJsonObject database = ReadFile("Words.json");
    QStringList translations;

    QString cleanWord = orig.trimmed();
    cleanWord.remove(QChar(0x200B));
    cleanWord = cleanWord.toLower();

    for (const QString& key : database.keys()) {
        QJsonObject obj = database.value(key).toObject();

        QString keyClean = key.trimmed().toLower();
        QString keyLowClean = obj.value("keyLow").toString().trimmed().toLower();

        for (const QString tkeys : obj.keys()) {
            if(tkeys.startsWith("translate_")){
                if(obj.value(tkeys).toString() == transOld){
                    obj.insert(tkeys, tranlNew);
                    database.insert(key, obj);
                    break;
                }
            }
        }
    }

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Translation Edit Seccsessfuly:" ;
    } else {
        qWarning() << "Failed to edit";
    }
}

void DataBase::DeleteTranslation(QString orig, QString toDel)
{
    QFile file("Words.json");
    QJsonObject database = ReadFile("Words.json");
    QStringList translations;

    QString cleanWord = orig.trimmed();
    cleanWord.remove(QChar(0x200B));
    cleanWord = cleanWord.toLower();

    for (const QString& key : database.keys()) {
        QJsonObject obj = database.value(key).toObject();

        QString keyClean = key.trimmed().toLower();
        QString keyLowClean = obj.value("keyLow").toString().trimmed().toLower();

        for (const QString tkeys : obj.keys()) {
            if(tkeys.startsWith("translate_")){
                if(obj.value(tkeys).toString() == toDel){
                    obj.remove(tkeys);
                    database.insert(key, obj);
                    break;
                }
            }
        }
    }

    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(database).toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Translation Edit Seccsessfuly:" ;
    } else {
        qWarning() << "Failed to edit";
    }

}

QStringList DataBase::GetAllTranslation(QString word)
{
    QJsonObject database = ReadFile("Words.json");
    QStringList translations;

    QString cleanWord = word.trimmed();
    cleanWord.remove(QChar(0x200B));
    cleanWord = cleanWord.toLower();

    for (const QString& key : database.keys()) {
        QJsonObject wordObj = database.value(key).toObject();

        QString keyClean = key.trimmed().toLower();
        QString keyLowClean = wordObj.value("keyLow").toString().trimmed().toLower();

        if (keyClean == cleanWord || keyLowClean == cleanWord) {

            if (wordObj.contains("translate_1"))
                translations << wordObj.value("translate_1").toString();

            for (const QString &tkey : wordObj.keys()) {
                if (tkey.startsWith("translate_")) {

                    bool ok = false;
                    int index = tkey.mid(10).toInt(&ok);

                    if (ok && index != 1 && index != 2) {
                        translations << wordObj.value(QString("translate_%1").arg(index)).toString();
                    }
                }
            }

            break;
        }
    }

    return translations;
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

