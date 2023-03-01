#include "userdele.h"
#include "ui_userdele.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件

UserDele::UserDele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDele)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("删除用户"));//设置软件标题
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
    ui->label->setText(tr("删除用户"));

    ui->UserEdit->setGeometry(130,80,250,30);
    ui->ManRBtn->setGeometry(130,130,90,30);
    ui->NorRBtn->setGeometry(230,130,90,30);
    ui->DeleBtn->setGeometry(370,190,75,30);
    ui->CancleBtn->setGeometry(290,190,75,30);
    ui->CloseBtn->setGeometry(432,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&UserDele::close);//这个牛逼


    ui->NorRBtn->setChecked(true);
    ui->ManRBtn->setEnabled(false);
    ui->NorRBtn->setEnabled(false);
    ui->ManRBtn->setFocusPolicy(Qt::NoFocus);
    ui->NorRBtn->setFocusPolicy(Qt::NoFocus);
    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->DeleBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);
    ui->UserEdit->setFocusPolicy(Qt::NoFocus);



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
                        "QPushButton:hover#CancleBtn{background-color:rgb(76,136,255);color:white;}"
                        "QPushButton#DeleBtn{background-color:rgb(233,66,66);}"
                        "QPushButton:pressed#DeleBtn{background-color:rgb(230,25,25);}");
    //信号与槽
    connect(ui->DeleBtn,SIGNAL(clicked(bool)),this,SLOT(deleBtnC()));


}

UserDele::~UserDele()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void UserDele::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void UserDele::mouseMoveEvent(QMouseEvent *event)
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
void UserDele::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}



void UserDele::deleData(QStringList data)
{
    ui->UserEdit->setText(data.at(0));
    if("管理员" == data.at(1))
    {
        ui->ManRBtn->setChecked(true);
    }else{
        ui->NorRBtn->setChecked(true);
    }
    this->show();
}

void UserDele::deleBtnC()
{
    QString str;
    str = QString("delete from users where UserName = '%1';").arg(ui->UserEdit->text());
    emit sendData(str);
    this->hide();

}

void UserDele::on_CancleBtn_clicked()
{
    this->hide();
}
