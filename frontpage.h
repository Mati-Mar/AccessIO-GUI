#ifndef FRONTPAGE_H
#define FRONTPAGE_H

#include <QMainWindow>

namespace Ui {
class FrontPage;
}

class FrontPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontPage(QWidget *parent = nullptr);
    //FrontPage(QWidget *parent = nullptr, QSerialPort port);
    explicit FrontPage(QWidget *parent = nullptr, QString portname = "PORDEFECTO");
    ~FrontPage();

private slots:
    void on_edificioPushButton_clicked();

private:
    Ui::FrontPage *ui;
    void initFrontpage();
};

#endif // FRONTPAGE_H
