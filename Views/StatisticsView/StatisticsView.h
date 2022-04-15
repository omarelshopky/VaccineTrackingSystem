#pragma once

#include <QMainWindow>
#include "ui_StatisticsView.h"

class StatisticsView : public QMainWindow, public Ui::StatisticsView
{
	Q_OBJECT

public:
	StatisticsView(QWidget *parent = Q_NULLPTR);
	~StatisticsView();
};
