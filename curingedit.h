#ifndef CURINGEDIT_H
#define CURINGEDIT_H

#include <QWidget>

namespace Ui {
class CuringEdit;
}

class CuringEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CuringEdit(QWidget *parent = nullptr);
    ~CuringEdit();
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
    Ui::CuringEdit *ui;
};

#endif // CURINGEDIT_H
