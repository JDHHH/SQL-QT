#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "dialog.h"
#include "inputview.h"
#include "areyousure.h"

#include "addfamily.h"
#include "addbody.h"
#include "addmoney.h"
#include "addrace.h"
#include "addschool.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QString year, number, name,sql,ID;
    QSqlQueryModel *model,*model1,*model2;
    int status = 0;



public slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushButton_15_clicked();

    void deleteInfor(QString database,QString ID);

    void on_tableView_2_clicked(const QModelIndex &index);



private:
    Ui::MainWindow *ui;
    InputView *i;
    AreYouSure *a;
    addFamily *f;
    addBody *b;
    addRace *r;
    addMoney *m;
    addSchool *s;
};
#endif // MAINWINDOW_H
