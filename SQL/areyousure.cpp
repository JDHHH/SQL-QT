#include "areyousure.h"
#include "ui_areyousure.h"

AreYouSure::AreYouSure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreYouSure)
{
    ui->setupUi(this);
    setWindowTitle("确认界面");
}

AreYouSure::~AreYouSure()
{
    delete ui;
}
