#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDateTime>



class DatabaseHandler
{
public:
    DatabaseHandler();
    ~DatabaseHandler();

    bool connect();
    void disconnect();

public:
    enum DeleteUserStatus
    {
        Success,
        UserNotFound,
        DatabaseError
    };

    DeleteUserStatus deleteUser(const QString &username);


    QSqlDatabase getDatabase() const;

    bool insertTask(int userID, const QString &taskName, const QString &description, const QString &priority,
                    const QString &repeat, const QString &dueDate, const QString &tag, const QString &reminder);

    QVector<QVector<QString>> getTasks(int userID);
    int checkEmailExists(const QString& email);
    bool CreateUser(const QString& email, const QString& firstName, const QString& lastName, const QString& userName, const QString& password, const QString& role);

    bool displayTaskDetails(const QString &taskName, QString &taskDetails);
    int getUserID_FromUsername(const QString &username);
    QList<QString> getUserTaskNames(int userID);
    bool SearchForUsername(QString &searchQuery, QString &UserName, QString &FName, QString &LName, QString &Email);
    //bool deleteUser(QString &username);
    bool DisplayUserDetails(int ID);
    bool GetUserDetails(int &ID, QString &UserName, QString &FName, QString &LName, QString &Email);
    QString Login(const QString &Username, const QString &Password);
    bool removeTask(const QString &taskName);









private:
    QSqlDatabase db;
    static const QString DATABASE_PATH;
};

#endif // DATABASEHANDLER_H
