#include "addfamily.h"
#include "ui_addfamily.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

extern bool flag;

addFamily::addFamily(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFamily)
{
    ui->setupUi(this);
    setWindowTitle("家庭信息");
}

addFamily::~addFamily()
{
    delete ui;
}



void addFamily::on_pushButton_clicked()
{
    if(flag==false){
        QString name = ui->lineEdit->text();
        QString guanxi = ui->lineEdit_2->text();
        QString position = ui->lineEdit_3->text();
        QString zhiwu = ui->lineEdit_4->text();
        QString tel = ui->lineEdit_5->text();
        QString beizhu = ui->lineEdit_6->text();


        QString sql = (QString("insert into students.dbo.family (学生编号,姓名,关系,工作单位,职务,电话,备注) values('%1','%2','%3','%4','%5','%6','%7');").arg(num).arg(name).arg(guanxi).arg(position).arg(zhiwu).arg(tel).arg(beizhu));

        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"insert data success!";
        }
        //qDebug()<<sql;

    }
    else{
        QString name = ui->lineEdit->text();
        QString guanxi = ui->lineEdit_2->text();
        QString position = ui->lineEdit_3->text();
        QString zhiwu = ui->lineEdit_4->text();
        QString tel = ui->lineEdit_5->text();
        QString beizhu = ui->lineEdit_6->text();


        QString sql = (QString("update students.dbo.family set 姓名='%1',工作单位='%2',职务='%3',电话='%4',备注='%5' where 关系='%6' and 学生编号='%7';").arg(name).arg(position).arg(zhiwu).arg(tel).arg(beizhu).arg(guanxi).arg(num));

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
    m->on_pushButton_6_clicked();
    close();
}

void addFamily::on_pushButton_2_clicked()
{
    close();
}

void addFamily::setNumber(QString num){
    this->num=num;
}

void addFamily::getdata(QString name, QString guanxi, QString position, QString zhiwu, QString tel, QString beizhu){
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(guanxi);
    ui->lineEdit_3->setText(position);
    ui->lineEdit_4->setText(zhiwu);
    ui->lineEdit_5->setText(tel);
    ui->lineEdit_6->setText(beizhu);
}
