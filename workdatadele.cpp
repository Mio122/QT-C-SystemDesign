#include "workdatadele.h"
#include "ui_workdatadele.h"
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件

WorkDataDele::WorkDataDele(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkDataDele)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("删除工作记录信息"));//设置软件标题
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
    ui->label->setText(tr("删除工作记录信息"));


    ui->DeleBtn->setGeometry(460,300,75,30);
    ui->CancleBtn->setGeometry(380,300,75,30);
    ui->CloseBtn->setGeometry(507,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));

    connect(ui->CloseBtn,&QPushButton::clicked,this,&WorkDataDele::close);//这个牛逼



    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->DeleBtn->setFocusPolicy(Qt::NoFocus);
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



    ui->ID->setEnabled(false);
    ui->ResinCos->setEnabled(false);
    ui->RobotID->setEnabled(false);
    ui->FiberGlassCos->setEnabled(false);
    ui->BathTubID->setEnabled(false);
    ui->CurAgCos->setEnabled(false);
    ui->SparyNum->setEnabled(false);
    ui->BathMark->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->timeEdit->setEnabled(false);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());




    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QLineEdit,QDateEdit,QTimeEdit{border:none;border-radius:0px;padding:2px 4px;"
                        "selection-background-color: blue;background-color:rgb(244,245,247);"
                        "font-family:'Microsoft YaHei';font-size:15px;}"
                        "QPushButton#CancleBtn{color:black;}"
                        "QPushButton:hover#CancleBtn{background-color:rgb(76,136,255);color:white;}"
                        "QPushButton#DeleBtn{background-color:rgb(233,66,66);}"
                        "QPushButton:pressed#DeleBtn{background-color:rgb(230,25,25);}");
    //信号与槽
    connect(ui->DeleBtn,SIGNAL(clicked(bool)),this,SLOT(DeleBtnC()));
}

WorkDataDele::~WorkDataDele()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void WorkDataDele::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void WorkDataDele::mouseMoveEvent(QMouseEvent *event)
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
void WorkDataDele::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}



void WorkDataDele::DeleBtnC()
{
    QString str;
    str = QString("delete from workdata where ID = '%1';").arg(ui->ID->text());
    emit sendData(str);
    this->hide();

}

void WorkDataDele::deleData(QStringList data)
{
    QStringList date = data.at(8).split("-");
    int y = date[0].toInt();
    int m = date[1].toInt();
    int d = date[2].toInt();
    QStringList time = data.at(9).split(":");
    int h = time[0].toInt();
    int f = time[1].toInt();
    int s = time[2].toInt();

    ui->ID->setText(data.at(0));
    ui->RobotID->setText(data.at(1));
    ui->BathTubID->setText(data.at(2));
    ui->BathMark->setText(data.at(3));
    ui->SparyNum->setText(data.at(4));
    ui->ResinCos->setText(data.at(5));
    ui->FiberGlassCos->setText(data.at(6));
    ui->CurAgCos->setText(data.at(7));
    ui->dateEdit->setDate(QDate(y,m,d));
    ui->timeEdit->setTime(QTime(h,f,s));

    this->show();


}

void WorkDataDele::on_CancleBtn_clicked()
{
    this->hide();
}
