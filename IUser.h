#ifndef IUSER_H
#define IUSER_H
#include <QString>

class IUser
{
public:
    virtual ~IUser() = default;

    virtual QString getUserName() const = 0;
    virtual QString getEmail() const = 0;
    virtual QString getFirstName() const = 0;
    virtual QString getLastName() const = 0;
    virtual QString getPassword() const = 0;
    virtual QString getRole() const = 0;


    virtual bool Canlogin(const QString& username, const QString& password) = 0;

    //add other shared features between user and admin maybe a delete function where you can delete your own account or other accounts on admin
};

#endif // IUSER_H
