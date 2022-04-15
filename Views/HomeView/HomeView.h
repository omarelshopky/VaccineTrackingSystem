#pragma once

#include <QMainWindow>
#include "ui_HomeView.h"

class HomeView : public QMainWindow, public Ui::HomeView
{
	Q_OBJECT

public:
	HomeView(QWidget *parent = Q_NULLPTR);
	~HomeView();
};
