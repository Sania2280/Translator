#include "quise.h"
#include <qdebug.h>
#include <random>
#include "database.h"
#include <QJsonObject>
#include "enum.h"
Quise::Quise() {}

QVector<QString> Quise::QuiseStr(int count, int max, Quis origLeng)
{
    std::random_device rd;  // аппаратный источник случайности (если доступен)
    std::mt19937 gen(rd()); // генератор Mersenne Twister
    std::uniform_int_distribution<> dist(0, max);

    DataBase DB;
    QJsonObject database = DB.ReadFile("Words.json");

    QVector<int> randoms;

    for (int i = 0; i < max; ++i) {

        randoms.push_back(i);
    }

    std::shuffle(randoms.begin(), randoms.end(),gen);

    QVector<QString> allWords;
    for (auto &i : database.keys()) {
        allWords.push_back(i);
    }

    QVector<QString> words;
    if(origLeng == Quis::EN){
        for (int i = 0; i < count; i++) {
            words.push_back(allWords[randoms[i]]);
        }
    }
    else if(origLeng == Quis::UK){
        for (int i = 0; i < count; ++i) {
            QJsonValue val = database[allWords[randoms[i]]];
            QJsonObject item = val.toObject();
            words.push_back(item["translate_1"].toString());
        }
    }

    return words;
}

QVector<bool> Quise::QuiseResult(QVector<QVector<QString>> data, Quis origLeng)
{
    DataBase DB;
    QJsonObject database = DB.ReadFile("Words.json");
    QVector<bool> result(data.size(), false);

    if(origLeng == Quis::EN){

        for (int i = 0; i < data.size(); ++i) {
            for (auto& key : database.keys()) {

                if(data[i][0] == key){
                    QJsonValue val = database[key];

                    if(val.isObject()){
                        QJsonObject item = val.toObject();
                        if(data[i][1] == item["translate_1"].toString() || data[i][1] == item["translate_2"].toString()){
                            result[i] = true;
                        }
                        else result[i] = false;
                    }
                }
            }
        }
    }

    else if (origLeng == Quis::UK) {
        for (int i = 0; i < data.size(); ++i) {
            for (const auto &key : database.keys()) {
                QJsonValue val = database.value(key);

                if (val.isObject()) {
                    QJsonObject item = val.toObject();
                    if (item["translate_1"].toString() == data[i][0] ) {
                        if (data[i][1] == key || data[i][1] == item["keyLow"].toString()) {
                            result[i] = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return result;

}


