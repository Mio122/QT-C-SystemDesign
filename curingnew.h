#ifndef CURINGNEW_H
#define CURINGNEW_H

#include <QWidget>

namespace Ui {
class CuringNew;
}

class CuringNew : public QWidget
{
    Q_OBJECT

public:
    explicit CuringNew(QWidget *parent = nullptr);
    ~CuringNew();
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
    Ui::CuringNew *ui;
};

#endif // CURINGNEW_H
