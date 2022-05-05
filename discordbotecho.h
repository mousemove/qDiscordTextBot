#ifndef DISCORDBOTECHO_H
#define DISCORDBOTECHO_H

#include <QObject>
#include <QDebug>
#include "discordbotabstractstrategy.h"
#include "additional/json.hpp"
using namespace nlohmann;
class discordBotEcho : public discordBotAbstractStrategy
{
    Q_OBJECT
public:
    discordBotEcho(QString prefix = "",QObject *parent = nullptr);
public slots:
  virtual void processMessage(QString type,QString data) ;
};

#endif // DISCORDBOTECHO_H
