#ifndef ADDRACE_H
#define ADDRACE_H

#include <QDialog>

namespace Ui {
class addRace;
}

class addRace : public QDialog
{
    Q_OBJECT

public:
    explicit addRace(QWidget *parent = nullptr);
    ~addRace();
    QString num;
    void setNumber(QString);
    void getdata(QString ,int);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addRace *ui;
};

#endif // ADDRACE_H
