#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "inputview.h"
#include <QSqlDatabase>					//头文件
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QSqlTableModel>
//#include <QCursor>

bool flag;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("学生信息管理系统");
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked));

    ui->photolabel->setScaledContents(true);

    //设置背景图片
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/images/bg1.jpg").scaled(this->size())));
    this->setPalette(palette);

    //ui->tableView->setShowGrid(false); // 可隐藏grid
    // 列头灰色
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");

    //ui->tableView_2->setShowGrid(false); // 可隐藏grid
    // 只能单选
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    // 以行作为选择标准
    // ui->tableView_2->setSelectionBehavior(QAbstractItemView::QAbstractItemView::SelectRows);

    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(225,225,225)};");
    //connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //查询
    sql = "select * from information as i ";
    if(ui->comboBox->currentText() != "unkown"){
        year = ui->comboBox->currentText();
    }
    else{
        year = "-1";
    }
    if(!ui->lineEdit->text().isEmpty()){
        number = ui->lineEdit->text();
    }
    else{
        number = "-1";
    }
    if(!ui->lineEdit_2->text().isEmpty()){
        name = ui->lineEdit_2->text();
    }
    else{
        name = "-1";
    }
    if(number!="-1"){
        //有学生编号
        if(name!="-1"){
            //有名字
            if(year!="-1"){
                //三种信息具备  0
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where i.[学生编号]="+number+" and cast(i.姓名 as varchar)='"+name+"' and i.[入学年份]="+year;
            }
            else{
                //仅仅缺少入学年份  1
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where i.[学生编号]="+number+" and cast(i.姓名 as varchar)='"+name+"'";
            }
        }
        else{
            //缺少姓名
            if(year!="-1"){
                //仅仅缺少姓名  1
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where i.[学生编号]="+number+" and i.[入学年份]="+year;
            }
            else{
                //缺少姓名及入学年份  2
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where i.[学生编号]="+number;
            }
        }
    }
    else{
        //缺少学生编号
        if(name!="-1"){
            //有名字
            if(year!="-1"){
                //仅仅缺少学生编号  1
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where cast(i.姓名 as varchar)='"+name+"' and i.[入学年份]="+year;
            }
            else{
                //缺少学生编号及入学年份  2
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where cast(i.姓名 as varchar)='"+name+"'";
            }
        }
        else {
            //缺少名字
            if(year!="-1"){
                //缺少学生编号及名字  2
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information as i where i.[入学年份]="+year;
            }
            else{
                //缺少学生编号及入学年份及名字  3
                sql = "select 学生编号,姓名,性别,入学年份,出生日期,民族,家庭住址,身份证号 from students.dbo.information";
                //qDebug()<<"can not find !!!";
            }
        }

    }

    model = new QSqlQueryModel(ui->tableView);
    model->setQuery(sql);

    model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, tr("入学年份"));
    model->setHeaderData(4, Qt::Horizontal, tr("出生日期"));
    model->setHeaderData(5, Qt::Horizontal, tr("民族"));
    model->setHeaderData(6, Qt::Horizontal, tr("家庭住址"));
    model->setHeaderData(7, Qt::Horizontal, tr("身份证号"));

    ui->tableView->setModel(model);


    //MainWindow::on_pushButton_6_clicked();

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //QStandardItemModel *addedDeviceItemMode=new QStandardItemModel();
    int row = ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row,0,QModelIndex());
    number = index1.data().toString();
    QString currentText = index.data().toString();
    //qDebug()<<number;

    model2 = new QSqlQueryModel(ui->tableView_3);

    QString cmd = QString ("SELECT 照片 FROM students.dbo.information WHERE 学生编号 = '%1'").arg(number);
    model2->setQuery(cmd);
    ui->tableView_3->setModel(model2);




    MainWindow::on_pushButton_6_clicked();
    //MainWindow::on_pushButton_7_clicked();
    //MainWindow::on_pushButton_8_clicked();
    //MainWindow::on_pushButton_9_clicked();
    //MainWindow::on_pushButton_10_clicked();

    MainWindow::on_tableView_3_clicked(index);
}


void MainWindow::on_pushButton_6_clicked()
{
    //家庭信息
    status=1;
    model1 = new QSqlQueryModel(ui->tableView_2);
    sql = "select 姓名,关系,工作单位,职务,电话,备注 from students.dbo.family as f where f.学生编号="+number;
    model1->setQuery(sql);

    //model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model1->setHeaderData(0, Qt::Horizontal, tr("姓名"));
    model1->setHeaderData(1, Qt::Horizontal, tr("关系"));
    model1->setHeaderData(2, Qt::Horizontal, tr("工作单位"));
    model1->setHeaderData(3, Qt::Horizontal, tr("职务"));
    model1->setHeaderData(4, Qt::Horizontal, tr("电话"));
    model1->setHeaderData(5, Qt::Horizontal, tr("备注"));

    ui->tableView_2->setModel(model1);
}

void MainWindow::on_pushButton_7_clicked()
{
    //学校信息
    status=2;
    model1 = new QSqlQueryModel(ui->tableView_2);
    sql = "select 学校名称,入学年份 from students.dbo.school as s where s.学生编号="+number;
    model1->setQuery(sql);

    //model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model1->setHeaderData(0, Qt::Horizontal, tr("学校名称"));
    model1->setHeaderData(1, Qt::Horizontal, tr("入学年份"));

    ui->tableView_2->setModel(model1);
}

void MainWindow::on_pushButton_8_clicked()
{
    //体质测量
    status =3;
    model1 = new QSqlQueryModel(ui->tableView_2);
    sql = "select 体重,身高 from students.dbo.body as b where b.学生编号="+number;
    model1->setQuery(sql);

    //model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model1->setHeaderData(0, Qt::Horizontal, tr("体重"));
    model1->setHeaderData(1, Qt::Horizontal, tr("身高"));

    ui->tableView_2->setModel(model1);
}

void MainWindow::on_pushButton_9_clicked()
{
    //主要比赛
    status=4;
    model1 = new QSqlQueryModel(ui->tableView_2);
    sql = "select 比赛名称,名次 from students.dbo.race as r where r.学生编号="+number;
    model1->setQuery(sql);

    //model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model1->setHeaderData(0, Qt::Horizontal, tr("比赛名称"));
    model1->setHeaderData(1, Qt::Horizontal, tr("名次"));

    ui->tableView_2->setModel(model1);
}

void MainWindow::on_pushButton_10_clicked()
{
    //收费情况
    status=5;
    model1 = new QSqlQueryModel(ui->tableView_2);
    sql = "select 项目,收费金额,发票单号 from students.dbo.money as m where m.学生编号="+number;
    model1->setQuery(sql);

    //model->setHeaderData(0, Qt::Horizontal, tr("学生编号"));
    model1->setHeaderData(0, Qt::Horizontal, tr("项目"));
    model1->setHeaderData(1, Qt::Horizontal, tr("收费金额"));
    model1->setHeaderData(2, Qt::Horizontal, tr("发票单号"));

    ui->tableView_2->setModel(model1);
}

void MainWindow::on_pushButton_2_clicked()
{
    //导出总表
    QString cmd = "select * from students.dbo.information i left join students.dbo.family f on i.学生编号=f.学生编号 left join students.dbo.school s on i.学生编号=s.学生编号 left join students.dbo.body b on i.学生编号=b.学生编号 left join students.dbo.race r on i.学生编号=r.学生编号 left join students.dbo.money m on i.学生编号=m.学生编号";

    QSqlQueryModel *m = new QSqlQueryModel(ui->tableView_4);
    m->setQuery(cmd);
    m->setHeaderData(0,Qt::Horizontal,tr("学生编号"));
    ui->tableView_4->setModel(m);



    QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),QString(), tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));

    if (filepath != "")
    {
        int row = ui->tableView_4->model()->rowCount();
        int col = ui->tableView_4->model()->columnCount();
        QList<QString> list;
        //添加列标题
        QString HeaderRow;
        for (int i = 0; i < col; i++)
        {
            HeaderRow.append(ui->tableView_4->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\t");
        }
        list.push_back(HeaderRow);
        for (int i = 0; i < row; i++)
        {
            QString rowStr = "";
            for (int j = 0; j < col; j++){
                QModelIndex index = ui->tableView_4->model()->index(i, j);
                rowStr += ui->tableView_4->model()->data(index).toString() + "\t";
            }
            list.push_back(rowStr);
        }
        QTextEdit textEdit;
        for (int i = 0; i < list.size(); i++)
        {
            textEdit.append(list.at(i));
        }

        QFile file(filepath);
        if (file.open(QFile::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(&file);
            ts.setCodec("GB2312");//这个地方大家自己判断是否用“utf-8”
            ts << textEdit.document()->toPlainText();
            file.close();
            //ui->lblQueryResult->setText(tr("数据导出成功"));
            qDebug()<<"数据导出成功";
        }else{
            //ui->lblQueryResult->setText(tr("文件打开错误，数据导出失败"));
            qDebug()<<"文件打开错误，数据导出失败";
        }
    }
    else{
        //qDebug()<<"文件没有打开？";
    }



}

void MainWindow::on_pushButton_3_clicked()
{
    //学生添加
    flag = false;
    i = new InputView();
    //i->setModal(false);
    i->show();
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButton_4_clicked()
{
    //学生修改

    flag= true;

    QString id,name,sex,date,minzu,home,IDnumber;
    int year;
    int rowToUpData;
    //QMap<int, int> rowMap;

    QAbstractItemModel *model = ui->tableView->model();
    QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.length() > 1)
    {
        QMessageBox::critical(this,"提示","请只选择一行来更改!");
    }
     rowToUpData = ui->tableView ->currentIndex().row();
     QModelIndex index =model->index(rowToUpData,0);

     id=index.sibling(rowToUpData,0).data().toString();
     name = index.sibling(rowToUpData,1).data().toString();
     sex = index.sibling(rowToUpData,2).data().toString();
     year = index.sibling(rowToUpData,3).data().toInt();
     date = index.sibling(rowToUpData,4).data().toString();
     minzu = index.sibling(rowToUpData,5).data().toString();
     home = index.sibling(rowToUpData,6).data().toString();
     IDnumber = index.sibling(rowToUpData,7).data().toString();


    i = new InputView();
    i->getdata(id,name,sex,year,date,minzu,home,IDnumber);
    i->show();

    MainWindow::on_pushButton_clicked();


}

void MainWindow::on_pushButton_5_clicked()
{
    //学生删除
    MainWindow::deleteInfor(QString("information"),QString("information"));
    MainWindow::on_pushButton_clicked();
}

void MainWindow::on_pushButton_14_clicked()
{
    //学生导出
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),QString(), tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));

    if (filepath != "")
    {
        int row = ui->tableView->model()->rowCount();
        int col = ui->tableView->model()->columnCount();
        QList<QString> list;
        //添加列标题
        QString HeaderRow;
        for (int i = 0; i < col; i++)
        {
            HeaderRow.append(ui->tableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\t");
        }
        list.push_back(HeaderRow);
        for (int i = 0; i < row; i++)
        {
            QString rowStr = "";
            for (int j = 0; j < col; j++){
                QModelIndex index = ui->tableView->model()->index(i, j);
                rowStr += ui->tableView->model()->data(index).toString() + "\t";
            }
            list.push_back(rowStr);
        }
        QTextEdit textEdit;
        for (int i = 0; i < list.size(); i++)
        {
            textEdit.append(list.at(i));
        }

        QFile file(filepath);
        if (file.open(QFile::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(&file);
            ts.setCodec("GB2312");//这个地方大家自己判断是否用“utf-8”
            ts << textEdit.document()->toPlainText();
            file.close();
            //ui->lblQueryResult->setText(tr("数据导出成功"));
            qDebug()<<"数据导出成功";
        }else{
            //ui->lblQueryResult->setText(tr("文件打开错误，数据导出失败"));
            qDebug()<<"文件打开错误，数据导出失败";
        }
    }
    else{
        //qDebug()<<"文件没有打开？";
    }

}

void MainWindow::on_pushButton_11_clicked()
{
    //学生附属信息添加
    flag = false;
    switch (status) {
    case 1:
        f = new addFamily();
        f->setNumber(number);
        f->show();
        break;
    case 2:
        s = new addSchool();
        s->setNumber(number);
        s->show();
        break;
    case 3:
        b = new addBody();
        b->setNumber(number);
        b->show();
        break;
    case 4:
        r = new addRace();
        r->setNumber(number);
        r->show();
        break;
    case 5:
        m = new addMoney();
        m->setNumber(number);
        m->show();
        break;
    default:
        break;
    }

    MainWindow::on_pushButton_clicked();

}

void MainWindow::on_pushButton_13_clicked()
{
    int rowToUpData;
    //QMap<int, int> rowMap;

    QAbstractItemModel *model = ui->tableView_2->model();
    QItemSelectionModel *selections = ui->tableView_2->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.length() > 1)
    {
        QMessageBox::critical(this,"提示","请只选择一行来更改!");
    }
     rowToUpData = ui->tableView_2 ->currentIndex().row();
     QModelIndex index =model->index(rowToUpData,0);


    //学生附属信息修改
    flag = true;
    if(status==1){
        QString name=index.sibling(rowToUpData,0).data().toString();
        QString guanxi = index.sibling(rowToUpData,1).data().toString();
        QString position = index.sibling(rowToUpData,2).data().toString();
        QString zhiwu = index.sibling(rowToUpData,3).data().toString();
        QString tel = index.sibling(rowToUpData,4).data().toString();
        QString beizhu = index.sibling(rowToUpData,5).data().toString();

        f = new addFamily();
        f->setNumber(number);
        f->getdata(name,guanxi,position,zhiwu,tel,beizhu);
        f->show();

    }
    else if(status==2){
        QString mingcheng=index.sibling(rowToUpData,0).data().toString();

        int year = index.sibling(rowToUpData,1).data().toInt();

        s = new addSchool();
        s->setNumber(number);
        s->getdata(mingcheng,year);
        s->show();
    }

    else if(status==3){
        float name=index.sibling(rowToUpData,0).data().toFloat();
        float guanxi = index.sibling(rowToUpData,1).data().toFloat();

        b = new addBody();
        b->setNumber(number);
        b->getdata(name,guanxi);
        b->show();
    }
    else if(status==4){
        QString name=index.sibling(rowToUpData,0).data().toString();
        int guanxi = index.sibling(rowToUpData,1).data().toInt();

        r = new addRace();
        r->setNumber(number);
        r->getdata(name,guanxi);
        r->show();
    }
    else if(status==5){
        QString name=index.sibling(rowToUpData,0).data().toString();
        float guanxi = index.sibling(rowToUpData,1).data().toFloat();
        QString sex = index.sibling(rowToUpData,2).data().toString();

        m = new addMoney();
        m->setNumber(number);
        m->getdata(name,guanxi,sex);
        m->show();
    }
    else {

    }

    MainWindow::on_pushButton_clicked();
}

void MainWindow::deleteInfor(QString database,QString ID){
    //删除函数

    if(database =="money"){
        sql = QString("delete from students.dbo.%1 where 学生编号 = '%2' and 发票单号='%3'").arg(database).arg(number).arg(ID);
    }
    else{
        sql = QString("delete from students.dbo.%1 where 学生编号 = '%2'").arg(database).arg(number);
    }

    a = new AreYouSure();
    a->show();
    if(a->exec() == QDialog::Accepted){
        QSqlQuery query;
        query.prepare(sql);
        if(!query.exec()){
            qDebug()<<"query error :"<<query.lastError();
        }
        else{
            qDebug()<<"delete data success!";
        }
        a->close();
    }
    else{
        a->close();
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    //学生附属信息删除
    switch (status) {
    case 1:
        MainWindow::deleteInfor(QString("family"),QString("family"));
        MainWindow::on_pushButton_6_clicked();
        break;
    case 2:
        MainWindow::deleteInfor(QString("school"),QString("school"));
        MainWindow::on_pushButton_7_clicked();
        break;
    case 3:
        MainWindow::deleteInfor(QString("body"),QString("body"));
        MainWindow::on_pushButton_8_clicked();
        break;
    case 4:
        MainWindow::deleteInfor(QString("race"),QString("race"));
        MainWindow::on_pushButton_9_clicked();
        break;
    case 5:
        MainWindow::deleteInfor(QString("money"),QString(ID));
        MainWindow::on_pushButton_10_clicked();
        break;
    default:
        break;
    }
    MainWindow::on_pushButton_clicked();

}

void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    //显示图片
    QModelIndex index2=model2->index(0,0,QModelIndex());//rowNum,columnNum为行列号

    QString str1= index2.data().toString();
    //qDebug()<<str1;

    QPixmap *img1 = new QPixmap(str1);

    img1->scaled(ui->photolabel->size(), Qt::KeepAspectRatio);
    if(img1 != NULL){
        ui->photolabel->setPixmap(*img1);
    }

}



void MainWindow::on_pushButton_15_clicked()
{
    //退出
    close();
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    //定位收费项目的唯一标识-发票单号
    if(status ==5){
        int row = ui->tableView_2->currentIndex().row();
        QModelIndex index1 = model1->index(row,2,QModelIndex());
        ID = index1.data().toString();
    }
    else{

    }

}



