#ifndef ROBOTEDIT_H
#define ROBOTEDIT_H

#include <QWidget>

namespace Ui {
class RobotEdit;
}

class RobotEdit : public QWidget
{
    Q_OBJECT

public:
    explicit RobotEdit(QWidget *parent = nullptr);
    ~RobotEdit();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void editData(QStringList);
    void SaveBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::RobotEdit *ui;
};

#endif // ROBOTEDIT_H
