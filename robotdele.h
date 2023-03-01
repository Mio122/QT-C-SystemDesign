#ifndef ROBOTDELE_H
#define ROBOTDELE_H

#include <QWidget>

namespace Ui {
class RobotDele;
}

class RobotDele : public QWidget
{
    Q_OBJECT

public:
    explicit RobotDele(QWidget *parent = nullptr);
    ~RobotDele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void DeleBtnC();
    void deleData(QStringList);

    void on_CancleBtn_clicked();

private:
    Ui::RobotDele *ui;
};

#endif // ROBOTDELE_H
