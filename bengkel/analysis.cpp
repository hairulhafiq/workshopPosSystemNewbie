#include "analysis.h"
#include "ui_analysis.h"
#include <QMessageBox>

ANALYSIS::ANALYSIS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ANALYSIS)
{
    ui->setupUi(this);
    QPixmap pix1("C:/Users/Hairul Hafiq/Documents/Workshop/Pic/mac_wallpaper.jpg");
    ui->labelBackground->setPixmap(pix1);

    ui->comboBox->addItem("Count by...");
    ui->comboBox->addItem("month");
    ui->comboBox->addItem("year");
}

ANALYSIS::~ANALYSIS()
{
    delete ui;
}

void ANALYSIS::on_pushButton_2_clicked()
{
    QString analize;
        analize = ui->comboBox->currentText();
        QSqlQueryModel *modal = new QSqlQueryModel();

        LOGIN conn;
        conn.connOpen();
        if(analize == "month")
        {
            QSqlQuery *qry = new QSqlQuery(conn.csmsDB);
            qry->prepare("select COUNT(receipt_no) from sales WHERE '"+analize+"' = '"+analize+"' and receipt_no = receipt_no   ");
            qry->exec();
            modal->setQuery(*qry);
            ui->listView->setModel(modal);
        }

        else if(analize=="year")
        {
            QSqlQuery *qry = new QSqlQuery(conn.csmsDB);
            qry->prepare("select COUNT(receipt_no) from sales WHERE '"+analize+"' = '"+analize+"' and receipt_no = receipt_no ");
            qry->exec();
            modal->setQuery(*qry);
            ui->listView->setModel(modal);
        }
        conn.connClose();
}

void ANALYSIS::on_pushButton_clicked()
{
    this->hide();
    SALE back;
    back.setModal(true);
    back.exec();
}
