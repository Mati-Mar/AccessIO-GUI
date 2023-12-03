#ifndef USUARIOSPAGE_H
#define USUARIOSPAGE_H

#include <QWidget>

namespace Ui {
class UsuariosPage;
}

class UsuariosPage : public QWidget
{
    Q_OBJECT

public:
    explicit UsuariosPage(QWidget *parent = nullptr);
    ~UsuariosPage();

private:
    Ui::UsuariosPage *ui;
};

#endif // USUARIOSPAGE_H
