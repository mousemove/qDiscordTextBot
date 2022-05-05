#ifndef DISCORDBOT_H
#define DISCORDBOT_H

#include <QObject>
#include "discordbotabstractstrategy.h"
#include "discordbotcore.h"
//небольшой медиатор для связки
class discordBot : public QObject
{
    Q_OBJECT
private:
    discordBotCore * _core;
    discordBotAbstractStrategy * _strategy;
    QString _apiKey;
public:
    explicit discordBot(QString apiKey,discordBotAbstractStrategy * strategy,QObject *parent = nullptr);
public slots:
    void noConnection();

};

#endif // DISCORDBOT_H
