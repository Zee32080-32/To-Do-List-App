#ifndef TASK_H
#define TASK_H


#include "ITask.h"
#include <string>
#include <vector>

class Task : public ITask {
private:
    std::string taskName;
    std::string Repeat;
    std::string description;
    std::string dueDate;
    std::string priority;
    std::string reminder;
    std::string tags;

public:
    Task();
    ~Task() override = default;

    std::string getTaskName() const override;
    void setTaskName(const std::string& name) override;

    std::string getRepeat() const override;
    void setRepeat(const std::string& RepeatVal) override;

    std::string getDescription() const override;
    void setDescription(const std::string& desc) override;

    std::string getDueDate() const override;
    void setDueDate(const std::string& date) override;

    std::string getPriority() const override;
    void setPriority(const std::string& prio) override;

    std::string getReminder() const override;
    void setReminder(const std::string& rem) override;

    std::string getTags() const override;
    void addTag(const std::string& tag) override;
    void removeTag(const std::string& tag) override;

    void AddTask() override;
    void RemoveTask() override;
    void TaskCompleted() override;
};

#endif // TASK_H
