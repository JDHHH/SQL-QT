#ifndef ADDBODY_H
#define ADDBODY_H

#include <QDialog>

namespace Ui {
class addBody;
}

class addBody : public QDialog
{
    Q_OBJECT

public:
    explicit addBody(QWidget *parent = nullptr);
    ~addBody();
    QString num;
    void setNumber(QString);
    void getdata(float height,float weight);

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addBody *ui;
};

#endif // ADDBODY_H
