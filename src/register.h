#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include"login.h"

namespace Ui {
class REGISTER;
}

class REGISTER : public QDialog
{
    Q_OBJECT

public:
    explicit REGISTER(QWidget *parent = nullptr);
    ~REGISTER();

private slots:
    void on_pushButtonAdd_2_clicked();

    void on_pushButtonUpdate_2_clicked();

    void on_pushButtonDelete_2_clicked();

    void on_pushButton_view_2_clicked();

    void on_searchButton_2_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButtonBack_clicked();

private:
    Ui::REGISTER *ui;
};

#endif // REGISTER_H
