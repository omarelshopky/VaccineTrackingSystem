#pragma once

#include <QMainWindow>
#include "ui_LoginView.h"

class LoginView : public QMainWindow, public Ui::LoginView
{
	Q_OBJECT

public:
	LoginView(QWidget *parent = Q_NULLPTR);
	~LoginView();
};
