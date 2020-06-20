#include "addschool.h"
#include "ui_addschool.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

extern bool flag;
addSchool::addSchool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSchool)
{
    ui->setupUi(this);
    setWindowTitle("学校信息");
}

addSchool::~addSchool()
{
    delete ui;
}

void addSchool::on_pushButton_clicked()
{
    if(flag == false){
        QString name = ui->lineEdit->text();
        QString year = ui->lineEdit_2->text();
        year.toInt();

        QString sql = (QString("insert into students.dbo.school (学生编号,学校名称,入学年份) values('%1','%2',%3);").arg(num).arg(name).arg(year));

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
        QString name = ui->lineEdit->text();
        QString year = ui->lineEdit_2->text();
        year.toInt();

        QString sql = (QString("update students.dbo.school set 学校名称='%1' where 入学年份=%2 and 学生编号='%3';").arg(name).arg(year).arg(num));

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
    MainWindow *m = new MainWindow();
    m->on_pushButton_7_clicked();
    close();
}

void addSchool::on_pushButton_2_clicked()
{
    close();
}


void addSchool::setNumber(QString num){
    this->num=num;
}

void addSchool::getdata(QString name,int year) {
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(QString::number(year, 10, 0));
}
