#ifndef FIBERSELE_H
#define FIBERSELE_H

#include <QWidget>

namespace Ui {
class FiberSele;
}

class FiberSele : public QWidget
{
    Q_OBJECT

public:
    explicit FiberSele(QWidget *parent = nullptr);
    ~FiberSele();
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
    Ui::FiberSele *ui;
};

#endif // FIBERSELE_H
