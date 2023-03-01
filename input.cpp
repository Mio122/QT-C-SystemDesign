#include "input.h"
#include "ui_input.h"
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件


Input::Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("导入数据"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(470,240);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,470,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,470,360);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色

    ui->UserLab->setGeometry(20,80,140,30);
    ui->UserLab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab->setText(tr("选择导入文件路径："));

    ui->PasswordLab->setGeometry(40,140,120,30);
    ui->PasswordLab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->PasswordLab->setText(tr("选择导入到表格："));

    ui->label->setGeometry(10,0,80,30);
    ui->label->setText(tr("导入数据"));

    ui->FileEdit->setGeometry(160,80,200,30);
    ui->FileBtn->setGeometry(370,80,60,30);

    ui->comboBox->setGeometry(160,140,200,30);

    ui->SaveBtn->setGeometry(370,200,75,30);
    ui->CancleBtn->setGeometry(290,200,75,30);
    ui->CloseBtn->setGeometry(432,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&Input::close);//这个牛逼

    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->SaveBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);
    ui->FileBtn->setFocusPolicy(Qt::NoFocus);
    ui->comboBox->setFocusPolicy(Qt::NoFocus);

    //设置combobox的下拉列表内容
    QStringList QList;
    QList.clear();
    QList<<tr("用户表")<<tr("浴缸信息表")<<tr("固化剂产品信息表")<<tr("固化剂消耗标准表")
         <<tr("玻纤产品信息表")<<tr("玻纤消耗标准表")<<tr("树脂产品信息表")<<tr("树脂消耗标准表")
         <<tr("用户操作记录表")<<tr("机器人信息表")<<tr("工作记录表");
    ui->comboBox->clear();
    ui->comboBox->addItems(QList);
    //QComboBox下拉列表不支持直接定义样式，需要在源代码中使用到样式委托对象QStyledItemDelegate
    QStyledItemDelegate * itemDelegate = new QStyledItemDelegate();
    ui->comboBox->setItemDelegate(itemDelegate);




    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QLineEdit{border:none;border-radius:0px;padding:2px 4px;"
                        "selection-background-color: blue;background-color:rgb(244,245,247);"
                        "font-family:'Microsoft YaHei';font-size:15px;}"
                        "QPushButton#CancleBtn{color:black;}"
                        "QPushButton:hover#CancleBtn{background-color:rgb(233,66,66);color:white;}"
                        "QPushButton#SaveBtn{background-color:rgb(76,136,255);}"
                        "QPushButton:pressed#SaveBtn{background-color:rgb(53,95,179);}"
                        "QPushButton#FileBtn{background-color:rgb(241,104,33);}"
                        "QPushButton:hover#FileBtn{background-color:rgb(250,185,91);}"
                        "QPushButton:pressed#FileBtn{background-color:rgb(241,104,33);}");

    ui->comboBox->setStyleSheet("QComboBox{border:1px groove gray;border-radius:0px;\
                                padding:1px 2px 1px 2px;}"
                                "QComboBox::drop-down{subcontrol-origin:padding;\
                                subcontrol-position:top right;width:30px;\
                                border-left-width:1px;border-left-color:darkgray;border-left-style:solid;\
                                border-top-right-radius:0px;border-bottom-right-radius:0px;\
                                image:url(:/image/ICON/arrow-D.png);}"
                                "QComboBox::drop-down:hover{image:url(:/image/ICON/arrow-DP.png);}"
                                "QComboBox::drop-down:pressed{image:url(:/image/ICON/arrow-D.png);}");


    //信号与槽
    connect(ui->FileBtn,SIGNAL(clicked(bool)),this,SLOT(openFile()));
    connect(ui->SaveBtn,SIGNAL(clicked(bool)),this,SLOT(SaveBtnC()));
}

Input::~Input()
{
    delete ui;
}

//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void Input::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void Input::mouseMoveEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果选中了标题范围
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        last = event->globalPos();//更新存储坐标为当前的全局坐标
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}

//···鼠标释放操作···
void Input::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}


void Input::openFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("选择导入的文件"),tr("C:\\"),tr("文本文档(*.txt)"));

    if(fileName == "")//如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
        {
            return;
        }
    else
    {

        ui->FileEdit->setText(fileName);
    }

}

void Input::SaveBtnC()
{
    QString table;
    switch (ui->comboBox->currentIndex()) {
    case 0: table = "users"; break;
    case 1: table = "bathtub"; break;
    case 2: table = "curingagent"; break;
    case 3: table = "curingagentcosting"; break;
    case 4: table = "fiberglass"; break;
    case 5: table = "fiberglasscosting"; break;
    case 6: table = "resin"; break;
    case 7: table = "resincosting"; break;
    case 8: table = "userlogin"; break;
    case 9: table = "robot"; break;
    case 10: table = "workdata"; break;
    default:;break;
    }
    QString data;
    data = QString("load data local infile '%1' into table %2 fields terminated by ',' optionally enclosed by '\"' lines terminated by '\\n';")
            .arg(ui->FileEdit->text()).arg(table);

    qDebug()<<data;
    emit sendData(data);
    ui->FileEdit->clear();
    this->hide();








}

void Input::on_CancleBtn_clicked()
{
    ui->FileEdit->clear();
    this->hide();
}
