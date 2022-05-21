#pragma once

#include <QStackedWidget>
#include <qlineedit.h>
#include <QMainWindow>
#include "ui_UserProfileView.h"
#include <iostream>
#include"../../Controllers/UserController/UserController.h"
#include "../../Config.h"

class UserProfileView : public QMainWindow, public Ui::UserProfileView
{
	Q_OBJECT
		UserController userController;
	QStackedWidget* widgetsStack;
	User user;
	bool view = true;
	UserController x;
public:
	UserProfileView(QWidget *parent = Q_NULLPTR);
	~UserProfileView();
	void setUser(User);
private:
	void toggleIsVaccinatedCheck();
	bool handleErrors(map<string, string> state);
	void handleAbroad(QString country);
	void initGovComboBox();
	void CloseButton();
	void Edit();
	void View();
	void SaveButton();
	void getInformation();
	void setInformation();
	void setInformation(User);
	void ShowPassword();
	void LogOutButton();
};
