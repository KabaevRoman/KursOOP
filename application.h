#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>
#include "tcpclient.h"
#include "interface.h"
#include "generator.h"

class TApplication : public QApplication
{
    Q_OBJECT

    TcpClient  *client;
    TInterface  *interface;
    TEventGenerator* generator;

public:
    TApplication(int,char**);
    ~TApplication();
public slots:
    void toModel(EEvents,void*);
    void fromModel(QByteArray);
    void sendModelParams(TParamData);
    void clear();
    void single();
    void mode(bool);
};

#endif // APPLICATION_H
