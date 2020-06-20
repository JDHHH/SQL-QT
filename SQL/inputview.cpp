#include "inputview.h"
#include "ui_inputview.h"
#include "mainwindow.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFileDialog>

extern bool flag;

InputView::InputView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputView)
{
    ui->setupUi(this);

    setWindowTitle("学生信息输入");
    image = new QImage();

}

InputView::~InputView()
{
    delete ui;
}

void InputView::on_pushButton_clicked()
{
    //确定插入数据
    QString studentsnumber = ui->lineEdit->text();
    if(flag ==false){
        studentsnumber = ui->lineEdit->text();
        QString name = ui->lineEdit_2->text();
        QString sex = ui->lineEdit_3->text();
        int year = ui->lineEdit_4->text().toInt();
        QString date = ui->lineEdit_5->text();
        QString minzu = ui->lineEdit_6->text();
        QString home = ui->lineEdit_7->text();
        QString IDnumber = ui->lineEdit_8->text();

        QString sql = (QString("insert into students.dbo.information (学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号,照片) values('%1','%2','%3',%4,'%5','%6','%7','%8','%9');").arg(studentsnumber).arg(name).arg(sex).arg(year).arg(date).arg(minzu).arg(home).arg(IDnumber).arg(fileName));

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
        //QString studentsnumber = ui->lineEdit->text();
        QString name = ui->lineEdit_2->text();
        QString sex = ui->lineEdit_3->text();
        int year = ui->lineEdit_4->text().toInt();
        QString date = ui->lineEdit_5->text();
        QString minzu = ui->lineEdit_6->text();
        QString home = ui->lineEdit_7->text();
        QString IDnumber = ui->lineEdit_8->text();

        QString sql = (QString("update students.dbo.information set 姓名='%1',性别='%2',入学年份=%3,出生日期='%4',民族='%5',家庭住址='%6',身份证号='%7',照片='%8' where 学生编号='%9';").arg(name).arg(sex).arg(year).arg(date).arg(minzu).arg(home).arg(IDnumber).arg(fileName).arg(studentsnumber));

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

    close();
}

void InputView::on_pushButton_2_clicked()
{
    //取消插入数据
    close();
}

void InputView::getdata(QString id1,QString name1,QString sex1,int year1,QString date1,QString minzu1,QString home1,QString IDnumber1)
{
    ui->lineEdit_4->clear();
    ui->lineEdit->setText(id1);
    ui->lineEdit_2->setText(name1);
    ui->lineEdit_3->setText(sex1);
    ui->lineEdit_4->setText(QString::number(year1, 10, 0));
    ui->lineEdit_5->setText(date1);
    ui->lineEdit_6->setText(minzu1);
    ui->lineEdit_7->setText(home1);
    ui->lineEdit_8->setText(IDnumber1);
}

void InputView::on_pushButton_3_clicked()
{
    //打开图片
    fileName = QFileDialog::getOpenFileName(
                    this, "open image file",
                    ".",
                    "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");
        if(fileName != "")
        {
            if(image->load(fileName))
            {
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->graphicsView->setScene(scene);
                ui->graphicsView->resize(131, 151);
                ui->graphicsView->show();
                //qDebug()<<fileName<<"!@#$%";
            }
        }

}
