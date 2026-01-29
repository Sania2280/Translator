#ifndef QUISE_H
#define QUISE_H
#include<QVector>
#include <QString>

#include "enum.h"

class Quise
{
public:
    Quise();

    QVector<QString> QuiseStr(int count, int max, Quis origLeng);
    QVector<bool> QuiseResult(QVector<QVector<QString>> data, Quis origLeng);

};

#endif // QUISE_H
