#include "mainwindow.h"
#include "dialog.h"
#include "inputview.h"
#include <QDialog>
#include <QApplication>
#include <QSqlDatabase>					//头文件
#include <QDebug>
#include <QMessageBox>
#include<QSqlError>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog d;
    InputView i;

    d.show();
    if(d.exec()==QDialog::Accepted){
        w.show();
        return a.exec();
    }
    else if(d.exec()==QDialog::Rejected){
        //d.close();
        a.closeAllWindows();
        return 1;
    }



}
