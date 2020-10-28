#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "sale.h"
#include <QDialog>

namespace Ui {
class ANALYSIS;
}

class ANALYSIS : public QDialog
{
    Q_OBJECT

public:
    explicit ANALYSIS(QWidget *parent = nullptr);
    ~ANALYSIS();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ANALYSIS *ui;
};

#endif // ANALYSIS_H
