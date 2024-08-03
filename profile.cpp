#include "profile.h"
#include "ui_profile.h"

Profile::Profile(const int &UserID, QWidget *parent): QMainWindow(parent), ui(new Ui::Profile)
{

    ui->setupUi(this);
    if (!dbHandler.connect())
    {
        qDebug() << "Failed to connect to the database in front page class.";
    }
    DisplayUserDetails(UserID);

}


Profile::~Profile()
{
    delete ui;
}

void Profile::DisplayUserDetails(int ID)
{

    QString UserName, FName, LName, Email;
    bool success = dbHandler.GetUserDetails(ID, UserName, FName, LName, Email);

    if (success)
    {
        ui->UserNameDetails_label->setText(UserName);
        ui->FNameDetails_label->setText(FName);
        ui->LNameDetails_label->setText(LName);
        ui->EmailDetails_label->setText(Email);
    }
    else
    {
        qDebug() << "Failed to retrieve user details for username:";
    }
}




