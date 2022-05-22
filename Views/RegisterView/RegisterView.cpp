#include "RegisterView.h"



RegisterView::RegisterView(QStackedWidget* widgetsStack, QWidget *parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	setupUi(this);

	// Initialize components prop
	nationalIdInput->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	this->clearView();

	// Attach signals function
	connect(registerBtn, &QPushButton::clicked, this, &RegisterView::signup);
	connect(isVaccinatedCheck, &QCheckBox::clicked, this, &RegisterView::toggleIsVaccinatedCheck);
	connect(loginBtn, &QCheckBox::clicked, this, &RegisterView::goToLogin);
	connect(countryComboBox, &QComboBox::currentTextChanged, this, &RegisterView::handleAbroad);
	connect(togglePassBtn, &QCheckBox::clicked, this, &RegisterView::togglePasswordVisibility);
}


RegisterView::~RegisterView() {}


void RegisterView::signup()
{
	map<string, string> state = userController.signup(
		firstNameInput->text().toStdString() + " " + lastNameInput->text().toStdString(),
		nationalIdInput->text().toStdString(),
		passwordInput->text().toStdString(),
		genderComboBox->currentText().toStdString(),
		ageSpinBox->value(),
		countryComboBox->currentText().toStdString(),
		governmentComboBox->currentText().toStdString(),
		isVaccinatedCheck->isChecked(),
		(isVaccinatedCheck->isChecked()) ? ((oneDoseRadioBtn->isChecked()) ? 1 : 2) : 0
	);

	if (handleErrors(state)) goToLogin();
}


void RegisterView::toggleIsVaccinatedCheck() {
	oneDoseRadioBtn->setEnabled(!oneDoseRadioBtn->isEnabled());
	twoDoseRadioBtn->setEnabled(!twoDoseRadioBtn->isEnabled());
}


bool RegisterView::handleErrors(map<string, string> state) {
	bool valid = true;

	if (state["nationalID"] != "") {
		nationalIdError->setText(QString::fromStdString(state["nationalID"]));
		nationalIdError->show();
		valid = false;
	}
	else {
		nationalIdError->hide();
	}

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


void RegisterView::goToLogin() {
	this->clearView();

	this->widgetsStack->setCurrentIndex(LOGIN_VIEW_INDEX);
}


void RegisterView::clearView() {
	this->initGovComboBox();

	firstNameInput->clear();
	lastNameInput->clear();
	nationalIdInput->clear();
	passwordInput->clear();
	ageSpinBox->setValue(5);
	countryComboBox->setCurrentIndex(0);
	genderComboBox->setCurrentIndex(0);
	governmentComboBox->setCurrentIndex(0);
	isVaccinatedCheck->setChecked(false);
	oneDoseRadioBtn->setEnabled(false);
	twoDoseRadioBtn->setEnabled(false);

	fullNameError->hide();
	nationalIdError->hide();
	passwordError->hide();
}


void RegisterView::handleAbroad(QString country) {
	

	if (country == "Abroad") {
		governmentComboBox->clear();
		governmentComboBox->addItem("Abroad");
	}
	else {
		this->initGovComboBox();
	}
}


void RegisterView::initGovComboBox() {
	governmentComboBox->clear();

	for (auto gov : governments) {
		governmentComboBox->addItem(QString::fromStdString(gov));
	}
}


void RegisterView::togglePasswordVisibility()
{
	if (togglePassBtn->isChecked()) {
		passwordInput->setEchoMode(QLineEdit::Normal);
	}
	else {
		passwordInput->setEchoMode(QLineEdit::Password);
	}
}
