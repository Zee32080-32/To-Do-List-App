# DESCRIPTION OF PROJECT
- To do list app
- Create an account to create tasks
- you can set task details
- view all your tasks
- mark a task as completed
- email verification for account creation
- made with QT C++ and data is stored on SQLite

## How to deploy
- install QT
- open the QT project file
- to use the app and for the email verification to work you need to follow these steps
    - sign in to your google account
    - click on "Security" in the left-hand menu
    - set up 2 step verifcation if you have not already
    - stay in the 2 step verification page and then click on app passwords
    - create an app name
    - when the password is given to you copy it into your laptop notes
    - go to line 127 on the createAccount.cpp and place your app username as the value 
    - go to line 128 on the createAccount.cpp and place your unique password as the value
    - now you can run the code :)

