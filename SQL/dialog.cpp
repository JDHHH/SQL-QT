#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlDatabase>					//头文件
#include <QDebug>
#include <QMessageBox>
#include<QSqlError>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);


    //设置背景图片
    ui->widget->setAutoFillBackground(true);   // 这个属性一定要设置
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/images/bg3.jpg").scaled(this->size())));
    this->setPalette(palette);

}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::OpenDatabase(QString name, QString password)
{

    db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("QTDSN");      //数据源名称（配置时 的名称）
    db.setHostName("localhost");                        //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName(name);                               //登录用户(需要修改)
    db.setPassword(password);                           //密码（需要修改）
    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else
        qDebug()<<"database open success!";
    return true;
}


void Dialog::on_enterBtn_accepted()
{
     QString name = ui->lineEdit->text();
     QString password = ui->lineEdit_2->text();
     if(!OpenDatabase(name, password))
         return;

}

void Dialog::on_enterBtn_rejected()
{
    close();
    return;
}
