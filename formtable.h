#ifndef FORMTABLE_H
#define FORMTABLE_H

#include <QWidget>

namespace Ui {
class FormTable;
}

class FormTable : public QWidget
{
    Q_OBJECT

public:
    explicit FormTable(QWidget *parent = nullptr);
    ~FormTable();

signals:
    void showTable(QString);


private slots:
    void YuGangBtnC();
    void GuhuaBtnC();
    void GuhuaBiaoBtnC();
    void BoqianBtnC();
    void BoqianBiaoBtnC();
    void ShuzhiBtnC();
    void ShuzhiBiaoBtnC();
    void YonghuBtnC();
    void JiqirenBtnC();
    void JiluBtnC();

private:
    Ui::FormTable *ui;
};

#endif // FORMTABLE_H
