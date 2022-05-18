#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <qvalidator.h>
#include "ui_LoginView.h"
#include "../../Controllers/AdminController/AdminController.h"
#include "../../Controllers/UserController/UserController.h"



class LoginView : public QMainWindow, public Ui::LoginView
{
	Q_OBJECT

    AdminController adminController;
	UserController userController;
	bool isAdmin = false;
	QStackedWidget *widgetStack;

public:
	LoginView(QStackedWidget *widgetStack, QWidget *parent = Q_NULLPTR);
	~LoginView();

private:
	void login();
	void changeUserType();
	void goToRegister();
	void clearView();
};
