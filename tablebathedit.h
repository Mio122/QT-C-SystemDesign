#ifndef TABLEBATHEDIT_H
#define TABLEBATHEDIT_H

#include <QWidget>

namespace Ui {
class TableBathEdit;
}

class TableBathEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TableBathEdit(QWidget *parent = nullptr);
    ~TableBathEdit();
private:
    void mousePressEvent(QMouseEvent* event);//鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event);//鼠标移动事件
    void mouseReleaseEvent(QMouseEvent* event);//是鼠标释放事件
signals:
    void sendData(QString);

private slots:
    void editData(QStringList);
    void SaveBtnC();


    void on_CancleBtn_clicked();

private:
    Ui::TableBathEdit *ui;
};

#endif // TABLEBATHEDIT_H
