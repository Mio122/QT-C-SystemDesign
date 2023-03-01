#include "report.h"
#include "ui_report.h"
#include <QStyledItemDelegate>
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件
#include <QFileDialog>
#include <QtDebug>
#include <QtPrintSupport/QPrinter>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>
#include <QtGui/QTextBlock>
#include <QFile>
#include <QtCore/QTextStream>

Report::Report(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("导出报表"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    this->setFixedSize(250,286);//设置窗口为固定大小

    ui->TitleLab->setGeometry(0,0,250,30);//设置标题区域位置和大小
    ui->TitleLab->setStyleSheet("QLabel{background-color:rgb(53,65,89);border-top-left-radius:8px;border-top-right-radius:8px;}");//设置标题区域颜色

    ui->InerLab->setGeometry(0,30,250,256);//设置标题区域大小
    ui->InerLab->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");//设置标题区域颜色

    ui->label->setGeometry(10,0,100,30);
    ui->label->setText(tr("导出报表"));



    ui->CloseBtn->setGeometry(212,0,30,30);
    ui->CloseBtn->setIcon(QIcon(":/image/ICON/close2.png"));
    ui->CloseBtn->setToolTip(tr("关闭"));
    ui->MonthBtn->setToolTip(tr("导出某年的月报表"));
    ui->QuarBtn->setToolTip(tr("导出某年的季度报表"));
    ui->YearBtn->setToolTip(tr("导出某年的年度报表"));

    //QComboBox下拉列表不支持直接定义样式，需要在源代码中使用到样式委托对象QStyledItemDelegate
    QStyledItemDelegate * itemDelegate = new QStyledItemDelegate();
    ui->YearCBox->setItemDelegate(itemDelegate);

    connect(ui->CloseBtn,&QPushButton::clicked,this,&Report::close);//这个牛逼

    ui->label->setFocusPolicy(Qt::NoFocus);
    ui->TitleLab->setFocusPolicy(Qt::NoFocus);
    ui->InerLab->setFocusPolicy(Qt::NoFocus);
    ui->CloseBtn->setFocusPolicy(Qt::NoFocus);
    ui->MonthBtn->setFocusPolicy(Qt::NoFocus);
    ui->QuarBtn->setFocusPolicy(Qt::NoFocus);
    ui->YearBtn->setFocusPolicy(Qt::NoFocus);
    ui->YearCBox->setFocusPolicy(Qt::NoFocus);

    this->setStyleSheet("QLabel{font-family:'Microsoft YaHei';font-size:15px;}"
                        "QLabel#label{color:white;}"
                        "QPushButton:hover#CloseBtn{background-color:rgb(233,66,66);}"
                        "QPushButton#MonthBtn{background-color:rgb(79,157,166);}"
                        "QPushButton#QuarBtn{background-color:rgb(35,49,66);}"
                        "QPushButton#YearBtn{background-color:rgb(144,0,72);}"
                        "QPushButton:hover#MonthBtn{background-color:rgb(128,203,211);}"
                        "QPushButton:hover#QuarBtn{background-color:rgb(104,130,161);}"
                        "QPushButton:hover#YearBtn{background-color:rgb(200,50,126);}"
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

    connect(ui->MonthBtn,SIGNAL(clicked(bool)),this,SLOT(MonthBtnC()));
    connect(ui->QuarBtn,SIGNAL(clicked(bool)),this,SLOT(QuarBtnC()));
    connect(ui->YearBtn,SIGNAL(clicked(bool)),this,SLOT(YearBtnC()));





}

Report::~Report()
{
    delete ui;
}


//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void Report::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标

    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void Report::mouseMoveEvent(QMouseEvent *event)
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
void Report::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}

QString Report::SaveFile()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("保存报表"),tr("C:\\"),tr("文档(*.doc)"));

    if(fileName == "")//如果用户直接关闭了文件浏览对话框，那么文件名就为空值，直接返回
        {
            return "";
        }
    else
    {
        return fileName;
    }

}

void Report::MonthBtnC()
{
    QString str = ui->YearCBox->currentText();
    emit MonthReport(str);

}

void Report::QuarBtnC()
{
    QString str = ui->YearCBox->currentText();
    emit QuarReport(str);
}

void Report::YearBtnC()
{
    QString str = ui->YearCBox->currentText();
    emit YearReport(str);
}

void Report::ReportMonth(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    MToReport(arr1,arr2,arr3,arr4,arr5,arr6,arr7);
}

void Report::ReportQuar(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    QToReport(arr1,arr2,arr3,arr4,arr5,arr6,arr7);
}

void Report::ReportYear(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    YToReport(arr1,arr2,arr3,arr4,arr5,arr6,arr7);
}



void Report::MToReport(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    QStringList title;
    title.push_back(QStringLiteral("浴缸品牌"));
    title.push_back(QStringLiteral("产量"));
    title.push_back(QStringLiteral("树脂消耗"));
    title.push_back(QStringLiteral("树脂花费"));
    title.push_back(QStringLiteral("玻纤消耗"));
    title.push_back(QStringLiteral("玻纤花费"));
    title.push_back(QStringLiteral("固化剂消耗"));
    title.push_back(QStringLiteral("固化剂花费"));

    QString html;
    QString t;
    QString A1;

    t = ui->YearCBox->currentText();

    html +="<h2 align=\"center\">"+t+QStringLiteral("月报表")+"</h2>";

    for(int i = 1,p = 0,h=36;i<13;i++)
    {
        html +="<h3 align=\"center\">"+QString("%1月").arg(i)+"</h3>";
        html +="<table width=\"680\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;font-family: Futura, Arial, sans-serif;\" bordercolor=\"gray\">";
        html +="<tr style=\background-color:gray\">";

        for(int i=0;i<title.count();i++)
        {
            html +=QString("<th style=\"background-color: #555;border: 1px solid #777;color: #fff;\">%1</th>").arg(title.at(i));
        }
        html +="</tr>";
        A1 =QStringLiteral("安华小户型浴缸");


        html +=QString("<td>%1</td>").arg(A1);
        html +=QString("<td>%1</td>").arg(arr1[p]);
        html +=QString("<td>%1</td>").arg(arr2[p]);
        html +=QString("<td>%1</td>").arg(arr3[p]);
        html +=QString("<td>%1</td>").arg(arr4[p]);
        html +=QString("<td>%1</td>").arg(arr5[p]);
        html +=QString("<td>%1</td>").arg(arr6[p]);
        html +=QString("<td>%1</td>").arg(arr7[p]);

        html +="</tr>";
        A1 =QStringLiteral("箭牌卫浴");
        p++;

        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(A1);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr1[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr2[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr3[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr4[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr5[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr6[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr7[p]);

        html +="</tr>";
        A1 =QStringLiteral("沃特玛按摩浴缸");
        p++;

        html +=QString("<td>%1</td>").arg(A1);
        html +=QString("<td>%1</td>").arg(arr1[p]);
        html +=QString("<td>%1</td>").arg(arr2[p]);
        html +=QString("<td>%1</td>").arg(arr3[p]);
        html +=QString("<td>%1</td>").arg(arr4[p]);
        html +=QString("<td>%1</td>").arg(arr5[p]);
        html +=QString("<td>%1</td>").arg(arr6[p]);
        html +=QString("<td>%1</td>").arg(arr7[p]);
        p++;

        html +="</tr>";
        A1 =QStringLiteral("合计");

        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(A1);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr1[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr2[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr3[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr4[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr5[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr6[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr7[h]);
        h++;


        html +="</table>";
    }

    //=================html转成word=============================
    QString address;
    address = SaveFile();
    qDebug()<<address;
    QFile outFile(address);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append );
    QTextStream ts(&outFile);
    ts.setCodec("utf-8");
    ts<<html<<endl;


}

void Report::QToReport(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    QStringList title;
    title.push_back(QStringLiteral("浴缸品牌"));
    title.push_back(QStringLiteral("产量"));
    title.push_back(QStringLiteral("树脂消耗"));
    title.push_back(QStringLiteral("树脂花费"));
    title.push_back(QStringLiteral("玻纤消耗"));
    title.push_back(QStringLiteral("玻纤花费"));
    title.push_back(QStringLiteral("固化剂消耗"));
    title.push_back(QStringLiteral("固化剂花费"));

    QString html;
    QString t;
    QString A1;

    t = ui->YearCBox->currentText();

    html +="<h2 align=\"center\">"+t+QStringLiteral("季度报表")+"</h2>";

    for(int i = 1,p = 0,h=12;i<5;i++)
    {
        html +="<h3 align=\"center\">"+QString("第%1季度").arg(i)+"</h3>";
        html +="<table width=\"680\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;font-family: Futura, Arial, sans-serif;\" bordercolor=\"gray\">";
        html +="<tr style=\background-color:gray\">";

        for(int i=0;i<title.count();i++)
        {
            html +=QString("<th style=\"background-color: #555;border: 1px solid #777;color: #fff;\">%1</th>").arg(title.at(i));
        }
        html +="</tr>";
        A1 =QStringLiteral("安华小户型浴缸");


        html +=QString("<td>%1</td>").arg(A1);
        html +=QString("<td>%1</td>").arg(arr1[p]);
        html +=QString("<td>%1</td>").arg(arr2[p]);
        html +=QString("<td>%1</td>").arg(arr3[p]);
        html +=QString("<td>%1</td>").arg(arr4[p]);
        html +=QString("<td>%1</td>").arg(arr5[p]);
        html +=QString("<td>%1</td>").arg(arr6[p]);
        html +=QString("<td>%1</td>").arg(arr7[p]);

        html +="</tr>";
        A1 =QStringLiteral("箭牌卫浴");
        p++;

        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(A1);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr1[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr2[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr3[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr4[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr5[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr6[p]);
        html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr7[p]);

        html +="</tr>";
        A1 =QStringLiteral("沃特玛按摩浴缸");
        p++;

        html +=QString("<td>%1</td>").arg(A1);
        html +=QString("<td>%1</td>").arg(arr1[p]);
        html +=QString("<td>%1</td>").arg(arr2[p]);
        html +=QString("<td>%1</td>").arg(arr3[p]);
        html +=QString("<td>%1</td>").arg(arr4[p]);
        html +=QString("<td>%1</td>").arg(arr5[p]);
        html +=QString("<td>%1</td>").arg(arr6[p]);
        html +=QString("<td>%1</td>").arg(arr7[p]);
        p++;

        html +="</tr>";
        A1 =QStringLiteral("合计");

        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(A1);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr1[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr2[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr3[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr4[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr5[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr6[h]);
        html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr7[h]);
        h++;


        html +="</table>";

       }
    //=================html转成word=============================
    QString address;
    address = SaveFile();
    qDebug()<<address;
    QFile outFile(address);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append );
    QTextStream ts(&outFile);
    ts.setCodec("utf-8");
    ts<<html<<endl;
}

void Report::YToReport(QVector<double> arr1, QVector<double> arr2, QVector<double> arr3, QVector<double> arr4, QVector<double> arr5, QVector<double> arr6, QVector<double> arr7)
{
    QStringList title;
    title.push_back(QStringLiteral("浴缸品牌"));
    title.push_back(QStringLiteral("产量"));
    title.push_back(QStringLiteral("树脂消耗"));
    title.push_back(QStringLiteral("树脂花费"));
    title.push_back(QStringLiteral("玻纤消耗"));
    title.push_back(QStringLiteral("玻纤花费"));
    title.push_back(QStringLiteral("固化剂消耗"));
    title.push_back(QStringLiteral("固化剂花费"));

    QString html;
    QString t;
    QString A1;

    t = ui->YearCBox->currentText();

    html +="<h2 align=\"center\">"+t+QStringLiteral("年度报表")+"</h2>";

    html +="<table width=\"680\" border=\"1\" align=\"center\" style=\"border-collapse:collapse;font-family: Futura, Arial, sans-serif;\" bordercolor=\"gray\">";
    html +="<tr style=\background-color:gray\">";

    for(int i=0;i<title.count();i++)
    {
        html +=QString("<th style=\"background-color: #555;border: 1px solid #777;color: #fff;\">%1</th>").arg(title.at(i));
    }
    html +="</tr>";
    A1 =QStringLiteral("安华小户型浴缸");


    html +=QString("<td>%1</td>").arg(A1);
    html +=QString("<td>%1</td>").arg(arr1[0]);
    html +=QString("<td>%1</td>").arg(arr2[0]);
    html +=QString("<td>%1</td>").arg(arr3[0]);
    html +=QString("<td>%1</td>").arg(arr4[0]);
    html +=QString("<td>%1</td>").arg(arr5[0]);
    html +=QString("<td>%1</td>").arg(arr6[0]);
    html +=QString("<td>%1</td>").arg(arr7[0]);

    html +="</tr>";
    A1 =QStringLiteral("箭牌卫浴");

    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(A1);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr1[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr2[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr3[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr4[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr5[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr6[1]);
    html +=QString("<td style=\"background-color: #ccc;\">%1</td>").arg(arr7[1]);

    html +="</tr>";
    A1 =QStringLiteral("沃特玛按摩浴缸");

    html +=QString("<td>%1</td>").arg(A1);
    html +=QString("<td>%1</td>").arg(arr1[2]);
    html +=QString("<td>%1</td>").arg(arr2[2]);
    html +=QString("<td>%1</td>").arg(arr3[2]);
    html +=QString("<td>%1</td>").arg(arr4[2]);
    html +=QString("<td>%1</td>").arg(arr5[2]);
    html +=QString("<td>%1</td>").arg(arr6[2]);
    html +=QString("<td>%1</td>").arg(arr7[2]);

    html +="</tr>";
    A1 =QStringLiteral("合计");

    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(A1);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr1[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr2[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr3[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr4[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr5[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr6[3]);
    html +=QString("<td style=\"background-color: #8158fc;\">%1</td>").arg(arr7[3]);


    html +="</table>";


    //=================html转成word=============================
    QString address;
    address = SaveFile();
    qDebug()<<address;
    QFile outFile(address);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append );
    QTextStream ts(&outFile);
    ts.setCodec("utf-8");
    ts<<html<<endl;

}

