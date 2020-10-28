#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include <QPixmap>
#include <QTime>


LOGIN::LOGIN(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LOGIN)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Hairul Hafiq/Documents/Bengkel/Pic/BG-CarServiceSystem-02.jpg");
    ui->background->setPixmap(pix.scaled(631,411));

    if(!connOpen())
          ui->labelStatus_2->setText("Failed to connect to Database");

        else
          ui->labelStatus_2->setText("Database is connected!!");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL (timeout()), this, SLOT (showTime()));
    timer->start();

    showDate();
}

LOGIN::~LOGIN()
{
    delete ui;
}


void LOGIN::on_loginbutton_clicked()
{

    QString username, password;
    username = ui->lineEditUsername->text();
    password = ui->lineEditPassword->text();

    QSqlQuery qry1,qry2;
        qry1.prepare("select * from users where usrname ='"+username+"'and password ='"+password+"'and privilage = '1'");
        qry2.prepare("select * from users where usrname ='"+username+"'and password ='"+password+"'and privilage = '0'");

        if(qry1.exec())
        {
            int count = 0;
            while(qry1.next())
            {
                count++;
            }

            if(count ==1)
            {
               ui->labelStatus_2->setText("username and password is correct");
               connClose();
               this ->hide();
               ADOPTION options;
               options.setModal(true);
               options.exec();
            }
            else if(count >1)
                ui->labelStatus_2->setText("duplicate username and password");

            else if(count <1)
                ui->labelStatus_2->setText("username and password is not correct");

        }

        if(qry2.exec())
        {
            int count = 0;
            while(qry2.next())
            {
                count++;
            }

            if(count ==1)
            {
               ui->labelStatus_2->setText("username and password is correct");
               connClose();
               this ->hide();
               BOOKING2 options;
               options.setModal(true);
               options.exec();
            }
            else if(count >1)
                ui->labelStatus_2->setText ("duplicate username and password");

            else if(count <1)
                ui->labelStatus_2->setText ("username and password is not correct");
        }
        ui ->lineEditUsername ->clear();
        ui ->lineEditPassword->clear();
  }

  void LOGIN::showTime()
  {
      QTime time = QTime::currentTime();
      QString time_txt = time.toString("hh : mm : ss");
      if((time.second()%2)== 0)
      {
          time_txt[3]=' ';
          time_txt[8]=' ';
      }
      ui->label_time->setText("Time : " + time_txt);
  }

  void LOGIN::showDate()
  {
      QDate date = QDate::currentDate();
      QString date_txt = date.toString("d MMMM yyyy");
      ui->label_date->setText("Date : " + date_txt);
  }
