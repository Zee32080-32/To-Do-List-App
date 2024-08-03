#include "login.h"
#include "ui_login.h"
#include "Validation.h"

// Initialise the member variable createAccountWindow to a null pointer
Login::Login(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Login), createAccountWindow(nullptr), frontPage(nullptr), adminPage(nullptr), dbHandler()
{
    ui->setupUi(this);

    if (!dbHandler.connect()) {
        qDebug() << "Failed to connect to the database in Login class.";
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_LoginPushButton_clicked()
{
    QString Username = ui->UserNameLineEdit->text();
    QString Password = ui->PasswordLineEdit->text();

    // Validate the input fields
    if (!Validation::isNotEmpty(Username)) {
        ui->label->setText("Username cannot be empty");
        return;
    }

    if (!Validation::isNotEmpty(Password)) {
        ui->label->setText("Password cannot be empty");
        return;
    }
    /*
    if (!Validation::isValidPassword(Password)) {
        ui->label->setText("Password must be at least 8 characters long and contain at least one number and one letter");
        return;
    }
*/

    QString role = dbHandler.Login(Username, Password);
    if (role == "User") {
        if (!frontPage) {
            frontPage = new FrontPage(Username);
        }
        frontPage->show();
        this->close();
    } else if (role == "Admin") {
        if (!adminPage) {
            adminPage = new AdminPage();
        }
        adminPage->show();
        this->close();
    } else {
        qDebug() << "login unsuccessful";
        ui->label->setText("User is not found");
    }
}

void Login::on_CrreateAccountPushButton_clicked()
{
    if (!createAccountWindow) {
        createAccountWindow = new CreateAccount();
    }
    createAccountWindow->show();
    this->close();
}
