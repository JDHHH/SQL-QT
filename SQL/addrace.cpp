#include "addrace.h"
#include "ui_addrace.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

extern bool flag;
addRace::addRace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRace)
{
    ui->setupUi(this);
    setWindowTitle("比赛信息");
}

addRace::~addRace()
{
    delete ui;
}

void addRace::on_pushButton_clicked()
{
    if(flag== false){
        QString name = ui->lineEdit->text();
        QString mingci = ui->lineEdit_2->text();
        mingci.toInt();

        QString sql = (QString("insert into students.dbo.race (学生编号,比赛名称,名次) values('%1','%2',%3);").arg(num).arg(name).arg(mingci));

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
        QString mingci = ui->lineEdit_2->text();
        mingci.toInt();

        QString sql = (QString("update students.dbo.race set 名次=%1 where 比赛名称='%2' and 学生编号='%3';").arg(mingci).arg(name).arg(num));

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
    m->on_pushButton_9_clicked();
    close();
}

void addRace::on_pushButton_2_clicked()
{
    close();
}

void addRace::setNumber(QString num){
    this->num=num;
}
void addRace::getdata(QString name, int mingci){
    ui->lineEdit->setText(name);
    ui->lineEdit_2->setText(QString::number(mingci, 10, 0));
}
