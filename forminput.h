#ifndef FORMINPUT_H
#define FORMINPUT_H

#include <QWidget>

namespace Ui {
class FormInput;
}

class FormInput : public QWidget
{
    Q_OBJECT

public:
    explicit FormInput(QWidget *parent = nullptr);
    ~FormInput();


signals:
    void showIn();
    void showOut();
    void showECharts();
    void showReport();



private slots:
    void outputData();
    void InBtnC();
    void OutBtnC();
    void EChartsBtnC();
    void OutReportBtnC();


private:
    Ui::FormInput *ui;
};

#endif // FORMINPUT_H
