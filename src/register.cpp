#include "register.h"
#include "ui_register.h"
#include<QMessageBox>

REGISTER::REGISTER(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::REGISTER)
{
    ui->setupUi(this);
    QPixmap pix1("D:/git/workshopPosSystemNewbie/Pic/mac_wallpaper.jpg");
    ui->labelBackground->setPixmap(pix1);

    ui->comboBox_2->addItem("0");
    ui->comboBox_2->addItem("1");
}

REGISTER::~REGISTER()
{
    delete ui;
}


void REGISTER::on_pushButtonAdd_2_clicked()
{
    QString usrname, plate , pass, passcon,name, ic, addr, phn,priv,current_millage, engine, others;
        LOGIN conn;
        usrname = ui ->username_2 ->text();
        plate = ui ->platenumber_2->text();
        pass = ui -> pwd_2->text();
        passcon = ui->lineEditConPass_2->text();
        name = ui ->fullname_2 ->text();
        ic = ui ->icnum_2->text();
        addr = ui -> address_4->text();
        phn = ui -> phonenum_2 -> text();
        priv = ui->comboBox_2->currentText();
        current_millage = ui->Millage_4->text();
        engine = ui->engineSize_4->text();
        others = ui->Others_4->text();

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
        }
        if (pass == passcon)
        {
            conn.connOpen();
            QSqlQuery qry,qry1;
            qry.prepare("insert into users (usrname, password, name, ic, address, phone, privilage) values('"+usrname+"','"+pass+"','"+name+"','"+ic+"','"+addr+"','"+phn+"','"+priv+"')");
            qry1.prepare("insert into cars (Plate_Number, username, Current_Mileage, Engine_Size, Others) values ('"+plate+"','"+usrname+"','"+current_millage+"','"+engine+"','"+others+"')");
            if(qry.exec() && qry1.exec()){
                conn.connClose();
                QMessageBox msgBox;
                msgBox.setText("The user has been successfully added.");
                msgBox.exec();
            }

            else
                QMessageBox::critical(this,tr("Error"), qry.lastError().text());
        }
        else
            QMessageBox::critical(this,tr("Error"),tr("Password and confirm password unmatched."));

        ui ->username_2 ->clear();
        ui ->platenumber_2->clear();
        ui -> pwd_2->clear();
        ui->lineEditConPass_2->clear();
        ui ->fullname_2 ->clear();
        ui ->icnum_2->clear();
        ui -> address_4->clear();
        ui -> phonenum_2 -> clear();
        ui->comboBox_2->clear();
        ui->Millage_4->clear();
        ui->engineSize_4->clear();
        ui->Others_4->clear();
}

void REGISTER::on_pushButtonUpdate_2_clicked()
{
    QString usrname, plate , pass, passcon,name, ic, addr, phn,priv,current_millage, engine, others;
    LOGIN conn;
    usrname = ui ->username_2 ->text();
    plate = ui ->platenumber_2->text();
    pass = ui -> pwd_2->text();
    passcon = ui->lineEditConPass_2->text();
    name = ui ->fullname_2 ->text();
    ic = ui ->icnum_2->text();
    addr = ui -> address_4->text();
    phn = ui -> phonenum_2 -> text();
    priv = ui->comboBox_2->currentText();
    current_millage = ui->Millage_4->text();
    engine = ui->engineSize_4->text();
    others = ui->Others_4->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open database";
    }
    if (pass == passcon)
    {
        conn.connOpen();
        QSqlQuery qry, qry1;
        qry.prepare("update users set username='"+usrname+"', password='"+pass+"', name='"+name+"', ic='"+ic+"', address='"+addr+"', phone='"+phn+"', privilage ='"+priv+"'where usrname='"+usrname+"'");
        qry1.prepare("update cars set Plate_Number='"+plate+"', username='"+usrname+"',Current_Mileage = '"+current_millage+"', Engine_Size = '"+engine+"', Others = '"+others+"' WHERE username = '"+usrname+"'");
        if(qry.exec() && qry1.exec()){
            conn.connClose();
            QMessageBox msgBox;
            msgBox.setText("The user has been updated.");
            msgBox.exec();
        }
        else
            QMessageBox::critical(this,tr(" Error "), qry.lastError().text());
    }

    ui ->username_2 ->clear();
    ui ->platenumber_2->clear();
    ui -> pwd_2->clear();
    ui->lineEditConPass_2->clear();
    ui ->fullname_2 ->clear();
    ui ->icnum_2->clear();
    ui -> address_4->clear();
    ui -> phonenum_2 -> clear();
    ui->comboBox_2->clear();
    ui->Millage_4->clear();
    ui->engineSize_4->clear();
    ui->Others_4->clear();
}

void REGISTER::on_pushButtonDelete_2_clicked()
{
    QString usrname,plate;
    LOGIN conn;
    usrname = ui ->username_2 ->text();
    plate = ui->platenumber_2->text();

    if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
        }

        conn.connOpen();
        QSqlQuery qry,qry1;
        qry.prepare("Delete from users where usrname = '"+usrname+"'");
        qry1.prepare("Delete from cars  where Plate_Number = '"+plate+"' and username = '"+usrname+"'");
        if (qry.exec() && qry1.exec()){
            conn.connClose();
            QMessageBox msgBox;
            msgBox.setText("The user has been deleted.");
            msgBox.exec();
        }
        else
            QMessageBox::critical(this,tr(" Error "), qry.lastError().text());

        ui ->username_2 ->clear();
        ui ->platenumber_2->clear();
}


void REGISTER::on_pushButton_view_2_clicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    LOGIN conn;

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.csmsDB);
    qry->prepare("select u.usrname,c.Plate_Number, u.password,u.privilage from users u, cars c where u.usrname = c.username");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void REGISTER::on_searchButton_2_clicked()
{
    QString search = ui->search_2->text();
    LOGIN conn;

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery *qry1 = new QSqlQuery(conn.csmsDB);
    qry1->prepare("select usrname from users where ic = '"+search+"'");

    if (qry1->exec())
    {
    model->setQuery(*qry1);
    ui->tableView_2->setModel(model);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qDebug()<<(model->rowCount());
    }

    else if (!qry1->exec())
        QMessageBox::critical(this, tr("Error"), tr("No user in database."));
}


void REGISTER::on_tableView_2_activated(const QModelIndex &index)
{
    QString value = ui->tableView_2->model()->data(index).toString();
        LOGIN conn;

        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database";
            return;
        }
        conn.connOpen();
        QSqlQuery qry1;
        qry1.prepare("select u.name, u.ic, u.address, u.phone, c.Current_Mileage, c.Engine_Size, c.Others from users u, cars c where u.usrname = '"+value+"' and c.username= u.usrname");

        if(qry1.exec())
        {
            if(qry1.next())
            {
                ui->name_2->setText(qry1.value(0).toString());
                ui->ic_2->setText(qry1.value(1).toString());
                ui->address_3->setText(qry1.value(2).toString());
                ui->phone_2->setText(qry1.value(3).toString());
                ui->Millage_3->setText(qry1.value(4).toString());
                ui->engineSize_3->setText(qry1.value(5).toString());
                ui->Others_3->setText(qry1.value(6).toString());
                conn.connClose();
            }
            else
                QMessageBox::critical(this,tr("Error"),qry1.lastError().text());
        }
        else
            QMessageBox::critical(this,tr("Error"),qry1.lastError().text());
}


void REGISTER::on_pushButtonBack_clicked()
{
    this->hide();
    ADOPTION main;
    main.setModal(true);
    main.exec();
}
