#ifndef BOOKING2_H
#define BOOKING2_H

#include <QDialog>
#include "login.h"
#include <QSql>

namespace Ui {
class BOOKING2;
}

class BOOKING2 : public QDialog
{
    Q_OBJECT

public:
    explicit BOOKING2(QWidget *parent = nullptr);
    ~BOOKING2();

private slots:
    void on_pushButton__newform_clicked();
    void on_pushButtonbooking_clicked();
    void on_pushButtoncancel_clicked();
    void on_pushButton_clicked();
    void on_pushButton_logout_clicked();

private:
    Ui::BOOKING2 *ui;
};

#endif // BOOKING2_H
