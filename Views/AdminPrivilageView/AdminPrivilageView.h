#pragma once

#include <QMainWindow>
#include "ui_AdminPrivilageView.h"

class AdminPrivilageView : public QMainWindow, public Ui::AdminPrivilageView
{
	Q_OBJECT

public:
	AdminPrivilageView(QWidget *parent = Q_NULLPTR);
	~AdminPrivilageView();
};
