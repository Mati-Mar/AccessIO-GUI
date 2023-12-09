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
    EdificioPage(QWidget *parent = nullptr,
                 QSerialPort* Port = nullptr,
                 PostgreSQLConnector* PSQLConnector = nullptr);
    ~EdificioPage();
    bool isUartConnectedFlag;

private slots:
    void on_reloadPushButton_clicked();

private:
    Ui::EdificioPage *ui;
    QSerialPort *Port;
    PostgreSQLConnector * PSQLConnector;
    void initEdificioPage ();
    void usuariosInsideBuildingCounter( void );
};

#endif // EDIFICIOPAGE_H
