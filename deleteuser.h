#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "databasehandler.h"

class DeleteUser : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUser(QWidget *parent = nullptr);
    ~DeleteUser();

private slots:
    void deleteUser();

private:
    DatabaseHandler *dbHandler;
    QLineEdit *usernameLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // DELETEUSER_H
