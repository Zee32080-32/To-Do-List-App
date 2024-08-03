#include "CalendarDialog.h"
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent), calendar(new QCalendarWidget(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(calendar);
    setLayout(layout);
    setWindowTitle("Calendar");

    connect(calendar, &QCalendarWidget::selectionChanged, this, &CalendarDialog::onCalendarSelectionChanged);
}

void CalendarDialog::setTasks(const QVector<TaskData> &tasks)
{
    tasksMap.clear();
    for (const TaskData &task : tasks) {
        QDate date = task.dueDate.date();
        if (!tasksMap.contains(date)) {
            tasksMap[date] = QVector<TaskData>();
        }
        tasksMap[date].append(task);
    }
    displayTasks();
}

void CalendarDialog::displayTasks()
{
    // Clear previous decorations
    calendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // Add tasks to the calendar
    for (auto it = tasksMap.begin(); it != tasksMap.end(); ++it) {
        QDate date = it.key();
        QVector<TaskData> tasks = it.value();
        // Example: Add custom decorations, you might need a custom widget or a different approach
        // calendar->setDateTextFormat(date, format);
    }
}

void CalendarDialog::handleTaskClick(const QDate &date)
{
    if (tasksMap.contains(date)) {
        QVector<TaskData> tasks = tasksMap[date];
        QString taskDetails;
        for (const TaskData &task : tasks) {
            taskDetails += QString("Task Name: %1\nDescription: %2\nPriority: %3\n\n")
                               .arg(task.taskName)
                               .arg(task.description)
                               .arg(task.priority);
        }
        QMessageBox::information(this, "Tasks", taskDetails);
    }
}

void CalendarDialog::onCalendarSelectionChanged()
{
    QDate selectedDate = calendar->selectedDate();
    handleTaskClick(selectedDate);
}
