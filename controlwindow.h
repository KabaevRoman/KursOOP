#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>

class TControlWindow : public QWidget
{
Q_OBJECT

    QPushButton *clearQueue_btn;
    QPushButton *singleCar_btn;
    QPushButton *autoSupply;

public:
    TControlWindow(bool,QWidget *parent = 0);
    ~TControlWindow();

    inline void setEnable(const bool m) { setEnabled(m); }

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void switchMode();

signals:
    void closing();
    void clear();
    void single();
    void mode(bool);
};

#endif // CONTROLWINDOW_H
