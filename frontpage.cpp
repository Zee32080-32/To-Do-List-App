#include "frontpage.h"
#include "ui_frontpage.h"

FrontPage::FrontPage(const QString &username, QWidget *parent): QMainWindow(parent), ui(new Ui::FrontPage), dbHandler(new DatabaseHandler),
task(new Task), profile(nullptr), user(nullptr)
{

    if (!dbHandler->connect())
    {
        qDebug() << "Failed to connect to the database in front page class.";
    }

    userID = dbHandler->getUserID_FromUsername(username);

    if (user) {
        qDebug() << user->getUserName();
    } else {
        qDebug() << "user is null!";
    }

    qDebug() << userID;
    ui->setupUi(this);
    ui->Repeat_comboBox->addItems({ "Daily", "Weekly", "Monthly", "Yearly", "Custom", "Never" });
    ui->AddTag_comboBox->addItems({"#Travel", "#Gym", "#Groceries", "#Shopping", "Custom"});
    ui->Reminder_comboBox->addItems({"Remind in 24 hrs", "Remind in a week", "Remind in a month", "Never"});
    ui->Priority_comboBox->addItems({"Low", "Medium", "High"});
    ui->TaskDetails_widget->hide();

    LoadTasks();
}

FrontPage::~FrontPage() {
    delete ui;
    delete task;
}

void FrontPage::LoadTasks() {
    QVector<QVector<QString>> taskRecords = dbHandler->getTasks(userID);
    tasks.clear(); // Clear the task list

    ui->Tasks_listWidget->clear(); // Clear the list widget

    for (int i = 0; i < taskRecords.size(); ++i) {
        TaskData taskData;

        taskData.taskName = taskRecords[i][0];
        taskData.description = taskRecords[i][1];
        taskData.priority = taskRecords[i][2];
        taskData.repeat = taskRecords[i][3];
        taskData.dueDate = QDateTime::fromString(taskRecords[i][4], "dd/MM/yyyy hh:mm");
        taskData.tag = taskRecords[i][5];
        taskData.reminder = taskRecords[i][6];

        tasks.insert(i, taskData);

        QListWidgetItem *item = new QListWidgetItem(ui->Tasks_listWidget);
        TaskItemWidget *taskItemWidget = new TaskItemWidget(taskData.taskName);
        item->setSizeHint(taskItemWidget->sizeHint());
        ui->Tasks_listWidget->setItemWidget(item, taskItemWidget);

        connect(taskItemWidget, &TaskItemWidget::viewDetailsClicked, this, &FrontPage::displayTaskDetails);
    }
}

void FrontPage::on_AddTask_pushButton_clicked() {
    ui->TaskDetails_widget->show();
}

void FrontPage::on_CreateTask_pushButton_clicked()
{
    QString taskName = ui->TName_lineEdit->text();
    QString Description = ui->Desc_textEdit->toPlainText();
    QString dueDateStr = ui->DDate_dateTimeEdit->dateTime().toString(Qt::ISODate);
    QDateTime dueDate = QDateTime::fromString(dueDateStr, Qt::ISODate);    QString Repeat = ui->Repeat_comboBox->currentText();
    QString Tag = ui->AddTag_comboBox->currentText();
    QString Reminder = ui->Reminder_comboBox->currentText();
    QString Priority = ui->Priority_comboBox->currentText();

    // Validate task name
    if (!Validation::isNotEmpty(taskName)) {
        QMessageBox::warning(this, "Validation Error", "Task name cannot be empty.");
        return;
    }

    // Validate priority
    if (!Validation::isNotEmpty(Priority) || Priority == "Select Priority") {
        QMessageBox::warning(this, "Validation Error", "Please select a priority.");
        return;
    }

    // Validate repeat
    if (!Validation::isNotEmpty(Repeat) || Repeat == "Select Repeat") {
        QMessageBox::warning(this, "Validation Error", "Please select a repeat option.");
        return;
    }

    // Validate tag
    if (!Validation::isNotEmpty(Tag) || Tag == "Select Tag") {
        QMessageBox::warning(this, "Validation Error", "Please select a tag.");
        return;
    }

    // Validate tag
    if (!Validation::isNotEmpty(Reminder) || Reminder == "Reminder") {
        QMessageBox::warning(this, "Validation Error", "Please select a Reminder.");
        return;
    }

    // Validate due date
    if (dueDate < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Validation Error", "Due date cannot be set before today's date.");
        return;
    }


    task->setTaskName(taskName.toStdString());
    task->setDescription(Description.toStdString());
    task->setDueDate(dueDateStr.toStdString()); // Pass the ISO 8601 string to setDueDate
    task->setRepeat(Repeat.toStdString());
    task->addTag(Tag.toStdString());
    task->setReminder(Reminder.toStdString());
    task->setPriority(Priority.toStdString());

    bool success = dbHandler->insertTask(userID, QString::fromStdString(task->getTaskName()),
                                         QString::fromStdString(task->getDescription()),
                                         QString::fromStdString(task->getPriority()),
                                         QString::fromStdString(task->getRepeat()),
                                         QString::fromStdString(task->getDueDate()),
                                         QString::fromStdString(task->getTags()),
                                         QString::fromStdString(task->getReminder()));
    if (!success) {
        qDebug() << "Failed to add task to the database.";
        return;
    }

    qDebug() << "Items added to UserItems Table";

    // Clear the existing tasks and reload
    ui->Tasks_listWidget->clear();
    tasks.clear();
    LoadTasks();
}

void FrontPage::markTaskCompleted(const QString &taskName) {
    // Remove the task from the database
    bool success = dbHandler->removeTask(taskName);
    if (!success) {
        qDebug() << "Failed to remove task from the database.";
        return;
    }

    // Remove the task from the UI list
    for (int i = 0; i < ui->Tasks_listWidget->count(); ++i) {
        QListWidgetItem *item = ui->Tasks_listWidget->item(i);
        TaskItemWidget *taskItemWidget = qobject_cast<TaskItemWidget *>(ui->Tasks_listWidget->itemWidget(item));
        if (taskItemWidget && taskItemWidget->getTaskName() == taskName) {
            delete item;
            break;
        }
    }

    qDebug() << "Task marked as completed and removed from the list.";
}

void FrontPage::displayTaskDetails(const QString &taskName) {
    QString taskDetails;
    bool displayTaskDetails = dbHandler->displayTaskDetails(taskName, taskDetails);

    if (displayTaskDetails) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Task Details"));
        msgBox.setText(taskDetails);
        QPushButton *completeButton = msgBox.addButton(tr("Mark Task Completed"), QMessageBox::ActionRole);
        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == completeButton) {
            markTaskCompleted(taskName);
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to retrieve task details."));
        qDebug() << "Error";
    }
}

void FrontPage::AddCustomValueToComboBox(QComboBox *comboBox, int Index) {
    if (comboBox->itemText(Index) == "Custom") {
        bool ok;
        QString customItem = QInputDialog::getText(this, tr("Custom Value"), tr("Enter custom Value:"), QLineEdit::Normal, "", &ok);
        if (ok && !customItem.isEmpty()) {
            int customIndex = comboBox->findText(customItem);
            if (customIndex == -1) {
                comboBox->addItem(customItem);
                customIndex = comboBox->count() - 1;
            }
            comboBox->setCurrentIndex(customIndex);
        } else {
            // Reset to previous selection if no custom item is entered
            comboBox->setCurrentIndex(0); // or any previous valid index
        }
    }
}

void FrontPage::on_Repeat_comboBox_currentIndexChanged(int index) {
    AddCustomValueToComboBox(ui->Repeat_comboBox, index);
}

void FrontPage::on_AddTag_comboBox_currentIndexChanged(int index) {
    AddCustomValueToComboBox(ui->AddTag_comboBox, index);
    for (int i = 0; i < ui->AddTag_comboBox->count(); ++i) {
        QString itemText = ui->AddTag_comboBox->itemText(i);
        if (!itemText.startsWith("#") && itemText != "Custom") {
            ui->AddTag_comboBox->setItemText(i, "#" + itemText);
        }
    }
}

void FrontPage::getUserID_FromUsername(const QString &username) {
    dbHandler->getUserID_FromUsername(username);
}

void FrontPage::loadUserTasks() {}

void FrontPage::sortAndDisplayTasks(const QList<TaskData> &tasks) {
    ui->Tasks_listWidget->clear();
    for (const TaskData &task : tasks) {
        QListWidgetItem *item = new QListWidgetItem(ui->Tasks_listWidget);
        TaskItemWidget *taskItemWidget = new TaskItemWidget(task.taskName);
        item->setSizeHint(taskItemWidget->sizeHint());
        ui->Tasks_listWidget->setItemWidget(item, taskItemWidget);

        connect(taskItemWidget, &TaskItemWidget::viewDetailsClicked, this, &FrontPage::displayTaskDetails);
    }
}

void FrontPage::on_Urgent_pushButton_clicked() {
    // Retrieve tasks from the database
    //QMap<int, TaskData> tasks = readTasksFromDatabase();

    // Sort tasks by priority
    QList<TaskData> sortedTasks = sortTasksByPriority(tasks);

    // Display the sorted tasks
    sortAndDisplayTasks(sortedTasks);
}

int FrontPage::priorityToInteger(const QString &priority) {
    if (priority == "High")
        return 3;
    else if (priority == "Medium")
        return 2;
    else // Low or any other value is considered Low priority
        return 1;
}

QList<TaskData> FrontPage::sortTasksByPriority(const QMap<int, TaskData> &tasks) {
    QList<TaskData> sortedTasks = tasks.values();
    std::sort(sortedTasks.begin(), sortedTasks.end(), [this](const TaskData &a, const TaskData &b) {
        return priorityToInteger(a.priority) > priorityToInteger(b.priority);
    });
    return sortedTasks;
}

QList<TaskData> FrontPage::sortTasksByDueDate(const QMap<int, TaskData> &tasks) {
    QList<TaskData> sortedTasks = tasks.values();

    // Sort tasks by due date
    std::sort(sortedTasks.begin(), sortedTasks.end(), [](const TaskData &a, const TaskData &b) {
        qDebug() << "Comparing due dates:" << a.dueDate << b.dueDate;
        return a.dueDate < b.dueDate;
    });

    return sortedTasks;
}

void FrontPage::on_DueToday_pushButton_clicked() {
    // Retrieve tasks from the database
    //QMap<int, TaskData> tasks = readTasksFromDatabase();

    // Sort tasks by due date
    QList<TaskData> sortedTasks = sortTasksByDueDate(tasks);

    // Display the sorted tasks
    sortAndDisplayTasks(sortedTasks);
}

std::optional<TaskData> FrontPage::searchTaskByName(const QString &taskName) {
    //QMap<int, TaskData> tasks = readTasksFromDatabase(); // Read tasks from the database

    for (const TaskData &task : tasks) {
        if (task.taskName.contains(taskName, Qt::CaseInsensitive)) {
            return task; // Return the matching task
        }
    }

    return std::nullopt; // Return an empty optional if no task is found
}

void FrontPage::on_Search_pushButton_clicked() {
    QString searchQuery = ui->Search_lineEdit->text().trimmed();

    if (!Validation::isNotEmpty(searchQuery)) {
        QMessageBox::warning(this, "Search Error", "Please enter a task name to search.");
        return;
    }

    std::optional<TaskData> matchingTask = searchTaskByName(searchQuery);

    if (!matchingTask.has_value()) {
        QMessageBox::information(this, "No Results", "No tasks found matching the search query.");
        return;
    }

    const TaskData &task = matchingTask.value();
    QString taskDetails = QString("Task Name: %1\nDescription: %2\nPriority: %3\nRepeat: %4\nDue Date: %5\nTag: %6\nReminder: %7")
                              .arg(task.taskName)
                              .arg(task.description)
                              .arg(task.priority)
                              .arg(task.repeat)
                              .arg(task.dueDate.toString("dd/MM/yyyy hh:mm"))
                              .arg(task.tag)
                              .arg(task.reminder);

    QMessageBox::information(this, tr("Task Details"), taskDetails);
}

void FrontPage::on_Calender_pushButton_clicked()
{



}

void FrontPage::on_ViewProfile_pushButton_clicked() {
    if (!profile)
    {
        profile = new Profile(userID);
    }
    profile->show();
    this->close();
}



void FrontPage::on_Logout_pushButton_clicked()
{
    QCoreApplication::quit();
}
