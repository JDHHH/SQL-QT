#ifndef ADDFAMILY_H
#define ADDFAMILY_H

#include <QDialog>

namespace Ui {
class addFamily;
}

class addFamily : public QDialog
{
    Q_OBJECT

public:
    explicit addFamily(QWidget *parent = nullptr);
    ~addFamily();
    QString num;
    void setNumber(QString);
    void getdata(QString ,QString ,QString ,QString ,QString ,QString  );

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addFamily *ui;
};

#endif // ADDFAMILY_H
