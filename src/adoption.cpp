#include "adoption.h"
#include "ui_adoption.h"

ADOPTION::ADOPTION(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADOPTION)
{
    ui->setupUi(this);
    QPixmap pix("D:/git/workshopPosSystemNewbie/src/Pic/mac_wallpaper.jpg");
    ui->labelbg->setPixmap(pix.scaled(311,411));
}

ADOPTION::~ADOPTION()
{
    delete ui;
}
void ADOPTION::on_Stockbutton_clicked()
{
    this->hide();
    STOCK options;
    options.setModal(true);
    options.exec();
}

void ADOPTION::on_Registrationbutton_clicked()
{
    this->hide();
    REGISTER options;
    options.setModal(true);
    options.exec();
}

void ADOPTION::on_Salesbutton_clicked()
{
    this->hide();
    SALE options;
    options.setModal(true);
    options.exec();
}

void ADOPTION::on_logoutbutton_clicked()
{
    this->hide();
    LOGIN back;
    back.setModal(true);
    back.exec();
}
