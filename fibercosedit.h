#ifndef FIBERCOSEDIT_H
#define FIBERCOSEDIT_H

#include <QWidget>

namespace Ui {
class FiberCosEdit;
}

class FiberCosEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FiberCosEdit(QWidget *parent = nullptr);
    ~FiberCosEdit();
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
    Ui::FiberCosEdit *ui;
};

#endif // FIBERCOSEDIT_H
