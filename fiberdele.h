#ifndef FIBERDELE_H
#define FIBERDELE_H

#include <QWidget>

namespace Ui {
class FiberDele;
}

class FiberDele : public QWidget
{
    Q_OBJECT

public:
    explicit FiberDele(QWidget *parent = nullptr);
    ~FiberDele();
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
    Ui::FiberDele *ui;
};

#endif // FIBERDELE_H
