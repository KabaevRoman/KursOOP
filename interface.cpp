#include "interface.h"
#include "paramwindow.h"
#include "statewindow.h"
#include "controlwindow.h"

#include <QDebug>

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(150,120);

    canControl = true;

    paramWindow   = nullptr;
    stateWindow   = nullptr;
    controlWindow = nullptr;

    paramWindow_btn = new QPushButton("Параметры",this);
    paramWindow_btn->setGeometry(15,10,120,30);
    connect(paramWindow_btn,SIGNAL(pressed()),this,SLOT(openParamWindow()));

    stateWindow_btn = new QPushButton("Состояние",this);
    stateWindow_btn->setGeometry(15,45,120,30);
    connect(stateWindow_btn,SIGNAL(pressed()),this,SLOT(openStateWindow()));

    controlWindow_btn = new QPushButton("Управление",this);
    controlWindow_btn->setGeometry(15,80,120,30);
    connect(controlWindow_btn,SIGNAL(pressed()),this,SLOT(openControlWindow()));
}

TInterface::~TInterface()
{
    delete controlWindow_btn;
    delete paramWindow_btn;
    delete stateWindow_btn;
}

void TInterface::setControlState(const bool s)
{
    canControl = s;
    qDebug()<<"interface state"<<canControl;
    if (paramWindow != nullptr)
        paramWindow->setEnable(s);
    if (controlWindow != nullptr)
        controlWindow->setEnable(s);
}

void TInterface::setCurrentParams(const TParamData pd)
{
    if (paramWindow != nullptr)
        paramWindow->setCurrentParams(pd);
}

void TInterface::setCurrentState(const TStateData sd)
{
    if (stateWindow != nullptr)
        stateWindow->setCurrentState(sd);
}

void TInterface::closeEvent(QCloseEvent* event)
{
    if (paramWindow != nullptr)
    {
        disconnect(paramWindow,SIGNAL(closing()),
                this,SLOT(paramWindowClosed()));
        paramWindow->close();
    }
    if (stateWindow != nullptr)
    {
        disconnect(stateWindow,SIGNAL(closing()),
                this,SLOT(stateWindowClosed()));
        stateWindow->close();
    }
    if (controlWindow != nullptr)
    {
        disconnect(controlWindow,SIGNAL(closing()),
                this,SLOT(controlWindowClosed()));
        controlWindow->close();
    }
    event->accept();
}

void TInterface::paramWindowClosed()
{
    disconnect(paramWindow,SIGNAL(closing()),
            this,SLOT(paramWindowClosed()));
    disconnect(paramWindow,SIGNAL(sendModelParams(TParamData)),
            this,SIGNAL(sendModelParams(TParamData)));
    disconnect(paramWindow,SIGNAL(restoreParams()),
            this,SLOT(restoreParams()));
    paramWindow = nullptr;
}

void TInterface::stateWindowClosed()
{
    disconnect(stateWindow,SIGNAL(closing()),
            this,SLOT(stateWindowClosed()));
    stateWindow = nullptr;
}

void TInterface::controlWindowClosed()
{
    disconnect(controlWindow,SIGNAL(closing()),
            this,SLOT(controlWindowClosed()));
    disconnect(controlWindow,SIGNAL(clear()),
            this,SIGNAL(clear()));
    disconnect(controlWindow,SIGNAL(single()),
            this,SIGNAL(single()));
    disconnect(controlWindow,SIGNAL(mode(bool)),
            this,SIGNAL(mode(bool)));
    controlWindow = nullptr;
}

void TInterface::restoreParams()
{
    emit paramRequest(PARAMREQUEST,nullptr);
}

void TInterface::openParamWindow()
{
    if (paramWindow == nullptr)
    {
        paramWindow = new TParamWindow(canControl);
        connect(paramWindow,SIGNAL(sendModelParams(TParamData)),
                this,SIGNAL(sendModelParams(TParamData)));
        connect(paramWindow,SIGNAL(closing()),
                this,SLOT(paramWindowClosed()));
        connect(paramWindow,SIGNAL(restoreParams()),
                this,SLOT(restoreParams()));
        paramWindow->show();
        emit paramRequest(PARAMREQUEST,nullptr);
    }
}

void TInterface::openStateWindow()
{
    if (stateWindow == nullptr)
    {
        stateWindow = new TStateWindow();
        connect(stateWindow,SIGNAL(closing()),
                this,SLOT(stateWindowClosed()));
        stateWindow->show();
        emit stateRequest(STATEREQUEST,nullptr);
    }
}

void TInterface::openControlWindow()
{
    if (controlWindow == nullptr)
    {
        controlWindow = new TControlWindow(canControl);
        connect(controlWindow,SIGNAL(closing()),
                this,SLOT(controlWindowClosed()));
        connect(controlWindow,SIGNAL(clear()),
                this,SIGNAL(clear()));
        connect(controlWindow,SIGNAL(single()),
                this,SIGNAL(single()));
        connect(controlWindow,SIGNAL(mode(bool)),
                this,SIGNAL(mode(bool)));
        controlWindow->show();
    }
}
