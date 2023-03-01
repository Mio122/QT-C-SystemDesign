#include "curingsele.h"
#include "ui_curingsele.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件

CuringSele::CuringSele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CuringSele)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("筛选固化剂信息"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(470,240);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,470,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,470,370);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色


    ui->UserLab_1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);



    ui->label->setGeometry(10,0,120,30);
    ui->label->setText(tr("筛选固化剂信息"));


    ui->SeleBtn->setGeometry(370,200,75,30);
    ui->CancleBtn->setGeometry(290,200,75,30);
    ui->CloseBtn->setGeometry(432,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&CuringSele::close);//这个牛逼



    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->SeleBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_1->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_2->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_3->setFocusPolicy(Qt::NoFocus);

    ui->CurAgeID->setFocus();
    setTabOrder(ui->CurAgeID,ui->CurAgeName);
    setTabOrder(ui->CurAgeName,ui->CurAgePrice);






    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
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
}

CuringSele::~CuringSele()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void CuringSele::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void CuringSele::mouseMoveEvent(QMouseEvent *event)
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
void CuringSele::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}


void CuringSele::SeleBtnC()
{
    QStringList str;
    str<<ui->CurAgeID->text()<<ui->CurAgeName->text()<<ui->CurAgePrice->text();
    QStringList data;
    if(str.at(0) != "") data<<QString("CurAgeID = '%1' ").arg(str.at(0));
    if(str.at(1) != "") data<<QString("CurAgeName = '%1' ").arg(str.at(1));
    if(str.at(2) != "") data<<QString("CurAgePrice = %1 ").arg(str.at(2));


    QString splus = "";
    for(int i = 1; i < data.count();i++)
    {
        splus += QString(" and %1").arg(data.at(i));

    }

    if(data.count() == 0)
    {
        splus = "select * from curingagent;";
    }else{
        splus = "select * from curingagent where "+data.at(0)+splus+";";
    }

    //qDebug()<<splus;
    emit sendData(splus);
    ui->CurAgeID->clear();
    ui->CurAgeName->clear();
    ui->CurAgePrice->clear();
    this->hide();

}

void CuringSele::on_CancleBtn_clicked()
{
    ui->CurAgeID->clear();
    ui->CurAgeName->clear();
    ui->CurAgePrice->clear();
    this->hide();
}
