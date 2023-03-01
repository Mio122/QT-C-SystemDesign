#ifndef WORKDATAEDIT_H
#define WORKDATAEDIT_H

#include <QWidget>

namespace Ui {
class WorkDataEdit;
}

class WorkDataEdit : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDataEdit(QWidget *parent = nullptr);
    ~WorkDataEdit();
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
    Ui::WorkDataEdit *ui;
};

#endif // WORKDATAEDIT_H
