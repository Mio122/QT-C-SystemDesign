#ifndef REPORT_H
#define REPORT_H

#include <QWidget>

namespace Ui {
class Report;
}

class Report : public QWidget
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件

    QString SaveFile();
    void MToReport(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void QToReport(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void YToReport(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);

signals:
    void MonthReport(QString);
    void QuarReport(QString);
    void YearReport(QString);

private slots:
    void MonthBtnC();
    void QuarBtnC();
    void YearBtnC();

    void ReportMonth(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void ReportQuar(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);
    void ReportYear(QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>,QVector<double>);


private:
    Ui::Report *ui;
};

#endif // REPORT_H
