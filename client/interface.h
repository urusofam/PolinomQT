#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <Qlabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class Tinterface : public QWidget {
    Q_OBJECT

    QLineEdit *anInputRe;
    QLineEdit *indexInput;
    QLineEdit *anInputIm;
    QLineEdit *rootsInputRe;
    QLineEdit *rootsInputIm;
    QLineEdit *xInputRe;
    QLineEdit *xInputIm;
    QLineEdit *inputSize;
    QLabel *resultLabel;

    QPushButton *addButton;
    QPushButton *changeButton;
    QPushButton *evaluateButton;
    QPushButton *resizeButton;
    QPushButton *indexButton;
    QPushButton *displayForm1Button;
    QPushButton *displayForm2Button;
public slots:
    void answer(QString);
private slots:
    void formRequest();
signals:
    void request(QString);
public:
    Tinterface(QWidget *parent = nullptr);
    ~Tinterface();
};
#endif
