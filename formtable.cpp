#include "formtable.h"
#include "ui_formtable.h"
#include <QFile>
#include "mainwindow.h"

FormTable::FormTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTable)
{
    ui->setupUi(this);

    //导入资源文件中的qss文件，对QPushButton下拉列表进行样式设置
    QFile qss(":/style/qss/style.qss");//设置qss文件打开路径
    qss.open(QFile::ReadOnly);//只读，打开qss文件
    if(qss.isOpen())
    {
        qApp->setStyleSheet(qss.readAll());//如果打开成功，设置样式
        qss.close();//关闭qss文件
    }

    ui->label->setGeometry(0,0,180,700);
    ui->label->setStyleSheet("QLabel{background-color:rgb(61,75,102);}");

    ui->YuGangBtn->setCheckable(true);
    ui->GuhuaBtn->setCheckable(true);
    ui->GuhuaBiaoBtn->setCheckable(true);
    ui->BoqianBtn->setCheckable(true);
    ui->BoqianBiaoBtn->setCheckable(true);
    ui->ShuzhiBtn->setCheckable(true);
    ui->ShuzhiBiaoBtn->setCheckable(true);
    ui->YonghuBtn->setCheckable(true);
    ui->JiqirenBtn->setCheckable(true);
    ui->JiluBtn->setCheckable(true);

    ui->YuGangBtn->setAutoExclusive(true);
    ui->GuhuaBtn->setAutoExclusive(true);
    ui->GuhuaBiaoBtn->setAutoExclusive(true);
    ui->BoqianBtn->setAutoExclusive(true);
    ui->BoqianBiaoBtn->setAutoExclusive(true);
    ui->ShuzhiBtn->setAutoExclusive(true);
    ui->ShuzhiBiaoBtn->setAutoExclusive(true);
    ui->YonghuBtn->setAutoExclusive(true);
    ui->JiqirenBtn->setAutoExclusive(true);
    ui->JiluBtn->setAutoExclusive(true);

    ui->YuGangBtn->setGeometry(20,10,140,40);
    ui->GuhuaBtn->setGeometry(20,55,140,40);
    ui->GuhuaBiaoBtn->setGeometry(20,100,140,40);
    ui->BoqianBtn->setGeometry(20,145,140,40);
    ui->BoqianBiaoBtn->setGeometry(20,190,140,40);
    ui->ShuzhiBtn->setGeometry(20,235,140,40);
    ui->ShuzhiBiaoBtn->setGeometry(20,280,140,40);
    ui->YonghuBtn->setGeometry(20,325,140,40);
    ui->JiqirenBtn->setGeometry(20,370,140,40);
    ui->JiluBtn->setGeometry(20,415,140,40);

    ui->YuGangBtn->setText(tr("浴缸信息表"));
    ui->GuhuaBtn->setText(tr("固化剂产品信息表"));
    ui->GuhuaBiaoBtn->setText(tr("固化剂消耗标准表"));
    ui->BoqianBtn->setText(tr("玻纤产品信息表"));
    ui->BoqianBiaoBtn->setText(tr("玻纤消耗标准表"));
    ui->ShuzhiBtn->setText(tr("树脂产品信息表"));
    ui->ShuzhiBiaoBtn->setText(tr("树脂消耗标准表"));
    ui->YonghuBtn->setText(tr("用户操作记录表"));
    ui->JiqirenBtn->setText(tr("机器人信息表"));
    ui->JiluBtn->setText(tr("工作记录表"));

    //一堆的信号与槽
    connect(ui->YuGangBtn,SIGNAL(clicked(bool)),this,SLOT(YuGangBtnC()));
    connect(ui->GuhuaBtn,SIGNAL(clicked(bool)),this,SLOT(GuhuaBtnC()));
    connect(ui->GuhuaBiaoBtn,SIGNAL(clicked(bool)),this,SLOT(GuhuaBiaoBtnC()));
    connect(ui->BoqianBtn,SIGNAL(clicked(bool)),this,SLOT(BoqianBtnC()));
    connect(ui->BoqianBiaoBtn,SIGNAL(clicked(bool)),this,SLOT(BoqianBiaoBtnC()));
    connect(ui->ShuzhiBtn,SIGNAL(clicked(bool)),this,SLOT(ShuzhiBtnC()));
    connect(ui->ShuzhiBiaoBtn,SIGNAL(clicked(bool)),this,SLOT(ShuzhiBiaoBtnC()));
    connect(ui->YonghuBtn,SIGNAL(clicked(bool)),this,SLOT(YonghuBtnC()));
    connect(ui->JiqirenBtn,SIGNAL(clicked(bool)),this,SLOT(JiqirenBtnC()));
    connect(ui->JiluBtn,SIGNAL(clicked(bool)),this,SLOT(JiluBtnC()));
}

FormTable::~FormTable()
{
    delete ui;
}


void FormTable::YuGangBtnC()
{
    MainWindow::Mark = 2;
    MainWindow::Table = "select * from bathtub;";
    emit showTable("bathtub");
}

void FormTable::GuhuaBtnC()
{
    MainWindow::Mark = 3;
    MainWindow::Table = "select * from curingagent;";
    emit showTable("curingagent");

}

void FormTable::GuhuaBiaoBtnC()
{
    MainWindow::Mark = 4;
    MainWindow::Table = "select * from curingagentcosting;";
    emit showTable("curingagentcosting");
}

void FormTable::BoqianBtnC()
{
    MainWindow::Mark = 5;
    MainWindow::Table = "select * from fiberglass;";
    emit showTable("fiberglass");
}

void FormTable::BoqianBiaoBtnC()
{
    MainWindow::Mark = 6;
    MainWindow::Table = "select * from fiberglasscosting;";
    emit showTable("fiberglasscosting");
}

void FormTable::ShuzhiBtnC()
{
    MainWindow::Mark = 7;
    MainWindow::Table = "select * from resin;";
    emit showTable("resin");
}

void FormTable::ShuzhiBiaoBtnC()
{
    MainWindow::Mark = 8;
    MainWindow::Table = "select * from resincosting;";
    emit showTable("resincosting");
}

void FormTable::YonghuBtnC()
{
    MainWindow::Mark = 9;
    MainWindow::Table = "select * from userlogin;";
    emit showTable("userlogin");
}

void FormTable::JiqirenBtnC()
{
    MainWindow::Mark = 10;
    MainWindow::Table = "select * from robot;";
    emit showTable("robot");
}

void FormTable::JiluBtnC()
{
    MainWindow::Mark = 11;
    MainWindow::Table = "select * from workdata;";
    emit showTable("workdata");
}
