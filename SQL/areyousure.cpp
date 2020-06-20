#include "areyousure.h"
#include "ui_areyousure.h"

AreYouSure::AreYouSure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreYouSure)
{
    ui->setupUi(this);
    setWindowTitle("确认界面");

//    QPalette palette;
//    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/images/bg1.jpg").scaled(this->size())));
//    this->setPalette(palette);
}

AreYouSure::~AreYouSure()
{
    delete ui;
}
