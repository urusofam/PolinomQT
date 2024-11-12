#include "communicator.h"

TCommunicator::TCommunicator(TCommParams &parameters, QObject *parent)
    : QUdpSocket(parent), params(parameters)
{
    isSocketReady = bind(params.rHost, params.rPort,
                         QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (isSocketReady)
        connect(this, &QUdpSocket::readyRead, this, &TCommunicator::recieve);
}

bool TCommunicator::isReady()
{
    return isSocketReady;
}

void TCommunicator::send(QByteArray mes)
{
    if (isSocketReady)
    {
        writeDatagram(mes, params.sHost, params.sPort);
    }
}

void TCommunicator::recieve()
{
    while (hasPendingDatagrams())
    {
        QByteArray mes;
        mes.resize(static_cast<int>(pendingDatagramSize()));
        readDatagram(mes.data(), mes.size());
        emit recieved(mes);
    }
}
