#ifndef FIBERCOSSELE_H
#define FIBERCOSSELE_H

#include <QWidget>

namespace Ui {
class FiberCosSele;
}

class FiberCosSele : public QWidget
{
    Q_OBJECT

public:
    explicit FiberCosSele(QWidget *parent = nullptr);
    ~FiberCosSele();
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
    Ui::FiberCosSele *ui;
};

#endif // FIBERCOSSELE_H
