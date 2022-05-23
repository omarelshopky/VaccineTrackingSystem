#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_AdminDashboardView.h"
#include "../../Controllers/AdminController/AdminController.h"
#include "../StatisticsView/StatisticsView.h"
#include "../WaitingListView/WaitingListView.h"


class AdminDashboardView : public QMainWindow, public Ui::AdminDashboardView
{
	Q_OBJECT

	QStackedWidget* widgetsStack;
	AdminController adminController;
	const int usersCountInTab = 1000;
	int currentUserTab = 0;
	bool isSearching = false;
	int currentUsersShown = 0;
	vector<User> users;
	bool isDeprecated = true;

public:
	AdminDashboardView(QStackedWidget *widgetsStack, QWidget *parent = Q_NULLPTR);
	~AdminDashboardView();
	void updateUserTable();

private:
	void initUserTable();
	void clearView();
	bool changeTab(bool isNext);
	void setRowData(int row, User user);
	void navigate(int pageIndex);
	void search();
	void cancleSearch(QString text);
	void deleteUsers();
	void logout();
};
