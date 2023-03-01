#ifndef FIBERCOSNEW_H
#define FIBERCOSNEW_H

#include <QWidget>

namespace Ui {
class FiberCosNew;
}

class FiberCosNew : public QWidget
{
    Q_OBJECT

public:
    explicit FiberCosNew(QWidget *parent = nullptr);
    ~FiberCosNew();
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
    Ui::FiberCosNew *ui;
};

#endif // FIBERCOSNEW_H
