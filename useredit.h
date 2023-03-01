#ifndef USEREDIT_H
#define USEREDIT_H

#include <QWidget>

namespace Ui {
class UserEdit;
}

class UserEdit : public QWidget
{
    Q_OBJECT

public:
    explicit UserEdit(QWidget *parent = nullptr);
    ~UserEdit();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
public:
    QStringList str;

signals:
    void sendData(QString);


private slots:

    void editData(QStringList);
    void SaveBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::UserEdit *ui;
};

#endif // USEREDIT_H
