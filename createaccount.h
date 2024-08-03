#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H
#include "DatabaseHandler.h"
#include "user.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslSocket>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "frontpage.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "validation.h"

namespace Ui
{
    class CreateAccount;
}

class CreateAccount : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

private slots:
    void on_CreateAccountpushButton_clicked();
    void onEmailSent(QNetworkReply* reply);
    void on_LoginpushButton_clicked();

    void on_VerifypushButton_clicked();

private:
    Ui::CreateAccount *ui;
    QNetworkAccessManager *networkManager;
    //QString generateVerificationCode();
    QSqlDatabase mydb;
    DatabaseHandler dbHandler;
    QDateTime verificationCodeTimestamp;
    User *user;
    FrontPage *frontPage;




    QString verificationCode;
    void sendEmail(const QString &to, const QString &subject, const QString &body);
    bool validateInputs();

};


#endif // CREATEACCOUNT_H
