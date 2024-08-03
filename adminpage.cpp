#include "adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent): QMainWindow(parent), ui(new Ui::AdminPage), deleteUserWidget(nullptr)
{
    ui->setupUi(this);
    if (!dbHandler.connect())
    {
        qDebug() << "Failed to connect to the database in front page class.";
    }
}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::on_Search_pushButton_clicked()
{
    QString searchQuery = ui->Search_lineEdit->text().trimmed();
    if (searchQuery.isEmpty())
    {
        QMessageBox::warning(this, "Search Error", "Please enter a task name to search.");
        return;
    }

    QString UserName, FName, LName, Email;
    bool success = dbHandler.SearchForUsername(searchQuery, UserName, FName, LName, Email);

    if (success)
    {
        ui->UserNameDetails_label->setText(UserName);
        ui->FNameDetails_label->setText(FName);
        ui->LNameDetails_label->setText(LName);
        ui->EmailDetails_label->setText(Email);

        int userID = dbHandler.getUserID_FromUsername(searchQuery);
        if (userID != -1)
        {
            loadUserTasks(userID);
        }
        else
        {
            qDebug() << "Failed to retrieve userID for username:" << searchQuery;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to retrieve user details.");
        qDebug() << "Failed to retrieve user details for username:" << searchQuery;
    }
}

void AdminPage::displayTaskDetails(const QString &taskName)
{
    QString taskDetails;
    if (dbHandler.displayTaskDetails(taskName, taskDetails))
    {
        QMessageBox::information(this, tr("Task Details"), taskDetails);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Failed to retrieve task details."));
        qDebug() << "Error retrieving task details for:" << taskName;
    }
}

void AdminPage::loadUserTasks(int UserID)
{
    QList<QString> taskNames = dbHandler.getUserTaskNames(UserID);

    for (const QString &taskName : taskNames)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->Tasks_listWidget);
        TaskItemWidget *taskItemWidget = new TaskItemWidget(taskName);
        item->setSizeHint(taskItemWidget->sizeHint());
        ui->Tasks_listWidget->setItemWidget(item, taskItemWidget);

        connect(taskItemWidget, &TaskItemWidget::viewDetailsClicked, this, &AdminPage::displayTaskDetails);
    }
}

void AdminPage::on_Delete_pushButton_clicked()
{
    if (!deleteUserWidget) {
        deleteUserWidget = new DeleteUser(this);
        deleteUserWidget->setAttribute(Qt::WA_DeleteOnClose); // Ensure proper cleanup
        deleteUserWidget->setMinimumSize(300, 200); // Set a reasonable minimum size
    }

    deleteUserWidget->show();
    deleteUserWidget->raise(); // Bring the widget to the front
    deleteUserWidget->activateWindow(); // Activate the widget window

    qDebug() << "DeleteUser widget shown";
}
