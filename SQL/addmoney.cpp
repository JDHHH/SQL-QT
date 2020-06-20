#include "addmoney.h"
#include "ui_addmoney.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

extern bool flag;
addMoney::addMoney(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMoney)
{
    ui->setupUi(this);
    setWindowTitle("收费信息");
}

addMoney::~addMoney()
{
    delete ui;
}



void addMoney::on_pushButton_clicked()
{
    if(flag == false){
        QString name = ui->lineEdit->text();
        QString money = ui->lineEdit_2->text();
        QString ID = ui->lineEdit_3->text();
        money.toFloat();
        // qDebug()<<num;

        QString sql = (QString("insert into students.dbo.money (学生编号,项目,收费金额,发票单号) values('%1','%2',%3,'%4');").arg(num).arg(name).arg(money).arg(ID));

        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"insert data success!";
        }
        // qDebug()<<sql;

    }

    else {
        QString name = ui->lineEdit->text();
        QString money = ui->lineEdit_2->text();
        QString ID = ui->lineEdit_3->text();
        money.toFloat();

        QString sql = (QString("update students.dbo.money set 项目='%1',收费金额=%2 where 学生编号='%3' and 发票单号='%4';").arg(name).arg(money).arg(num).arg(ID));

        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"update data success!";
        }
        //qDebug()<<sql;
     }

    MainWindow *m = new MainWindow();
    m->on_pushButton_10_clicked();
    close();
}

void addMoney::on_pushButton_2_clicked()
{
    close();
}

void addMoney::setNumber(QString num){
    this->num=num;
}

void addMoney::getdata(QString name, float money, QString danhao){
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(QString::number(money, 10, 2));
    ui->lineEdit_3->setText(danhao);
}
