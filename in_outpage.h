#ifndef IN_OUTPAGE_H
#define IN_OUTPAGE_H

#include <QWidget>

namespace Ui {
class In_OutPage;
}

class In_OutPage : public QWidget
{
    Q_OBJECT

public:
    explicit In_OutPage(QWidget *parent = nullptr);
    ~In_OutPage();

private:
    Ui::In_OutPage *ui;
};

#endif // IN_OUTPAGE_H
