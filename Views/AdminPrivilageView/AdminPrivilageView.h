#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_AdminPrivilageView.h"
#include "../../Controllers/AdminController/AdminController.h"
#include <qvalidator.h>

class AdminPrivilageView : public QMainWindow, public Ui::AdminPrivilageView
{
	Q_OBJECT

	AdminController adminController;
	QStackedWidget* widgetStack;

public:
	AdminPrivilageView(QStackedWidget* widgetStack, QWidget* parent = Q_NULLPTR);
	~AdminPrivilageView();

private:
	void giveAdminPrivilage();
	void goBack();
	void clearView();
};
