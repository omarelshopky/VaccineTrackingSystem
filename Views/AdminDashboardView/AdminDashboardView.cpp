#include "AdminDashboardView.h"


AdminDashboardView::AdminDashboardView(QStackedWidget *widgetsStack, QWidget *parent) :
	QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;
    setupUi(this);

	// Initialize components prop
	nationalIdInput->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	initUserTable();
	clearView();

	// Attach signals function
	connect(statBtn, &QPushButton::clicked, this, [this] { navigate(STATISTICS_VIEW_INDEX); });
	connect(addAdminBtn, &QPushButton::clicked, this, [this] { navigate(ADMIN_PRIVILAGE_VIEW_INDEX); });
	connect(waitingListBtn, &QPushButton::clicked, this, [this] { navigate(WAITING_LIST_VIEW_INDEX); });
	connect(nextBtn, &QPushButton::clicked, this, [this] { changeTab(true); });
	connect(previousBtn, &QPushButton::clicked, this, [this] { changeTab(false); });
	connect(searchBtn, &QPushButton::clicked, this, &AdminDashboardView::search);
	connect(nationalIdInput, &QLineEdit::textChanged, this, &AdminDashboardView::cancleSearch);
	connect(deleteBtn, &QPushButton::clicked, this, &AdminDashboardView::deleteUsers);
	connect(logoutBtn, &QPushButton::clicked, this, &AdminDashboardView::logout);
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
		if (allUsersCount > i) {
			setRowData(i, users[i + (long long)currentUserTab * usersCountInTab]);
			currentUsersShown = i;
		}
		else
			usersTable->hideRow(i);
	}

	// Row for User retrieved from search 
	usersTable->insertRow(usersTable->rowCount());
	for (int j = 0; j < 8; j++) {
		usersTable->setItem(usersCountInTab, j, new QTableWidgetItem());
	}
}


void AdminDashboardView::updateUserTable() {
	int allUsersCount = adminController.viewUsers().size();
	vector<User> users = User::select();

	for (int i = 0; i < usersCountInTab; i++) {
		long long index = i + (long long)currentUserTab * usersCountInTab;
		if (allUsersCount > index) {
			setRowData(i, users[index]);
			currentUsersShown = i;
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
		usersTable->clearSelection();
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
	switch (pageIndex)
	{
	case STATISTICS_VIEW_INDEX:
		((StatisticsView*)(widgetsStack->widget(STATISTICS_VIEW_INDEX)))->updateUiData();
		break;
	case WAITING_LIST_VIEW_INDEX:
		((WaitingListView*)(widgetsStack->widget(WAITING_LIST_VIEW_INDEX)))->updateUiData();
	default:
		break;
	}

	widgetsStack->setCurrentIndex(pageIndex);
}


void AdminDashboardView::search() {
	User user = adminController.viewUser(nationalIdInput->text().toStdString());

	if (user.nationalID != "") {
		for (int i = 0; i < currentUsersShown+1; i++) {
			usersTable->hideRow(i);
		}

		nationalIdError->hide();
		setRowData(usersCountInTab, user);
		isSearching = true;
	}
	else {
		nationalIdError->show();
	}
}


void AdminDashboardView::cancleSearch(QString text="manual") {
	if ((text == "" || text == "manual") && isSearching) {
		isSearching = false;
		usersTable->hideRow(usersCountInTab);
		
		if (text == "") {
			for (int i = 0; i < currentUsersShown+1; i++) {
				usersTable->showRow(i);
			}
		}
	}
	deleteMsg->hide();
}
      
		
void AdminDashboardView::deleteUsers() {
	if (isSearching) {
		adminController.deleteUser(usersTable->item(usersCountInTab, 0)->text().toStdString());
		cancleSearch();
		nationalIdInput->clear();
	}
	else {
		for (int i = 0; i < usersCountInTab; i++) {
			if (usersTable->item(i, 0)->isSelected()) {
				adminController.deleteUser(usersTable->item(i, 0)->text().toStdString());
			}
		}
		usersTable->clearSelection();
	}
	
	updateUserTable();
	deleteMsg->show();
}


void AdminDashboardView::logout() {
	widgetsStack->setCurrentIndex(LOGIN_VIEW_INDEX);
	clearView();
}


void AdminDashboardView::clearView() {
	currentUserTab = 0;
	nationalIdInput->clear();
	nationalIdError->hide();
	deleteMsg->hide();
	usersTable->clearSelection();
}