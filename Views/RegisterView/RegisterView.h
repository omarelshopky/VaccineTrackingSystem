#pragma once

#include <QMainWindow>
#include "ui_RegisterView.h"

class RegisterView : public QMainWindow, public Ui::RegisterView
{
	Q_OBJECT

public:
	RegisterView(QWidget *parent = Q_NULLPTR);
	~RegisterView();
};
