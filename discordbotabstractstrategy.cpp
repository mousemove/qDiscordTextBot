#include "discordbotabstractstrategy.h"

discordBotAbstractStrategy::discordBotAbstractStrategy(QString prefix, QObject *parent) : QObject(parent),_prefix(prefix)
{

}

void discordBotAbstractStrategy::setId(QString id)
{
 _id = id;
}
