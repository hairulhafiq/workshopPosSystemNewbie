#include "booking2.h"
#include "ui_booking2.h"
#include "QMessageBox"

BOOKING2::BOOKING2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BOOKING2)
{
    ui->setupUi(this);
    QPixmap pix1("C:/Users/Hairul Hafiq/Documents/bengkel/Pic/Dark-Red-Abstract-Images-HD-Wallpaper-Desktop.jpg");
        ui->customerbackgroud->setPixmap(pix1);
    ui->setupUi(this);
    ui->comboBoxDay->addItem("1");
        ui->comboBoxDay->addItem("2");
        ui->comboBoxDay->addItem("3");
        ui->comboBoxDay->addItem("4");
        ui->comboBoxDay->addItem("5");
        ui->comboBoxDay->addItem("6");
        ui->comboBoxDay->addItem("7");
        ui->comboBoxDay->addItem("8");
        ui->comboBoxDay->addItem("9");
        ui->comboBoxDay->addItem("10");
        ui->comboBoxDay->addItem("11");
        ui->comboBoxDay->addItem("12");
        ui->comboBoxDay->addItem("13");
        ui->comboBoxDay->addItem("14");
        ui->comboBoxDay->addItem("15");
        ui->comboBoxDay->addItem("16");
        ui->comboBoxDay->addItem("17");
        ui->comboBoxDay->addItem("18");
        ui->comboBoxDay->addItem("19");
        ui->comboBoxDay->addItem("20");
        ui->comboBoxDay->addItem("21");
        ui->comboBoxDay->addItem("22");
        ui->comboBoxDay->addItem("23");
        ui->comboBoxDay->addItem("24");
        ui->comboBoxDay->addItem("25");
        ui->comboBoxDay->addItem("26");
        ui->comboBoxDay->addItem("27");
        ui->comboBoxDay->addItem("28");
        ui->comboBoxDay->addItem("29");
        ui->comboBoxDay->addItem("30");
        ui->comboBoxDay->addItem("31");

        ui->comboBoxMonth->addItem("1");
        ui->comboBoxMonth->addItem("2");
        ui->comboBoxMonth->addItem("3");
        ui->comboBoxMonth->addItem("4");
        ui->comboBoxMonth->addItem("5");
        ui->comboBoxMonth->addItem("6");
        ui->comboBoxMonth->addItem("7");
        ui->comboBoxMonth->addItem("8");
        ui->comboBoxMonth->addItem("9");
        ui->comboBoxMonth->addItem("10");
        ui->comboBoxMonth->addItem("11");
        ui->comboBoxMonth->addItem("12");

        ui->comboBoxYear->addItem("2019");
        ui->comboBoxYear->addItem("2020");
        ui->comboBoxYear->addItem("2021");
        ui->comboBoxYear->addItem("2022");
}

BOOKING2::~BOOKING2()
{
    delete ui;
}

void BOOKING2::on_pushButton__newform_clicked()
{
    ui->groupBox->setEnabled(true);
    int bigNo, smallNo;

    bigNo = 1000;
    smallNo = 0;

    int randomValue = qrand() % ((bigNo +1) - smallNo)+ smallNo;

    ui->lineEdit_booking_id->setText("B" + QString::number(randomValue));

    ui->lineEdit_customer_name->clear();
    ui->lineEditplate->clear();
    ui->tableView->clearSelection();
}

void BOOKING2::on_pushButtonbooking_clicked()
{
    QString ID,name,plate,day,month,year;
        LOGIN conn;

        ID = ui->lineEdit_booking_id->text();
        name = ui->lineEdit_customer_name->text();
        plate = ui->lineEditplate->text();
        day = ui->comboBoxDay->currentText();
        month= ui->comboBoxMonth->currentText();
        year = ui->comboBoxYear->currentText();

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
        }

        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into booking(id,name,Plate_Number,day,month,year) values('"+ID+"','"+name+"','"+plate+"','"+day+"','"+month+"','"+year+"')");
            if(qry.exec()){
                QSqlQueryModel *modal = new QSqlQueryModel();
                QSqlQuery *qry1 = new QSqlQuery(conn.csmsDB);
                qry1->prepare("select b.Plate_Number, b.day, b.month, b.year, s.day, s.month, s.year from booking b, sales s WHERE b.name = '"+name+"' and s.name = '"+name+"'");
                qry1->exec();
                modal->setQuery(*qry1);
                ui->tableView->setModel(modal);
                ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                conn.connClose();

                QMessageBox msgBox;
                msgBox.setText("Service date been set.");
                msgBox.exec();
            }
            else
                QMessageBox::critical(this,tr("Error"), qry.lastError().text());
}

void BOOKING2::on_pushButtoncancel_clicked()
{
    QString ID,name,plate;
        LOGIN conn;

        ID = ui->lineEdit_booking_id->text();
        name = ui->lineEdit_customer_name->text();
        plate = ui->lineEditplate->text();

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
        }

        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("Delete from booking where id = '"+ID+"' and name = '"+name+"'");
        if(qry.exec()){
            QSqlQueryModel *modal = new QSqlQueryModel();
            QSqlQuery *qry1 = new QSqlQuery(conn.csmsDB);
            qry1->prepare("select b.Plate_Number, b.day, b.month, b.year, s.day, s.month, s.year from booking b, sales s WHERE b.name = '"+name+"' and s.name = '"+name+"'");
            qry1->exec();
            modal->setQuery(*qry1);
            ui->tableView->setModel(modal);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

            conn.connClose();
            QMessageBox msgBox;
            msgBox.setText("Service date is canceled.");
            msgBox.exec();
        }
        else
            QMessageBox::critical(this,tr("Error"), qry.lastError().text());

}

void BOOKING2::on_pushButton_clicked()
{
    QString name,plate;
    LOGIN conn;


    name = ui->lineEdit_customer_name->text();
    plate = ui->lineEditplate->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open database";
    }

    conn.connOpen();

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *qry1 = new QSqlQuery(conn.csmsDB);
    qry1->prepare("select b.Plate_Number, b.day, b.month, b.year, s.day, s.month, s.year from booking b, sales s WHERE b.name = '"+name+"' and s.name = '"+name+"' and b.Plate_Number = '"+plate+"' and s.number_plate='"+plate+"'");
    qry1->exec();
    modal->setQuery(*qry1);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void BOOKING2::on_pushButton_logout_clicked()
{
    this->hide();
    LOGIN logout;
    logout.setModal(true);
    logout.exec();
}
