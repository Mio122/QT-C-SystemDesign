#include "formuser.h"
#include "ui_formuser.h"
#include "mainwindow.h"

FormUser::FormUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUser)
{
    ui->setupUi(this);

    ui->label->setGeometry(0,0,180,700);
    ui->label->setStyleSheet("QLabel{background-color:rgb(61,75,102);}");

    ui->UserEditBtn->setCheckable(true);
    ui->UserChangeBtn->setCheckable(true);
    ui->UserEditBtn->setAutoExclusive(true);
    ui->UserChangeBtn->setAutoExclusive(true);

    ui->UserEditBtn->setGeometry(20,10,140,40);
    ui->UserChangeBtn->setGeometry(20,55,140,40);
    ui->UserEditBtn->setText(tr("编辑用户"));
    ui->UserChangeBtn->setText(tr("切换用户"));

    connect(ui->UserEditBtn,SIGNAL(clicked(bool)),this,SLOT(userEditC()));
    connect(ui->UserChangeBtn,SIGNAL(clicked(bool)),this,SLOT(UserChangeC()));

    ui->UserEditBtn->setEnabled(false);


}

FormUser::~FormUser()
{
    delete ui;
}

void FormUser::userEditC()
{
    MainWindow::Mark = 1;
    MainWindow::Table = "select * from users;";
    emit showUsersTab("users");
}

void FormUser::UserChangeC()
{
    MainWindow::Mark = 0;
    emit showUserChange();
}

void FormUser::change()
{
    if(MainWindow::userType == true){
        ui->UserEditBtn->setEnabled(true);
    }else{
        ui->UserEditBtn->setEnabled(false);
    }

}
