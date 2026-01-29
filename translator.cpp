#include "translator.h"
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "database.h"

QString original;

Translator::Translator(QObject *parent) : QObject(parent) {
    connect(&manager, &QNetworkAccessManager::finished,
            this, &Translator::onReplyFinished);
}

void Translator::translate(const QString &text, const QString &targetLang) {
    original = text;

    QUrl url("https://api-free.deepl.com/v2/translate");
    QNetworkRequest request(url);

    // Устанавливаем Content-Type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Передаем ключ через заголовок Authorization
    request.setRawHeader("Authorization", "DeepL-Auth-Key caed2d0e-5883-4ec6-8289-7211f7c1f503:fx"); // <-- замените на свой ключ

    // Параметры запроса без auth_key
    QUrlQuery params;
    params.addQueryItem("text", text);
    params.addQueryItem("target_lang", targetLang);

    QByteArray postData = params.query(QUrl::FullyEncoded).toUtf8();

    // Отправка POST
    QNetworkReply* reply = manager.post(request, postData);

    // Подключаем к существующему слоту обработки ответа
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        this->onReplyFinished(reply);
    });
}


void Translator::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(response);
        if (!json.isNull()) {
            auto translated = json["translations"].toArray()[0].toObject()["text"].toString();

            DataBase DB;
            DB.SaveNewWord(original, translated);

            emit translationReady(translated);
        }
    } else {
        qDebug() << "Translation error:" << reply->errorString();
    }
    reply->deleteLater();
}
