#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_UserProfileView.h"
#include"../../Controllers/UserController/UserController.h"


class UserProfileView : public QMainWindow, public Ui::UserProfileView
{
	Q_OBJECT

	QStackedWidget* widgetsStack;
	UserController userController;
	User user;
	bool view = false;

public:
	UserProfileView(QStackedWidget *widgetsStack, QWidget *parent = Q_NULLPTR);
	~UserProfileView();
	void setUser(string nationalId);

private:
	void initGovComboBox();
	void getUserInformation();
	void toggleIsVaccinatedCheck();
	void togglePasswordVisibility();
	void handleAbroad(QString country);
	bool handleErrors(map<string, string> state);
	void clearView();
	void logout();
	void saveEdit();
	void toggleEditMode();
	void setUserInformation();
	void setUserInformation(User);
	void deleteUser();
};
