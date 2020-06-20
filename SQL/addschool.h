#ifndef ADDSCHOOL_H
#define ADDSCHOOL_H

#include <QDialog>

namespace Ui {
class addSchool;
}

class addSchool : public QDialog
{
    Q_OBJECT

public:
    explicit addSchool(QWidget *parent = nullptr);
    ~addSchool();
    QString num;
    void setNumber(QString);
    void getdata(QString,int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addSchool *ui;
};

#endif // ADDSCHOOL_H
