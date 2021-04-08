#include "statewindow.h"
#include "interface.h"

#include <QDebug>

TStateWindow::TStateWindow(QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    setFixedSize(240,240);
    setWindowTitle("Состояние");

    l4 = new QLabel("Состояние мойки:",this);
    l4->setGeometry(10,10,180,20);
    l5 = new QLabel("Состояния мастера:",this);
    l5->setGeometry(10,35,100,20);
    state_washer = new QLabel(this);
    state_washer->setGeometry(110,35,30,20);
    state_worker = new QLabel(this);
    state_worker->setGeometry(110,60,30,20);
}

TStateWindow::~TStateWindow()
{
    delete state_worker;
    delete state_washer;
    delete l5;
    delete l4;

}

void TStateWindow::setCurrentState(const TStateData s)
{
    qDebug()<<"TStateWindow::setCurrentState"<<s.washer<<s.worker;
    if(s.washer == true)
        state_washer->setText("мойка свободна");
    else
        state_washer->setText("Мойка занята");
    if(s.worker == true)
        state_worker->setText("Есть свободные мастера");
    else
        state_worker->setText("Нет свободных мастеров");
}

void TStateWindow::closeEvent(QCloseEvent* event)
{
    emit closing();
    event->accept();
}

