#ifndef ADDMONEY_H
#define ADDMONEY_H

#include <QDialog>

namespace Ui {
class addMoney;
}

class addMoney : public QDialog
{
    Q_OBJECT

public:

    explicit addMoney(QWidget *parent = nullptr);
    ~addMoney();
    QString num;
    void setNumber(QString);
    void getdata(QString ,float,QString );

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addMoney *ui;
};

#endif // ADDMONEY_H
