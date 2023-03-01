#ifndef ROBOTNEW_H
#define ROBOTNEW_H

#include <QWidget>

namespace Ui {
class RobotNew;
}

class RobotNew : public QWidget
{
    Q_OBJECT

public:
    explicit RobotNew(QWidget *parent = nullptr);
    ~RobotNew();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void SaveBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::RobotNew *ui;
};

#endif // ROBOTNEW_H
