#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件

signals:
    void sendData(QString);


private slots:
    void openFile();


    void on_SaveBtn_clicked();

    void on_CancleBtn_clicked();

private:
    void sleep(int msec);
    int count = 0;

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
