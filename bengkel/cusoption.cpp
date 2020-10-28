#include "cusoption.h"
#include "ui_cusoption.h"

CUSOPTION::CUSOPTION(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CUSOPTION)
{
    ui->setupUi(this);
}

CUSOPTION::~CUSOPTION()
{
    delete ui;
}
