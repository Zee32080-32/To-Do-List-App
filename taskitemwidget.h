#ifndef TASKITEMWIDGET_H
#define TASKITEMWIDGET_H

#include <QWidget>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>

class TaskItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TaskItemWidget(const QString &taskName, QWidget *parent = nullptr);
    QString getTaskName() const;



signals:
    void viewDetailsClicked(const QString &taskName);

private:
    QLabel *taskNameLabel;
    QPushButton *viewDetailsButton;
    QString taskName;


private slots:
    void onViewDetailsButtonClicked();
};

#endif // TASKITEMWIDGET_H
