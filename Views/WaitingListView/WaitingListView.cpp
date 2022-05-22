#include "WaitingListView.h"

WaitingListView::WaitingListView(QStackedWidget* widgetsStack, QWidget *parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	setupUi(this);

	// Initialize components prop
	initDoseTable(0);
	initDoseTable(1);

	// Attach signals function
	connect(dose1NextBtn, &QPushButton::clicked, this, [this] { changeTab(0, true); });
	connect(dose1PreviousBtn, &QPushButton::clicked, this, [this] { changeTab(0, false); });
	connect(dose2NextBtn, &QPushButton::clicked, this, [this] { changeTab(1, true); });
	connect(dose2PreviousBtn, &QPushButton::clicked, this, [this] { changeTab(1, false); });
	connect(dose1FinishBtn, &QPushButton::clicked, this, [this] { finishUserDose(0); });
	connect(dose2FinishBtn, &QPushButton::clicked, this, [this] { finishUserDose(1); });
	connect(backBtn, &QPushButton::clicked, this, &WaitingListView::goBack);
}

WaitingListView::~WaitingListView() {}


void WaitingListView::initDoseWaitingListQueue() {
	vector<User> users = adminController.viewUsers();

	for (auto user : users) {
		if (user.dosesNumber != 2)
			doseWaitingList[user.dosesNumber].push(user);
	}

	setDoseUserCount(0, doseWaitingList[0].size());
	setDoseUserCount(1, doseWaitingList[1].size());
}


void WaitingListView::initDoseTable(bool isDose2Table) {
	QTableWidget* table = (isDose2Table) ? dose2Table : dose1Table;

	for (int i = 0; i < usersCountInTab; i++) {
		table->insertRow(table->rowCount());

		for (int j = 0; j < 6; j++) {
			table->setItem(i, j, new QTableWidgetItem());
		}
		table->hideRow(i);
	}
}


void WaitingListView::updateDoseTable(bool isDose2Table) {
	QTableWidget* table = (isDose2Table) ? dose2Table : dose1Table;
	queue <User> shownUsers = doseWaitingList[isDose2Table];

	for (int i = 0; i < currentTab[isDose2Table] * usersCountInTab; i++) {
		shownUsers.pop();
	}

	for (int i = 0; i < usersCountInTab; i++) {
		if (!shownUsers.empty()) {
			setRowData(isDose2Table, i, shownUsers.front());
			shownUsers.pop();
		}
		else {
			table->hideRow(i);
		}
	}
}


bool WaitingListView::changeTab(bool isDose2Table, bool isNext) {
	QPushButton* previousBtn = (isDose2Table) ? dose2PreviousBtn : dose1PreviousBtn;
	QPushButton* nextBtn = (isDose2Table) ? dose2NextBtn : dose1NextBtn;
	queue <User> shownUsers = doseWaitingList[isDose2Table];
	bool changed = false;

	if (isNext) {
		if (doseWaitingList[isDose2Table].size() >= ((long long)currentTab[isDose2Table] + 1) * usersCountInTab) {
			currentTab[isDose2Table]++;
			changed = true;

			if (!previousBtn->isEnabled()) previousBtn->setEnabled(true);

			if (doseWaitingList[isDose2Table].size() < ((long long)currentTab[isDose2Table] + 1) * usersCountInTab) {
				nextBtn->setEnabled(false);
			}
		}
	}
	else {
		if (currentTab[isDose2Table] != 0) {
			currentTab[isDose2Table]--;
			changed = true;

			if (!nextBtn->isEnabled()) nextBtn->setEnabled(true);

			if (currentTab[isDose2Table] == 0) {
				previousBtn->setEnabled(false);
			}
		}
	}

	if (changed) {
		((isDose2Table) ? dose2CurrentTabLbl : dose1CurrentTabLbl)->setText(QString::fromStdString(to_string(currentTab[isDose2Table]+1)));
		updateDoseTable(isDose2Table);
	}

	return changed;
}


void WaitingListView::setRowData(bool isDose2Table, int row, User user) {
	QTableWidget* table = (isDose2Table) ? dose2Table : dose1Table;

	table->showRow(row);
	table->item(row, 0)->setText(QString::fromStdString(user.nationalID));
	table->item(row, 1)->setText(QString::fromStdString(user.fullName));
	table->item(row, 2)->setText(QString::fromStdString(user.gender));
	table->item(row, 3)->setText(QString::fromStdString(to_string(user.age)));
	table->item(row, 4)->setText(QString::fromStdString(user.country));
	table->item(row, 5)->setText(QString::fromStdString(user.government));
}


void WaitingListView::finishUserDose(bool isDose2Table) {
	((isDose2Table) ? dose2Table : dose1Table)->hideRow(0);

	if (isDose2Table == 0) {
		doseWaitingList[1].push(doseWaitingList[0].front());
		setDoseUserCount(1, doseWaitingList[1].size());

		if (!(doseWaitingList[1].size() >= ((long long)currentTab[1] + 1) * usersCountInTab)) {
			updateDoseTable(1);
		}
	}

	User user;
	user.nationalID = ((isDose2Table) ? dose2Table : dose1Table)->item(0, 0)->text().toStdString();
	user.age = ((isDose2Table) ? dose2Table : dose1Table)->item(0, 3)->text().toInt();
	user.dosesNumber = isDose2Table + 1;
	user.isVaccinated = true;
	user.update();

	doseWaitingList[isDose2Table].pop();
	setDoseUserCount(isDose2Table, doseWaitingList[isDose2Table].size());
	updateDoseTable(isDose2Table);
}


void WaitingListView::goBack() {
	clearView();
	widgetsStack->setCurrentIndex(ADMIN_DASHBOARD_VIEW_INDEX);
}


void WaitingListView::clearView() {
	// Clear queue data
	for (int i = 0; i < 2; i++) {
		queue<User> empty;
		swap(doseWaitingList[i], empty);
	}
}


void WaitingListView::updateUiData() {
	initDoseWaitingListQueue();

	for (int i = 0; i < 2; i++) {
		currentTab[i] = 0;
		updateDoseTable(i);
	}
}


void WaitingListView::setDoseUserCount(bool isDose2Table, int count) {
	((isDose2Table) ? dose2CountLbl : dose1CountLbl)->setText(QString::fromStdString("x" + to_string(doseWaitingList[isDose2Table].size()) + " User"));
}