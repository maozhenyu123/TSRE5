#ifndef SIGNALWINDOW_H
#define	SIGNALWINDOW_H

#include <QtWidgets>

class SignalObj;

class SignalWindow : public QWidget {
    Q_OBJECT

public:
    SignalWindow();
    virtual ~SignalWindow();
    void showObj(SignalObj* obj);
    
public slots:
    void exitNow();
    void chSubEnabled(int i);
    
private:
    static const int maxSubObj = 30;
    QLineEdit name;
    QLineEdit description;
    QCheckBox chSub[maxSubObj];
    QPushButton bSub[maxSubObj];
    QLineEdit dSub[maxSubObj];
    QGridLayout vSub[maxSubObj];
    QWidget wSub[maxSubObj];
    QSignalMapper signalsChSect;
    SignalObj* sobj;
};

#endif	/* SIGNALWINDOW_H */

