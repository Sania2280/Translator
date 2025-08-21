#include "quise.h"
#include <qdebug.h>
#include<random>
#include "database.h"
#include <QJsonObject>

Quise::Quise() {}

QVector<QString> Quise::QuiseStr(int count, int max)
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
    for (int i = 0; i < count; i++) {
        words.push_back(allWords[randoms[i]]);
    }
    return words;
}
