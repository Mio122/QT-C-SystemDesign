#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QMouseEvent>//用到QMouseEvent就要包含这个头文件
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QVector>
#include <QFile>
#include <QSettings>


int MainWindow::Mark = 0;
QString MainWindow::Table;
QStringList MainWindow::UserInfo;
bool MainWindow::userType = false;
QString MainWindow::UserLogin ="";
QString MainWindow::UserLoginAddre = "E:/AABiYeSheJi/userlogin.txt";
int MainWindow::ID;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isRun = false;




/*连接MySQL数据库*/
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");//连接数据库主机名，如果"127.0.0.1"不行，就使用"localhost"
    db.setPort(3366);//连接数据库端口号3366
    db.setDatabaseName("newdesign");//连接数据库名new
    db.setUserName("root");//数据库用户名root
    db.setPassword("2019");//数据库密码2019
    bool ok = db.open();//打开数据库


    if(!ok)
    {
        //qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        QApplication::beep();//发出警报声
        return;
    }
    else
    {
        //qDebug()<<"连接成功"<<"connect to mysql successful";

    }


/*各个子界面的初始化*/
    LoginWin = new DatabaseLogin;
    LoginWin->show();

    UserWin = new FormUser;
    TableWin = new FormTable;
    InputWin = new FormInput;
    ExitWin = new FormExit;

    NewUser = new UserNew;    
    EditUser = new UserEdit;
    DeleUser = new UserDele;
    SeleUser = new UserSele;
    SqlWin = new SQLSear;
    ChanUser = new UserChan;
    BathTab = new TableBath;
    EditBathTab = new TableBathEdit;
    DeleBathTab = new TableBathDele;
    SeleBatnTab = new TableBathSele;
    NewCuring = new CuringNew;
    EditCuring = new CuringEdit;
    DeleCuring = new CuringDele;
    SeleCuring = new CuringSele;
    NewResin = new ResinNew;
    EditResin = new ResinEdit;
    DeleResin = new ResinDele;
    SeleResin = new ResinSele;
    NewFiber = new FiberNew;
    EditFiber = new FiberEdit;
    DeleFiber = new FiberDele;
    SeleFiber = new FiberSele;
    NewResinCos = new ResinCosNew;
    EditResinCos = new ResinCosEdit;
    DeleResinCos = new ResinCosDele;
    SeleResinCos = new ResinCosSele;
    NewCuringCos = new CuringCosNew;
    EditCuringCos = new CuringCosEdit;
    DeleCuringCos = new CuringCosDele;
    SeleCuringCos = new CuringCosSele;
    NewFiberCos = new FiberCosNew;
    EditFiberCos = new FiberCosEdit;
    DeleFiberCos = new FiberCosDele;
    SeleFiberCos = new FiberCosSele;
    DeleUserLog = new UserLogDele;
    SeleUserLog = new UserLogSele;
    NewRobot = new RobotNew;
    EditRobot = new RobotEdit;
    DeleRobot = new RobotDele;
    SeleRobot = new RobotSele;
    DataWork = new WorkData;
    EditWorkData = new WorkDataEdit;
    DeleWorkData = new WorkDataDele;
    SeleWorkData = new WorkDataSele;
    InputData = new Input;
    OutputData = new OutPut;
    Echarts = new ECharts;
    report = new Report;
    Set = new Setting;




    clientRect = QApplication::desktop()->availableGeometry(); //用户可用窗口大小【这个很强】


    setWindowIcon(QIcon(":/image/ICON/engineer.png"));//设置软件图标
    setWindowTitle(tr("物料消耗管理软件"));//设置软件标题
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    //this->setFixedSize(1000,618);//设置窗口为固定大小
    this->resize(QSize(1000,618));

    ui->label->setGeometry(0,0,clientRect.width(),30);//设置标题区域大小
    ui->label->setStyleSheet("background-color:rgb(28,102,220)");//设置标题区域颜色

    ui->label_2->setGeometry(10,0,300,30);
    ui->label_2->setStyleSheet("color:rgb(255,255,255);font-family:'Microsoft YaHei';font-size:14px;");


    ui->closeButton->setGeometry(1000-30,0,30,30);//设置按钮位置和大小
    ui->closeButton->setToolTip(tr("关闭"));//设置鼠标放上去后的文字提示
    QIcon close_icon(":/image/ICON/close2.png");//设置按钮图标所在位置
    ui->closeButton->setIcon(close_icon);//添加按钮图标


    ui->closeButton->setFlat(true);//设置按钮背景透明
    connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(windowClosed()));//连接按钮信号与槽，使点击后关闭窗口
    connect(ExitWin,SIGNAL(ExitApp()),this,SLOT(windowClosed()));
    ui->closeButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/ICON/red1.png);}");//设置鼠标滑过颜色变化



    ui->minButton->setGeometry(1000-90,0,30,30);//设置按钮位置和大小
    ui->minButton->setToolTip(tr("最小化"));//设置鼠标放上去后的文字提示
    QIcon min_icon(":/image/ICON/min1.png");//设置按钮图标所在位置
    ui->minButton->setIcon(min_icon);//添加按钮图标


    ui->setButton->setGeometry(1000-120,0,30,30);
    ui->setButton->setToolTip(tr("设置"));//设置鼠标放上去后的文字提示
    QIcon set_icon(":/image/ICON/set.png");//设置按钮图标所在位置
    ui->setButton->setIcon(set_icon);//添加按钮图标
    ui->setButton->setFlat(true);//设置按钮背景透明
    ui->setButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/ICON/blue2.png);}");//设置鼠标滑过颜色变化



    ui->minButton->setFlat(true);//设置按钮背景透明
    connect(ui->minButton,SIGNAL(clicked()),this,SLOT(windowMin()));//连接信号与槽，使点击后最小化窗口
    ui->minButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/ICON/blue2.png);}");//设置鼠标滑过颜色变化

    ui->maxButton->setGeometry(1000-60,0,30,30);//设置按钮位置和大小
    ui->maxButton->setToolTip(tr("最大化"));//设置鼠标放上去后的文字提示
    QIcon max_icon(":/image/ICON/max2.png");//设置按钮图标所在位置
    ui->maxButton->setIcon(max_icon);//添加按钮图标

    ui->maxButton->setFlat(true);
    connect(ui->maxButton,SIGNAL(clicked()),this,SLOT(windowMax()));//连接信号与槽，使点击后最小化窗口
    ui->maxButton->setStyleSheet("QPushButton:hover{border-image:url(:/image/ICON/blue2.png);}");//设置鼠标滑过颜色变化




    ui->listWidget->setGeometry(0,30,180,700);//设置listwidget的位置和大小
    ui->listWidget->setStyleSheet("QListWidget{font-family:'Microsoft YaHei';font-size:15px;}"
                                  "QListWidget{color:rgb(255,255,255); background:rgb(8,17,31);border:0px groove gray;}"
                                  "QListWidget::Item{height:50px;border:0px groove gray;padding-left:15;}"
                                  "QListWidget::Item:hover{color:rgb(255,255,255);border-image:url(:/image/ICON/gray.png);border:0px groove gray;}"
                                  "QListWidget::Item:selected{color:rgb(255,255,255);border-image:url(:/image/ICON/gray.png);border:0px groove gray;}"
                                  );//设置显示的效果，美化listwidget
    ui->listWidget->setIconSize(QSize(25,25));//设置列表图标大小
    ui->listWidget->setFocusPolicy(Qt::NoFocus);//去掉选中时的虚线框显示（去掉焦点）

    QListWidgetItem *add_item_1 = new QListWidgetItem(ui->listWidget);//声明实例化一个项目
    add_item_1->setText(tr("用户"));//给项目命名
    add_item_1->setIcon(QIcon(":/image/ICON/yonghu.png"));//给项目添加图标


    QListWidgetItem *add_item_2 = new QListWidgetItem(ui->listWidget);
    add_item_2->setIcon(QIcon(":/image/ICON/biaoge.png"));
    add_item_2->setText(tr("表格"));

    QListWidgetItem *add_item_3 = new QListWidgetItem(ui->listWidget);
    add_item_3->setIcon(QIcon(":/image/ICON/daoru-tianchong.png"));
    add_item_3->setText(tr("导入/导出"));

    QListWidgetItem *add_item_4 = new QListWidgetItem(ui->listWidget);
    add_item_4->setIcon(QIcon(":/image/ICON/tuichu.png"));
    add_item_4->setText(tr("退出系统"));

    ui->listWidget->setCurrentRow(0);


    ui->stackedWidget->setGeometry(180,30,180,700);//设置stackedwidget的位置和大小
    ui->stackedWidget->setStyleSheet("QStackedWidget{background:rgb(255,255,255);}");//设置显示效果
    ui->stackedWidget->addWidget(UserWin);
    ui->stackedWidget->addWidget(TableWin);
    ui->stackedWidget->addWidget(InputWin);
    ui->stackedWidget->addWidget(ExitWin);//添加widget到stackedwidget中成为新的页面
    ui->stackedWidget->setCurrentWidget(UserWin);//设置默认页面为显示页面
    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(showPage(QModelIndex)));
    //连接信号与槽，点击列表的某一行，列表发出信号，将本行的索引作为信号发出，改变页面的槽得到信号，获取当前行号，改变页面

    ui->SearBtn->setGeometry(1000-406,46,70,30);
    ui->HighBtn->setGeometry(1000-326,46,70,30);
    ui->NewBtn->setGeometry(1000-246,46,70,30);
    ui->EditBtn->setGeometry(1000-166,46,70,30);
    ui->DeleBtn->setGeometry(1000-86,46,70,30);
    ui->tableView->setGeometry(370,80,1000-380,500);
    ui->UpPageBtn->setGeometry(1000-76,585,30,30);
    ui->DownPageBtn->setGeometry(1000-42,585,30,30);

    ui->SearBtn->setText(tr("筛选"));
    ui->HighBtn->setText(tr("高级"));
    ui->NewBtn->setText(tr("新建"));
    ui->EditBtn->setText(tr("编辑"));
    ui->DeleBtn->setText(tr("删除"));
    ui->UpPageBtn->setToolTip(tr("上一页"));
    ui->DownPageBtn->setToolTip(tr("下一页"));

    ui->SearBtn->setIcon(QIcon(":/image/ICON/shaixuan.png"));
    ui->SearBtn->setIconSize(QSize(20,20));
    ui->HighBtn->setIcon(QIcon(":/image/ICON/gaojisousuo.png"));
    ui->HighBtn->setIconSize(QSize(20,20));
    ui->NewBtn->setIcon(QIcon(":/image/ICON/xinjian.png"));
    ui->NewBtn->setIconSize(QSize(20,20));
    ui->EditBtn->setIcon(QIcon(":/image/ICON/bianji.png"));
    ui->EditBtn->setIconSize(QSize(20,20));
    ui->DeleBtn->setIcon(QIcon(":/image/ICON/shanchu.png"));
    ui->DeleBtn->setIconSize(QSize(20,20));
    ui->UpPageBtn->setIcon(QIcon(":/image/ICON/UpPage.png"));
    ui->DownPageBtn->setIcon(QIcon(":/image/ICON/DownPage.png"));

    ui->SearBtn->setStyleSheet("QPushButton{background-color:rgba(53,65,89,100%);border-radius:0px;}"
                               "QPushButton:hover{background-color:rgb(54,112,227);color:white;}"
                               "QPushButton:pressed{background-color:rgb(53,65,89);border-style:inset;}");
    ui->HighBtn->setStyleSheet("QPushButton{background-color:rgba(53,65,89,100%);border-radius:0px;}"
                               "QPushButton:hover{background-color:rgb(54,112,227);color:white;}"
                               "QPushButton:pressed{background-color:rgb(53,65,89);border-style:inset;}");
    ui->NewBtn->setStyleSheet("QPushButton{background-color:rgba(33,181,95,100%);border-radius:0px;}"
                               "QPushButton:pressed{background-color:rgb(53,65,89);border-style:inset;}");
    ui->EditBtn->setStyleSheet("QPushButton{background-color:rgba(6,155,255,100%);border-radius:0px;}"
                               "QPushButton:pressed{background-color:rgb(53,65,89);border-style:inset;}");
    ui->DeleBtn->setStyleSheet("QPushButton{background-color:rgba(255,102,104,100%);border-radius:0px;}"
                               "QPushButton:pressed{background-color:rgb(53,65,89);border-style:inset;}");
    ui->UpPageBtn->setStyleSheet("QPushButton{background-color:rgba(255,102,104,0%);border-radius:0px;}"
                               "QPushButton:pressed{border:1px groove gray;}");
    ui->DownPageBtn->setStyleSheet("QPushButton{background-color:rgba(255,102,104,0%);border-radius:0px;}"
                                   "QPushButton:pressed{border:1px groove gray;}");


    ui->tableView->setAlternatingRowColors(true);//设置table隔行变色
    ui->tableView->setFrameShape(QFrame::NoFrame);//设置table无边框
    ui->tableView->setShowGrid(true);//设置table内部线条不显示
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//设置最后一列填满表格
    ui->tableView->resizeColumnsToContents();//设置列宽适应内容调整宽度
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中表格时为整行选中
    ui->tableView->setFocusPolicy(Qt::NoFocus);//设置选中表格时没有虚线框（不显示焦点）
    ui->tableView->horizontalHeader()->setFixedHeight(30);//设置表头的高度
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置设置表头样式，背景色，字体颜色，大小
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(54,151,255);color:white;padding-left: 4px;\
                                                    font-family:'Microsoft YaHei';font-size:15px;border: 0px solid gray;}");
    //设置table样式，设置表格内容的背景色，字体颜色，大小
    ui->tableView->setStyleSheet("QTableView{color:black;background-color:rgb(173,216,230,0%);\
                                 alternate-background-color:rgb(211,211,211);selection-color:rgb(255,255,255);selection-background-color:rgb(112,128,144);\
                                 border:0px groove gray;padding:2px 4px;border-radius:0px;\
                                 font-family:'Microsoft YaHei';font-size:15px;gridline-color:darkgray;}");


                                 /*完成相应的信号与槽连接*/

    //=================登录界面=========
    connect(LoginWin,SIGNAL(sendData()),this,SLOT(receiveData()));
    connect(this,SIGNAL(clearData()),LoginWin,SLOT(ClearEdit()));


    //=================删除和编辑数据交互========
    connect(this,SIGNAL(transData(QStringList)),DeleUser,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEData(QStringList)),EditUser,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transBathData(QStringList)),DeleBathTab,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEBathData(QStringList)),EditBathTab,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transCurData(QStringList)),DeleCuring,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transECurData(QStringList)),EditCuring,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transCurCData(QStringList)),DeleCuringCos,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transECurCData(QStringList)),EditCuringCos,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transFibData(QStringList)),DeleFiber,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEFibData(QStringList)),EditFiber,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transFibCData(QStringList)),DeleFiberCos,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEFibCData(QStringList)),EditFiberCos,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transResData(QStringList)),DeleResin,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEResData(QStringList)),EditResin,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transResCData(QStringList)),DeleResinCos,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEResCData(QStringList)),EditResinCos,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transRotData(QStringList)),DeleRobot,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transERotData(QStringList)),EditRobot,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transLogData(QStringList)),DeleUserLog,SLOT(deleData(QStringList)));

    connect(this,SIGNAL(transWorkData(QStringList)),DeleWorkData,SLOT(deleData(QStringList)));
    connect(this,SIGNAL(transEWorkData(QStringList)),EditWorkData,SLOT(editData(QStringList)));

    connect(this,SIGNAL(transEChartDay(QVector<double>,QVector<double>,QVector<double>)),Echarts,SLOT(EchartDay(QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transEChartWeek(QVector<double>,QVector<double>,QVector<double>)),Echarts,SLOT(EchartWeek(QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transEChartMonth(QVector<double>,QVector<double>,QVector<double>)),Echarts,SLOT(EchartMonth(QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transEChartQuar(QVector<double>,QVector<double>,QVector<double>)),Echarts,SLOT(EchartQuar(QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transEChartYear(QVector<double>,QVector<double>,QVector<double>)),Echarts,SLOT(EchartYear(QVector<double>,QVector<double>,QVector<double>)));

    connect(this,SIGNAL(transReportMonth(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)),report,SLOT(ReportMonth(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transReportQuar(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)),report,SLOT(ReportQuar(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)));
    connect(this,SIGNAL(transReportYear(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)),report,SLOT(ReportYear(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>)));



    //=================用户选项卡相关=====
    connect(UserWin,SIGNAL(showUsersTab(QString)),this,SLOT(showModel(QString)));
    connect(UserWin,SIGNAL(showUserChange()),this,SLOT(changeUsers()));
    connect(this,SIGNAL(change()),UserWin,SLOT(change()));


    //=================导入导出选项卡=====
    connect(InputWin,SIGNAL(showIn()),this,SLOT(showInData()));
    connect(InputWin,SIGNAL(showOut()),this,SLOT(showOutData()));
    connect(InputWin,SIGNAL(showECharts()),this,SLOT(showECharts()));
    connect(InputWin,SIGNAL(showReport()),this,SLOT(showReport()));


    //=================表格选项卡相关======
    connect(TableWin,SIGNAL(showTable(QString)),this,SLOT(showModel(QString)));


    //=================主界面的新建，编辑，删除，筛选和高级======
    connect(ui->NewBtn,SIGNAL(clicked(bool)),this,SLOT(newData()));
    connect(ui->EditBtn,SIGNAL(clicked(bool)),this,SLOT(editData()));
    connect(ui->DeleBtn,SIGNAL(clicked(bool)),this,SLOT(deleData()));
    connect(ui->SearBtn,SIGNAL(clicked(bool)),this,SLOT(searData()));
    connect(ui->HighBtn,SIGNAL(clicked(bool)),this,SLOT(highData()));
    connect(ui->setButton,SIGNAL(clicked(bool)),this,SLOT(showSet()));


    //=================用户表的切换用户，新建用户，编辑用户，删除用户，筛选用户===
    connect(ChanUser,SIGNAL(userChan()),this,SLOT(receiveData()));
    connect(this,SIGNAL(error()),ChanUser,SLOT(Warn()));
    connect(this,SIGNAL(correct()),ChanUser,SLOT(Correct()));
    connect(NewUser,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleUser,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditUser,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleUser,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));


    //=================表格选项卡的表格相关操作========================
    //-----------------浴缸表--------------------------------------
    connect(BathTab,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleBathTab,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditBathTab,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleBatnTab,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------固化剂产品信息表--------------------------------------
    connect(NewCuring,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleCuring,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditCuring,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleCuring,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));

    //-----------------固化剂消耗标准表--------------------------------------
    connect(NewCuringCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleCuringCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditCuringCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleCuringCos,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------玻纤产品信息表--------------------------------------
    connect(NewFiber,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleFiber,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditFiber,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleFiber,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------玻纤消耗标准表--------------------------------------
    connect(NewFiberCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleFiberCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditFiberCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleFiberCos,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------树脂产品信息表--------------------------------------
    connect(NewResin,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleResin,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditResin,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleResin,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------树脂消耗标准表--------------------------------------
    connect(NewResinCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleResinCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditResinCos,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleResinCos,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------用户操作记录表--------------------------------------
    connect(DeleUserLog,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleUserLog,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------机器人信息表--------------------------------------
    connect(NewRobot,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleRobot,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditRobot,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleRobot,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));
    //-----------------工作记录表--------------------------------------
    connect(DataWork,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(DeleWorkData,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(EditWorkData,SIGNAL(sendData(QString)),this,SLOT(RunSql(QString)));
    connect(SeleWorkData,SIGNAL(sendData(QString)),this,SLOT(SQLRun(QString)));

    //=================高级SQL语言相关====================
    connect(SqlWin,SIGNAL(sendSQL(QString)),this,SLOT(RunSQL(QString)));
    //=================导入导出相关=======================
    connect(InputData,SIGNAL(sendData(QString)),this,SLOT(Run(QString)));
    connect(OutputData,SIGNAL(sendData(QString)),this,SLOT(Run(QString)));
    connect(Set,SIGNAL(sendData(QString)),this,SLOT(Run(QString)));
    connect(Echarts,SIGNAL(sendDataDay(QStringList)),this,SLOT(EchartDay(QStringList)));
    connect(Echarts,SIGNAL(sendDataWeek(QStringList)),this,SLOT(EchartWeek(QStringList)));
    connect(Echarts,SIGNAL(sendDataMonth(QStringList)),this,SLOT(EchartMonth(QStringList)));
    connect(Echarts,SIGNAL(sendDataQuar(QStringList)),this,SLOT(EchartQuar(QStringList)));
    connect(Echarts,SIGNAL(sendDataYear(QStringList)),this,SLOT(EchartYear(QStringList)));
    connect(report,SIGNAL(MonthReport(QString)),this,SLOT(MonthReport(QString)));
    connect(report,SIGNAL(QuarReport(QString)),this,SLOT(QuarReport(QString)));
    connect(report,SIGNAL(YearReport(QString)),this,SLOT(YearReport(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete LoginWin;
    delete UserWin;
    delete TableWin;
    delete InputWin;
    delete ExitWin;
    delete NewUser;
    delete EditUser;
    delete DeleUser;
    delete SeleUser;
    delete SqlWin;
    delete ChanUser;
    delete BathTab;
    delete EditBathTab;
    delete DeleBathTab;
    delete SeleBatnTab;
    delete NewCuring;
    delete EditCuring;
    delete DeleCuring;
    delete SeleCuring;
    delete NewResin;
    delete EditResin;
    delete DeleResin;
    delete SeleResin;
    delete NewFiber;
    delete EditFiber;
    delete DeleFiber;
    delete SeleFiber;
    delete NewResinCos;
    delete EditResinCos;
    delete DeleResinCos;
    delete SeleResinCos;
    delete NewCuringCos;
    delete EditCuringCos;
    delete DeleCuringCos;
    delete SeleCuringCos;
    delete NewFiberCos;
    delete EditFiberCos;
    delete DeleFiberCos;
    delete SeleFiberCos;
    delete DeleUserLog;
    delete SeleUserLog;
    delete NewRobot;
    delete EditRobot;
    delete DeleRobot;
    delete SeleRobot;
    delete DataWork;
    delete EditWorkData;
    delete DeleWorkData;
    delete SeleWorkData;
    delete InputData;
    delete OutputData;
    delete Echarts;
    delete report;
    delete Set;
}

void MainWindow::windowClosed()//关闭窗口的槽实现
{
    QFile file(MainWindow::UserLoginAddre);
    file.open(QIODevice::Append | QIODevice::Text);
    file.write(UserLogin.toUtf8());
    file.close();
    db.close();//关闭数据库
    this->close();
}

void MainWindow::windowMin()//最小化窗口的槽实现
{
    this->showMinimized();
}

void MainWindow::windowMax()//最大化窗口的槽实现
{
    if(isMaxWindow){
        resize(1000, 618);
        move((clientRect.width() - this->width())/2, (clientRect.height() - this->height())/2); // 居中
        isMaxWindow = false;
        isHalfWindow = false;
    }else{
//        showMaximized();
        resize(clientRect.width(), clientRect.height());
        move(0, 0);
        isMaxWindow = true;
        isHalfWindow = false;
    }
    updateNormalBtn();
}

//···鼠标按下操作···
static QPoint last(0,0);//保存一个坐标
const int TITLE_HEIGHT = 30;//保存标题高度，也就是鼠标点击区域高度
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        last = event->globalPos();//坐标存储为全局坐标，即桌面屏幕坐标


    }
}

//···鼠标移动操作···
//实时修改窗口的坐标
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    if(event->y()<TITLE_HEIGHT)//如果选中了标题范围
    {
        if (isMaxWindow || isHalfWindow) {
            //this->showNormal(); // 拖动最大化的窗口是否需要变成正常？
            resize(1000, 618);
            isMaxWindow = false;
            isHalfWindow = false;
        }else{
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        last = event->globalPos();//更新存储坐标为当前的全局坐标
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
        }
        if(event->globalY() == 0){ // 鼠标拖动窗体到屏幕顶端最大化窗体
            move(0, 0);
            resize(clientRect.width(), clientRect.height());
            isMaxWindow = true;
            isHalfWindow = false;
        }
        if(event->globalX() < 4){// 鼠标拖动窗体到屏幕最左端窗体占左半边屏幕大小
            resize(1000, clientRect.height());
            move(0, 0);
            isMaxWindow = false;
            isHalfWindow = true;
        }
        if(event->globalX() > clientRect.width() - 4){// 鼠标拖动窗体到屏幕最右端窗体占右半边屏幕大小
            resize(1000, clientRect.height());
            move(clientRect.width()-1000, 0);
            isMaxWindow = false;
            isHalfWindow = true;
        }
    }
        updateNormalBtn();
}

//···鼠标释放操作···
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//选中标题栏
    {
        int dx = event->globalX() - last.x();//得到鼠标移动后的全局坐标X减去移动前的全局坐标X，得到移动距离dx
        int dy = event->globalY() - last.y();//得到鼠标移动后的全局坐标X减去移动前的全局坐标y，得到移动距离dy
        this->move(this->x()+dx,this->y()+dy);//设置窗口以当前坐标为基准移动dx和dy距离到新的位置
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->y()<TITLE_HEIGHT)//如果点击了标题范围
    {
        if(isMaxWindow){
            resize(1000, 618);
            move((clientRect.width() - this->width())/2, (clientRect.height() - this->height())/2); // 居中
            isMaxWindow = false;
            isHalfWindow = false;
        }else{
            //showMaximized();
            resize(clientRect.width(), clientRect.height());
            move(0, 0);
            isMaxWindow = true;
            isHalfWindow = false;
        }
    }
    updateNormalBtn();
}

void MainWindow::updateNormalBtn()
{
    if(isMaxWindow){
        ui->maxButton->setToolTip(tr("还原"));
        ui->closeButton->setGeometry(1366-30,0,30,30);//设置按钮位置和大小
        ui->minButton->setGeometry(1366-90,0,30,30);//设置按钮位置和大小
        ui->maxButton->setGeometry(1366-60,0,30,30);//设置按钮位置和大小
        ui->setButton->setGeometry(1366-120,0,30,30);

        ui->maxButton->setIcon(QIcon(":/image/ICON/huanyuan.png"));//添加按钮图标
        ui->SearBtn->setGeometry(1366-406,46,70,30);
        ui->HighBtn->setGeometry(1366-326,46,70,30);
        ui->NewBtn->setGeometry(1366-246,46,70,30);
        ui->EditBtn->setGeometry(1366-166,46,70,30);
        ui->DeleBtn->setGeometry(1366-86,46,70,30);
        ui->tableView->setGeometry(370,80,1366-380,600);
        ui->UpPageBtn->setGeometry(1366-76,685,30,30);
        ui->DownPageBtn->setGeometry(1366-42,685,30,30);

    }else if(isHalfWindow){
            ui->closeButton->setGeometry(1000-30,0,30,30);//设置按钮位置和大小
            ui->minButton->setGeometry(1000-90,0,30,30);//设置按钮位置和大小
            ui->maxButton->setGeometry(1000-60,0,30,30);//设置按钮位置和大小
            ui->setButton->setGeometry(1000-120,0,30,30);
            ui->tableView->setGeometry(370,80,1000-380,600);
            ui->UpPageBtn->setGeometry(1000-76,685,30,30);
            ui->DownPageBtn->setGeometry(1000-42,685,30,30);
        }else{
            ui->maxButton->setToolTip(tr("最大化"));
            ui->closeButton->setGeometry(1000-30,0,30,30);//设置按钮位置和大小
            ui->minButton->setGeometry(1000-90,0,30,30);//设置按钮位置和大小
            ui->maxButton->setGeometry(1000-60,0,30,30);//设置按钮位置和大小
            ui->setButton->setGeometry(1000-120,0,30,30);
            ui->maxButton->setIcon(QIcon(":/image/ICON/max2.png"));//添加按钮图标
            ui->SearBtn->setGeometry(1000-406,46,70,30);
            ui->HighBtn->setGeometry(1000-326,46,70,30);
            ui->NewBtn->setGeometry(1000-246,46,70,30);
            ui->EditBtn->setGeometry(1000-166,46,70,30);
            ui->DeleBtn->setGeometry(1000-86,46,70,30);
            ui->tableView->setGeometry(370,80,1000-380,500);
            ui->UpPageBtn->setGeometry(1000-76,585,30,30);
            ui->DownPageBtn->setGeometry(1000-42,585,30,30);

        }


}

void MainWindow::showPage(const QModelIndex &index)//显示页面，实现页面切换的槽函数的实现
{
    int i = index.row();//获取列表当前行号，从0开始
    //qDebug()<<index;
    switch(i)//选择判断是第几行，相应改变stackedwidget的页面显示
    {
    case 0: ui->stackedWidget->setCurrentWidget(UserWin);break;
    case 1: ui->stackedWidget->setCurrentWidget(TableWin);break;
    case 2: ui->stackedWidget->setCurrentWidget(InputWin);break;
    case 3: ui->stackedWidget->setCurrentWidget(ExitWin);break;
    default: ui->stackedWidget->setCurrentWidget(UserWin);break;
    }
}


void MainWindow::showModel(QString data)
{
    //利用MVC将数据库表内容显示在tableView上
    model = new QMySqlQueryModel(this);

//    model->setQuery(QString("select * from %1;").arg(data));
    //列名
    int i = MainWindow::Mark;
    switch (i)
    {
    case 1:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);                //将UserLogin记录下来用于刷新数据
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("用户名"));
        model->setHeaderData(1,Qt::Horizontal,tr("账号类型"));
        model->setHeaderData(2,Qt::Horizontal,tr("密码"));
        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);
    }
        break;
    case 2:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("浴缸名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("浴缸长度"));
        model->setHeaderData(3,Qt::Horizontal,tr("浴缸宽度"));
        model->setHeaderData(4,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(5,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(6,Qt::Horizontal,tr("固化剂编号"));

        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,128);
        ui->tableView->setColumnWidth(1,128);
        ui->tableView->setColumnWidth(2,128);
        ui->tableView->setColumnWidth(3,128);
        ui->tableView->setColumnWidth(4,128);
        ui->tableView->setColumnWidth(5,128);
        ui->tableView->setColumnWidth(6,128);
    }
        break;

    case 3:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("固化剂编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("固化剂名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("固化剂单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);


    }
        break;
    case 4:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("固化剂编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 5:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("玻纤名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("玻纤单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);
    }
        break;
    case 6:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);


    }
        break;
    case 7:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("树脂名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("树脂单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);

    }
        break;
    case 8:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 9:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        model->setHeaderData(2,Qt::Horizontal,tr("登录时间"));
        model->setHeaderData(3,Qt::Horizontal,tr("操作记录保存地址"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 10:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("机器人编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("机器人名称"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,450);
        ui->tableView->setColumnWidth(1,450);

    }
        break;
   case 11:
    {
        model->setQuery(QString("select * from %1;").arg(data));
        UserLogin += QString("select * from %1;").arg(data);
        UserLogin += "\n";
        model->setHeaderData(0,Qt::Horizontal,tr("序号"));
        model->setHeaderData(1,Qt::Horizontal,tr("机器人编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(3,Qt::Horizontal,tr("浴缸标签"));
        model->setHeaderData(4,Qt::Horizontal,tr("喷涂次数"));
        model->setHeaderData(5,Qt::Horizontal,tr("树脂消耗/千克"));
        model->setHeaderData(6,Qt::Horizontal,tr("玻纤消耗/千克"));
        model->setHeaderData(7,Qt::Horizontal,tr("固化剂消耗/千克"));
        model->setHeaderData(8,Qt::Horizontal,tr("喷涂日期"));
        model->setHeaderData(9,Qt::Horizontal,tr("喷涂时间"));

        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,45);
        ui->tableView->setColumnWidth(1,90);
        ui->tableView->setColumnWidth(2,90);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,80);
        ui->tableView->setColumnWidth(5,110);
        ui->tableView->setColumnWidth(6,110);
        ui->tableView->setColumnWidth(7,130);
        ui->tableView->setColumnWidth(8,120);
        ui->tableView->setColumnWidth(9,90);

    }
        break;
    default:ui->tableView->setModel(model);//放数据;
        break;
    }





    ui->tableView->verticalHeader()->hide();//不显示序号


}

void MainWindow::changeUsers()
{
    ChanUser->show();

}

//新建，编辑，删除后的刷新显示
void MainWindow::RunSql(QString str)
{
    QSqlQuery query(db);
    query.exec(str);
    UserLogin += str;
    UserLogin += "\n";

    int i = MainWindow::Mark;
    switch (i) {
    case 1: showModel("users");break;
    case 2: showModel("bathtub");break;
    case 3: showModel("curingagent");break;
    case 4: showModel("curingagentcosting");break;
    case 5: showModel("fiberglass");break;
    case 6: showModel("fiberglasscosting");break;
    case 7: showModel("resin");break;
    case 8: showModel("resincosting");break;
    case 9: showModel("userlogin");break;
    case 10: showModel("robot");break;
    case 11: showModel("workdata");break;
    default:;break;
    }


    qDebug()<<str;
}

//筛选运行后的表格显示
void MainWindow::SQLRun(QString str)
{
    MainWindow::Table = str;
    model = new QMySqlQueryModel(this);
    model->setQuery(str);
    UserLogin += str;
    UserLogin += "\n";

    int i = MainWindow::Mark;

    switch(i)
    {
    case 1:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("用户名"));
        model->setHeaderData(1,Qt::Horizontal,tr("账号类型"));
        model->setHeaderData(2,Qt::Horizontal,tr("密码"));
        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);
    }break;
    case 2:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("浴缸名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("浴缸长度"));
        model->setHeaderData(3,Qt::Horizontal,tr("浴缸宽度"));
        model->setHeaderData(4,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(5,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(6,Qt::Horizontal,tr("固化剂编号"));

        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,128);
        ui->tableView->setColumnWidth(1,128);
        ui->tableView->setColumnWidth(2,128);
        ui->tableView->setColumnWidth(3,128);
        ui->tableView->setColumnWidth(4,128);
        ui->tableView->setColumnWidth(5,128);
        ui->tableView->setColumnWidth(6,128);


    }
        break;
    case 3:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("固化剂编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("固化剂名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("固化剂单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);


    }
        break;
    case 4:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("固化剂编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 5:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("玻纤名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("玻纤单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);
    }
        break;
    case 6:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("玻纤编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);


    }
        break;
    case 7:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("树脂名称"));
        model->setHeaderData(2,Qt::Horizontal,tr("树脂单价（元/千克）"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,300);
        ui->tableView->setColumnWidth(1,300);
        ui->tableView->setColumnWidth(2,300);

    }
        break;
    case 8:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("树脂编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("第一次喷涂参考量/千克"));
        model->setHeaderData(3,Qt::Horizontal,tr("第二次喷涂参考量/千克"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 9:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        model->setHeaderData(2,Qt::Horizontal,tr("登录时间"));
        model->setHeaderData(3,Qt::Horizontal,tr("操作记录保存地址"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,225);
        ui->tableView->setColumnWidth(1,225);
        ui->tableView->setColumnWidth(2,225);
        ui->tableView->setColumnWidth(3,225);

    }
        break;
    case 10:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("机器人编号"));
        model->setHeaderData(1,Qt::Horizontal,tr("机器人名称"));


        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,450);
        ui->tableView->setColumnWidth(1,450);

    }
        break;
   case 11:
    {
        model->setHeaderData(0,Qt::Horizontal,tr("序号"));
        model->setHeaderData(1,Qt::Horizontal,tr("机器人编号"));
        model->setHeaderData(2,Qt::Horizontal,tr("浴缸编号"));
        model->setHeaderData(3,Qt::Horizontal,tr("浴缸标签"));
        model->setHeaderData(4,Qt::Horizontal,tr("喷涂次数"));
        model->setHeaderData(5,Qt::Horizontal,tr("树脂消耗/千克"));
        model->setHeaderData(6,Qt::Horizontal,tr("玻纤消耗/千克"));
        model->setHeaderData(7,Qt::Horizontal,tr("固化剂消耗/千克"));
        model->setHeaderData(8,Qt::Horizontal,tr("喷涂日期"));
        model->setHeaderData(9,Qt::Horizontal,tr("喷涂时间"));

        ui->tableView->setModel(model);//放数据
        ui->tableView->setColumnWidth(0,45);
        ui->tableView->setColumnWidth(1,90);
        ui->tableView->setColumnWidth(2,90);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,80);
        ui->tableView->setColumnWidth(5,110);
        ui->tableView->setColumnWidth(6,110);
        ui->tableView->setColumnWidth(7,130);
        ui->tableView->setColumnWidth(8,120);
        ui->tableView->setColumnWidth(9,90);

    }
        break;
    default:;break;
    }

    ui->tableView->verticalHeader()->hide();//不显示序号
}

//高级筛选后的表格显示
void MainWindow::RunSQL(QString str)
{
    model = new QMySqlQueryModel(this);
    model->setQuery(str);
    UserLogin += str;
    UserLogin += "\n";
    ui->tableView->setModel(model);//放数据
    ui->tableView->verticalHeader()->hide();//不显示序号
}

void MainWindow::showInData()
{
    InputData->show();
}

void MainWindow::showOutData()
{
    OutputData->show();
}

void MainWindow::showECharts()
{
    Echarts->show();
}

void MainWindow::showReport()
{
    report->show();
}

void MainWindow::EchartDay(QStringList str)
{
    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(31);
    QVector<double> arr2(31);
    QVector<double> arr3(31);
    arr1={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    arr2={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    arr3={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //select years,months,days,bathtubname,count from bathcountd where years = 2018 and months = 'january' and bathtubname = '箭牌卫浴';
    //查询浴缸生产量
    if(str.at(2) == "bath"){

        data = QString("select days,bathtubname,count from bathcountd where years = %1 and months = %2 and bathtubname = '安华小户型浴缸';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr1[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select days,bathtubname,count from bathcountd where years = %1 and months = %2 and bathtubname = '箭牌卫浴';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select days,bathtubname,count from bathcountd where years = %1 and months = %2 and bathtubname = '沃特玛按摩浴缸';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            arr3[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        for(int i=0;i<20;i++){
            qDebug()<<arr1[i];
        }

    emit transEChartDay(arr1,arr2,arr3);



    }else if(str.at(2) == "cos"){
    //select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗量
    data = QString("select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = %1 and months = %2 group by days;").arg(str.at(0)).arg(str.at(1));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }


    emit transEChartDay(arr1,arr2,arr3);



    }else if(str.at(2) == "price"){
    //select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗带来的开销
    data = QString("select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = %1 and months = %2 group by days;").arg(str.at(0)).arg(str.at(1));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }
    emit transEChartDay(arr1,arr2,arr3);
    }

}

void MainWindow::EchartWeek(QStringList str)
{
    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(6);
    QVector<double> arr2(6);
    QVector<double> arr3(6);
    arr1={0,0,0,0,0,0};
    arr2={0,0,0,0,0,0};
    arr3={0,0,0,0,0,0};
    int a;

    //select years,months,days,bathtubname,count from bathcountd where years = 2018 and months = 'january' and bathtubname = '箭牌卫浴';
    //查询浴缸生产量
    if(str.at(2) == "bath"){

        data = QString("select weeks,bathtubname,count from bathcountw where years = %1 and months = %2 and bathtubname = '安华小户型浴缸';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        query.seek(0);
        a = query.value(0).toInt();
        query.exec(data);
        while(query.next()){
            qDebug()<<query.value(0).toInt()-a<<query.value(2).toDouble();
            arr1[query.value(0).toInt()-a] = query.value(2).toDouble();
        }

        data = QString("select weeks,bathtubname,count from bathcountw where years = %1 and months = %2 and bathtubname = '箭牌卫浴';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        query.seek(0);
        a = query.value(0).toInt();
        query.exec(data);
        while(query.next()){
            qDebug()<<query.value(0).toInt()-a<<query.value(2).toDouble();
            arr2[query.value(0).toInt()-a] = query.value(2).toDouble();
        }

        data = QString("select weeks,bathtubname,count from bathcountw where years = %1 and months = %2 and bathtubname = '沃特玛按摩浴缸';").arg(str.at(0)).arg(str.at(1));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        query.seek(0);
        a = query.value(0).toInt();
        query.exec(data);
        while(query.next()){
            qDebug()<<query.value(0).toInt()-a<<query.value(2).toDouble();
            arr3[query.value(0).toInt()-a] = query.value(2).toDouble();
        }

    emit transEChartWeek(arr1,arr2,arr3);



    }else if(str.at(2) == "cos"){
    //select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗量
    data = QString("select weeks,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountw where years = %1 and months = %2 group by weeks;").arg(str.at(0)).arg(str.at(1));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    query.seek(0);
    a = query.value(0).toInt();
    query.exec(data);
    while(query.next()){
        arr1[query.value(0).toInt()-a] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-a] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-a] = query.value(3).toDouble();
    }


    emit transEChartWeek(arr1,arr2,arr3);



    }else if(str.at(2) == "price"){
    //select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗带来的开销
    data = QString("select weeks,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePricee) as CurAgePrice from bathcountw where years = %1 and months = %2 group by weeks;").arg(str.at(0)).arg(str.at(1));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    query.seek(0);
    a = query.value(0).toInt();
    query.exec(data);
    while(query.next()){
        arr1[query.value(0).toInt()-a] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-a] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-a] = query.value(3).toDouble();
    }
    emit transEChartWeek(arr1,arr2,arr3);
    }


}

void MainWindow::EchartMonth(QStringList str)
{
    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(12);
    QVector<double> arr2(12);
    QVector<double> arr3(12);
    arr1={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    arr2={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    arr3={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    //select years,months,days,bathtubname,count from bathcountd where years = 2018 and months = 'january' and bathtubname = '箭牌卫浴';
    //查询浴缸生产量
    if(str.at(1) == "bath"){

        data = QString("select Months,bathtubname,count from bathcountm where years = %1 and bathtubname = '安华小户型浴缸';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr1[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select Months,bathtubname,count from bathcountw where years = %1 and bathtubname = '箭牌卫浴';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select Months,bathtubname,count from bathcountw where years = %1 and bathtubname = '沃特玛按摩浴缸';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr3[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

    emit transEChartMonth(arr1,arr2,arr3);



    }else if(str.at(1) == "cos"){
    //select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗量
    data = QString("select Months,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountm where years = %1 group by Months;").arg(str.at(0));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }


    emit transEChartMonth(arr1,arr2,arr3);



    }else if(str.at(1) == "price"){
    //select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗带来的开销
    data = QString("select Months,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountm where years = %1 group by Months;").arg(str.at(0));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }
    emit transEChartMonth(arr1,arr2,arr3);
    }




}

void MainWindow::EchartQuar(QStringList str)
{
    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(4);
    QVector<double> arr2(4);
    QVector<double> arr3(4);
    arr1={0, 0, 0, 0};
    arr2={0, 0, 0, 0};
    arr3={0, 0, 0, 0};

    //select years,months,days,bathtubname,count from bathcountd where years = 2018 and months = 'january' and bathtubname = '箭牌卫浴';
    //查询浴缸生产量
    if(str.at(1) == "bath"){

        data = QString("select Quarter,bathtubname,count from bathcountq where years = %1 and bathtubname = '安华小户型浴缸';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr1[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select Quarter,bathtubname,count from bathcountq where years = %1 and bathtubname = '箭牌卫浴';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

        data = QString("select Quarter,bathtubname,count from bathcountq where years = %1 and bathtubname = '沃特玛按摩浴缸';").arg(str.at(0));
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr3[query.value(0).toInt()-1] = query.value(2).toDouble();
        }

    emit transEChartQuar(arr1,arr2,arr3);



    }else if(str.at(1) == "cos"){
    //select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗量
    data = QString("select Quarter,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountq where years = %1 group by Quarter;").arg(str.at(0));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }


    emit transEChartQuar(arr1,arr2,arr3);



    }else if(str.at(1) == "price"){
    //select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗带来的开销
    data = QString("select Quarter,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountq where years = %1 group by Quarter;").arg(str.at(0));
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[query.value(0).toInt()-1] = query.value(1).toDouble();
        arr2[query.value(0).toInt()-1] = query.value(2).toDouble();
        arr3[query.value(0).toInt()-1] = query.value(3).toDouble();
    }
    emit transEChartQuar(arr1,arr2,arr3);
    }

}

void MainWindow::EchartYear(QStringList str)
{
    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(2);
    QVector<double> arr2(2);
    QVector<double> arr3(2);
    arr1={0, 0};
    arr2={0, 0};
    arr3={0, 0};

    //select years,months,days,bathtubname,count from bathcountd where years = 2018 and months = 'january' and bathtubname = '箭牌卫浴';
    //查询浴缸生产量
    if(str.at(1) == "bath"){

        data = QString("select Years,bathtubname,count from bathcounty where bathtubname = '安华小户型浴缸';");
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        int i =0;
        while(query.next()){

            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr1[i] = query.value(2).toDouble();
            i++;
        }

        data = QString("select Years,bathtubname,count from bathcounty where bathtubname = '箭牌卫浴';");
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        i = 0;
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr2[i] = query.value(2).toDouble();
            i++;
        }

        data = QString("select Years,bathtubname,count from bathcounty where bathtubname = '沃特玛按摩浴缸';");
        query.exec(data);
        UserLogin += data;
        UserLogin += "\n";
        i = 0;
        while(query.next()){
            qDebug()<<query.value(0).toInt()-1<<query.value(2).toDouble();
            arr3[i] = query.value(2).toDouble();
            i++;
        }

    emit transEChartYear(arr1,arr2,arr3);



    }else if(str.at(1) == "cos"){
    //select days,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗量
    data = QString("select Years,sum(resincos) as resincos,sum(fiberglasscos) as fiberglasscos,sum(curagecos) as curagecos from bathcounty group by Years;");
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int i =0;
    while(query.next()){
        arr1[i] = query.value(1).toDouble();
        arr2[i] = query.value(2).toDouble();
        arr3[i] = query.value(3).toDouble();
        i++;
    }


    emit transEChartYear(arr1,arr2,arr3);



    }else if(str.at(1) == "price"){
    //select days,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcountd where years = 2018 and months = 'january' group by days;
    //查询物料消耗带来的开销
    data = QString("select Years,sum(ResinPrice) as ResinPrice,sum(FiberGlassPrice) as FiberGlassPrice,sum(CurAgePrice) as CurAgePrice from bathcounty group by Years;");
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int i = 0;
    while(query.next()){
        arr1[i] = query.value(1).toDouble();
        arr2[i] = query.value(2).toDouble();
        arr3[i] = query.value(3).toDouble();
        i++;
    }
    emit transEChartYear(arr1,arr2,arr3);
    }

}

void MainWindow::MonthReport(QString str)
{
    QString year;
    if(str == "2018年"){
        year = "2018";
    }else if(str == "2019年"){
        year = "2019";
    }

    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(48);//产量
    QVector<double> arr2(48);//树脂消耗
    QVector<double> arr3(48);//树脂花费
    QVector<double> arr4(48);//玻纤消耗
    QVector<double> arr5(48);//玻纤花费
    QVector<double> arr6(48);//固化剂消耗
    QVector<double> arr7(48);//固化剂花费

    arr1={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr2={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr3={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr4={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr5={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr6={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};
    arr7={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0};

    data = QString("select Months,bathtubname,count,resincos,ResinPrice,fiberglasscos,FiberGlassPrice,curagecos,CurAgePrice from bathcountm where years = %1;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int i =0;
    while(query.next()){
        arr1[i] = query.value(2).toDouble();
        arr2[i] = query.value(3).toDouble();
        arr3[i] = query.value(4).toDouble();
        arr4[i] = query.value(5).toDouble();
        arr5[i] = query.value(6).toDouble();
        arr6[i] = query.value(7).toDouble();
        arr7[i] = query.value(8).toDouble();
        i++;
    }
    data = QString("select months, sum(count),sum(resincos),sum(ResinPrice),sum(fiberglasscos),sum(FiberGlassPrice),sum(curagecos),sum(CurAgePrice) from bathcountm where years = %1 group by months;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int a =36;
    while(query.next()){
        arr1[a] = query.value(1).toDouble();
        arr2[a] = query.value(2).toDouble();
        arr3[a] = query.value(3).toDouble();
        arr4[a] = query.value(4).toDouble();
        arr5[a] = query.value(5).toDouble();
        arr6[a] = query.value(6).toDouble();
        arr7[a] = query.value(7).toDouble();
        a++;
    }
    qDebug()<<arr1[36]<<arr2[36]<<arr3[36]<<arr4[36]<<arr5[36]<<arr6[36]<<arr7[36];
    emit transReportMonth(arr1,arr2,arr3,arr4,arr5,arr6,arr7);

}

void MainWindow::QuarReport(QString str)
{
    QString year;
    if(str == "2018年"){
        year = "2018";
    }else if(str == "2019年"){
        year = "2019";
    }

    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(16);//产量
    QVector<double> arr2(16);//树脂消耗
    QVector<double> arr3(16);//树脂花费
    QVector<double> arr4(16);//玻纤消耗
    QVector<double> arr5(16);//玻纤花费
    QVector<double> arr6(16);//固化剂消耗
    QVector<double> arr7(16);//固化剂花费

    arr1={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr2={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr3={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr4={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr5={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr6={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};
    arr7={0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0, 0, 0,0};

    data = QString("select quarter,bathtubname,count,resincos,ResinPrice,fiberglasscos,FiberGlassPrice,curagecos,CurAgePrice from bathcountq where years = %1;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int i =0;
    while(query.next()){
        arr1[i] = query.value(2).toDouble();
        arr2[i] = query.value(3).toDouble();
        arr3[i] = query.value(4).toDouble();
        arr4[i] = query.value(5).toDouble();
        arr5[i] = query.value(6).toDouble();
        arr6[i] = query.value(7).toDouble();
        arr7[i] = query.value(8).toDouble();
        i++;
    }
    data = QString("select quarter, sum(count),sum(resincos),sum(ResinPrice),sum(fiberglasscos),sum(FiberGlassPrice),sum(curagecos),sum(CurAgePrice) from bathcountq where years = %1 group by quarter;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int a =12;
    while(query.next()){
        arr1[a] = query.value(1).toDouble();
        arr2[a] = query.value(2).toDouble();
        arr3[a] = query.value(3).toDouble();
        arr4[a] = query.value(4).toDouble();
        arr5[a] = query.value(5).toDouble();
        arr6[a] = query.value(6).toDouble();
        arr7[a] = query.value(7).toDouble();
        a++;
    }
    qDebug()<<arr1[12]<<arr2[12]<<arr3[12]<<arr4[12]<<arr5[12]<<arr6[12]<<arr7[12];
    emit transReportQuar(arr1,arr2,arr3,arr4,arr5,arr6,arr7);

}

void MainWindow::YearReport(QString str)
{
    QString year;
    if(str == "2018年"){
        year = "2018";
    }else if(str == "2019年"){
        year = "2019";
    }

    QSqlQuery query(db);
    QString data;
    QVector<double> arr1(4);//产量
    QVector<double> arr2(4);//树脂消耗
    QVector<double> arr3(4);//树脂花费
    QVector<double> arr4(4);//玻纤消耗
    QVector<double> arr5(4);//玻纤花费
    QVector<double> arr6(4);//固化剂消耗
    QVector<double> arr7(4);//固化剂花费

    arr1={0, 0, 0,0};
    arr2={0, 0, 0,0};
    arr3={0, 0, 0,0};
    arr4={0, 0, 0,0};
    arr5={0, 0, 0,0};
    arr6={0, 0, 0,0};
    arr7={0, 0, 0,0};

    data = QString("select years,bathtubname,count,resincos,ResinPrice,fiberglasscos,FiberGlassPrice,curagecos,CurAgePrice from bathcounty where years = %1;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    int i =0;
    while(query.next()){
        arr1[i] = query.value(2).toDouble();
        arr2[i] = query.value(3).toDouble();
        arr3[i] = query.value(4).toDouble();
        arr4[i] = query.value(5).toDouble();
        arr5[i] = query.value(6).toDouble();
        arr6[i] = query.value(7).toDouble();
        arr7[i] = query.value(8).toDouble();
        i++;
    }
    data = QString("select years, sum(count),sum(resincos),sum(ResinPrice),sum(fiberglasscos),sum(FiberGlassPrice),sum(curagecos),sum(CurAgePrice) from bathcounty where years = %1;").arg(year);
    query.exec(data);
    UserLogin += data;
    UserLogin += "\n";
    while(query.next()){
        arr1[3] = query.value(1).toDouble();
        arr2[3] = query.value(2).toDouble();
        arr3[3] = query.value(3).toDouble();
        arr4[3] = query.value(4).toDouble();
        arr5[3] = query.value(5).toDouble();
        arr6[3] = query.value(6).toDouble();
        arr7[3] = query.value(7).toDouble();
    }
    qDebug()<<arr1[3]<<arr2[3]<<arr3[3]<<arr4[3]<<arr5[3]<<arr6[3]<<arr7[3];
    emit transReportYear(arr1,arr2,arr3,arr4,arr5,arr6,arr7);

}

void MainWindow::Run(QString str)
{
    QSqlQuery query(db);
    query.exec(str);
    UserLogin += str;
    UserLogin += "\n";
    if(MainWindow::Mark == 9){
        showModel("userlogin");
    }

}

void MainWindow::showSet()
{
    Set->show();
}



void MainWindow::receiveData()
{
    //qDebug()<<MainWindow::UserInfo.at(0)<<MainWindow::UserInfo.at(1);


    //qDebug()<<"连接成功"<<"connect to mysql successful";
    QSqlQuery query(db);
    //QSqlQuery类提供了执行和操作SQL语句的方法
    QString str;
    userType = false;

    str = QString("select * from users where username = '%1' && password = '%2' ;").arg(MainWindow::UserInfo.at(0)).arg(MainWindow::UserInfo.at(1));
    retQuery = query.exec(str);
    UserLogin += str;
    UserLogin += "\n";
    //qDebug()<<retQuery<<str;
    retResult = query.seek(0);
    if(retQuery){
        if(retResult){
            //qDebug()<<query.value(3).toString();
            if(!isRun){
                this->show();
                setWindowState(Qt::WindowMaximized);
                isMaxWindow = true;
                isHalfWindow = false;
                updateNormalBtn();
                isRun = true;
                LoginWin->hide();
            }
            showModel("");

            ui->label_2->setText(QString("欢迎%1%2登录本系统").arg(query.value(1).toString()).arg(query.value(0).toString()));
            if(query.value(1).toString()=="管理员"){
                userType = true;
                //qDebug()<<"现在是管理员账号登录";
                ui->NewBtn->setEnabled(true);
                ui->EditBtn->setEnabled(true);
                ui->DeleBtn->setEnabled(true);
                ui->HighBtn->setEnabled(true);
            }else{
                userType = false;
                //qDebug()<<"现在是普通用户账号登录";
                ui->NewBtn->setEnabled(false);
                ui->EditBtn->setEnabled(false);
                ui->
                        ->setEnabled(false);
                ui->HighBtn->setEnabled(false);
            }
            emit correct();
            emit change();
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
            UserLogin = "====================="+MainWindow::UserInfo.at(0)+"--"+current_date+"============================";
            UserLogin += "\n";
            str = QString("insert into userlogin(username,logintime) values('%1',now()) ;").arg(MainWindow::UserInfo.at(0));
            query.exec(str);
            UserLogin += str;
            UserLogin += "\n";
            str = QString("select ID from userlogin order by ID;");
            query.exec(str);
            query.last();
            UserLogin += str;
            UserLogin += "\n";
            ID = query.value(0).toInt();

        }else{
            //qDebug()<<"登录失败";
            if(!isRun){
                emit clearData();
            }else{
                emit error();
            }

        }
    }
}

void MainWindow::newData()
{
    int i = MainWindow::Mark;
    switch (i)
    {
    case 1:NewUser->show(); break;
    case 2:BathTab->show(); break;
    case 3:NewCuring->show(); break;
    case 4:NewCuringCos->show(); break;
    case 5:NewFiber->show(); break;
    case 6:NewFiberCos->show(); break;
    case 7:NewResin->show(); break;
    case 8:NewResinCos->show(); break;
    case 9:; break;
    case 10:NewRobot->show(); break;
    case 11:DataWork->show(); break;
    default:; break;
    }
}

void MainWindow::editData()
{
    model = new QMySqlQueryModel(ui->tableView);
    model->setQuery(MainWindow::Table);
    int curRow = ui->tableView->currentIndex().row();
    int curCol = model->columnCount();
    QStringList str;

    for(int i = 0;i < curCol; i++){
    str << model->data(model->index(curRow,i)).toString();
    }
    //qDebug()<<str<<curCol;


    int i = MainWindow::Mark;
    switch (i)
    {
    case 1:emit transEData(str); break;
    case 2:emit transEBathData(str); break;
    case 3:emit transECurData(str); break;
    case 4:emit transECurCData(str); break;
    case 5:emit transEFibData(str); break;
    case 6:emit transEFibCData(str); break;
    case 7:emit transEResData(str); break;
    case 8:emit transEResCData(str); break;
    case 9:; break;
    case 10:emit transERotData(str); break;
    case 11:emit transEWorkData(str); break;
    default:; break;
    }
}

void MainWindow::deleData()
{
    model = new QMySqlQueryModel(ui->tableView);
    model->setQuery(MainWindow::Table);
    UserLogin += MainWindow::Table;
    UserLogin += "\n";
    int curRow = ui->tableView->currentIndex().row();
    int curCol = model->columnCount();
    QStringList str;

    for(int i = 0;i < curCol; i++){
    str << model->data(model->index(curRow,i)).toString();
    }
    //qDebug()<<str<<curCol;



    int i = MainWindow::Mark;
    switch (i)
    {
    case 1:emit transData(str); break;
    case 2:emit transBathData(str); break;
    case 3:emit transCurData(str); break;
    case 4:emit transCurCData(str); break;
    case 5:emit transFibData(str); break;
    case 6:emit transFibCData(str); break;
    case 7:emit transResData(str); break;
    case 8:emit transResCData(str); break;
    case 9:emit transLogData(str); break;
    case 10:emit transRotData(str); break;
    case 11:emit transWorkData(str); break;
    default:; break;
    }

}

void MainWindow::searData()
{
    int i = MainWindow::Mark;
    switch (i)
    {
    case 1:SeleUser->show(); break;
    case 2:SeleBatnTab->show(); break;
    case 3:SeleCuring->show(); break;
    case 4:SeleCuringCos->show(); break;
    case 5:SeleFiber->show(); break;
    case 6:SeleFiberCos->show(); break;
    case 7:SeleResin->show(); break;
    case 8:SeleResinCos->show(); break;
    case 9:SeleUserLog->show(); break;
    case 10:SeleRobot->show(); break;
    case 11:SeleWorkData->show(); break;
    default:; break;
    }

}

void MainWindow::highData()
{
    SqlWin->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qApp->quit();//当关闭父窗口时，关闭子窗口。
}

















