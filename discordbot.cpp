#include "discordbot.h"

discordBot::discordBot(QString apiKey, discordBotAbstractStrategy *strategy, QObject *parent) : QObject(parent),_apiKey(apiKey),_strategy(strategy),_core(new discordBotCore(apiKey))
{
    connect(_core, &discordBotCore::noConnection,this,&discordBot::noConnection);

    connect(_core,&discordBotCore::processMessage,_strategy,&discordBotAbstractStrategy::processMessage);
    connect(_core,&discordBotCore::sendBotId,_strategy,&discordBotAbstractStrategy::setId);
    connect(_strategy,&discordBotAbstractStrategy::sendTextMessage,_core,&discordBotCore::sendTextMessage);
    _core->webSocketConnect();

}

void discordBot::noConnection()
{
    exit(EXIT_FAILURE);
}
