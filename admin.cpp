#include "admin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Admin::Admin(const QString& username, const QString& email, const QString& password, const QString& firstName, const QString& lastName)
    : username(username), email(email), password(password), firstName(firstName), lastName(lastName) {}

QString Admin::getUserName() const {
    return username;
}

QString Admin::getEmail() const {
    return email;
}

QString Admin::getPassword() const {
    return password;
}

QString Admin::getFirstName() const {
    return firstName;
}

QString Admin::getLastName() const {
    return lastName;
}

bool Admin::Canlogin(const QString& username, const QString& password) {
    return this->username == username && this->password == password;
}

QString Admin::getRole() const {
    return "Admin";
}


void Admin::viewAllUsers() {
    // Implementation for viewing all users
    QSqlQuery query;
    if(query.exec("SELECT * FROM UserInfo")) {
        while(query.next()) {
            qDebug() << "Username:" << query.value("UserName").toString();
            // Add more details as needed
        }
    } else {
        qDebug() << "Failed to retrieve users:" << query.lastError().text();
    }
}

void Admin::removeUser(const QString& username) {
    // Implementation for removing a user
    QSqlQuery query;
    query.prepare("DELETE FROM UserInfo WHERE UserName = :username");
    query.bindValue(":username", username);
    if(!query.exec()) {
        qDebug() << "Failed to remove user:" << query.lastError().text();
    }
}


