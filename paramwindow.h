#ifndef PARAMWINDOW_H
#define PARAMWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "paramdata.h"

class TParamWindow : public QWidget
{
Q_OBJECT

    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QSpinBox *NumOfWorkers;
    QDoubleSpinBox *probability;
    QPushButton *accept_btn;
    QPushButton *cancel_btn;

public:
    TParamWindow(bool,QWidget *parent = 0);
    ~TParamWindow();

    inline void setEnable(const bool m) { setEnabled(m); }
    void setCurrentParams(const TParamData);

protected:
    void closeEvent(QCloseEvent*);

protected slots:
    void setModelParam();

signals:
    void closing();
    void sendModelParams(TParamData);
    void restoreParams();
};

#endif // PARAMWINDOW_H
