#include "addbody.h"
#include "ui_addbody.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "mainwindow.h"
extern bool flag;

addBody::addBody(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addBody)
{
    ui->setupUi(this);
    setWindowTitle("体质测量信息");
}

addBody::~addBody()
{
    delete ui;
}



void addBody::on_pushButton_clicked()
{
    if(flag==false){
        QString height = ui->lineEdit->text();
        QString weight = ui->lineEdit_2->text();
        height.toFloat();
        weight.toFloat();

        QString sql = (QString("insert into students.dbo.body (学生编号,身高,体重) values('%1',%2,%3);").arg(num).arg(height).arg(weight));

        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"insert data success!";
        }
    }
    else{
        QString height = ui->lineEdit->text();
        QString weight = ui->lineEdit_2->text();
        height.toFloat();
        weight.toFloat();

        QString sql = (QString("update students.dbo.body set 身高=%1,体重=%2 where 学生编号='%3';").arg(height).arg(weight).arg(num));

        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"update data success!";
        }
    }

    //qDebug()<<sql;
    //没有效果！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
    MainWindow *m = new MainWindow();
    m->on_pushButton_8_clicked();
    close();
}

void addBody::on_pushButton_2_clicked()
{
    close();
}

void addBody::getdata( float height, float weight){
    ui->lineEdit->setText(QString::number(height, 10, 2));
    ui->lineEdit_2->setText(QString::number(weight, 10, 2));
}

void addBody::setNumber(QString num){
    this->num=num;
}
