#include "RegisterView.h"



RegisterView::RegisterView(QStackedWidget* widgetsStack, QWidget *parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	setupUi(this);
	fullNameError->hide();
	nationalIdError->hide();
	passwordError->hide();
	nationalIdInput->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	
	// Attach signals function
	connect(registerBtn, &QPushButton::clicked, this, &RegisterView::signup);
	connect(isVaccinatedCheck, &QCheckBox::clicked, this, &RegisterView::toggleIsVaccinatedCheck);
	connect(loginBtn, &QCheckBox::clicked, this, &RegisterView::goToLogin);
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
	this->widgetsStack->setCurrentIndex(0);
}