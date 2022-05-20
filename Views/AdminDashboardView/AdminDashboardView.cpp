#include "AdminDashboardView.h"


AdminDashboardView::AdminDashboardView(QStackedWidget *widgetsStack, QWidget *parent) :
	QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;
    setupUi(this);

	// Initialize components prop
	nationalIdInput->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	initUserTable();

	// Attach signals function
	connect(statBtn, &QPushButton::clicked, this, [this] { navigate(4); });
	connect(addAdminBtn, &QPushButton::clicked, this, [this] { navigate(5); });
	connect(nextBtn, &QPushButton::clicked, this, [this] { changeTab(true); });
	connect(previousBtn, &QPushButton::clicked, this, [this] { changeTab(false); });
	//connect(backBtn, &QPushButton::clicked, this, &AdminDashboardView::previousView);
}


AdminDashboardView::~AdminDashboardView() {}


void AdminDashboardView::initUserTable() {
	vector<User> users = adminController.viewUsers();
	int allUsersCount = users.size();

	for (int i = 0; i < usersCountInTab; i++) {
		usersTable->insertRow(usersTable->rowCount());

		for (int j = 0; j < 8; j++) {
			usersTable->setItem(i, j, new QTableWidgetItem());
		}
		if (allUsersCount > i)
			setRowData(i, users[i + currentUserTab * usersCountInTab]);
		else
			usersTable->hideRow(i);
	}
}


void AdminDashboardView::updateUserTable() {
	int allUsersCount = adminController.viewUsers().size();
	vector<User> users = User::select();

	for (int i = 0; i < usersCountInTab; i++) {
		if (allUsersCount > i + currentUserTab * usersCountInTab) {
			setRowData(i, users[i + currentUserTab * usersCountInTab]);
		}
		else {
			usersTable->hideRow(i);
		}
	}
}


bool AdminDashboardView::changeTab(bool isNext) {
	int allUsersCount = adminController.viewUsers().size();
	bool changed = false;

	if (isNext) {
		if (allUsersCount >= (currentUserTab + 1) * usersCountInTab) {
			currentUserTab++;
			changed = true;

			if (!previousBtn->isEnabled()) previousBtn->setEnabled(true);

			if (!(allUsersCount >= (currentUserTab + 1) * usersCountInTab)) {
				nextBtn->setEnabled(false);
			}
		}
	}
	else { 
		if (currentUserTab != 0) {
			currentUserTab--;
			changed = true;

			if (!nextBtn->isEnabled()) nextBtn->setEnabled(true);

			if (currentUserTab == 0) {
				previousBtn->setEnabled(false);
			}
		}
	}

	if (changed) {
		currentTabLbl->setText(QString::fromStdString(to_string(currentUserTab)));
		updateUserTable();
	}
	
	return changed;
}


void AdminDashboardView::setRowData(int row, User user) {
	usersTable->showRow(row);
	usersTable->item(row, 0)->setText(QString::fromStdString(user.nationalID));
	usersTable->item(row, 1)->setText(QString::fromStdString(user.fullName));
	usersTable->item(row, 2)->setText(QString::fromStdString(user.gender));
	usersTable->item(row, 3)->setText(QString::fromStdString(to_string(user.age)));
	usersTable->item(row, 4)->setText(QString::fromStdString(user.country));
	usersTable->item(row, 5)->setText(QString::fromStdString(user.government));
	usersTable->item(row, 6)->setText((user.isVaccinated)? "Yes" : "No");
	usersTable->item(row, 7)->setText(QString::fromStdString(to_string(user.dosesNumber)));
}


void AdminDashboardView::navigate(int pageIndex) {
	widgetsStack->setCurrentIndex(pageIndex);
}