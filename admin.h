#ifndef ADMIN_H
#define ADMIN_H
#include "IAdmin.h"
#include <QString>

class Admin: public IAdmin
{
private:
    QString username;
    QString email;
    QString password;
    QString firstName;
    QString lastName;

public:
    Admin(const QString& username, const QString& email, const QString& password, const QString& firstName, const QString& lastName);

    QString getUserName() const override;
    QString getEmail() const override;
    QString getPassword() const override;
    QString getFirstName() const override;
    QString getLastName() const override;
    bool Canlogin(const QString& username, const QString& password) override;
    QString getRole() const override;


    void viewAllUsers() override;
    void removeUser(const QString& username) override;
};

#endif // ADMIN_H
