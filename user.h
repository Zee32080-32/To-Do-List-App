#ifndef USER_H
#define USER_H
#include "IUser.h"

class User: public IUser
{
private:
    QString username;
    QString email;
    QString password;
    QString firstName;
    QString lastName;

public:
    User(const QString& username, const QString& email, const QString& password, const QString& firstName, const QString& lastName);

    QString getUserName() const override;
    QString getEmail() const override;
    QString getFirstName() const override;
    QString getLastName() const override;
    QString getPassword() const override;
    bool Canlogin(const QString& username, const QString& password) override;
    QString getRole() const override;



};

#endif // USER_H
