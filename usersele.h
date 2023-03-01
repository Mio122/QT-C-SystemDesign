#ifndef USERSELE_H
#define USERSELE_H

#include <QWidget>

namespace Ui {
class UserSele;
}

class UserSele : public QWidget
{
    Q_OBJECT

public:
    explicit UserSele(QWidget *parent = nullptr);
    ~UserSele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
public:
    bool spe;
    QString type;
signals:
    void sendData(QString);

private slots:
    void SeleBtnC();
    void Special();
    void Special0();
    void Special00();



    void on_CancleBtn_clicked();

private:
    Ui::UserSele *ui;
};

#endif // USERSELE_H
