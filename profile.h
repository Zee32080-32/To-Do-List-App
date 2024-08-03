#ifndef PROFILE_H
#define PROFILE_H
#include "databasehandler.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Profile;
}

class Profile : public QMainWindow
{
    Q_OBJECT

public:
    explicit Profile(const int &userID, QWidget *parent = nullptr);
    ~Profile();

private:
    Ui::Profile *ui;
    DatabaseHandler dbHandler;
    QSqlDatabase mydb;


    void DisplayUserDetails(int ID);


};

#endif // PROFILE_H
