#include "Task.h"

Task::Task()
{

}

std::string Task::getTaskName() const {
    return taskName;
}

void Task::setTaskName(const std::string& name) {
    taskName = name;
}

std::string Task::getRepeat() const {
    return Repeat;
}

void Task::setRepeat(const std::string& RepeatVal) {
    Repeat = RepeatVal;
}


std::string Task::getDescription() const {
    return description;
}

void Task::setDescription(const std::string& desc) {
    description = desc;
}

std::string Task::getDueDate() const {
    return dueDate;
}

void Task::setDueDate(const std::string& date) {
    dueDate = date;
}

std::string Task::getPriority() const {
    return priority;
}

void Task::setPriority(const std::string& prio) {
    priority = prio;
}

std::string Task::getReminder() const {
    return reminder;
}

void Task::setReminder(const std::string& rem) {
    reminder = rem;
}

std::string Task::getTags() const {
    return tags;
}

void Task::addTag(const std::string& tag) {
    tags = tag;
}

void Task::removeTag(const std::string& tag) {
    tags = "";
}

void Task::AddTask()
{}

void Task::RemoveTask()
{}

void Task::TaskCompleted()
{}
