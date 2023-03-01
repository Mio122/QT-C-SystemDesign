#ifndef CURINGSELE_H
#define CURINGSELE_H

#include <QWidget>

namespace Ui {
class CuringSele;
}

class CuringSele : public QWidget
{
    Q_OBJECT

public:
    explicit CuringSele(QWidget *parent = nullptr);
    ~CuringSele();
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
    Ui::CuringSele *ui;
};

#endif // CURINGSELE_H
