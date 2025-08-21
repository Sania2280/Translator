#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Translator : public QObject {
    Q_OBJECT

public:
    explicit Translator(QObject *parent = nullptr);
    void translate(const QString &text, const QString &targetLang = "EN");

signals:
    void translationReady(const QString &translatedText);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
};
