#include "UserProfileView.h"

UserProfileView::UserProfileView(QStackedWidget* widgetsStack, QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	setupUi(this);

	// Initialize components prop
	clearView();

	// Attach signals function
	connect(EditAndCloseBtn, &QPushButton::clicked, this, &UserProfileView::toggleEditMode);
	connect(countryComboBox, &QComboBox::currentTextChanged, this, &UserProfileView::handleAbroad);
	connect(saveBtn, &QPushButton::clicked, this, &UserProfileView::saveEdit);
	connect(isVaccinatedCheck, &QCheckBox::clicked, this, &UserProfileView::toggleIsVaccinatedCheck);
	connect(togglePassBtn, &QPushButton::clicked, this, &UserProfileView::togglePasswordVisibility);
	connect(backBtn, &QPushButton::clicked, this, &UserProfileView::logout);
}


void UserProfileView::setUser(string nationalId)  {
	this->user = userController.display(nationalId);
	getUserInformation();
}

/*********************  Information    ****************/

void UserProfileView::setUserInformation()
{
	user.fullName = fullNameInput->text().toStdString();
	user.password = passwordInput->text().toStdString();
	user.isVaccinated = isVaccinatedCheck->isChecked();
	if (user.isVaccinated) {
		user.dosesNumber = (oneDoseRadioBtn->isChecked() ? 1 : 2);
	}
	else {
		user.dosesNumber = 0;
	}
	user.country = (countryComboBox->currentIndex() == 0 ? "Egypt" : "Abroad");
	user.government = (countryComboBox->currentIndex() == 0 ? governments[governmentComboBox->currentIndex()] : "Abroad");
	user.age = ageSpinBox->value();
	user.gender = (genderComboBox->currentIndex() == 0 ? "Male" : "Female");
}


void UserProfileView::setUserInformation(User oldUser) {
	user.fullName = oldUser.fullName;
	user.password = oldUser.password;
	user.isVaccinated = oldUser.isVaccinated;
	user.age = oldUser.age;
	user.country = oldUser.country;
	user.dosesNumber = oldUser.dosesNumber;
	user.gender = oldUser.gender;
	user.government = oldUser.government;
}


void UserProfileView::getUserInformation()
{
	fullNameInput->setText(user.fullName.c_str());
	nationalIdInput->setText(user.nationalID.c_str());
	passwordInput->setText(user.password.c_str());
	genderComboBox->setCurrentIndex((user.gender == "Male") ? 0 : 1);
	ageSpinBox->setValue(user.age);
	isVaccinatedCheck->setChecked(user.isVaccinated);

	if (isVaccinatedCheck->isChecked())
	{
		if (user.dosesNumber==1)
			oneDoseRadioBtn->setChecked(true);
		else
			twoDoseRadioBtn->setChecked(true);
	}

	handleAbroad(user.country.c_str());
	if (user.country == "Egypt")
	{
		countryComboBox->setCurrentIndex(0);

		int indx = 0;
		for (int i = 0; i < sizeof(governments); i++)
		{
			if (user.government == governments[i])
			{
				indx = i;
				break;
			}
		}

		governmentComboBox->setCurrentIndex(indx);
	}
	else
	{
		countryComboBox->setCurrentIndex(1);
	}
}


/*********************  Edit and View    ****************/

void UserProfileView::toggleEditMode() {
	view = !view;

	fullNameInput->setEnabled(!view);
	fullNameInput->setStyleSheet(fullNameInput->styleSheet());
	passwordInput->setEnabled(!view);
	passwordInput->setStyleSheet(passwordInput->styleSheet());
	ageSpinBox->setEnabled(!view);
	ageSpinBox->setStyleSheet(ageSpinBox->styleSheet());
	genderComboBox->setEnabled(!view);
	genderComboBox->setStyleSheet(genderComboBox->styleSheet());
	countryComboBox->setEnabled(!view);
	countryComboBox->setStyleSheet(countryComboBox->styleSheet());
	governmentComboBox->setEnabled(!view);
	governmentComboBox->setStyleSheet(governmentComboBox->styleSheet());
	isVaccinatedCheck->setEnabled(!view);
	oneDoseRadioBtn->setEnabled(!view);
	twoDoseRadioBtn->setEnabled(!view);
	saveBtn->setEnabled(!view);
	backBtn->setEnabled(view);
	togglePassBtn->setEnabled(!view);
	
	if (view) {
		EditAndCloseBtn->setText("Edit");
		getUserInformation();
	}
	else {
		EditAndCloseBtn->setText("Close");
	}
}


/*********************  Buttons    ****************/

void UserProfileView::saveEdit()
{
	User old = user;
	setUserInformation();

	if (handleErrors(userController.edit(user))) {
		toggleEditMode();
	}
	else { // Return user data after edition
		setUserInformation(old);
	}
}


void UserProfileView::logout()
{
	this->user = User();

	this->widgetsStack->setCurrentIndex(LOGIN_VIEW_INDEX);
}

/*********************  Handling    ****************/

bool UserProfileView::handleErrors(map<string, string> state) {
	bool valid = true;

	if (state["fullName"] != "") {
		fullNameError->setText(QString::fromStdString(state["fullName"]));
		fullNameError->show();
		valid = false;
	}
	else {
		fullNameError->hide();
	}

	if (state["password"] != "") {
		passwordError->setText(QString::fromStdString(state["password"]));
		passwordError->show();
		valid = false;
	}
	else {
		passwordError->hide();
	}

	return valid;
}

void UserProfileView::handleAbroad(QString country) {


	if (country == "Abroad") {
		governmentComboBox->clear();
		governmentComboBox->addItem("Abroad");
	}
	else {
		this->initGovComboBox();
	}
}


void UserProfileView::initGovComboBox() {
	governmentComboBox->clear();

	for (auto gov : governments) {
		governmentComboBox->addItem(QString::fromStdString(gov));
	}
}


void UserProfileView::toggleIsVaccinatedCheck()
{
	oneDoseRadioBtn->setEnabled(isVaccinatedCheck->isChecked());
	twoDoseRadioBtn->setEnabled(isVaccinatedCheck->isChecked());
}


void UserProfileView::togglePasswordVisibility()
{
	if (togglePassBtn->isChecked()) {
		passwordInput->setEchoMode(QLineEdit::Normal);
	}
	else {
		passwordInput->setEchoMode(QLineEdit::Password);
	}
}


void UserProfileView::clearView() {
	view = false;
	togglePassBtn->setChecked(false);
	toggleEditMode();
	fullNameError->hide();
	passwordError->hide();
}

UserProfileView::~UserProfileView() {}
