#pragma once

#include <QMainWindow>
#include "ui_AdminDashboardView.h"

class AdminDashboardView : public QMainWindow, public Ui::AdminDashboardView
{
	Q_OBJECT

public:
	AdminDashboardView(QWidget *parent = Q_NULLPTR);
	~AdminDashboardView();
};
