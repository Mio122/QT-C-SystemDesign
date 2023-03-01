#ifndef RESINCOSDELE_H
#define RESINCOSDELE_H

#include <QWidget>

namespace Ui {
class ResinCosDele;
}

class ResinCosDele : public QWidget
{
    Q_OBJECT

public:
    explicit ResinCosDele(QWidget *parent = nullptr);
    ~ResinCosDele();
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
    Ui::ResinCosDele *ui;
};

#endif // RESINCOSDELE_H
