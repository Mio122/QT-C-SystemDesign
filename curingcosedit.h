#ifndef CURINGCOSEDIT_H
#define CURINGCOSEDIT_H

#include <QWidget>

namespace Ui {
class CuringCosEdit;
}

class CuringCosEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CuringCosEdit(QWidget *parent = nullptr);
    ~CuringCosEdit();
signals:
    void sendData(QString);
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
private slots:
    void editData(QStringList);
    void SaveBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::CuringCosEdit *ui;
};

#endif // CURINGCOSEDIT_H
