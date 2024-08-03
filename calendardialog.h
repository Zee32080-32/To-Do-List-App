#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QMap>

struct TaskData {
    QString taskName;
    QString description;
    QString priority;
    QDateTime dueDate;
    // Other fields...
};

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    void setTasks(const QVector<TaskData> &tasks); // Set tasks for the calendar

private:
    QCalendarWidget *calendar;
    QMap<QDate, QVector<TaskData>> tasksMap; // Map of date to tasks
    void displayTasks();
    void handleTaskClick(const QDate &date);

private slots:
    void onCalendarSelectionChanged(); // Slot for calendar date change
};

#endif // CALENDARDIALOG_H
