#ifndef VALIDATION_H
#define VALIDATION_H

#include <QString>
#include <QRegularExpression>

class Validation
{
public:
    static bool isValidEmail(const QString &email);
    static bool isValidPassword(const QString &password);
    static bool isNotEmpty(const QString &field);
    static bool isValidVerificationCode(const QString &code);
    static bool doPasswordsMatch(const QString &password1, const QString &password2);
};

#endif // VALIDATION_H
