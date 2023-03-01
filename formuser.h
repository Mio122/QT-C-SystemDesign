#ifndef FORMUSER_H
#define FORMUSER_H

#include <QWidget>

namespace Ui {
class FormUser;
}

class FormUser : public QWidget
{
    Q_OBJECT

public:
    explicit FormUser(QWidget *parent = nullptr);
    ~FormUser();

private slots:
    void userEditC();
    void UserChangeC();
    void change();



signals:
    void showUsersTab(QString);
    void showUserChange();




private:
    Ui::FormUser *ui;
};

#endif // FORMUSER_H
