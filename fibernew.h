#ifndef FIBERNEW_H
#define FIBERNEW_H

#include <QWidget>

namespace Ui {
class FiberNew;
}

class FiberNew : public QWidget
{
    Q_OBJECT

public:
    explicit FiberNew(QWidget *parent = nullptr);
    ~FiberNew();
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
    Ui::FiberNew *ui;
};

#endif // FIBERNEW_H
