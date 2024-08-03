#include "user.h"
#include "qdebug.h"

User::User(const QString& username, const QString& email, const QString& password, const QString& firstName, const QString& lastName)
    : username(username), email(email), password(password), firstName(firstName), lastName(lastName)
{
    qDebug() << "User constructor:";
    qDebug() << "Username:" << username;
    qDebug() << "Email:" << email;
    qDebug() << "Password:" << password;
    qDebug() << "First Name:" << firstName;
    qDebug() << "Last Name:" << lastName;
}

QString User::getUserName() const {
    return username;
}

QString User::getEmail() const {
    return email;
}

QString User::getPassword() const {
    return password;
}

QString User::getFirstName() const {
    return firstName;
}

QString User::getLastName() const {
    return lastName;
}

bool User::Canlogin(const QString& username, const QString& password)
{
    qDebug()<<username;
    qDebug()<<this->username;
    return this->username == username && this->password == password;
}

QString User::getRole() const {
    return "User";
}
