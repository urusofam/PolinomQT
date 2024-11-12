#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "polinom.h"

#include "communicator.h"

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;
    Tpolinom polinom;
public:

    TApplication(int, char**);

signals:

public slots:

    void recieve(QByteArray);

};

#endif // APPLICATION_H
