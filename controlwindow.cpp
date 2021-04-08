#include "controlwindow.h"

TControlWindow::TControlWindow(bool m, QWidget *parent) :
    QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    setFixedSize(200,130);
    setWindowTitle("Управление");

    setEnabled(m);

    clearQueue_btn = new QPushButton("Очистить очередь",this);
    clearQueue_btn->setGeometry(10,10,180,20);
    connect(clearQueue_btn,SIGNAL(pressed()),this,SIGNAL(clear()));
    singleCar_btn = new QPushButton("Приезд машины",this);
    singleCar_btn->setGeometry(10,40,180,20);
    connect(singleCar_btn,SIGNAL(pressed()),this,SIGNAL(single()));
    autoSupply = new QPushButton("Приезд машины автомат.",this);
    autoSupply->setGeometry(10,70,180,20);
    connect(autoSupply,SIGNAL(pressed()),this,SLOT(switchMode()));
}

TControlWindow::~TControlWindow()
{
    delete autoSupply;
    delete singleCar_btn;
    delete clearQueue_btn;
}

void TControlWindow::closeEvent(QCloseEvent* event)
{
    emit closing();
    event->accept();
}

void TControlWindow::switchMode()
{
    bool m = !clearQueue_btn->isEnabled();
    clearQueue_btn->setEnabled(m);
    singleCar_btn->setEnabled(m);
    autoSupply->setText(m?"Автоматический режим":"Ручной режим");
    emit mode(!m);
}
