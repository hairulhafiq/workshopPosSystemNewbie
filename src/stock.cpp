#include "stock.h"
#include "ui_stock.h"
#include <QMessageBox>

STOCK::STOCK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::STOCK)
{
    ui->setupUi(this);

    QPixmap pix("D:/git/workshopPosSystemNewbie/Pic/mac_wallpaper.jpg");
    ui->labelBackground->setPixmap(pix.scaled(631,411));

        ui->comboBoxDay_2->addItem("1");
        ui->comboBoxDay_2->addItem("2");
        ui->comboBoxDay_2->addItem("3");
        ui->comboBoxDay_2->addItem("4");
        ui->comboBoxDay_2->addItem("5");
        ui->comboBoxDay_2->addItem("6");
        ui->comboBoxDay_2->addItem("7");
        ui->comboBoxDay_2->addItem("8");
        ui->comboBoxDay_2->addItem("9");
        ui->comboBoxDay_2->addItem("10");
        ui->comboBoxDay_2->addItem("11");
        ui->comboBoxDay_2->addItem("12");
        ui->comboBoxDay_2->addItem("13");
        ui->comboBoxDay_2->addItem("14");
        ui->comboBoxDay_2->addItem("15");
        ui->comboBoxDay_2->addItem("16");
        ui->comboBoxDay_2->addItem("17");
        ui->comboBoxDay_2->addItem("18");
        ui->comboBoxDay_2->addItem("19");
        ui->comboBoxDay_2->addItem("20");
        ui->comboBoxDay_2->addItem("21");
        ui->comboBoxDay_2->addItem("22");
        ui->comboBoxDay_2->addItem("23");
        ui->comboBoxDay_2->addItem("24");
        ui->comboBoxDay_2->addItem("25");
        ui->comboBoxDay_2->addItem("26");
        ui->comboBoxDay_2->addItem("27");
        ui->comboBoxDay_2->addItem("28");
        ui->comboBoxDay_2->addItem("29");
        ui->comboBoxDay_2->addItem("30");
        ui->comboBoxDay_2->addItem("31");

        ui->comboBoxMonth_2->addItem("1");
        ui->comboBoxMonth_2->addItem("2");
        ui->comboBoxMonth_2->addItem("3");
        ui->comboBoxMonth_2->addItem("4");
        ui->comboBoxMonth_2->addItem("5");
        ui->comboBoxMonth_2->addItem("6");
        ui->comboBoxMonth_2->addItem("7");
        ui->comboBoxMonth_2->addItem("8");
        ui->comboBoxMonth_2->addItem("9");
        ui->comboBoxMonth_2->addItem("10");
        ui->comboBoxMonth_2->addItem("11");
        ui->comboBoxMonth_2->addItem("12");

        ui->comboBoxYear_2->addItem("2019");
        ui->comboBoxYear_2->addItem("2020");
        ui->comboBoxYear_2->addItem("2021");
}

STOCK::~STOCK()
{
    delete ui;
}

void STOCK::on_pushButtonAdd_2_clicked()
{
    QString stkname, stkquantity, stkprice, stksupp,day,month,year;
        LOGIN conn;
        stkname = ui ->stockName_2 ->text();
        stkquantity = ui ->stockQuantity_2->text();
        stkprice = ui -> stockPrice_2->text();
        stksupp = ui -> Supplier_2->text();
        day = ui->comboBoxDay_2->currentText();
        month= ui->comboBoxMonth_2->currentText();
        year = ui->comboBoxYear_2->currentText();

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
        }

        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into stocks (Name,Quantity,Price,Supplier,day,month,year) values('"+stkname+"','"+stkquantity+"','"+stkprice+"','"+stksupp+"','"+day+"','"+month+"','"+year+"')");

        if(qry.exec()){
            conn.connClose();
            QMessageBox msgBox;
            msgBox.setText("The stock has been successfully added.");
            msgBox.exec();
        }
        else
            QMessageBox::critical(this,tr("Error"), qry.lastError().text());

        ui->stockName_2->clear();
        ui->stockPrice_2->clear();
        ui->stockQuantity_2->clear();
        ui->Supplier_2->clear();
}

void STOCK::on_pushButtonUpdate_2_clicked()
{
    QString stkname, stkquantity, stkprice, stksupp,day,month,year;
        LOGIN conn;
        stkname = ui ->stockName_2 ->text();
        stkquantity = ui ->stockQuantity_2->text();
        stkprice = ui -> stockPrice_2->text();
        stksupp = ui -> Supplier_2->text();
        day = ui->comboBoxDay_2->currentText();
        month= ui->comboBoxMonth_2->currentText();
        year = ui->comboBoxYear_2->currentText();

        if(!conn.connOpen())
            {
                qDebug()<<"Failed to open database";
            }

            conn.connOpen();
            QSqlQuery qry1;
            qry1.prepare("update stocks set Name='"+stkname+"', Quantity='"+stkquantity+"',Price='"+stkprice+"',Supplier = '"+stksupp+"', day='"+day+"',month='"+month+"',year='"+year+"' where Name='"+stkname+"'");

            if(qry1.exec()){
                conn.connClose();
                QMessageBox msgBox;
                msgBox.setText("The stock has been successfully updated.");
                msgBox.exec();
            }
            else
                QMessageBox::critical(this,tr(" Error "), qry1.lastError().text());
            ui->stockName_2->clear();
            ui->stockPrice_2->clear();
            ui->stockQuantity_2->clear();
            ui->Supplier_2->clear();
}


void STOCK::on_pushButton_view_2_clicked()
{
    LOGIN conn;

        QSqlQueryModel *modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery *qry = new QSqlQuery(conn.csmsDB);
        qry->prepare("select Name from stocks");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_2->setModel(modal);
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        qDebug()<<(modal->rowCount());
}

void STOCK::on_searchButton_2_clicked()
{
    LOGIN conn;
        QString search = ui->search_2->text();
        QSqlQueryModel *modal = new QSqlQueryModel();


        conn.connOpen();
        QSqlQuery *qry = new QSqlQuery(conn.csmsDB);
        qry->prepare("select Name from stocks where Name = '"+search+"'");
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView_2->setModel(modal);
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        qDebug()<<(modal->rowCount());
}

void STOCK::on_tableView_2_activated(const QModelIndex &index)
{
    QString value = ui->tableView_2->model()->data(index).toString();
        LOGIN conn;

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
            return;
        }
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("select Supplier, Quantity, Price from stocks where Name = '"+value+"'");

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->SuppName_2->setText(qry.value(0).toString());
                ui->ProdPrice_2->setText(qry.value(2).toString());
                ui->ProdQuantity_2->setText(qry.value(1).toString());
            }
            conn.connClose();
        }
        else
            QMessageBox::critical(this,tr("Error::"),qry.lastError().text());
}

void STOCK::on_pushButtonBack_clicked()
{
    this->hide();
    ADOPTION back;
    back.setModal(true);
    back.exec();
}
