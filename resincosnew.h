#ifndef RESINCOSNEW_H
#define RESINCOSNEW_H

#include <QWidget>

namespace Ui {
class ResinCosNew;
}

class ResinCosNew : public QWidget
{
    Q_OBJECT

public:
    explicit ResinCosNew(QWidget *parent = nullptr);
    ~ResinCosNew();
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
    Ui::ResinCosNew *ui;
};

#endif // RESINCOSNEW_H
