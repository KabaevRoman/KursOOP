#include "paramwindow.h"

#include <QDebug>

TParamWindow::TParamWindow(bool m, QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    setWindowTitle("Параметры");
    setFixedSize(240,240);

    setEnabled(m);

    l1 = new QLabel("Количество мастеров:",this);
    l1->setGeometry(10,10,180,20);
    NumOfWorkers = new QSpinBox(this);
    NumOfWorkers->setRange(2,10);
    NumOfWorkers->setGeometry(180,10,50,20);
    l2 = new QLabel("Вероятность ожидания:",this);
    l2->setGeometry(10,35,180,20);
    probability = new QDoubleSpinBox(this);
    probability->setSingleStep(0.1);
    probability->setRange(0,1);
    probability->setGeometry(180,35,50,20);

    accept_btn = new QPushButton("Применить",this);
    accept_btn->setGeometry(10,90,85,30);
    connect(accept_btn,SIGNAL(pressed()),this,SLOT(setModelParam()));
    cancel_btn = new QPushButton("Отменить",this);
    cancel_btn->setGeometry(105,90,85,30);
    connect(cancel_btn,SIGNAL(pressed()),this,SIGNAL(restoreParams()));
}

TParamWindow::~TParamWindow()
{
    delete l1;
    delete l2;
    delete cancel_btn;
    delete accept_btn;
    delete probability;
    delete NumOfWorkers;

}

void TParamWindow::closeEvent(QCloseEvent* event)
{
    emit closing();
    event->accept();
}

void TParamWindow::setModelParam()
{
    TParamData pd;
    pd.NumOfWorkers = NumOfWorkers->value();
    pd.probability = probability->value();
    emit sendModelParams(pd);
}

void TParamWindow::setCurrentParams(const TParamData pd)
{
    qDebug()<<"TParamWindow::setCurrentParams";
    NumOfWorkers->setValue(pd.NumOfWorkers);
    probability->setValue(pd.probability);
}
