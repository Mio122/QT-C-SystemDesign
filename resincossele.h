#ifndef RESINCOSSELE_H
#define RESINCOSSELE_H

#include <QWidget>

namespace Ui {
class ResinCosSele;
}

class ResinCosSele : public QWidget
{
    Q_OBJECT

public:
    explicit ResinCosSele(QWidget *parent = nullptr);
    ~ResinCosSele();
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
    Ui::ResinCosSele *ui;
};

#endif // RESINCOSSELE_H
