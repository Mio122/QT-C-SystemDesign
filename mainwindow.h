#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "databaselogin.h"
#include "formexit.h"
#include "forminput.h"
#include "formtable.h"
#include "formuser.h"
#include <QDesktopWidget>
#include "usernew.h"
#include "useredit.h"
#include "userdele.h"
#include "usersele.h"
#include "sqlsear.h"
#include "userchan.h"
#include "tablebath.h"
#include "tablebathedit.h"
#include "tablebathdele.h"
#include "tablebathsele.h"
#include "curingnew.h"
#include "curingedit.h"
#include "curingdele.h"
#include "curingsele.h"
#include "resinnew.h"
#include "resinedit.h"
#include "resindele.h"
#include "resinsele.h"
#include "fibernew.h"
#include "fiberedit.h"
#include "fiberdele.h"
#include "fibersele.h"
#include "resincosnew.h"
#include "resincosedit.h"
#include "resincosdele.h"
#include "resincossele.h"
#include "curingcosnew.h"
#include "curingcosedit.h"
#include "curingcosdele.h"
#include "curingcossele.h"
#include "fibercosnew.h"
#include "fibercosedit.h"
#include "fibercosdele.h"
#include "fibercossele.h"
#include "userlogdele.h"
#include "userlogsele.h"
#include "robotnew.h"
#include "robotedit.h"
#include "robotdele.h"
#include "robotsele.h"
#include "workdata.h"
#include "workdataedit.h"
#include "workdatadele.h"
#include "workdatasele.h"
#include "input.h"
#include "output.h"
#include "echarts.h"
#include "report.h"
#include "setting.h"

#include "qmysqlquerymodel.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QCloseEvent>//让父窗口关闭的同时关闭子窗口






namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QRect clientRect;

    bool isMaxWindow;
    bool isHalfWindow;
    bool retQuery;
    bool retResult;
    bool isRun;

    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
    void mouseDoubleClickEvent(QMouseEvent *event);
    void updateNormalBtn();


signals:
    void clearData();
    void change();
    void error();
    void correct();
    void transData(QStringList);
    void transEData(QStringList);

    void transBathData(QStringList);
    void transEBathData(QStringList);

    void transCurData(QStringList);
    void transECurData(QStringList);

    void transFibData(QStringList);
    void transEFibData(QStringList);

    void transResData(QStringList);
    void transEResData(QStringList);

    void transCurCData(QStringList);
    void transECurCData(QStringList);

    void transFibCData(QStringList);
    void transEFibCData(QStringList);

    void transResCData(QStringList);
    void transEResCData(QStringList);

    void transRotData(QStringList);
    void transERotData(QStringList);

    void transLogData(QStringList);

    void transWorkData(QStringList);
    void transEWorkData(QStringList);


    void transEChartDay(QVector<double>,QVector<double>,QVector<double>);
    void transEChartWeek(QVector<double>,QVector<double>,QVector<double>);
    void transEChartMonth(QVector<double>,QVector<double>,QVector<double>);
    void transEChartQuar(QVector<double>,QVector<double>,QVector<double>);
    void transEChartYear(QVector<double>,QVector<double>,QVector<double>);

    void transReportMonth(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void transReportQuar(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void transReportYear(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);


private slots:
    void windowClosed();//关闭窗口的槽声明
    void windowMin();//最小化窗口的槽声明
    void windowMax();
    void receiveData();
    void newData();
    void editData();
    void deleData();
    void searData();
    void highData();
    void showPage(const QModelIndex &index);
    void showModel(QString);
    void changeUsers();
    void RunSql(QString);
    void SQLRun(QString);
    void RunSQL(QString);
    void showInData();
    void showOutData();
    void showECharts();
    void showReport();
    void EchartDay(QStringList);
    void EchartWeek(QStringList);
    void EchartMonth(QStringList);
    void EchartQuar(QStringList);
    void EchartYear(QStringList);
    void MonthReport(QString);
    void QuarReport(QString);
    void YearReport(QString);
    void Run(QString);
    void showSet();


private:
    QSqlDatabase db;
    QMySqlQueryModel *model;



public:
    DatabaseLogin *LoginWin;
    FormUser *UserWin;
    FormTable *TableWin;
    FormInput *InputWin;
    FormExit *ExitWin;
    UserNew *NewUser;
    UserEdit *EditUser;
    UserDele *DeleUser;
    UserSele *SeleUser;
    SQLSear *SqlWin;
    UserChan * ChanUser;
    TableBath *BathTab;
    TableBathEdit *EditBathTab;
    TableBathDele *DeleBathTab;
    TableBathSele *SeleBatnTab;
    CuringNew *NewCuring;
    CuringEdit *EditCuring;
    CuringDele *DeleCuring;
    CuringSele *SeleCuring;
    ResinNew *NewResin;
    ResinEdit *EditResin;
    ResinDele *DeleResin;
    ResinSele *SeleResin;
    FiberNew *NewFiber;
    FiberEdit *EditFiber;
    FiberDele *DeleFiber;
    FiberSele *SeleFiber;
    ResinCosNew *NewResinCos;
    ResinCosEdit *EditResinCos;
    ResinCosDele *DeleResinCos;
    ResinCosSele *SeleResinCos;
    CuringCosNew *NewCuringCos;
    CuringCosEdit *EditCuringCos;
    CuringCosDele *DeleCuringCos;
    CuringCosSele *SeleCuringCos;
    FiberCosNew *NewFiberCos;
    FiberCosEdit *EditFiberCos;
    FiberCosDele *DeleFiberCos;
    FiberCosSele *SeleFiberCos;
    UserLogDele *DeleUserLog;
    UserLogSele *SeleUserLog;
    RobotNew *NewRobot;
    RobotEdit *EditRobot;
    RobotDele *DeleRobot;
    RobotSele *SeleRobot;
    WorkData *DataWork;
    WorkDataEdit *EditWorkData;
    WorkDataDele *DeleWorkData;
    WorkDataSele *SeleWorkData;
    Input *InputData;
    OutPut *OutputData;
    ECharts *Echarts;
    Report *report;
    Setting *Set;


    static int Mark;
    static QString Table;
    static QStringList UserInfo;
    static bool userType;
    static QString UserLogin;
    static QString UserLoginAddre;
    static int ID;


protected:
    void closeEvent(QCloseEvent * event);//closeEvent的重新定义

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
