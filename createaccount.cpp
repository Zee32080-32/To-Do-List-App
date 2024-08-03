#include "createaccount.h"
#include "ui_createaccount.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

CreateAccount::CreateAccount(QWidget *parent): QMainWindow(parent), ui(new Ui::CreateAccount), networkManager(new QNetworkAccessManager(this)), user(nullptr),frontPage(nullptr), dbHandler()
{

    ui->setupUi(this);

    if (!dbHandler.connect())
    {
        qDebug() << "Failed to connect to the database in crete account class.";
    }

    ui->Verificationlabel->hide();
    ui->VerificationlineEdit->hide();
    ui->VerifypushButton->hide();
    ui->EmailInUselabel->hide();
    //connect(networkManager, &QNetworkAccessManager::finished, this, &CreateAccount::onEmailSent);

    //connect(ui->VerifypushButton, &QPushButton::clicked, this, &CreateAccount::on_VerifypushButton_clicked);


}

CreateAccount::~CreateAccount()
{
    delete ui;
    if (user) delete user; // Clean up newUser

}

bool CreateAccount::validateInputs()
{
    QString email = ui->EmaillineEdit->text();
    QString password = ui->PasswordlineEdit->text();
    QString confirmedPassword = ui->RePasswordlineEdit->text();
    QString firstName = ui->FNamelineEdit->text();
    QString lastName = ui->LNamelineEdit->text();
    QString userName = ui->UserNamelineEdit->text();

    if (!Validation::isNotEmpty(email) || !Validation::isValidEmail(email))
    {
        QMessageBox::warning(this, "Input Error", "Please enter a valid email address.");
        return false;
    }

    if (!Validation::isNotEmpty(password) || !Validation::isValidPassword(password))
    {
        QMessageBox::warning(this, "Input Error", "Password must be at least 8 characters long and contain at least one number and one letter.");
        return false;
    }

    if (!Validation::doPasswordsMatch(password, confirmedPassword))
    {
        QMessageBox::warning(this, "Input Error", "Passwords do not match.");
        return false;
    }

    if (!Validation::isNotEmpty(firstName) || !Validation::isNotEmpty(lastName) || !Validation::isNotEmpty(userName))
    {
        QMessageBox::warning(this, "Input Error", "Please fill out all fields.");
        return false;
    }

    return true;
}



void CreateAccount::on_CreateAccountpushButton_clicked()
{
    if (!validateInputs()) {
        return;
    }

    QString email = ui->EmaillineEdit->text();

    int count = dbHandler.checkEmailExists(email);

    if (count == -1) {
        qDebug() << "Error occurred while checking email.";
        return;
    }

    if (count > 0)
    {
        qDebug() << "Email already exists in the database";
        ui->EmailInUselabel->show();
    }
    else
    {
        qDebug() << "Email does not exist in the database";

        verificationCode = QString::number(QRandomGenerator::global()->bounded(100000, 1000000));
        QString subject = "Account Verification";
        QString body = "Your verification code is: " + verificationCode + "\nThis code will expire in 5 minutes.";

        sendEmail(email, subject, body);

        ui->Verificationlabel->show();
        ui->VerificationlineEdit->show();
        ui->VerifypushButton->show();

        verificationCodeTimestamp = QDateTime::currentDateTime();
    }
}


void CreateAccount::on_LoginpushButton_clicked()
{

}



void CreateAccount::sendEmail(const QString &to, const QString &subject, const QString &body)
{
    QString smtpServer = "smtp.gmail.com";
    int port = 465;
    QString username = "Enter the username here";
    QString password = "your_app_specific_password_here"; // Use the generated app-specific password

    QString message = QString("To: %1\r\n"
                              "From: %2\r\n"
                              "Subject: %3\r\n"
                              "\r\n"
                              "%4\r\n")
                          .arg(to)
                          .arg(username)
                          .arg(subject)
                          .arg(body);

    QSslSocket *socket = new QSslSocket(this);
    socket->connectToHostEncrypted(smtpServer, port);

    if (!socket->waitForConnected(10000)) {
        qDebug() << "Failed to connect to host!" << socket->errorString();
        delete socket;
        return;
    }

    if (!socket->waitForEncrypted(10000)) {
        qDebug() << "Failed to establish encrypted connection!" << socket->errorString();
        delete socket;
        return;
    }

    auto readResponse = [&]() -> QByteArray {
        if (!socket->waitForReadyRead(10000)) {
            qDebug() << "Timeout or error while waiting for response: " << socket->errorString();
            return QByteArray();
        }
        QByteArray response = socket->readAll();
        qDebug() << "Server response:" << response;
        return response;
    };

    auto sendCommand = [&](const QString &command) -> bool {
        socket->write(command.toUtf8());
        socket->flush();
        QByteArray response = readResponse();
        if (response.isEmpty() || !response.startsWith("2")) { // Check for 2xx response
            qDebug() << "SMTP command failed: " << command;
            return false;
        }
        return true;
    };

    auto sendBase64Command = [&](const QString &command) -> bool {
        QByteArray base64Command = command.toUtf8().toBase64();
        base64Command.append("\r\n");
        return sendCommand(base64Command);
    };

    if (!sendCommand("EHLO smtp.gmail.com\r\n")) { delete socket; return; }
    if (!sendCommand("AUTH LOGIN\r\n")) { delete socket; return; }
    if (!sendBase64Command(username)) { delete socket; return; }
    if (!sendBase64Command(password)) { delete socket; return; }
    if (!sendCommand(QString("MAIL FROM:<%1>\r\n").arg(username))) { delete socket; return; }
    if (!sendCommand(QString("RCPT TO:<%1>\r\n").arg(to))) { delete socket; return; }
    if (!sendCommand("DATA\r\n")) { delete socket; return; }

    socket->write((message + "\r\n.\r\n").toUtf8());
    socket->flush();
    QByteArray dataResponse = readResponse();
    if (dataResponse.isEmpty() || !dataResponse.startsWith("2")) { // Check for 2xx response
        qDebug() << "SMTP DATA command failed";
        delete socket;
        return;
    }

    if (!sendCommand("QUIT\r\n")) { delete socket; return; }

    verificationCodeTimestamp = QDateTime::currentDateTime();

    if (socket->error() == QAbstractSocket::UnknownSocketError) {
        qDebug() << "Email successfully sent!";
    } else {
        qDebug() << "Failed to send email: " << socket->errorString();
    }

    socket->disconnectFromHost();
    delete socket;
}


void CreateAccount::onEmailSent(QNetworkReply* reply)
{

    if(reply->error() == QNetworkReply::NoError) {
        qDebug() << "Email successfully sent!";
    } else {
        qDebug() << "Failed twefewfo send email: " << reply->errorString();
    }
    reply->deleteLater();
}

void CreateAccount::on_VerifypushButton_clicked()
{
    QString enteredCode = ui->VerificationlineEdit->text();

    // Check if the code has expired
    QDateTime currentTime = QDateTime::currentDateTime();
    int secondsElapsed = verificationCodeTimestamp.secsTo(currentTime);
    int expirationTimeInSeconds = 1 * 60; // 5 mins in seconds
    if (secondsElapsed > expirationTimeInSeconds)
    {
        qDebug() << "Verification code has expired!";
        ui->Verificationlabel->setText("E-mail has not been able to be verified!");
        return;
    }

    // Proceed with verification if the code is within the expiration time
    if (Validation::isValidVerificationCode(enteredCode) && enteredCode == verificationCode)
    {
        qDebug() << "Verification successful!";
        ui->Verificationlabel->setText("E-mail has been successfully verified! Account being created");
        if(dbHandler.CreateUser(ui->EmaillineEdit->text(), ui->FNamelineEdit->text(), ui->LNamelineEdit->text(), ui->UserNamelineEdit->text(), ui->PasswordlineEdit->text(), "User"))
        {

            qDebug() << "Data inserted into UserInfo table";
            user = new User(ui->UserNamelineEdit->text(), ui->EmaillineEdit->text(), ui->PasswordlineEdit->text(), ui->FNamelineEdit->text(), ui->LNamelineEdit->text());
            if (!frontPage)
            {
                frontPage = new FrontPage(ui->UserNamelineEdit->text());
            }
            frontPage->show();
            this->close();
        }
        else
        {
            qDebug() << "Failed to insert data into UserInfo table";
        }
    }
    else
    {
        qDebug() << "Verification failed!";
        ui->Verificationlabel->setText("E-mail has not been able to be verified!");

        // Handle verification failure
    }




}

