#include "StatisticsView.h"

StatisticsView::StatisticsView(QStackedWidget *widgetsStack, QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	// Setup the UI components
	setupUi(this);

	// Initialize components prop
	customStatValues["vaccine"] = {};
	customStatValues["age"] = {};
	customStatValues["gender"] = {};
	initVaccinatedPieChart();
	initAgeDonutChart();
	initAreaTableItems();
	updateUiData();

	// Attach signals function
	connect(backBtn, &QPushButton::clicked, this, &StatisticsView::previousView);
	connect(vaccinated2DosesBtn, &QPushButton::clicked, this, [this]{ toggleDoseBtn(2); });
	connect(vaccinated1DoseBtn, &QPushButton::clicked, this, [this] { toggleDoseBtn(1); });
	connect(vaccinated0DoseBtn, &QPushButton::clicked, this, [this] { toggleDoseBtn(0); });
	connect(genderFemaleBtn, &QPushButton::clicked, this, [this] { toggleGenderBtn("Female"); });
	connect(genderMaleBtn, &QPushButton::clicked, this, [this] { toggleGenderBtn("Male"); });
	connect(age5_17Btn, &QPushButton::clicked, this, [this] { toggleAgeBtn("5 to 17"); });
	connect(age18_30Btn, &QPushButton::clicked, this, [this] { toggleAgeBtn("18 to 30"); });
	connect(age31_64Btn, &QPushButton::clicked, this, [this] { toggleAgeBtn("31 to 64"); });
	connect(age65Btn, &QPushButton::clicked, this, [this] { toggleAgeBtn("over 65"); });
	connect(areaTable, &QTableWidget::cellClicked, this, &StatisticsView::handleAreaTableClick);
	connect(cstmCalcBtn, &QPushButton::clicked, this, &StatisticsView::calculateCustomStat);
}


StatisticsView::~StatisticsView() {}


void StatisticsView::updateUiData() {
	// Set Registered people data
	allUsersCount = adminController.getAllUsersCount();
	regPeopleCountLbl->setText(arrangeNumber(allUsersCount));

	this->setVaccinatedData();
	this->setGenderData();
	this->setAreaData();
	this->setAgeData();
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


void StatisticsView::initVaccinatedPieChart() {
	this->vaccinatedPieChartSeries = new QPieSeries();

	vaccinatedPieChartSeries->append("0 Dose", 5);
	vaccinatedPieChartSeries->append("1 Dose", 5);
	vaccinatedPieChartSeries->append("2 Doses", 5);

	// Show percentage of each sliece
	vaccinatedPieChartSeries->setLabelsVisible();
	vaccinatedPieChartSeries->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

	// Configure slices color
	vaccinatedPieChartSeries->slices()[0]->setBrush(QColor(178, 6, 0));
	vaccinatedPieChartSeries->slices()[1]->setBrush(QColor(255, 140, 50));
	vaccinatedPieChartSeries->slices()[2]->setBrush(QColor(107, 203, 119));

	QChart* chart = new QChart();
	chart->addSeries(vaccinatedPieChartSeries);
	chart->legend()->hide();

	chart->setContentsMargins(-78, -78, -78, -78); // Remove useless margin
	chart->setBackgroundBrush(QBrush(QColor(127, 181, 255))); // Set the same color for char background

	vaccinatedPieChartFrame->layout()->addWidget(new QChartView(chart));
}


void StatisticsView::updateVaccinatedPieChart(map<int, int> vaccinatedStat) {
	vaccinatedPieChartSeries->slices()[0]->setValue(vaccinatedStat[0]);
	vaccinatedPieChartSeries->slices()[1]->setValue(vaccinatedStat[1]);
	vaccinatedPieChartSeries->slices()[2]->setValue(vaccinatedStat[2]);

	for (auto slice : vaccinatedPieChartSeries->slices()) slice->setLabel(QString("%1%").arg(100 * slice->percentage(), 0, 'f', 1));
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

	areaBarChartVeiw = new QChartView(chart);

	if (areaBarChartFrame->layout()->count() == 0) areaBarChartFrame->layout()->addWidget(areaBarChartVeiw);
}


void StatisticsView::initAgeDonutChart() {
	ageDountChartSeries = new QPieSeries();
	ageDountChartSeries->setHoleSize(0.35);

	ageDountChartSeries->append("5 to 17", 5);
	ageDountChartSeries->append("18 to 30", 5);
	ageDountChartSeries->append("31 to 64", 5);
	ageDountChartSeries->append("over 65", 5);

	// Show percentage of each sliece
	ageDountChartSeries->setLabelsVisible();
	ageDountChartSeries->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

	// Configure slices color
	ageDountChartSeries->slices()[0]->setBrush(QColor(41, 126, 183));
	ageDountChartSeries->slices()[1]->setBrush(QColor(107, 203, 119));
	ageDountChartSeries->slices()[2]->setBrush(QColor(255, 140, 50));
	ageDountChartSeries->slices()[3]->setBrush(QColor(178, 6, 0));

	QChart* chart = new QChart();
	chart->addSeries(ageDountChartSeries);
	chart->legend()->hide();

	chart->setContentsMargins(-75, -75, -75, -75); // Remove useless margin
	chart->setBackgroundBrush(QBrush(QColor(127, 181, 255))); // Set the same color for char background

	ageDountChartFrame->layout()->addWidget(new QChartView(chart));
}


void StatisticsView::updateAgeDonutChart(map<string, int> ageStat) {
	ageDountChartSeries->slices()[0]->setValue(ageStat["5<>17"]);
	ageDountChartSeries->slices()[1]->setValue(ageStat["18<>30"]);
	ageDountChartSeries->slices()[2]->setValue(ageStat["31<>64"]);
	ageDountChartSeries->slices()[3]->setValue(ageStat["<65"]);

	for (auto slice : ageDountChartSeries->slices()) slice->setLabel(QString("%1%").arg(100 * slice->percentage(), 0, 'f', 1));
}


std::string StatisticsView::fromatNumberCommas(int number) {
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << number;
	return ss.str();
}


QString StatisticsView::arrangeNumber(int number) {
	return QString::fromStdString(fromatNumberCommas(number));
}


void StatisticsView::previousView() {
	widgetsStack->setCurrentIndex(ADMIN_DASHBOARD_VIEW_INDEX);
}


void StatisticsView::setVaccinatedData() {
	map<int, int> vaccinatedStat = adminController.statOfAllDoses();

	vaccinated2DosesCountLbl->setText(arrangeNumber(vaccinatedStat[2]));
	vaccinated1DosesCountLbl->setText(arrangeNumber(vaccinatedStat[1]));
	vaccinated0DosesCountLbl->setText(arrangeNumber(vaccinatedStat[0]));
	waitingCountLbl->setText(arrangeNumber(vaccinatedStat[0]));

	updateVaccinatedPieChart(vaccinatedStat);
}


void StatisticsView::setGenderData() {
	map<std::string, int> genderStat = adminController.statOfAllGenders();
	float malePercentage = 100 * ((float)genderStat["Male"] / (float)allUsersCount);

	genderMaleCountLbl->setText(arrangeNumber(genderStat["Male"]));
	genderFemaleCountLbl->setText(arrangeNumber(genderStat["Female"]));

	genderMalePercentLbl->setText(QString("%1%").arg(malePercentage, 0, 'f', 1));
	genderFemalePercentLbl->setText(QString("%1%").arg(100.0 - malePercentage, 0, 'f', 1));

	genderPercentBar->setValue(malePercentage);
}


void StatisticsView::setAreaData() {
	map<std::string, int> areaStat = adminController.statOfAllGovernments();
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


void StatisticsView::setAgeData() {
	map<std::string, int> ageStat = adminController.statOfAllAges();

	age5_17CountLbl->setText(arrangeNumber(ageStat["5<>17"]));
	age18_30CountLbl->setText(arrangeNumber(ageStat["18<>30"]));
	age31_64CountLbl->setText(arrangeNumber(ageStat["31<>64"]));
	age65CountLbl->setText(arrangeNumber(ageStat["<65"]));

	updateAgeDonutChart(ageStat);
}


void StatisticsView::toggleDoseBtn(int dosesNumber) {
	vaccinatedPieChartSeries->slices()[dosesNumber]->setExploded(!vaccinatedPieChartSeries->slices()[dosesNumber]->isExploded());
	toggleFilterValue("vaccine", (dosesNumber == 2) ? "2x Doses" : (dosesNumber == 1) ? "1x Dose" : "0x Dose");
	cstmVaccinatedValuesLbl->setText(QString::fromStdString(prepareFilterValuesString(customStatValues["vaccine"])));
}


void StatisticsView::toggleGenderBtn(string gender) {
	toggleFilterValue("gender", gender);
	cstmGenderValuesLbl->setText(QString::fromStdString(prepareFilterValuesString(customStatValues["gender"])));
}


void StatisticsView::toggleAgeBtn(string ageClass) {
	int sliceIndex = 0;

	if (ageClass == "5 to 17") sliceIndex = 0;
	else if (ageClass == "18 to 30") sliceIndex = 1;
	else if (ageClass == "31 to 64") sliceIndex = 2;
	else if (ageClass == "over 65") sliceIndex = 3;

	ageDountChartSeries->slices()[sliceIndex]->setExploded(!ageDountChartSeries->slices()[sliceIndex]->isExploded());
	toggleFilterValue("age", ageClass);
	cstmAgeValuesLbl->setText(QString::fromStdString(prepareFilterValuesString(customStatValues["age"])));
}

void StatisticsView::toggleFilterValue(string filterName, string value) {
	auto it = std::find(customStatValues[filterName].begin(), customStatValues[filterName].end(), value);
	if (it != customStatValues[filterName].end())
		customStatValues[filterName].erase(it);
	else
		customStatValues[filterName].push_back(value);
}


string StatisticsView::prepareFilterValuesString(vector<string> values) {
	if (values.size() == 0) return "-";

	string res = values[0];

	for (int i = 1; i < values.size(); i++) {
		res += ", " + values[i];
	}

	return res;
}


void StatisticsView::handleAreaTableClick(int x, int y) {
	cstmAreaValuesLbl->setText(areaTable->item(x, 0)->text());
}


void StatisticsView::calculateCustomStat() {
	vector<User> users;

	if (cstmAreaValuesLbl->text() == "-")
		users = User::select();
	else
		users = User::select({ {"Government", "=", cstmAreaValuesLbl->text().toStdString()} });

	int cnt = 0;

	for (auto user : users) {
		bool valid = true;
		if (evaluateGenderConditions(user) && evaluateAgeConditions(user) && evaluateVaccineConditions(user)) {
			cnt++;
		}
	}

	cstmCountValueLbl->setText(arrangeNumber(cnt));
	cstmPercentValueLbl->setText(QString("%1%").arg(100 * ((float)cnt / (float)allUsersCount), 0, 'f', 1));
}


bool StatisticsView::evaluateGenderConditions(User user) {
	switch (customStatValues["gender"].size()) {
	case 0:
		return true;
	case 1:
		return (user.gender == customStatValues["gender"][0]);
	case 2:
		return (user.gender == "Male" || user.gender == "Female");
	}
}


bool StatisticsView::evaluateVaccineConditions(User user) {
	if (customStatValues["vaccine"].size() == 0) {
		return true;
	}
	else {
		bool valid = false;

		for (auto rule : customStatValues["vaccine"]) {
			int doses = (rule == "2x Doses") ? 2 : (rule == "1x Dose") ? 1 : 0;

			if (doses == user.dosesNumber) valid = true;
		}

		return valid;
	}
}


bool StatisticsView::evaluateAgeConditions(User user) {
	if (customStatValues["age"].size() == 0) {
		return true;
	}
	else {
		bool valid = false;

		for (auto rule : customStatValues["age"]) {
			if (rule == "5 to 17") {
				if (user.age >= 5 && user.age <= 17) valid = true;
			} 
			else if (rule == "18 to 30") {
				if (user.age >= 18 && user.age <= 30) valid = true;
			}
			else if (rule == "31 to 64") {
				if (user.age >= 31 && user.age <= 64) valid = true;
			}
			else if (rule == "over 65") {
				if (user.age >= 65) valid = true;
			}
		}

		return valid;
	}
}