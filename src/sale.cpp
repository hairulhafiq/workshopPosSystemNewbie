#include "sale.h"
#include "ui_sale.h"
#include <QTime>
#include <QDate>
#include<cstdlib>
#include<QMessageBox>

SALE::SALE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SALE)
{
    ui->setupUi(this);

    QPixmap pix("D:/git/workshopPosSystemNewbie/Pic/mac_wallpaper.jpg");
    ui->labelbg->setPixmap(pix.scaled(960,632));

    QTime masa = QTime::currentTime();
    qsrand((uint)masa.msec());

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


}

SALE::~SALE()
{
    delete ui;
}

void SALE::on_pushButtonNew_clicked()
{
    LOGIN conn;
       ui->groupBoxSales->setEnabled(true);
       ui->lineEditName->setEnabled(true);
       ui->lineEditPlate->setEnabled(true);
       ui->totalPrice->setEnabled(false);
       ui->lineEditItem->setEnabled(false);

       QSqlQueryModel * modal = new QSqlQueryModel();
       conn.connOpen();
       QSqlQuery * qry = new QSqlQuery(conn.csmsDB);

       qry->prepare("select Name from stocks where Quantity != 0");
       qry->exec();
       modal->setQuery(*qry);
       ui->listView->setModel(modal);

       int bigNo, smallNo;

       bigNo = 1000;
       smallNo = 0;

       int randomValue = qrand() % ((bigNo +1) - smallNo)+ smallNo;

       ui->receiptNo->setText("STS" + QString::number(randomValue));

       ui->lineEditName->clear();
       ui->lineEditItem->clear();
       ui->lineEditPlate->clear();
       ui->quantity1->clear();
       ui->tableView->clearMask();
       conn.connClose();
}

void SALE::on_pushButtonAnalysis_clicked()
{
    this->hide();
    ANALYSIS summary;
    summary.setModal(true);
    summary.exec();
}


void SALE::on_pushButtonNextItem_clicked()
{
    LOGIN conn;


        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
            return;
        }

        QString name,plate,receiptNo,qtySold,day,month,year,itemSold,totalPriceString;
        double price= 0, totalPrice=0;

        name = ui->lineEditName->text();
        plate = ui->lineEditPlate->text();
        day = ui->comboBoxDay->currentText();
        month= ui->comboBoxMonth->currentText();
        year = ui->comboBoxYear->currentText();
        itemSold= ui->lineEditItem->text();
        qtySold = ui->quantity1->text();
        receiptNo = ui -> receiptNo ->text();

        QSqlQuery qry,qry1,q,qry2,qry3,qry5;
        int hai;



        qry.exec("select Price from stocks where Name = '"+itemSold+"'");

        if(qry.next())
            price= qry.value(0).toDouble();

        totalPrice= price*qtySold.toInt();

        totalPriceString = QString::number(totalPrice);

        qry1.prepare("INSERT INTO sales (receipt_no,name,number_plate,item,quantity,day,month,year,total_price) values ('"+receiptNo+"','"+name+"','"+plate+"','"+itemSold+"','"+qtySold+"','"+day+"','"+month+"','"+year+"','"+totalPriceString+"')");
        q.exec("update stocks set Quantity = (Quantity - '"+qtySold+"') where Name= '"+itemSold+"' ");
        qry1.exec();

        qry3.exec("SELECT Quantity from stocks where Name = '"+itemSold+"'");
        if (qry3.next()){
            hai = qry3.value(0).toInt();
            if(hai == 0)
            {
               QMessageBox msgBox;
               msgBox.setText("The Stock is Empty now. You should restock.");
               msgBox.exec();
               ui->listView->clearMask();
               QSqlQueryModel * modal = new QSqlQueryModel();
               QSqlQuery * qry5 = new QSqlQuery(conn.csmsDB);
               qry5->prepare("select Name from stocks where Quantity != 0");
               qry5->exec();
               modal->setQuery(*qry5);
               ui->listView->setModel(modal);
            }
        }

        QSqlQueryModel *modal = new QSqlQueryModel();

        QSqlQuery *qry4 = new QSqlQuery(conn.csmsDB);
        qry4->prepare("select item, quantity, total_price from sales where receipt_no = '"+receiptNo+"'");
        qry4->exec();
        modal->setQuery(*qry4);
        ui->tableView->setModel(modal);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui->lineEditItem->clear();
        ui->quantity1->clear();


        conn.close();
}

void SALE::on_pushButtonCancel_clicked()
{
    QString receiptNo,item,qtySold,day,month,year;
        LOGIN conn;

        receiptNo = ui -> receiptNo ->text();
        item = ui->lineEditItem->text();
        qtySold = ui->quantity1->text();
        day = ui->comboBoxDay->currentText();
        month= ui->comboBoxMonth->currentText();
        year = ui->comboBoxYear->currentText();

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
            return;
        }
        conn.connOpen();
        QSqlQuery qry,qry1,qry2;
        qry.prepare("SELECT * from sales where receipt_no = '"+receiptNo+"' and item= '"+item+"' and quantity = '"+qtySold+"' and day ='"+day+"' and month='"+month+"' and year='"+year+"'");

        QMessageBox::StandardButton confirmDelete;
        if(qry.exec())
        {
            while(qry.next())
            {
                confirmDelete = QMessageBox::question(this, "Delete item sold","Are you sure you want to delete Item = " + item);
                if(confirmDelete==QMessageBox::Yes)
                {
                    qry1.exec("Delete from sales where receipt_no = '"+receiptNo+"' and item= '"+item+"' and day ='"+day+"' and month='"+month+"' and year='"+year+"' ");
                    qry2.exec("update stocks set Quantity = (Quantity  + '"+qtySold+"') where Name= '"+item+"' ");
                }
            }
        }

        QSqlQueryModel *modal = new QSqlQueryModel();

        QSqlQuery *qry4 = new QSqlQuery(conn.csmsDB);
        qry4->prepare("select item, quantity, total_price from sales where receipt_no = '"+receiptNo+"'");
        qry4->exec();
        modal->setQuery(*qry4);
        ui->tableView->setModel(modal);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        ui->lineEditItem->clear();
        ui->quantity1->clear();
}


void SALE::on_TotalButton_clicked()
{
    LOGIN conn;
        QString receiptNo,day,month,year;
        receiptNo= ui -> receiptNo ->text();
        day = ui->comboBoxDay->currentText();
        month= ui->comboBoxMonth->currentText();
        year = ui->comboBoxYear->currentText();
        conn.connOpen();

        QSqlQuery qry2;
        double total = 0;
        qry2.exec("select SUM(total_price) from sales where receipt_no = '"+receiptNo+"' and day='"+day+"' and month='"+month+"' and year ='"+year+"'");

        if(qry2.next())
            total += qry2.value(0).toDouble();

        ui->totalPrice->setText("RM " + QString::number(total));

        conn.connClose();
}


void SALE::on_listView_activated(const QModelIndex &index)
{
    QString itemSold;
    QString value = ui->listView->model()->data(index).toString();
        LOGIN conn;

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
            return;
        }
        conn.connOpen();
        QSqlQuery qry1,qry3;
        qry1.prepare("select Name from stocks where Name = '"+value+"'");


        if(qry1.exec())
        {

            if(qry1.next())
            {
                ui->lineEditItem->setText(qry1.value(0).toString());

            }


            conn.connClose();

        }
        else
            QMessageBox::critical(this,tr("Error"),qry1.lastError().text());


}

void SALE::on_pushButtonBack_clicked()
{
    this->hide();
    ADOPTION main;
    main.setModal(true);
    main.exec();
}
