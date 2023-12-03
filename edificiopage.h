#ifndef EDIFICIOPAGE_H
#define EDIFICIOPAGE_H

#include <QWidget>
#include <QString>
#include <QSerialPort>

#include "postgresqlconnector.h"

namespace Ui {
class EdificioPage;
}

class EdificioPage : public QWidget
{
    Q_OBJECT

public:
    explicit EdificioPage(QWidget *parent = nullptr);
    EdificioPage(QWidget *parent = nullptr, QSerialPort* Port = nullptr);
    ~EdificioPage();
    bool isUartConnectedFlag;

private:
    Ui::EdificioPage *ui;
    QSerialPort *Port;
    void initEdificioPage ();
};

#endif // EDIFICIOPAGE_H
