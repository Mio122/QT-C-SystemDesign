#ifndef USERDELE_H
#define USERDELE_H

#include <QWidget>

namespace Ui {
class UserDele;
}

class UserDele : public QWidget
{
    Q_OBJECT

public:
    explicit UserDele(QWidget *parent = nullptr);
    ~UserDele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void deleData(QStringList);
    void deleBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::UserDele *ui;
};

#endif // USERDELE_H
