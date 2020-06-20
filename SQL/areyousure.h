#ifndef AREYOUSURE_H
#define AREYOUSURE_H

#include <QDialog>

namespace Ui {
class AreYouSure;
}

class AreYouSure : public QDialog
{
    Q_OBJECT

public:
    explicit AreYouSure(QWidget *parent = nullptr);
    ~AreYouSure();

private:
    Ui::AreYouSure *ui;
};

#endif // AREYOUSURE_H
