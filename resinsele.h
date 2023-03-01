#ifndef RESINSELE_H
#define RESINSELE_H

#include <QWidget>

namespace Ui {
class ResinSele;
}

class ResinSele : public QWidget
{
    Q_OBJECT

public:
    explicit ResinSele(QWidget *parent = nullptr);
    ~ResinSele();
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
    Ui::ResinSele *ui;
};

#endif // RESINSELE_H
