#ifndef CUSOPTION_H
#define CUSOPTION_H

#include <QDialog>

namespace Ui {
class CUSOPTION;
}

class CUSOPTION : public QDialog
{
    Q_OBJECT

public:
    explicit CUSOPTION(QWidget *parent = nullptr);
    ~CUSOPTION();

private:
    Ui::CUSOPTION *ui;
};

#endif // CUSOPTION_H
