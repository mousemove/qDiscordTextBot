#include "discordbotecho.h"

discordBotEcho::discordBotEcho(QString prefix,QObject *parent):discordBotAbstractStrategy(prefix,parent)
{

}

void discordBotEcho::processMessage(QString type, QString data)
{
    //Это реализация простого эхо бота. Значит нам нужно отслеживать лишь события MESSAGE_CREATE отправляя собеседнику что хотим отправить
    json j = json::parse(data.toStdString());
    if(type == "MESSAGE_CREATE")
    {
        QString author =  QString::fromStdString(j["author"]["id"]);

        if(author != _id){//проверяем что пришедшее в текстовый канал сообщение не от бота

            QString message = QString::fromStdString(j["content"]);//сообщение пользователя
            QString id = QString::fromStdString(j["id"]);
            QString channel_id = QString::fromStdString(j["channel_id"]);
            emit sendTextMessage(message,id,channel_id);

        }

    }


}
