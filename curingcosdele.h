#ifndef CURINGCOSDELE_H
#define CURINGCOSDELE_H

#include <QWidget>

namespace Ui {
class CuringCosDele;
}

class CuringCosDele : public QWidget
{
    Q_OBJECT

public:
    explicit CuringCosDele(QWidget *parent = nullptr);
    ~CuringCosDele();

signals:
    void sendData(QString);


private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
private slots:
    void DeleBtnC();
    void deleData(QStringList);

    void on_CancleBtn_clicked();

private:
    Ui::CuringCosDele *ui;
};

#endif // CURINGCOSDELE_H
