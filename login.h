#ifndef LOGIN_H
#define LOGIN_H
#include "frontpage.h"
#include "createaccount.h"
#include "DatabaseHandler.h"
#include "User.h"
#include "Admin.h"
#include "adminpage.h"
#include <QString>
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "Validation.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();


private slots:
    void on_LoginPushButton_clicked();
    void on_CrreateAccountPushButton_clicked();

private:
    Ui::Login *ui;
    //pointer variable named createAccountWindow that can point to an object of type CreateAccount
    CreateAccount *createAccountWindow;
    FrontPage *frontPage;
    AdminPage *adminPage;


    DatabaseHandler dbHandler;


    QSqlDatabase mydb;
};
#endif // LOGIN_H
