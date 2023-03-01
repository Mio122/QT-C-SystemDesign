#ifndef TABLEBATHSELE_H
#define TABLEBATHSELE_H

#include <QWidget>

namespace Ui {
class TableBathSele;
}

class TableBathSele : public QWidget
{
    Q_OBJECT

public:
    explicit TableBathSele(QWidget *parent = nullptr);
    ~TableBathSele();

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
    Ui::TableBathSele *ui;
};

#endif // TABLEBATHSELE_H
