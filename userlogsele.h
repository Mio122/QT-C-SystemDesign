#ifndef USERLOGSELE_H
#define USERLOGSELE_H

#include <QWidget>

namespace Ui {
class UserLogSele;
}

class UserLogSele : public QWidget
{
    Q_OBJECT

public:
    explicit UserLogSele(QWidget *parent = nullptr);
    ~UserLogSele();
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
    Ui::UserLogSele *ui;
};

#endif // USERLOGSELE_H
