#ifndef RESINNEW_H
#define RESINNEW_H

#include <QWidget>

namespace Ui {
class ResinNew;
}

class ResinNew : public QWidget
{
    Q_OBJECT

public:
    explicit ResinNew(QWidget *parent = nullptr);
    ~ResinNew();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void SaveBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::ResinNew *ui;
};

#endif // RESINNEW_H
