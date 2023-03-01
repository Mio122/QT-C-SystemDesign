#ifndef ECHARTS_H
#define ECHARTS_H



#include <QWebKitPlatformPlugin>
#include <QWebFrame>
#include <QWidget>

namespace Ui {
class ECharts;
}

class ECharts : public QWidget
{
    Q_OBJECT

public:
    explicit ECharts(QWidget *parent = nullptr);
    ~ECharts();

public:
    int flag;

private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件

signals:
    void sendDataDay(QStringList);
    void sendDataWeek(QStringList);
    void sendDataMonth(QStringList);
    void sendDataQuar(QStringList);
    void sendDataYear(QStringList);

private slots:
    void DayBtnC();
    void WeekBtnC();
    void MonthBtnC();
    void QuarBtn();
    void YearBtnC();

    void slot();
    void closeEcharts();



    void EchartDay(QVector<double>,QVector<double>,QVector<double>);
    void EchartWeek(QVector<double>,QVector<double>,QVector<double>);
    void EchartMonth(QVector<double>,QVector<double>,QVector<double>);
    void EchartQuar(QVector<double>,QVector<double>,QVector<double>);
    void EchartYear(QVector<double>,QVector<double>,QVector<double>);


private:
    Ui::ECharts *ui;
};

#endif // ECHARTS_H
