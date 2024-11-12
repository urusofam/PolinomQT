#include "application.h"

TApplication::TApplication(int argc, char *argv[])
    : QApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,QHostAddress("127.0.0.1"), 10000};

    com = new TCommunicator(pars, this);
    interface = new Tinterface();
    interface->show();

    connect(com,SIGNAL(recieved(QByteArray)),this,SLOT(fromCommunicator(QByteArray)));
    connect(interface,SIGNAL(request(QString)),this,SLOT(toCommunicator(QString)));

}

void TApplication::fromCommunicator(QByteArray mes)
{
    interface->answer(QString(mes));
}

void TApplication::toCommunicator(QString mes)
{
    com->send(QByteArray().append(mes.toUtf8()));

}
