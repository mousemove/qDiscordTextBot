#include <QCoreApplication>
#include "discordbot.h"
#include "discordbotecho.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    discordBot d("===YOU TOKEN HERE===========",new discordBotEcho);
    return a.exec();
}
