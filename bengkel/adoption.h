#ifndef ADOPTION_H
#define ADOPTION_H

#include <QDialog>
#include "login.h"
#include "sale.h"
#include "register.h"
#include "stock.h"

namespace Ui {
class ADOPTION;
}

class ADOPTION : public QDialog
{
    Q_OBJECT

public:
    explicit ADOPTION(QWidget *parent = nullptr);
    ~ADOPTION();

private slots:
    void on_Stockbutton_clicked();
    void on_Registrationbutton_clicked();
    void on_Salesbutton_clicked();
    void on_logoutbutton_clicked();

private:
    Ui::ADOPTION *ui;
};

#endif // ADOPTION_H
