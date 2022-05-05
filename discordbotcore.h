#ifndef DISCORDBOTCORE_H
#define DISCORDBOTCORE_H

#include <QObject>
#include "discordbotabstractstrategy.h"
#include <QtDebug>
#include <QtNetwork>
#include <QtWebSockets/QWebSocket>
#include "additional/json.hpp"//беру json.hpp от nlohmann'а мне лично удобнее работать с ним чем с реализацией от Qt
using namespace nlohmann;
class discordBotCore : public QObject
{
    Q_OBJECT
private:
    QString _apiKey;
    QString myId;

    QNetworkAccessManager * _accessManager;
    unsigned int _intents;//дефолтное значение 512 для обработки guild_messages(см. https://discord.com/developers/docs/topics/gateway)
    QVector<QPair<QByteArray,QByteArray>> discordHeader;
    QString endpoint;
    QWebSocket  webSocket;
    QTimer hearthBeat;

    unsigned hearthBeatInterval = 41250;


private:
    QString HTTPget(QString url,const QVector<QPair<QByteArray,QByteArray>> & header = {});
    QString HTTPpost(QString url, const QByteArray &data, const QVector<QPair<QByteArray,QByteArray>> & header = {});
private slots:
    void onConnected();
    void onHearthBeat();
    void onTextMessageReceived(QString message);
    void closed();
public:
    explicit discordBotCore(QString apiKey,unsigned int intents = 512,QObject *parent = nullptr);
     void webSocketConnect();
    ~discordBotCore();
public slots:
    void sendTextMessage(QString data, QString reply, QString channel);
signals:
    void processMessage(QString type,QString data);
    void sendBotId(QString id);
    void noConnection();
};

#endif // DISCORDBOTCORE_H
