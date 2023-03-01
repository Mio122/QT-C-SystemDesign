#ifndef ROBOTSELE_H
#define ROBOTSELE_H

#include <QWidget>

namespace Ui {
class RobotSele;
}

class RobotSele : public QWidget
{
    Q_OBJECT

public:
    explicit RobotSele(QWidget *parent = nullptr);
    ~RobotSele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void SeleBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::RobotSele *ui;
};

#endif // ROBOTSELE_H
