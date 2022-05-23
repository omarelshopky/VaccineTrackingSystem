#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_WaitingListView.h"
#include "../../Controllers/AdminController/AdminController.h"
#include "../AdminDashboardView/AdminDashboardView.h"


class WaitingListView : public QMainWindow, public Ui::WaitingListView
{
	Q_OBJECT

	QStackedWidget* widgetsStack;
	AdminController adminController;
	queue<User> doseWaitingList[2];
	const int usersCountInTab = 1000;
	int currentTab[2];

public:
	WaitingListView(QStackedWidget* widgetsStack, QWidget *parent = Q_NULLPTR);
	~WaitingListView();
	void updateUiData();

private:
	void initDoseWaitingListQueue();
	void initDoseTable(bool isDose2Table);
	bool changeTab(bool isDose2Table, bool isNext);
	void updateDoseTable(bool isDose2Table);
	void setRowData(bool isDose2Table, int row, User user);
	void setDoseUserCount(bool isDose2Table, int count);
	void finishUserDose(bool isDose2Table);
	void goBack();
	void clearView();
};

