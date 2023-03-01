#include "workdata.h"
#include "ui_workdata.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件

WorkData::WorkData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkData)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("新建工作记录信息"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(545,340);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,545,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,545,370);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色


    ui->UserLab_1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->UserLab_10->setAlignment(Qt::AlignRight|Qt::AlignVCenter);




    ui->label->setGeometry(10,0,200,30);
    ui->label->setText(tr("新建工作记录信息"));


    ui->SaveBtn->setGeometry(460,300,75,30);
    ui->CancleBtn->setGeometry(380,300,75,30);
    ui->CloseBtn->setGeometry(507,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&WorkData::close);//这个牛逼



    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->SaveBtn->setFocusPolicy(Qt::NoFocus);
    ui->CancleBtn->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_1->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_2->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_3->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_4->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_5->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_6->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_7->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_8->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_9->setFocusPolicy(Qt::NoFocus);
    ui->UserLab_10->setFocusPolicy(Qt::NoFocus);


    ui->ID->setFocus();
    setTabOrder(ui->ID,ui->ResinCos);
    setTabOrder(ui->ResinCos,ui->RobotID);
    setTabOrder(ui->RobotID,ui->FiberGlassCos);
    setTabOrder(ui->FiberGlassCos,ui->BathTubID);
    setTabOrder(ui->BathTubID,ui->CurAgCos);
    setTabOrder(ui->CurAgCos,ui->SparyNum);
    setTabOrder(ui->SparyNum,ui->BathMark);
    setTabOrder(ui->BathMark,ui->dateEdit);
    setTabOrder(ui->dateEdit,ui->timeEdit);




    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());




    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QLineEdit,QDateEdit,QTimeEdit{border:none;border-radius:0px;padding:2px 4px;"
                        "selection-background-color: blue;background-color:rgb(244,245,247);"
                        "font-family:'Microsoft YaHei';font-size:15px;}"
                        "QPushButton#CancleBtn{color:black;}"
                        "QPushButton:hover#CancleBtn{background-color:rgb(233,66,66);color:white;}"
                        "QPushButton#SaveBtn{background-color:rgb(76,136,255);}"
                        "QPushButton:pressed#SaveBtn{background-color:rgb(53,95,179);}");
    //信号与槽
    connect(ui->SaveBtn,SIGNAL(clicked(bool)),this,SLOT(SaveBtnC()));
}

WorkData::~WorkData()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void WorkData::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void WorkData::mouseMoveEvent(QMouseEvent *event)
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
void WorkData::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}



void WorkData::SaveBtnC()
{
    QString str;
    str = QString("insert into workdata values(%1,'%2','%3','%4',%5,%6,%7,%8,'%9','%10');")\
            .arg(ui->ID->text()).arg(ui->RobotID->text()).arg(ui->BathTubID->text())\
            .arg(ui->BathMark->text()).arg(ui->SparyNum->text()).arg(ui->ResinCos->text())\
            .arg(ui->FiberGlassCos->text()).arg(ui->CurAgCos->text()).arg(ui->dateEdit->text())\
            .arg(ui->timeEdit->text());
    emit sendData(str);
    ui->ID->clear();
    ui->ResinCos->clear();
    ui->RobotID->clear();
    ui->FiberGlassCos->clear();
    ui->BathTubID->clear();
    ui->CurAgCos->clear();
    ui->SparyNum->clear();
    ui->BathMark->clear();
    this->hide();
}

void WorkData::on_CancleBtn_clicked()
{
    ui->ID->clear();
    ui->ResinCos->clear();
    ui->RobotID->clear();
    ui->FiberGlassCos->clear();
    ui->BathTubID->clear();
    ui->CurAgCos->clear();
    ui->SparyNum->clear();
    ui->BathMark->clear();
    this->hide();
}
