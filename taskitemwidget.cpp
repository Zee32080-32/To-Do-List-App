#include "taskitemwidget.h"

TaskItemWidget::TaskItemWidget(const QString &taskName, QWidget *parent): QWidget(parent), taskName(taskName)
{
    taskNameLabel = new QLabel(taskName, this);
    viewDetailsButton = new QPushButton("View Details", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(taskNameLabel);
    layout->addWidget(viewDetailsButton);

    setLayout(layout);

    connect(viewDetailsButton, &QPushButton::clicked, this, &TaskItemWidget::onViewDetailsButtonClicked);
}

void TaskItemWidget::onViewDetailsButtonClicked()
{
    emit viewDetailsClicked(taskName);
}

QString TaskItemWidget::getTaskName() const
{
    return taskName;

}
