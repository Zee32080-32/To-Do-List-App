#ifndef FRONTPAGE_H
#define FRONTPAGE_H

#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QMainWindow>
#include <optional>
#include "task.h"
#include "DatabaseHandler.h"
#include "taskitemwidget.h"
#include "profile.h"
#include "user.h"
#include <QPainter>
#include "validation.h"

struct TaskData
{
    QString taskName;
    QString description;
    QString priority;
    QString repeat;
    QDateTime dueDate;
    QString tag;
    QString reminder;
};

namespace Ui
{
    class FrontPage;
}

class FrontPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontPage(const QString &username, QWidget *parent = nullptr);
    ~FrontPage();

private slots:
    void on_AddTask_pushButton_clicked();

    void on_CreateTask_pushButton_clicked();

    void on_Repeat_comboBox_currentIndexChanged(int index);

    void on_AddTag_comboBox_currentIndexChanged(int index);

    void on_Urgent_pushButton_clicked();

    void on_DueToday_pushButton_clicked();

    void on_Search_pushButton_clicked();

    void on_Calender_pushButton_clicked();

    void on_ViewProfile_pushButton_clicked();

    void on_Logout_pushButton_clicked();

private:
    Ui::FrontPage *ui;
    QSqlDatabase mydb;
    DatabaseHandler *dbHandler;
    Task *task; // Pointer to the current Task
    void AddCustomValueToComboBox(QComboBox *comboBox, int Index);
    void displayTaskDetails(const QString &taskName);
    QMap<int, TaskData> tasks; // Member variable to store tasks
    Profile *profile;
    User *user;
    void LoadTasks();
    void markTaskCompleted(const QString &taskName);

    QCalendarWidget *calendarWidget;
    void updateCalendar();




    int userID;

    void getUserID_FromUsername(const QString &username);
    void loadUserTasks();
    QMap<int, TaskData> readTasksFromDatabase();
    void sortAndDisplayTasks(const QList<TaskData> &tasks);

    QList<TaskData> sortTasksByPriority(const QMap<int, TaskData> &tasks);
    QList<TaskData> sortTasksByDueDate(const QMap<int, TaskData> &tasks);


    int priorityToInteger(const QString &priority);
    std::optional<TaskData> searchTaskByName(const QString &taskName);



};


#endif // FRONTPAGE_H
