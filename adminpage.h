#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "databasehandler.h"
#include "taskitemwidget.h"
#include "deleteuser.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private slots:
    void on_Search_pushButton_clicked();

    void on_Delete_pushButton_clicked();

private:
    Ui::AdminPage *ui;
    QSqlDatabase mydb;
    DatabaseHandler dbHandler;
    int getUserID_FromUsername(const QString &username);
    void loadUserTasks(int UserID);
    void displayTaskDetails(const QString &taskName);
    void deleteUser(); // And this declaration as well
    DeleteUser *deleteUserWidget;

};

#endif // ADMINPAGE_H
