#include "usersele.h"
#include "ui_usersele.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件

UserSele::UserSele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSele)
{
    ui->setupUi(this);
    spe = false;

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("查找用户"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(470,235);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,470,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,470,360);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色

    ui->UserLab->setGeometry(50,80,80,30);
    ui->UserLab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab->setText(tr("用户名："));
    ui->AccountLab->setGeometry(50,130,80,30);
    ui->AccountLab->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->AccountLab->setText(tr("账户类型："));

    ui->label->setGeometry(10,0,80,30);
    ui->label->setText(tr("查找用户"));

    ui->UserEdit->setGeometry(130,80,250,30);
    ui->ManRBtn->setGeometry(130,130,90,30);
    ui->NorRBtn->setGeometry(220,130,90,30);
    ui->AllRBtn->setGeometry(330,130,90,30);
    ui->SeleBtn->setGeometry(370,190,75,30);
    ui->CancleBtn->setGeometry(290,190,75,30);
    ui->CloseBtn->setGeometry(432,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&UserSele::close);//这个牛逼


    ui->AllRBtn->setChecked(true);
    ui->ManRBtn->setFocusPolicy(Qt::NoFocus);
    ui->NorRBtn->setFocusPolicy(Qt::NoFocus);
    ui->AllRBtn->setFocusPolicy(Qt::NoFocus);
    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->SeleBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);






    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QRadioButton{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QRadioButton:indicator{width:15px;height:15px;}"
                        "QRadioButton:indicator:unchecked{image: url(:/image/ICON/unchecked.png);}"
                        "QRadioButton:indicator:checked{image: url(:/image/ICON/checked.png);}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QLineEdit{border:none;border-radius:0px;padding:2px 4px;"
                        "selection-background-color: blue;background-color:rgb(244,245,247);"
                        "font-family:'Microsoft YaHei';font-size:15px;}"
                        "QPushButton#CancleBtn{color:black;}"
                        "QPushButton:hover#CancleBtn{background-color:rgb(233,66,66);color:white;}"
                        "QPushButton#SeleBtn{background-color:rgb(76,136,255);}"
                        "QPushButton:pressed#SeleBtn{background-color:rgb(53,95,179);}");
    //信号与槽
    connect(ui->SeleBtn,SIGNAL(clicked(bool)),this,SLOT(SeleBtnC()));
    connect(ui->ManRBtn,SIGNAL(toggled(bool)),this,SLOT(Special()));
    connect(ui->NorRBtn,SIGNAL(toggled(bool)),this,SLOT(Special0()));
    connect(ui->AllRBtn,SIGNAL(toggled(bool)),this,SLOT(Special00()));
}

UserSele::~UserSele()
{
    delete ui;
}



//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void UserSele::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void UserSele::mouseMoveEvent(QMouseEvent *event)
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
void UserSele::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}


void UserSele::SeleBtnC()
{
    QString str;
    bool user = true;
    if("" == ui->UserEdit->text()){
        user = false;
    }
    if(user){
        if(spe){
            str = QString("select * from users where UserName = '%1' and AccountType = '%2';").arg(ui->UserEdit->text()).arg(type);
        }else{
            str = QString("select * from users where UserName = '%1';").arg(ui->UserEdit->text());
        }
    }else{
        if(spe){
            str = QString("select * from users where AccountType = '%1';").arg(type);
        }else{
            str = QString("select * from users ;");
        }
    }
    emit sendData(str);
    ui->UserEdit->clear();
    this->hide();

}

void UserSele::Special()
{
    spe = true;
    type = "管理员";
}

void UserSele::Special0()
{
    spe = true;
    type = "普通用户";
}

void UserSele::Special00()
{
    spe = false;
}


void UserSele::on_CancleBtn_clicked()
{
    ui->UserEdit->clear();
    this->hide();
}
