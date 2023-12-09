#ifndef USUARIOSPAGE_H
#define USUARIOSPAGE_H

#include <QWidget>
#include <QSerialPort>

#include "postgresqlconnector.h"

namespace Ui {
class UsuariosPage;
}

class UsuariosPage : public QWidget
{
    Q_OBJECT

public:
    explicit UsuariosPage(QWidget *parent = nullptr,
                          QSerialPort* Port = nullptr,
                          PostgreSQLConnector* PSQLConnector = nullptr);
    ~UsuariosPage();

private slots:
    void on_Commit_clicked();

private:
    Ui::UsuariosPage *ui;
    void initUsuariosPage( void );
    QSerialPort *Port;
    PostgreSQLConnector * PSQLConnector;
};

#endif // USUARIOSPAGE_H
