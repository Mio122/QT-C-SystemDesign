#include "echarts.h"
#include "ui_echarts.h"

#include "cJSON.h"

#include <QStyledItemDelegate>
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件
#include <QtDebug>

ECharts::ECharts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ECharts)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("折线/柱状图"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(870,590);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,870,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,870,560);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色

    ui->label->setGeometry(10,0,100,30);
    ui->label->setText(tr("折线/柱状图"));
    ui->webView->setGeometry(0,30,870,450);



    ui->CloseBtn->setGeometry(832,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));
    ui->DayBtn->setToolTip(tr("查询某年某月的每日信息"));
    ui->WeekBtn->setToolTip(tr("查询某年某月的每周信息"));
    ui->MonthBtn->setToolTip(tr("查询某年的每月信息"));
    ui->QuarBtn->setToolTip(tr("查询某年的每个季度信息"));
    ui->YearBtn->setToolTip(tr("查询每年的信息"));

    //QComboBox下拉列表不支持直接定义样式，需要在源代码中使用到样式委托对象QStyledItemDelegate
    QStyledItemDelegate * itemDelegate = new QStyledItemDelegate();
    ui->YearCBox->setItemDelegate(itemDelegate);
    ui->MonthCBox->setItemDelegate(itemDelegate);
    ui->TypeCBox->setItemDelegate(itemDelegate);



    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->DayBtn->setFocusPolicy(Qt::NoFocus);
    ui->WeekBtn->setFocusPolicy(Qt::NoFocus);
    ui->MonthBtn->setFocusPolicy(Qt::NoFocus);
    ui->QuarBtn->setFocusPolicy(Qt::NoFocus);
    ui->YearBtn->setFocusPolicy(Qt::NoFocus);
    ui->YearCBox->setFocusPolicy(Qt::NoFocus);
    ui->MonthCBox->setFocusPolicy(Qt::NoFocus);
    ui->TypeCBox->setFocusPolicy(Qt::NoFocus);

    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QPushButton#DayBtn{background-color:rgb(255,89,89);}"
                        "QPushButton#WeekBtn{background-color:rgb(151,100,199);}"
                        "QPushButton#MonthBtn{background-color:rgb(79,157,166);}"
                        "QPushButton#QuarBtn{background-color:rgb(35,49,66);}"
                        "QPushButton#YearBtn{background-color:rgb(144,0,72);}"
                        "QPushButton:hover#DayBtn{background-color:rgb(255,131,131);}"
                        "QPushButton:hover#WeekBtn{background-color:rgb(185,142,227);}"
                        "QPushButton:hover#MonthBtn{background-color:rgb(128,203,211);}"
                        "QPushButton:hover#QuarBtn{background-color:rgb(104,130,161);}"
                        "QPushButton:hover#YearBtn{background-color:rgb(200,50,126);}"
                        "QPushButton:pressed#DayBtn{background-color:rgb(255,89,89);}"
                        "QPushButton:pressed#WeekBtn{background-color:rgb(151,100,199);}"
                        "QPushButton:pressed#MonthBtn{background-color:rgb(79,157,166);}"
                        "QPushButton:pressed#QuarBtn{background-color:rgb(35,49,66);}"
                        "QPushButton:pressed#YearBtn{background-color:rgb(144,0,72);}"
                        );
    ui->YearCBox->setStyleSheet("QComboBox{border:1px groove gray;border-radius:0px;\
                                padding:1px 2px 1px 2px;}"
                                "QComboBox::drop-down{subcontrol-origin:padding;\
                                subcontrol-position:top right;width:30px;\
                                border-left-width:1px;border-left-color:darkgray;border-left-style:solid;\
                                border-top-right-radius:0px;border-bottom-right-radius:0px;\
                                image:url(:/image/ICON/arrow-D.png);}"
                                "QComboBox::drop-down:hover{image:url(:/image/ICON/arrow-DP.png);}"
                                "QComboBox::drop-down:pressed{image:url(:/image/ICON/arrow-D.png);}");
    ui->MonthCBox->setStyleSheet("QComboBox{border:1px groove gray;border-radius:0px;\
                                padding:1px 2px 1px 2px;}"
                                "QComboBox::drop-down{subcontrol-origin:padding;\
                                subcontrol-position:top right;width:30px;\
                                border-left-width:1px;border-left-color:darkgray;border-left-style:solid;\
                                border-top-right-radius:0px;border-bottom-right-radius:0px;\
                                image:url(:/image/ICON/arrow-D.png);}"
                                "QComboBox::drop-down:hover{image:url(:/image/ICON/arrow-DP.png);}"
                                "QComboBox::drop-down:pressed{image:url(:/image/ICON/arrow-D.png);}");
    ui->TypeCBox->setStyleSheet("QComboBox{border:1px groove gray;border-radius:0px;\
                                padding:1px 2px 1px 2px;}"
                                "QComboBox::drop-down{subcontrol-origin:padding;\
                                subcontrol-position:top right;width:30px;\
                                border-left-width:1px;border-left-color:darkgray;border-left-style:solid;\
                                border-top-right-radius:0px;border-bottom-right-radius:0px;\
                                image:url(:/image/ICON/arrow-D.png);}"
                                "QComboBox::drop-down:hover{image:url(:/image/ICON/arrow-DP.png);}"
                                "QComboBox::drop-down:pressed{image:url(:/image/ICON/arrow-D.png);}");



    //信号与槽
    connect(ui->DayBtn,SIGNAL(clicked(bool)),this,SLOT(DayBtnC()));
    connect(ui->WeekBtn,SIGNAL(clicked(bool)),this,SLOT(WeekBtnC()));
    connect(ui->MonthBtn,SIGNAL(clicked(bool)),this,SLOT(MonthBtnC()));
    connect(ui->QuarBtn,SIGNAL(clicked(bool)),this,SLOT(QuarBtn()));
    connect(ui->YearBtn,SIGNAL(clicked(bool)),this,SLOT(YearBtnC()));
    connect(ui->CloseBtn,SIGNAL(clicked(bool)),this,SLOT(closeEcharts()));//这个牛逼



    connect(ui->webView,SIGNAL(loadFinished(bool)),this,SLOT(slot()));










}

ECharts::~ECharts()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void ECharts::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void ECharts::mouseMoveEvent(QMouseEvent *event)
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
void ECharts::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}

void ECharts::DayBtnC()
{
    flag = 1;
    ui->webView->load(QUrl::fromLocalFile("E:/AABiYeSheJi/Qt/Database/html/day.html"));
}

void ECharts::WeekBtnC()
{
    flag = 2;
    ui->webView->load(QUrl::fromLocalFile("E:/AABiYeSheJi/Qt/Database/html/week.html"));



}

void ECharts::MonthBtnC()
{
    flag = 3;
    ui->webView->load(QUrl::fromLocalFile("E:/AABiYeSheJi/Qt/Database/html/month.html"));

}

void ECharts::QuarBtn()
{
    flag = 4;
    ui->webView->load(QUrl::fromLocalFile("E:/AABiYeSheJi/Qt/Database/html/quarter.html"));
}

void ECharts::YearBtnC()
{

    flag = 5;
    ui->webView->load(QUrl::fromLocalFile("E:/AABiYeSheJi/Qt/Database/html/year.html"));


}

void ECharts::slot()
{
    switch (flag) {
    case 1:
    {
        int a,b,c;
        QStringList str;
        str.clear();
        a = ui->YearCBox->currentIndex();
        b = ui->MonthCBox->currentIndex();
        c = ui->TypeCBox->currentIndex();
        switch (a) {
        case 0: str<<"2018";break;
        case 1: str<<"2019";break;
        default:;break;
        }
        switch (b) {
        case 0:str<<"01";break;
        case 1:str<<"02";break;
        case 2:str<<"03";break;
        case 3:str<<"04";break;
        case 4:str<<"05";break;
        case 5:str<<"06";break;
        case 6:str<<"07";break;
        case 7:str<<"08";break;
        case 8:str<<"09";break;
        case 9:str<<"10";break;
        case 10:str<<"11";break;
        case 11:str<<"12";break;
        default:;break;

        }
        switch (c) {
        case 0:str<<"bath";break;
        case 1:str<<"cos";break;
        case 2:str<<"price";break;
        default:;break;

        }

        emit sendDataDay(str);
        qDebug()<<str;
    }break;
    case 2:
    {
        int a,b,c;
        QStringList str;
        str.clear();
        a = ui->YearCBox->currentIndex();
        b = ui->MonthCBox->currentIndex();
        c = ui->TypeCBox->currentIndex();
        switch (a) {
        case 0: str<<"2018";break;
        case 1: str<<"2019";break;
        default:;break;
        }
        switch (b) {
        case 0:str<<"01";break;
        case 1:str<<"02";break;
        case 2:str<<"03";break;
        case 3:str<<"04";break;
        case 4:str<<"05";break;
        case 5:str<<"06";break;
        case 6:str<<"07";break;
        case 7:str<<"08";break;
        case 8:str<<"09";break;
        case 9:str<<"10";break;
        case 10:str<<"11";break;
        case 11:str<<"12";break;
        default:;break;

        }
        switch (c) {
        case 0:str<<"bath";break;
        case 1:str<<"cos";break;
        case 2:str<<"price";break;
        default:;break;

        }
        emit sendDataWeek(str);
        qDebug()<<str;

    }break;
    case 3:
    {

        int a,c;
        QStringList str;
        str.clear();
        a = ui->YearCBox->currentIndex();
        c = ui->TypeCBox->currentIndex();
        switch (a) {
        case 0: str<<"2018";break;
        case 1: str<<"2019";break;
        default:;break;
        }

        switch (c) {
        case 0:str<<"bath";break;
        case 1:str<<"cos";break;
        case 2:str<<"price";break;
        default:;break;

        }
        emit sendDataMonth(str);
        qDebug()<<str;

    }break;
    case 4:
    {
        int a,c;
        QStringList str;
        str.clear();
        a = ui->YearCBox->currentIndex();
        c = ui->TypeCBox->currentIndex();
        switch (a) {
        case 0: str<<"2018";break;
        case 1: str<<"2019";break;
        default:;break;
        }

        switch (c) {
        case 0:str<<"bath";break;
        case 1:str<<"cos";break;
        case 2:str<<"price";break;
        default:;break;

        }
        emit sendDataQuar(str);
        qDebug()<<str;

    }break;
    case 5:
    {
        int a,c;
        QStringList str;
        str.clear();
        a = ui->YearCBox->currentIndex();
        c = ui->TypeCBox->currentIndex();
        switch (a) {
        case 0: str<<"2018";break;
        case 1: str<<"2019";break;
        default:;break;
        }

        switch (c) {
        case 0:str<<"bath";break;
        case 1:str<<"cos";break;
        case 2:str<<"price";break;
        default:;break;

        }
        emit sendDataYear(str);
        qDebug()<<str;

    }break;
    default:;break;

    }

}

void ECharts::closeEcharts()
{
    ui->webView->load(QUrl::fromLocalFile(""));
    this->hide();
}



void ECharts::EchartDay(QVector<double> arr1,QVector<double> arr2,QVector<double> arr3)
{
    cJSON *root;
    char *out;
    double P1[31];
    double P2[31];
    double P3[31];
    root=cJSON_CreateObject();
    for(int i=0;i<31;i++){
        P1[i]=arr1[i];
        P2[i]=arr2[i];
        P3[i]=arr3[i];
    }

    cJSON_AddItemToObject(root, "value", cJSON_CreateDoubleArray(P1, 31));
    cJSON_AddItemToObject(root, "value2", cJSON_CreateDoubleArray(P2, 31));
    cJSON_AddItemToObject(root, "value3", cJSON_CreateDoubleArray(P3, 31));

    if(ui->TypeCBox->currentIndex()==0){
        const char *legend[3] = { "安华小户型浴缸", "箭牌卫浴", "沃特玛按摩浴缸" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }else {
        const char *legend[3] = { "树脂", "玻纤", "固化剂" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }



    out=cJSON_Print(root);
    cJSON_Minify(out);
    QString str = QString(out);
    free(out);//注意：这个千万别忘记，网上的很多人的资料把这个忘记了，造成内存泄漏
    cJSON_Delete(root);

    str.replace(QRegExp("\""), "\\\"");

    QString strVal = QString("showhello(\"%1\");").arg(str);

    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);

}

void ECharts::EchartWeek(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3)
{
    cJSON *root;
    char *out;
    double P1[6];
    double P2[6];
    double P3[6];
    root=cJSON_CreateObject();
    for(int i=0;i<6;i++){
        P1[i]=arr1[i];
        P2[i]=arr2[i];
        P3[i]=arr3[i];
    }

    cJSON_AddItemToObject(root, "value", cJSON_CreateDoubleArray(P1, 6));
    cJSON_AddItemToObject(root, "value2", cJSON_CreateDoubleArray(P2, 6));
    cJSON_AddItemToObject(root, "value3", cJSON_CreateDoubleArray(P3, 6));

    if(ui->TypeCBox->currentIndex()==0){
        const char *legend[3] = { "安华小户型浴缸", "箭牌卫浴", "沃特玛按摩浴缸" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }else {
        const char *legend[3] = { "树脂", "玻纤", "固化剂" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }



    out=cJSON_Print(root);
    cJSON_Minify(out);
    QString str = QString(out);
    free(out);//注意：这个千万别忘记，网上的很多人的资料把这个忘记了，造成内存泄漏
    cJSON_Delete(root);

    str.replace(QRegExp("\""), "\\\"");

    QString strVal = QString("showhello(\"%1\");").arg(str);

    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);

}

void ECharts::EchartMonth(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3)
{
    cJSON *root;
    char *out;
    double P1[12];
    double P2[12];
    double P3[12];
    root=cJSON_CreateObject();
    for(int i=0;i<12;i++){
        P1[i]=arr1[i];
        P2[i]=arr2[i];
        P3[i]=arr3[i];
    }

    cJSON_AddItemToObject(root, "value", cJSON_CreateDoubleArray(P1, 12));
    cJSON_AddItemToObject(root, "value2", cJSON_CreateDoubleArray(P2, 12));
    cJSON_AddItemToObject(root, "value3", cJSON_CreateDoubleArray(P3, 12));

    if(ui->TypeCBox->currentIndex()==0){
        const char *legend[3] = { "安华小户型浴缸", "箭牌卫浴", "沃特玛按摩浴缸" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }else {
        const char *legend[3] = { "树脂", "玻纤", "固化剂" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }



    out=cJSON_Print(root);
    cJSON_Minify(out);
    QString str = QString(out);
    free(out);//注意：这个千万别忘记，网上的很多人的资料把这个忘记了，造成内存泄漏
    cJSON_Delete(root);

    str.replace(QRegExp("\""), "\\\"");

    QString strVal = QString("showhello(\"%1\");").arg(str);

    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);

}

void ECharts::EchartQuar(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3)
{
    cJSON *root;
    char *out;
    double P1[4];
    double P2[4];
    double P3[4];
    root=cJSON_CreateObject();
    for(int i=0;i<4;i++){
        P1[i]=arr1[i];
        P2[i]=arr2[i];
        P3[i]=arr3[i];
    }

    cJSON_AddItemToObject(root, "value", cJSON_CreateDoubleArray(P1, 4));
    cJSON_AddItemToObject(root, "value2", cJSON_CreateDoubleArray(P2, 4));
    cJSON_AddItemToObject(root, "value3", cJSON_CreateDoubleArray(P3, 4));

    if(ui->TypeCBox->currentIndex()==0){
        const char *legend[3] = { "安华小户型浴缸", "箭牌卫浴", "沃特玛按摩浴缸" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }else {
        const char *legend[3] = { "树脂", "玻纤", "固化剂" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }



    out=cJSON_Print(root);
    cJSON_Minify(out);
    QString str = QString(out);
    free(out);//注意：这个千万别忘记，网上的很多人的资料把这个忘记了，造成内存泄漏
    cJSON_Delete(root);

    str.replace(QRegExp("\""), "\\\"");

    QString strVal = QString("showhello(\"%1\");").arg(str);

    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);

}

void ECharts::EchartYear(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3)
{
    cJSON *root;
    char *out;
    double P1[2];
    double P2[2];
    double P3[2];
    root=cJSON_CreateObject();
    for(int i=0;i<2;i++){
        P1[i]=arr1[i];
        P2[i]=arr2[i];
        P3[i]=arr3[i];
    }

    cJSON_AddItemToObject(root, "value", cJSON_CreateDoubleArray(P1, 2));
    cJSON_AddItemToObject(root, "value2", cJSON_CreateDoubleArray(P2, 2));
    cJSON_AddItemToObject(root, "value3", cJSON_CreateDoubleArray(P3, 2));

    if(ui->TypeCBox->currentIndex()==0){
        const char *legend[3] = { "安华小户型浴缸", "箭牌卫浴", "沃特玛按摩浴缸" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }else {
        const char *legend[3] = { "树脂", "玻纤", "固化剂" };
        cJSON_AddItemToObject(root, "legend", cJSON_CreateStringArray(legend, 3));
    }



    out=cJSON_Print(root);
    cJSON_Minify(out);
    QString str = QString(out);
    free(out);//注意：这个千万别忘记，网上的很多人的资料把这个忘记了，造成内存泄漏
    cJSON_Delete(root);

    str.replace(QRegExp("\""), "\\\"");

    QString strVal = QString("showhello(\"%1\");").arg(str);

    ui->webView->page()->mainFrame()->evaluateJavaScript(strVal);

}
