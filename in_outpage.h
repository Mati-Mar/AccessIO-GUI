#ifndef IN_OUTPAGE_H
#define IN_OUTPAGE_H

#include <QWidget>
#include <QSerialPort>
#include <QSqlTableModel>
#include <QStringList>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "postgresqlconnector.h"

namespace Ui {
class In_OutPage;
}

class In_OutPage : public QWidget
{
    Q_OBJECT

public:
    In_OutPage(QWidget *parent = nullptr,
                QSerialPort* Port = nullptr,
                PostgreSQLConnector* PSQLConnector = nullptr);
    ~In_OutPage();

private slots:
    void on_nombreLineEdit_returnPressed();
    void on_apellidoLineEdit_returnPressed();
    void on_lupaPushButton_clicked();

private:
    Ui::In_OutPage *ui;
    void initIn_OutPage( void );
    QSerialPort *Port;
    PostgreSQLConnector * PSQLConnector;

    void formatTablaUsuarios ( QString nombre, QString apellido );
    QString ubicacionUsuarioAMostrar (QString &ubicacion);
};

#endif // IN_OUTPAGE_H
