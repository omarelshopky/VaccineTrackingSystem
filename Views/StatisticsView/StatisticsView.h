#pragma once

#include <QMainWindow>
#include <QtCharts>
#include <iomanip>
#include <locale>
#include "ui_StatisticsView.h"
#include "../../Controllers/AdminController/AdminController.h"


class StatisticsView : public QMainWindow, public Ui::StatisticsView
{
	Q_OBJECT

private:
	QStackedWidget *widgetsStack;
	AdminController adminController;
	int allUsersCount;

public:
	StatisticsView(QStackedWidget *widgetsStack, QWidget *parent = Q_NULLPTR);
	~StatisticsView();


	/**
	 * @brief Updates the Ui data with the records from the database
	 */
	void updateUiData();

private:
	/**
	 * @brief Draws the vaccinated piechart that visualize system records
	 * @param map<int, int> vaccinatedStat map of the count of each vaccinated doses
	 */
	void drawVaccinatedPieChart(map<int, int> vaccinatedStat);


	/**
	 * @brief Draws the Area barchart that visualize each area records
	 * @param map<std::string, int> areaStat map of the count of each area in the database
	 */
	void drawAreaBarChart(map<std::string, int> areaStat);


	/**
	 * @brief Initialize items in the area table and configue central alignment
	 */
	void initAreaTableItems();


	/**
	 * @brief Format numbers by add commas after each 3 digits
	 * @param int number to be formated
	 * @return string the number after adding the commas 
	 */
	std::string fromatNumberCommas(int number);


	/**
	 * @brief Arrange number to shown in the view components
	 * @param int number to be formated
	 * @return QString the number after suitable formating
	 */
	QString arrangeNumber(int number);


	/*
	 * @brief Returns to the previous view (Admin Dashboard)
	 */
	void previousView();
};
