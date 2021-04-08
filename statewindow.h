#ifndef STATEWINDOW_H
#define STATEWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>

#include "statedata.h"

class TStateWindow : public QWidget
{
Q_OBJECT

    QLabel *l4;
    QLabel *l5;
    QLabel *l6;
    QLabel *state_washer;
    QLabel *state_worker;

public:
    TStateWindow(QWidget *parent = 0);
    ~TStateWindow();

    void setCurrentState(const TStateData);

protected:
    void closeEvent(QCloseEvent*);

signals:
    void closing();
};

#endif // STATEWINDOW_H
