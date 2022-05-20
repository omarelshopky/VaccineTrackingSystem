#pragma once

#include <QMainWindow>
#include <QtCharts>
#include "ui_StatisticsView.h"
#include "../../Controllers/AdminController/AdminController.h"


class StatisticsView : public QMainWindow, public Ui::StatisticsView
{
	Q_OBJECT

private:
	QStackedWidget *widgetsStack;
	AdminController adminController;
	QPieSeries* vaccinatedPieChartSeries;
	QPieSeries* ageDountChartSeries;
	QChartView* areaBarChartVeiw;
	map<string, vector<string>> customStatValues;
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
	 * @brief Initialize the vaccinated piechart that visualize system records
	 */
	void initVaccinatedPieChart();


	/**
	 * @brief Update the vaccinated piechart that visualize system records
	 * @param map<int, int> vaccinatedStat map of the count of each vaccinated doses
	 */
	void updateVaccinatedPieChart(map<int, int> vaccinatedStat);


	/**
	 * @brief Initalize the age dount chart that visualize system records
	 */
	void initAgeDonutChart();


	/**
	 * @brief Update the age dount chart that visualize system records
	 * @param map<string, int> ageStat map of the count of each age class
	 */
	void updateAgeDonutChart(map<string, int> ageStat);


	/**
	 * @brief Initialize items in the area table and configue central alignment
	 */
	void initAreaTableItems();


	/**
	 * @brief Draws the Area barchart that visualize each area records
	 * @param map<std::string, int> areaStat map of the count of each area in the database
	 */
	void drawAreaBarChart(map<std::string, int> areaStat);


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


	/*
	 * @brief Sets the vaccinated tab data
	 */
	void setVaccinatedData();


	/*
	 * @brief Sets the gender tab data
	 */
	void setGenderData();


	/*
	 * @brief Sets the area tab data
	 */
	void setAreaData();


	/*
	 * @brief Sets the age tab data
	 */
	void setAgeData();

	
	/*
	 * @brief Handle buttons click to select custom features to filter with
	 */
	void toggleDoseBtn(int dosesNumber);
	void toggleGenderBtn(string gender);
	void toggleAgeBtn(string ageClass);
	void toggleFilterValue(string filterName, string value);
	void handleAreaTableClick(int x, int y);


	string prepareFilterValuesString(vector<string> values);

	void calculateCustomStat();

	bool evaluateGenderConditions(User user);
	bool evaluateVaccineConditions(User user);
	bool evaluateAgeConditions(User user);
};
