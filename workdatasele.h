#ifndef WORKDATASELE_H
#define WORKDATASELE_H

#include <QWidget>

namespace Ui {
class WorkDataSele;
}

class WorkDataSele : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDataSele(QWidget *parent = nullptr);
    ~WorkDataSele();
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
    Ui::WorkDataSele *ui;
};

#endif // WORKDATASELE_H
