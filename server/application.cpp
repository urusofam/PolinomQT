#include "application.h"
#include "polinom.h"
#include "common.h"
#include "number.h"
#include <iostream>
TApplication::TApplication(int argc, char *argv[])
    : QCoreApplication(argc,argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(pars, this);
    polinom = Tpolinom();
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    Tarray coefficients,roots;
    QString answer, s;
    int secondNumber , thirdNumber,fourthNumber;
    number  x, v;
    int pos1 = msg.indexOf(separator.toLatin1());
    int t = msg.left(pos1).toInt();
    QString strMsg = QString::fromLatin1(msg);
    QStringList list = strMsg.split(';');
    switch (t)
    {
        case PRINT_CLASSIC:
            coefficients = polinom.getCoefficients();
            for (int i = coefficients.getSize() - 1; i >= 0; i--) {
                if (coefficients[i].getIm() < 0) {
                    s.append("(").append(QString::number(coefficients[i].getRe())).append(QString::number(coefficients[i].getIm())).append("i)x^").append(QString::number(i));
                } else {
                    s.append("(").append(QString::number(coefficients[i].getRe())).append("+").append(QString::number(coefficients[i].getIm())).append("i)x^").append(QString::number(i));
                }
                if (i > 0) s.append(" + ");
            }

            answer << QString().setNum(PRINT_ANSWER) << s;
            break;
        case PRINT_CANONIC:
            roots = polinom.getRoots();
            if (polinom.getAn().getIm() < 0) s += "(" + QString::number(polinom.getAn().getRe()) + QString::number(polinom.getAn().getIm()) + "i)";
            else s += "(" + QString::number(polinom.getAn().getRe()) + "+" + QString::number(polinom.getAn().getIm()) + "i)";
            for (int i = 0; i < roots.getSize(); i++){
                if (roots[i].getIm() < 0) s += "(x - (" + QString::number(roots[i].getRe()) + QString::number(roots[i].getIm()) + "i))";
                else s += "(x - (" + QString::number(roots[i].getRe()) + "+" + QString::number(roots[i].getIm()) + "i))";
            }
            answer << QString().setNum(PRINT_ANSWER) << s;
            break;
        case ADD_ROOT:
            if (list.size() >= 2) {
                secondNumber = list.at(1).toDouble();
                thirdNumber = list.at(2).toDouble();
                polinom.getRoots().addElement(number(secondNumber, thirdNumber));
                polinom.calculateCoefficients();
            }
            break;
        case CHANGE_AN:
            if (list.size() >= 2) {
                secondNumber = list.at(1).toDouble();
                thirdNumber = list.at(2).toDouble();
                number newAn(secondNumber, thirdNumber);
                polinom = Tpolinom(newAn, polinom.getRoots());
            }
            break;
        case CHANGE_SIZE:
            if (list.size() >= 1) {
                secondNumber = list.at(1).toInt();
                polinom.getRoots().changeSize(secondNumber);
                polinom.calculateCoefficients();
            }
            break;
        case CHANGE_ONE_ROOT:
            if (list.size() >= 3) {
                secondNumber = list.at(1).toInt();
                thirdNumber = list.at(2).toDouble();
                fourthNumber = list.at(3).toDouble();
                number root(thirdNumber, fourthNumber);
                polinom.getRoots().changeElement(secondNumber, root);
                polinom.calculateCoefficients();
            }
            break;
        case VAL_REQUEST:
            if (list.size() >= 2) {
                secondNumber = list.at(1).toDouble();
                thirdNumber = list.at(2).toDouble();
                number x(secondNumber, thirdNumber);
                number result = polinom.evaluate(x);
                s.append((result.getIm() > 0) ? "Результат: " + QString::number(result.getRe()) + "+" + QString::number(result.getIm()) + "i"
                                              : "Результат: " + QString::number(result.getRe()) + QString::number(result.getIm()) + "i");
                answer << QString().setNum(PRINT_ANSWER) << s;
            }
            break;
        default:
            return;
    }
    comm->send(QByteArray().append(answer.toUtf8()));
}
