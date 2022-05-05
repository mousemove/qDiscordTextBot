#include "discordbotcore.h"

discordBotCore::discordBotCore(QString apiKey,unsigned int intents,QObject *parent) : QObject(parent), _apiKey(apiKey),_accessManager(new QNetworkAccessManager(this)),_intents(intents)
{
    discordHeader.push_back({"Authorization",QString("Bot "+_apiKey).toUtf8()});
    discordHeader.push_back({"Content-Type","application/json"});
    discordHeader.push_back({"User-Agent","DiscordBot"});


    hearthBeat.setInterval(hearthBeatInterval);
    connect(&hearthBeat,&QTimer::timeout,this,&discordBotCore::onHearthBeat);

}

discordBotCore::~discordBotCore()
{
    disconnect(&webSocket, &QWebSocket::connected, this, &discordBotCore::onConnected);
    disconnect(&webSocket, &QWebSocket::textMessageReceived, this, &discordBotCore::onTextMessageReceived);
    disconnect(&webSocket, &QWebSocket::disconnected, this, &discordBotCore::closed);

    hearthBeat.stop();

}

void discordBotCore::sendTextMessage(QString data, QString reply,QString channel)
{
    QString message = reply == "" ? "{\"content\": \" "+data+" \"}" : "{\"content\": \""+data+"\",\"message_reference\":{\"message_id\":"+reply+"}}" ;
    QString result = HTTPpost("https://discord.com/api/channels/"+channel+"/messages",message.toUtf8(),discordHeader);
}


void discordBotCore::webSocketConnect()
{
    try
    {
        json j = json::parse(HTTPget("https://discord.com/api/gateway/bot",discordHeader).toStdString());
        endpoint = QString::fromStdString(j["url"]);
    }
    catch (std::exception & e) {
        emit noConnection();
        return;
    }
    connect(&webSocket, &QWebSocket::connected, this, &discordBotCore::onConnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &discordBotCore::onTextMessageReceived);
    connect(&webSocket, &QWebSocket::disconnected, this, &discordBotCore::closed);
    webSocket.open(endpoint);




}

QString discordBotCore::HTTPget(QString url,const QVector<QPair<QByteArray, QByteArray> > & header)
{
    QNetworkRequest request(url);
    if(!header.isEmpty())
    {
        for(auto i: header)
        {
            request.setRawHeader(i.first,i.second);
        }
    }
    QEventLoop loop;
    auto k = _accessManager->get(request);
    connect(k,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    return k->readAll();
}

QString discordBotCore::HTTPpost(QString url,const QByteArray & data,const QVector<QPair<QByteArray,QByteArray>> & header)
{
    QNetworkRequest request(url);
    if(!header.isEmpty())
    {
        for(auto i: header)
        {
            request.setRawHeader(i.first,i.second);
        }
    }
    QEventLoop loop;
    auto k = _accessManager->post(request,data);
    connect(k,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();
    return k->readAll();
}

void discordBotCore::onConnected()
{
    qDebug() << "connect";
}

void discordBotCore::onHearthBeat()
{
    webSocket.sendTextMessage("{\"op\": 1,\"d\": 2  }");
}

void discordBotCore::onTextMessageReceived(QString message)
{
    static QString previous = "";
    if (message == previous) return;
    previous = message;

    json data = json::parse(message.toStdString());
    if(data["t"].is_null())
    {
        if (!data["d"].is_null()){//передаем токен с опкодом 2
            webSocket.sendTextMessage("{ \"op\": 2,\"d\": {\"token\": \""+_apiKey+"\", \"properties\": {\"$os\": \"linux\",\"$browser\": \"disco\",  \"$device\": \"disco\"},\"intents\":   "+QString().setNum(_intents)+"}}");
            hearthBeat.start();
        }
        else
        {
            //ответа на hearthbeat соощение не требуется(на данный момент)
        }
    }
    else if(data["t"] == "READY")
    {
        emit sendBotId(QString::fromStdString(data["d"]["user"]["id"]));
    }
    else //Все другие сообщения обрабатываются выбранной стратегией бота
    {

        //todo расструктуировать сообщение из строки в структуру и перенести это на плечи Core а не стратегии
        emit processMessage(QString::fromStdString(data["t"]),QString::fromStdString(data["d"].dump()));//без завязки на nlohmann json в стратегии обработчике

    }


}

void discordBotCore::closed()
{
    disconnect(&webSocket, &QWebSocket::connected, this, &discordBotCore::onConnected);
    disconnect(&webSocket, &QWebSocket::textMessageReceived, this, &discordBotCore::onTextMessageReceived);
    disconnect(&webSocket, &QWebSocket::disconnected, this, &discordBotCore::closed);
    qDebug() << "connection closed";
    hearthBeat.stop();
    QThread::sleep(2000);
    webSocketConnect();

}

