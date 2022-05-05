#ifndef DISCORDBOTABSTRACTSTRATEGY_H
#define DISCORDBOTABSTRACTSTRATEGY_H
//Абстрактный класс для стратегий обработки сообщений
#include <QObject>

class discordBotAbstractStrategy : public QObject
{
    Q_OBJECT
protected:

    QString _prefix;
    QString _id;
public:
    explicit discordBotAbstractStrategy(QString prefix = "",QObject *parent = nullptr);
signals:
    void sendTextMessage(QString data, QString relpy,QString channel);//отправка сообщения
public slots:
    virtual void processMessage(QString type,QString data) = 0;//todo расструктуировать сообщение из строки в структуру и перенести это на плечи Core а не стратегии
    void setId(QString id);
};

#endif // DISCORDBOTABSTRACTSTRATEGY_H
