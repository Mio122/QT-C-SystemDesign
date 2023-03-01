#ifndef USERNEW_H
#define USERNEW_H

#include <QWidget>

namespace Ui {
class UserNew;
}

class UserNew : public QWidget
{
    Q_OBJECT

public:
    explicit UserNew(QWidget *parent = nullptr);
    ~UserNew();

private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void SaveBtnC();
    void setType();
    void setTypeT();
    void CloseBtnC();

    void on_CancleBtn_clicked();

public:
    QString type;


private:
    Ui::UserNew *ui;
};

#endif // USERNEW_H
