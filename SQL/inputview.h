#ifndef INPUTVIEW_H
#define INPUTVIEW_H

#include <QDialog>
#include <QImage>


namespace Ui {
class InputView;
}

class InputView : public QDialog
{
    Q_OBJECT

public:
    explicit InputView(QWidget *parent = nullptr);
    ~InputView();
    QString fileName ="null";

    void getdata(QString id1,QString name1,QString sex1,int year1,QString date1,QString minzu1,QString home1,QString IDnumber1);

public slots:
    //void show(QString id1,QString name1,QString sex1,QString date1,QString minzu1,QString home1,QString IDnumber1);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_pushButton_3_clicked();

private:
    Ui::InputView *ui;
    QImage *image;
};

#endif // INPUTVIEW_H
