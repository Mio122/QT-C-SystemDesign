#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件
#include <QFileDialog>
#include <QtDebug>

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("软件设置"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(470,240);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,470,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,470,360);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色

    ui->UserLab->setGeometry(20,80,140,30);
    ui->UserLab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);



    ui->label->setGeometry(10,0,80,30);
    ui->label->setText(tr("软件设置"));

    ui->FileEdit->setGeometry(160,80,200,30);

    ui->FileBtn->setGeometry(370,80,60,30);


    ui->SaveBtn->setGeometry(370,200,75,30);
    ui->CancleBtn->setGeometry(290,200,75,30);
    ui->CloseBtn->setGeometry(432,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&Setting::close);//这个牛逼

    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->SaveBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);
    ui->FileBtn->setFocusPolicy(Qt::NoFocus);

    ui->FileEdit->setText(MainWindow::UserLoginAddre);

    connect(ui->FileBtn,SIGNAL(clicked(bool)),this,SLOT(openFile()));



    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QLineEdit{border:none;border-radius:0px;padding:2px 4px;"
                        "selection-background-color: blue;background-color:rgb(244,245,247);"
                        "font-family:'Microsoft YaHei';font-size:15px;}"
                        "QPushButton#CancleBtn{color:black;}"
                        "QPushButton:hover#CancleBtn{background-color:rgb(233,66,66);color:white;}"
                        "QPushButton#SaveBtn{background-color:rgb(76,136,255);}"
                        "QPushButton#SureBtn{background-color:rgb(76,136,255);}"
                        "QPushButton:pressed#SaveBtn{background-color:rgb(53,95,179);}"
                        "QPushButton#FileBtn{background-color:rgb(241,104,33);}"
                        "QPushButton:hover#FileBtn{background-color:rgb(250,185,91);}"
                        "QPushButton:pressed#FileBtn{background-color:rgb(241,104,33);}"
                        "QPushButton#FileBtn_2{background-color:rgb(241,104,33);}"
                        "QPushButton:hover#FileBtn_2{background-color:rgb(250,185,91);}"
                        "QPushButton:pressed#FileBtn_2{background-color:rgb(241,104,33);}");
}

Setting::~Setting()
{
    delete ui;
}

//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void Setting::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void Setting::mouseMoveEvent(QMouseEvent *event)
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
void Setting::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}

void Setting::openFile()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("选择保存的文件路径"),tr("C:\\"),tr("文本文档(*.txt)"));

    if(fileName == "")//如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
        {
            return;
        }
    else
    {

        ui->FileEdit->setText(fileName);
    }

}



void Setting::on_SaveBtn_clicked()
{
    MainWindow::UserLoginAddre = ui->FileEdit->text();
    QString str = QString("Update userlogin set fileaddre = '%1' where ID = %2;").arg(MainWindow::UserLoginAddre).arg(MainWindow::ID);
    emit sendData(str);
    this->hide();

}

void Setting::on_CancleBtn_clicked()
{
    ui->FileEdit->setText(MainWindow::UserLoginAddre);
    this->hide();
}
