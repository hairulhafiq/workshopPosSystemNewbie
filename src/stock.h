#ifndef STOCK_H
#define STOCK_H

#include <QDialog>
#include"login.h"
#include"adoption.h"

namespace Ui {
class STOCK;
}

class STOCK : public QDialog
{
    Q_OBJECT

public:
    explicit STOCK(QWidget *parent = nullptr);
    ~STOCK();

private slots:
    void on_pushButtonAdd_2_clicked();

    void on_pushButtonUpdate_2_clicked();

    void on_pushButton_view_2_clicked();

    void on_searchButton_2_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButtonBack_clicked();

private:
    Ui::STOCK *ui;
};

#endif // STOCK_H
