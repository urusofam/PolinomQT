#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "common.h"

Tinterface::Tinterface(QWidget *parent) : QWidget(parent) {
    anInputRe = new QLineEdit(this);
    anInputIm = new QLineEdit(this);
    rootsInputRe = new QLineEdit(this);
    rootsInputIm = new QLineEdit(this);
    xInputRe = new QLineEdit(this);
    xInputIm = new QLineEdit(this);
    inputSize = new QLineEdit(this);
    indexInput = new QLineEdit(this);

    resultLabel = new QLabel("Результат:", this);

    addButton = new QPushButton("Добавить корень", this);
    changeButton = new QPushButton("Изменить коэффициент", this);
    evaluateButton = new QPushButton("Вычислить значение", this);
    resizeButton = new QPushButton("Изменить размер корней", this);
    displayForm1Button = new QPushButton("Вывести полином в 1 форме", this);
    displayForm2Button = new QPushButton("Вывести полином во 2 форме", this);
    indexButton = new QPushButton("Изменить корень по номеру", this);

    connect(addButton, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(changeButton, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(evaluateButton, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(resizeButton, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(displayForm1Button, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(displayForm2Button, &QPushButton::clicked, this, &Tinterface::formRequest);
    connect(indexButton, &QPushButton::clicked, this, &Tinterface::formRequest);



    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Коэффициент an:", this));
    QHBoxLayout *anLayout = new QHBoxLayout();
    anLayout->addWidget(anInputRe);
    anLayout->addWidget(anInputIm);
    anLayout->addWidget(new QLabel("i", this));
    mainLayout->addLayout(anLayout);
    mainLayout->addWidget(new QLabel("Номер корня:", this));
    mainLayout->addWidget(indexInput);
    mainLayout->addWidget(new QLabel("Корень:", this));
    QHBoxLayout *rootsLayout = new QHBoxLayout();
    rootsLayout->addWidget(rootsInputRe);
    rootsLayout->addWidget(rootsInputIm);
    rootsLayout->addWidget(new QLabel("i", this));
    mainLayout->addLayout(rootsLayout);
    mainLayout->addWidget(new QLabel("Размер массива корней:", this));
    mainLayout->addWidget(inputSize);
    mainLayout->addWidget(new QLabel("x:", this));
    QHBoxLayout *xLayout = new QHBoxLayout();
    xLayout->addWidget(xInputRe);
    xLayout->addWidget(xInputIm);
    xLayout->addWidget(new QLabel("i", this));
    mainLayout->addLayout(xLayout);
    mainLayout->addWidget(resultLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(changeButton);
    buttonLayout->addWidget(indexButton);
    buttonLayout->addWidget(evaluateButton);
    buttonLayout->addWidget(resizeButton);
    buttonLayout->addWidget(displayForm1Button);
    buttonLayout->addWidget(displayForm2Button);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

Tinterface::~Tinterface() {}

void Tinterface::formRequest()
{
    QString mes ="";
    QPushButton *btn = (QPushButton*)sender();
    if (btn == addButton){
        mes << QString().setNum(ADD_ROOT);
        mes << rootsInputRe->text() << rootsInputIm->text();
    }
    if (btn == changeButton){
        mes << QString().setNum(CHANGE_AN);
        mes << anInputRe->text() << anInputIm->text();
    }
    if (btn == evaluateButton){
        mes << QString().setNum(VAL_REQUEST);
        mes << xInputRe->text() << xInputIm->text();
    }
    if (btn == resizeButton){
        mes << QString().setNum(CHANGE_SIZE);
        mes << inputSize->text();
    }
    if (btn == displayForm1Button){
        mes << QString().setNum(PRINT_CLASSIC);
    }
    if (btn == displayForm2Button){
        mes << QString().setNum(PRINT_CANONIC);
    }
    if (btn == indexButton){
        mes << QString().setNum(CHANGE_ONE_ROOT);
        mes << indexInput->text() << rootsInputRe->text() << rootsInputIm->text();
    }
    emit request(mes);
}

void Tinterface::answer(QString msg)
{
    QString text;
    int p = msg.indexOf(separator);
    int t = msg.left(p).toInt();
    msg = msg.mid(p+1,msg.length()-p-2);
    if (t == PRINT_ANSWER){
        text += msg;
        resultLabel->setText(text);
    }
}
