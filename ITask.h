#ifndef ITASK_H
#define ITASK_H

#include <string>
#include <vector>

enum class Priority { LowPriority, MediumPriority, HighPriority};

class ITask {
public:
    enum Priority {
        Low,
        Medium,
        High
    };

    virtual ~ITask() = default;

    virtual std::string getTaskName() const = 0;
    virtual void setTaskName(const std::string& taskName) = 0;

    virtual std::string getRepeat() const = 0;
    virtual void setRepeat(const std::string& RepeatVal) = 0;

    virtual std::string getDescription() const = 0;
    virtual void setDescription(const std::string& description) = 0;

    virtual std::string getDueDate() const = 0;
    virtual void setDueDate(const std::string& dueDate) = 0;

    virtual std::string getPriority() const = 0;
    virtual void setPriority(const std::string& priority) = 0;

    virtual std::string getReminder() const = 0;
    virtual void setReminder(const std::string& reminder) = 0;

    virtual std::string getTags() const = 0;
    virtual void addTag(const std::string& tag) = 0;
    virtual void removeTag(const std::string& tag) = 0;

    virtual void AddTask() = 0;
    virtual void RemoveTask() = 0;
    virtual void TaskCompleted() = 0;


};


#endif // ITASK_H
