#include "forminput.h"
#include "ui_forminput.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

FormInput::FormInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormInput)
{
    ui->setupUi(this);

    ui->label->setGeometry(0,0,180,700);
    ui->label->setStyleSheet("QLabel{background-color:rgb(61,75,102);}");

    ui->InputBtn->setCheckable(true);
    ui->OutDataBtn->setCheckable(true);
    ui->OutReportBtn->setCheckable(true);
    ui->EChartsBtn->setCheckable(true);

    ui->InputBtn->setAutoExclusive(true);
    ui->OutDataBtn->setAutoExclusive(true);
    ui->OutReportBtn->setAutoExclusive(true);
    ui->EChartsBtn->setAutoExclusive(true);

    ui->InputBtn->setGeometry(20,10,140,40);
    ui->OutDataBtn->setGeometry(20,55,140,40);
    ui->OutReportBtn->setGeometry(20,100,140,40);
    ui->EChartsBtn->setGeometry(20,145,140,40);

    ui->InputBtn->setText(tr("导入数据"));
    ui->OutDataBtn->setText(tr("导出数据"));
    ui->OutReportBtn->setText(tr("导出报表"));
    ui->EChartsBtn->setText(tr("折线/柱状图"));

    //信号与槽
    connect(ui->InputBtn,SIGNAL(clicked(bool)),this,SLOT(InBtnC()));
    connect(ui->OutDataBtn,SIGNAL(clicked(bool)),this,SLOT(OutBtnC()));
    connect(ui->EChartsBtn,SIGNAL(clicked(bool)),this,SLOT(EChartsBtnC()));
    connect(ui->OutReportBtn,SIGNAL(clicked(bool)),this,SLOT(OutReportBtnC()));
}

FormInput::~FormInput()
{
    delete ui;
}



void FormInput::outputData()
{
    QSettings *config = new QSettings("E:\\hahaya.ini", QSettings::IniFormat);

    config->setValue("ip/first","555");
    config->setValue("ip/second","125.2.2.9");
    config->setValue("oops/id","3115000284");

    delete config;
}

void FormInput::InBtnC()
{
    emit showIn();
}

void FormInput::OutBtnC()
{
    emit showOut();
}

void FormInput::EChartsBtnC()
{
    emit showECharts();
}

void FormInput::OutReportBtnC()
{
    emit showReport();
}
