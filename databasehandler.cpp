#include "DatabaseHandler.h"

const QString DatabaseHandler::DATABASE_PATH = "D:/Zeeshan/Documents/ToDoListApp/build/Desktop_Qt_6_8_0_MSVC2019_64bit-Debug/database.db";

DatabaseHandler::DatabaseHandler()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_PATH);
}

DatabaseHandler::~DatabaseHandler()
{
    disconnect();
}

bool DatabaseHandler::connect()
{
    if (!db.isOpen())
    {
        if (db.open())
        {
            qDebug() << "Database connection established.";
            return true;
        }
        else
        {
            qDebug() << "Error: Could not connect to database.";
            qDebug() << db.lastError().text();
            return false;
        }
    }
    return true; // Already open
}

void DatabaseHandler::disconnect()
{
    if (db.isOpen())
    {
        db.close();
        qDebug() << "Database connection closed.";
    }
}

QSqlDatabase DatabaseHandler::getDatabase() const
{
    return db;
}

bool DatabaseHandler::insertTask(int userID, const QString &taskName, const QString &description, const QString &priority,
                                 const QString &repeat, const QString &dueDate, const QString &tag, const QString &reminder)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO UserItems (UserID, TaskName, Description, Priority, Repeat, DueDate, Tag, Reminder) VALUES (?,?,?,?,?,?,?,?)");

    insertQuery.addBindValue(userID);
    insertQuery.addBindValue(taskName);
    insertQuery.addBindValue(description);
    insertQuery.addBindValue(priority);
    insertQuery.addBindValue(repeat);
    insertQuery.addBindValue(dueDate);
    insertQuery.addBindValue(tag);
    insertQuery.addBindValue(reminder);

    if (!insertQuery.exec()) {
        qDebug() << "Error inserting task into UserItems Table:" << insertQuery.lastError().text();
        return false;
    }

    qDebug() << "Items added to UserItems Table";
    return true;
}

QVector<QVector<QString>> DatabaseHandler::getTasks(int userID) {
    QSqlQuery query;
    query.prepare("SELECT TaskName, Description, Priority, Repeat, DueDate, Tag, Reminder FROM UserItems WHERE UserID = ?");
    query.addBindValue(userID);

    QVector<QVector<QString>> tasks;

    if (query.exec())
    {
        while (query.next())
        {
            QVector<QString> taskData;
            taskData.append(query.value(0).toString());
            taskData.append(query.value(1).toString());
            taskData.append(query.value(2).toString());
            taskData.append(query.value(3).toString());
            taskData.append(query.value(4).toString());
            taskData.append(query.value(5).toString());
            taskData.append(query.value(6).toString());

            tasks.append(taskData);
        }
    }
    else
    {
        qDebug() << "Failed to retrieve tasks:" << query.lastError();
    }

    return tasks;
}


int DatabaseHandler::checkEmailExists(const QString& email)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM UserInfo WHERE Email = :email");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return -1; // Indicates an error
    }

    query.next();
    return query.value(0).toInt();
}

bool DatabaseHandler::CreateUser(const QString& email, const QString& firstName, const QString& lastName, const QString& userName, const QString& password, const QString& role)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO UserInfo (Email, FName, LName, UserName, Password, Role) VALUES (?, ?, ?, ?, ?, ?)");
    insertQuery.addBindValue(email);
    insertQuery.addBindValue(firstName);
    insertQuery.addBindValue(lastName);
    insertQuery.addBindValue(userName);
    insertQuery.addBindValue(password);
    insertQuery.addBindValue(role);


    if (!insertQuery.exec())
    {
        qDebug() << "Failed to insert data into UserInfo table:" << insertQuery.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseHandler::displayTaskDetails(const QString &taskName, QString &taskDetails)
{
    // Retrieve task details from the database and display them
    QSqlQuery query;
    query.prepare("SELECT Description, Priority, Repeat, DueDate, Tag, Reminder FROM UserItems WHERE TaskName = ?");
    query.addBindValue(taskName);

    if (query.exec() && query.next())
    {
        QString description = query.value(0).toString();
        QString priority = query.value(1).toString();
        QString repeat = query.value(2).toString();
        QString dueDate = query.value(3).toString();
        QString tag = query.value(4).toString();
        QString reminder = query.value(5).toString();

        taskDetails = QString("Task Name: %1\nDescription: %2\nPriority: %3\nRepeat: %4\nDue Date: %5\nTag: %6\nReminder: %7")
                                  .arg(taskName)
                                  .arg(description)
                                  .arg(priority)
                                  .arg(repeat)
                                  .arg(dueDate)
                                  .arg(tag)
                                  .arg(reminder);
        return true;
    }
    else
    {
        return false;
    }
}

int DatabaseHandler::getUserID_FromUsername(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT UID FROM UserInfo WHERE Username = ?");
    query.addBindValue(username);

    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }
    else
    {
        qDebug() << "Failed to retrieve user ID:" << query.lastError().text();
        return -1; // Return an invalid user ID or handle the error appropriately
    }
}


bool DatabaseHandler::SearchForUsername(QString &searchQuery, QString &UserName, QString &FName, QString &LName, QString &Email)
{

    QSqlQuery query;
    query.prepare("SELECT UserName, FName, LName, Email FROM UserInfo WHERE UserName = :Username_Text");
    query.bindValue(":Username_Text", searchQuery);
    if(query.exec())
    {
        while(query.next())
        {
            UserName = query.value(0).toString();
            FName = query.value(1).toString();
            LName = query.value(2).toString();
            Email = query.value(3).toString();
        }
    }
    else
    {
        return false;
    }
    return true;
}




QList<QString> DatabaseHandler::getUserTaskNames(int userID)
{
    QList<QString> tasks;

    QSqlQuery query;
    query.prepare("SELECT TaskName FROM UserItems WHERE UserID = ?");
    query.addBindValue(userID);

    if (query.exec())
    {
        while (query.next())
        {
            tasks.append(query.value(0).toString());
        }
    }
    else
    {
        qDebug() << "Failed to retrieve tasks:" << query.lastError().text();
    }

    return tasks;
}

/*
bool DatabaseHandler::deleteUser(QString &username)
{
    QSqlQuery query;
    query.prepare("DELETE FROM UserInfo WHERE UserName = :username");
    query.bindValue(":username", username);

    if (!query.exec())
    {
        qDebug() << "Failed to delete user:" << query.lastError().text();
        return false;
    }
    else
    {
        if (query.numRowsAffected() == 0)
        {
            qDebug() << "No user found with the username:" << username;
            return false;  // Indicate that the user was not found
        }
        return true;
    }
}
*/

bool DatabaseHandler::GetUserDetails(int &ID, QString &UserName, QString &FName, QString &LName, QString &Email)
{

    QSqlQuery query;
    query.prepare("SELECT UserName, FName, LName, Email FROM UserInfo WHERE UID = :UID");
    query.bindValue(":UID", ID);
    if(query.exec())
    {
        while(query.next())
        {
            UserName = query.value(0).toString();
            FName = query.value(1).toString();
            LName = query.value(2).toString();
            Email = query.value(3).toString();
        }
    }
    else
    {
        return false;
    }
    return true;
}


QString DatabaseHandler::Login(const QString &Username, const QString &Password)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM UserInfo WHERE UserName = :username AND Password = :password");
    qry.bindValue(":username", Username);
    qry.bindValue(":password", Password);

    if (qry.exec())
    {
        if (qry.next())
        {
            QString userID = qry.value("UID").toString(); // Assuming there's a 'UID' column in your UserInfo table
            QString role = qry.value("Role").toString(); // Assuming there's a 'Role' column in your UserInfo table
            qDebug() << userID << "This is the UID";

            if (role == "User")
            {
                QSqlQuery updateAllFalseQry;
                updateAllFalseQry.prepare("UPDATE UserInfo SET LastToLogin = 'False' WHERE UID != :userid");
                updateAllFalseQry.bindValue(":userid", userID);
                if (!updateAllFalseQry.exec())
                {
                    qDebug() << "Failed to set other LastToLogin to false:" << updateAllFalseQry.lastError().text();
                }

                QSqlQuery updateQry;
                updateQry.prepare("UPDATE UserInfo SET LastToLogin = 'True' WHERE UID = :userid");
                updateQry.bindValue(":userid", userID);
                if (!updateQry.exec())
                {
                    qDebug() << "Failed to update LastToLogin:" << updateQry.lastError().text();
                }
                qDebug() << "role is user";
                return role;
            }
            else if (role == "Admin")
            {
                qDebug() << "role is admin";
                return role;
            }
            else
            {
                qDebug() << "login unsuccessful";
                return "login unsuccessful";
            }
        }
        else
        {
            // Query executed but no results found
            qDebug() << "Invalid username or password.";
            return "login unsuccessful";
        }
    }
    else
    {
        // Query failed to execute
        qDebug() << "Query execution failed:" << qry.lastError().text();
        return "login unsuccessful";
    }
}

bool DatabaseHandler::removeTask(const QString &taskName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM UserItems WHERE TaskName = :taskName");
    query.bindValue(":taskName", taskName);
    return query.exec();
}

DatabaseHandler::DeleteUserStatus DatabaseHandler::deleteUser(const QString &username) {
    QSqlQuery query;
    query.prepare("DELETE FROM UserInfo WHERE UserName = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Failed to delete user:" << query.lastError().text();
        return DatabaseError;
    }

    if (query.numRowsAffected() == 0) {
        return UserNotFound;
    }

    return Success;
}


