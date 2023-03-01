#ifndef TABLEBATHDELE_H
#define TABLEBATHDELE_H

#include <QWidget>

namespace Ui {
class TableBathDele;
}

class TableBathDele : public QWidget
{
    Q_OBJECT

public:
    explicit TableBathDele(QWidget *parent = nullptr);
    ~TableBathDele();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);


private slots:
    void deleData(QStringList);
    void DeleBtnC();


    void on_CancleBtn_clicked();

private:
    Ui::TableBathDele *ui;
};

#endif // TABLEBATHDELE_H
