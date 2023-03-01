#ifndef SQLSEAR_H
#define SQLSEAR_H

#include <QWidget>

namespace Ui {
class SQLSear;
}

class SQLSear : public QWidget
{
    Q_OBJECT

public:
    explicit SQLSear(QWidget *parent = nullptr);
    ~SQLSear();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendSQL(QString);


private slots:
    void RunBtnC();




    void on_CancleBtn_clicked();

private:
    Ui::SQLSear *ui;
};

#endif // SQLSEAR_H
