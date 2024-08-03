#ifndef IADMIN_H
#define IADMIN_H
#include <QString>
#include "IUser.h"

class IAdmin: public IUser
{
public:
    virtual ~IAdmin() = default;
    virtual void viewAllUsers() = 0;
    virtual void removeUser(const QString& username) = 0;
};

#endif // IADMIN_H
