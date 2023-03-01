#ifndef CURINGCOSNEW_H
#define CURINGCOSNEW_H

#include <QWidget>

namespace Ui {
class CuringCosNew;
}

class CuringCosNew : public QWidget
{
    Q_OBJECT

public:
    explicit CuringCosNew(QWidget *parent = nullptr);
    ~CuringCosNew();
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
    Ui::CuringCosNew *ui;
};

#endif // CURINGCOSNEW_H
