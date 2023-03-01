#ifndef TABLEBATH_H
#define TABLEBATH_H

#include <QWidget>

namespace Ui {
class TableBath;
}

class TableBath : public QWidget
{
    Q_OBJECT

public:
    explicit TableBath(QWidget *parent = nullptr);
    ~TableBath();
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
    Ui::TableBath *ui;
};

#endif // TABLEBATH_H
