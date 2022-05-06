#include "StatisticsView.h"

StatisticsView::StatisticsView(QStackedWidget *widgetsStack, QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	// Setup the UI components
	setupUi(this);
	initAreaTableItems();
	updateUiData();
	
	connect(backBtn, &QPushButton::clicked, this, &StatisticsView::previousView);
}


StatisticsView::~StatisticsView() {}


void StatisticsView::updateUiData() {
	allUsersCount = adminController.getAllUsersCount();

	// Set Registered people data
	regPeopleCountLbl->setText(arrangeNumber(allUsersCount));

	// Set Vaccinated data
	map<int, int> vaccinatedStat = adminController.statOfAllDoses();

	vaccinated2DosesCountLbl->setText(arrangeNumber(vaccinatedStat[2]));
	vaccinated1DosesCountLbl->setText(arrangeNumber(vaccinatedStat[1]));
	vaccinated0DosesCountLbl->setText(arrangeNumber(vaccinatedStat[0]));

	drawVaccinatedPieChart(vaccinatedStat);

	// Set Gender data
	map<std::string, int> genderStat = adminController.statOfAllGenders();
	float malePercentage = 100 * ((float)genderStat["male"] / (float)allUsersCount);

	genderMaleCountLbl->setText(arrangeNumber(genderStat["male"]));
	genderFemaleCountLbl->setText(arrangeNumber(genderStat["female"]));

	genderMalePercentLbl->setText(QString("%1%").arg(malePercentage, 0, 'f', 1));
	genderFemalePercentLbl->setText(QString("%1%").arg(100.0-malePercentage, 0, 'f', 1));

	genderPercentBar->setValue(malePercentage);

	// Set Area data
	map<std::string, int> areaStat = adminController.statOfAllGovernment();
	int abroadCount = allUsersCount;

	// Set area table
	for (int i = 0; i < 22; i++) { 
		areaTable->item(i, 0)->setText(QString::fromStdString(governments[i]));
		areaTable->item(i, 1)->setText(arrangeNumber(areaStat[governments[i]]));
		areaTable->item(i, 2)->setText(QString("%1%").arg(100.0 * ((float)areaStat[governments[i]] / (float)allUsersCount), 0, 'f', 1));

		abroadCount -= areaStat[governments[i]];
	}

	areaTable->item(22, 0)->setText("Abroad");
	areaTable->item(22, 1)->setText(arrangeNumber(abroadCount));
	areaTable->item(22, 2)->setText(QString("%1%").arg(100.0 * ((float)abroadCount / (float)allUsersCount), 0, 'f', 1));

	areaStat["Abroad"] = abroadCount;
	drawAreaBarChart(areaStat);
}


void StatisticsView::initAreaTableItems() {
	for (int i = 0; i < 23; i++) 
		for (int j = 0; j < 3; j++)
		{
			areaTable->setItem(i, j, new QTableWidgetItem());
			if (j != 0)
				areaTable->item(i, j)->setTextAlignment(Qt::AlignHCenter);
		}
}


void StatisticsView::drawVaccinatedPieChart(map<int, int> vaccinatedStat) {
	QPieSeries* series = new QPieSeries();

	series->append("2 Doses", vaccinatedStat[2]);
	series->append("1 Dose", vaccinatedStat[1]);
	series->append("0 Dose", vaccinatedStat[0]);

	// Show percentage of each sliece
	series->setLabelsVisible();
	series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
	for (auto slice : series->slices()) slice->setLabel(QString("%1%").arg(100 * slice->percentage(), 0, 'f', 1));

	// Configure slices color
	series->slices()[0]->setBrush(QColor(107, 203, 119));
	series->slices()[1]->setBrush(QColor(255, 140, 50));
	series->slices()[2]->setBrush(QColor(178, 6, 0));

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->legend()->hide();
	
	chart->setContentsMargins(-95, -95, -95, -95); // Remove useless margin
	chart->setBackgroundBrush(QBrush(QColor(127, 181, 255))); // Set the same color for char background

	QChartView* chartView = new QChartView(chart);
	vaccinatedPieChartFrame->layout()->addWidget(chartView);
}


void StatisticsView::drawAreaBarChart(map<std::string, int> areaStat) {
	QBarSeries* series = new QBarSeries();
	QBarSet* set = new QBarSet("Area");
	QStringList areas;

	int mx = 0;

	for (map<std::string, int>::iterator it = areaStat.begin(); it != areaStat.end(); it++) {
		areas << QString::fromStdString(it->first);
		*set << it->second;
		mx = max(mx, it->second);
	}
	series->append(set);
	
	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(areas);
	chart->addAxis(axisX, Qt::AlignBottom);
	chart->axisX()->setLabelsAngle(270);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	axisY->setRange(0, mx);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chart->legend()->setVisible(false);
	chart->setContentsMargins(-35, -10, -30, -30); // Remove useless margin
	chart->setBackgroundBrush(QBrush(QColor(127, 181, 255))); // Set the same color for char background

	QChartView* chartView = new QChartView(chart);
	areaBarChartFrame->layout()->addWidget(chartView);
}


std::string StatisticsView::fromatNumberCommas(int number)
{
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << number;
	return ss.str();
}


QString StatisticsView::arrangeNumber(int number) {
	return QString::fromStdString(fromatNumberCommas(number));
}


void StatisticsView::previousView() {
	widgetsStack->setCurrentIndex(3);
}