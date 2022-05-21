#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_RegisterView.h"
#include"../../Controllers/UserController/UserController.h"

class RegisterView : public QMainWindow, public Ui::RegisterView
{
	Q_OBJECT

		UserController userController;
	QStackedWidget *widgetsStack;

public:
	RegisterView(QStackedWidget* widgetsStack, QWidget *parent = Q_NULLPTR);
	~RegisterView();

private:
	void signup();
	void toggleIsVaccinatedCheck();
	bool handleErrors(map<string, string> state);
	void goToLogin();
	void clearView();
	void handleAbroad(QString country);
	void initGovComboBox();
	void togglePasswordVisibility();
};
