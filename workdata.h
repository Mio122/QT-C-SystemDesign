#ifndef WORKDATA_H
#define WORKDATA_H

#include <QWidget>

namespace Ui {
class WorkData;
}

class WorkData : public QWidget
{
    Q_OBJECT

public:
    explicit WorkData(QWidget *parent = nullptr);
    ~WorkData();
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
    Ui::WorkData *ui;
};

#endif // WORKDATA_H
