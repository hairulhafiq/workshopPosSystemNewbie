#ifndef SALE_H
#define SALE_H

#include <QDialog>
#include"adoption.h"
#include "login.h"
#include "analysis.h"
#include <QDialog>

namespace Ui {
class SALE;
}

class SALE : public QDialog
{
    Q_OBJECT

public:
    explicit SALE(QWidget *parent = nullptr);
    ~SALE();

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonAnalysis_clicked();
    void on_pushButtonNextItem_clicked();
    void on_pushButtonCancel_clicked();
    void on_TotalButton_clicked();
    void on_listView_activated(const QModelIndex &index);
    void on_pushButtonBack_clicked();

private:
    Ui::SALE *ui;
};

#endif // SALE_H
