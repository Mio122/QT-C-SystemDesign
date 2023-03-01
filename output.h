#ifndef OUTPUT_H
#define OUTPUT_H

#include <QWidget>

namespace Ui {
class OutPut;
}

class OutPut : public QWidget
{
    Q_OBJECT

public:
    explicit OutPut(QWidget *parent = nullptr);
    ~OutPut();
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
    Ui::OutPut *ui;
};

#endif // OUTPUT_H
