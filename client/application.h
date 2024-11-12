#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>

#include "interface.h"
#include "communicator.h"

class TApplication : public QApplication
{
    Q_OBJECT
    TCommunicator *com;
    Tinterface *interface;
public:
    TApplication(int, char**);
public slots:
    void fromCommunicator(QByteArray);
    void toCommunicator(QString);
};

#endif
