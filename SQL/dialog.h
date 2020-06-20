#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QSqlDatabase db;
    bool OpenDatabase(QString name, QString password);

private slots:
    void on_enterBtn_accepted();


    void on_enterBtn_rejected();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
