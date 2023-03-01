#ifndef WORKDATADELE_H
#define WORKDATADELE_H

#include <QWidget>

namespace Ui {
class WorkDataDele;
}

class WorkDataDele : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDataDele(QWidget *parent = nullptr);
    ~WorkDataDele();
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
    Ui::WorkDataDele *ui;
};

#endif // WORKDATADELE_H
