#ifndef RESINDELE_H
#define RESINDELE_H

#include <QWidget>

namespace Ui {
class ResinDele;
}

class ResinDele : public QWidget
{
    Q_OBJECT

public:
    explicit ResinDele(QWidget *parent = nullptr);
    ~ResinDele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);


private slots:
    void DeleBtnC();
    void deleData(QStringList);

    void on_CancleBtn_clicked();

private:
    Ui::ResinDele *ui;
};

#endif // RESINDELE_H
