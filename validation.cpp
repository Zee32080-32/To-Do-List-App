#include "Validation.h"

bool Validation::isValidEmail(const QString &email)
{
    QRegularExpression emailRegex(R"(^[^\s@]+@[^\s@]+\.[^\s@]+$)");
    return emailRegex.match(email).hasMatch();
}

bool Validation::isValidPassword(const QString &password)
{
    // Example: Password must be at least 8 characters long and contain at least one number and one letter
    QRegularExpression passwordRegex(R"((?=.*[a-zA-Z])(?=.*\d)[a-zA-Z\d]{8,})");
    return passwordRegex.match(password).hasMatch();
}

bool Validation::isNotEmpty(const QString &field)
{
    return !field.trimmed().isEmpty();
}

bool Validation::isValidVerificationCode(const QString &code)
{
    // Example: Code should be 6 digits
    QRegularExpression codeRegex(R"(\d{6})");
    return codeRegex.match(code).hasMatch();
}

bool Validation::doPasswordsMatch(const QString &password1, const QString &password2)
{
    return password1 == password2;
}
