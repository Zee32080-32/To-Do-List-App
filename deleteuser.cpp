#include "deleteuser.h"

DeleteUser::DeleteUser(QWidget *parent) : QDialog(parent), dbHandler(new DatabaseHandler)
{
    if (!dbHandler->connect())
    {
        qDebug() << "Failed to connect to the database in front page class.";
    }

    this->setWindowTitle("Delete User");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Enter username to delete:", this);
    layout->addWidget(label);

    usernameLineEdit = new QLineEdit(this);
    layout->addWidget(usernameLineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &DeleteUser::deleteUser);
    connect(cancelButton, &QPushButton::clicked, this, &DeleteUser::close);

    this->setLayout(layout);
}

DeleteUser::~DeleteUser()
{
    delete dbHandler;
}

void DeleteUser::deleteUser() {
    QString username = usernameLineEdit->text();

    if (username.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Username field must be filled out.");
        return;
    }

    DatabaseHandler::DeleteUserStatus status = dbHandler->deleteUser(username);

    switch (status)
    {
    case DatabaseHandler::Success:
        QMessageBox::information(this, "Success", "User deleted successfully.");
        this->accept(); // Close the dialog
        break;
    case DatabaseHandler::UserNotFound:
        QMessageBox::warning(this, "User Not Found", "The specified user does not exist.");
        break;
    case DatabaseHandler::DatabaseError:
    default:
        qDebug() << "Failed to delete user:" << username;
        QMessageBox::critical(this, "Database Error", "Failed to delete user from the database.");
        break;
    }
}
