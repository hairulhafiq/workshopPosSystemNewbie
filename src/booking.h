#ifndef BOOKING_H
#define BOOKING_H

#include <QDialog>
#include "login.h"
#include <QSql>

namespace Ui {
class BOOKING;
}

class BOOKING : public QDialog
{
    Q_OBJECT

public:
    explicit BOOKING(QWidget *parent = nullptr);
    ~BOOKING();

private slots:
    void on_pushButtoncancel_clicked();
    void on_pushButton__newform_clicked();
    void on_pushButtonbooking_clicked();
    void on_pushButton_clicked();
    void on_pushButton_logout_clicked();

private:
    Ui::BOOKING *ui;
};

#endif // BOOKING_H
