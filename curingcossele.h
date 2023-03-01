#ifndef CURINGCOSSELE_H
#define CURINGCOSSELE_H

#include <QWidget>

namespace Ui {
class CuringCosSele;
}

class CuringCosSele : public QWidget
{
    Q_OBJECT

public:
    explicit CuringCosSele(QWidget *parent = nullptr);
    ~CuringCosSele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void SeleBtnC();

    void on_CancleBtn_clicked();

private:
    Ui::CuringCosSele *ui;
};

#endif // CURINGCOSSELE_H
