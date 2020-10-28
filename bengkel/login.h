#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include "adoption.h"
#include "booking2.h"

namespace Ui { class LOGIN; }


class LOGIN : public QDialog
{
    Q_OBJECT

public:
    LOGIN(QWidget *parent = nullptr);
    ~LOGIN();

    QSqlDatabase csmsDB;
    void connClose()
        {
            csmsDB.close();
            csmsDB.removeDatabase(QSqlDatabase::defaultConnection);
        }

        bool connOpen()
        {
            csmsDB = QSqlDatabase::addDatabase("QSQLITE");
            csmsDB.setDatabaseName("D:/git/workshopPosSystemNewbie/bengkel/Car");


            if(!csmsDB.open()){
               qDebug()<<("Failed to connect to Database");
                return false;
            }
            else{
                qDebug()<<("Connected!!");
                return true;
            }
        }

private slots:
        void on_loginbutton_clicked();
        void showDate();
        void showTime();
private:
    Ui::LOGIN *ui;
};
#endif // LOGIN_H
