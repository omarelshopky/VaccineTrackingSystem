#pragma once

#include <QMainWindow>
#include "ui_UserProfileView.h"

class UserProfileView : public QMainWindow, public Ui::UserProfileView
{
	Q_OBJECT

public:
	UserProfileView(QWidget *parent = Q_NULLPTR);
	~UserProfileView();
};
