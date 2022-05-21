#include "UserProfileView.h"

UserProfileView::UserProfileView(QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetsStack = widgetsStack;

	setupUi(this);

	// Initialize components prop

	user = x.display("22222222222222");
	nationalIdInput->setReadOnly(true);
	getInformation();
	View();
	// Attach signals function
	connect(EditAndCloseBtn, &QPushButton::clicked, this, &UserProfileView::CloseButton);
	connect(isVaccinatedCheck, &QCheckBox::clicked, this, &UserProfileView::toggleIsVaccinatedCheck);
	connect(countryComboBox, &QComboBox::currentTextChanged, this, &UserProfileView::handleAbroad);
	connect(saveBtn, &QPushButton::clicked, this, &UserProfileView::SaveButton);
	connect(ShowPasswordCheck, &QCheckBox::clicked, this, &UserProfileView::ShowPassword);
	connect(backBtn, &QPushButton::clicked, this, &UserProfileView::LogOutButton);
}
void UserProfileView::setUser(User user)  // lma tegy tendh 3la el function de , el parameter beta3ha hyb2a mn function display elly fe UserController
{
	this->user = user;
}

/*********************  Information    ****************/

void UserProfileView::setInformation()
{
	user.fullName = firstNameInput->text().toStdString() + " " + lastNameInput->text().toStdString();
	user.password = passwordInput->text().toStdString();
	user.isVaccinated = isVaccinatedCheck->isChecked();
	if (user.isVaccinated)
	{
		user.dosesNumber = (oneDoseRadioBtn->isChecked() ? 1 : 2);
	}
	else
	{
		user.dosesNumber = 0;
	}
	user.country = (countryComboBox->currentIndex() == 0 ? "Egypt" : "Abroad");
	user.government = (countryComboBox->currentIndex() == 0 ? governments[governmentComboBox->currentIndex()] : "Abroad");
	user.age = ageSpinBox->value();
	user.gender = (genderComboBox->currentIndex() == 0 ? "Male" : "Female");
}

void UserProfileView::setInformation(User oldUser)
{
	user.fullName = oldUser.fullName;
	user.password = oldUser.password;
	user.isVaccinated = oldUser.isVaccinated;
	user.age = oldUser.age;
	user.country = oldUser.country;
	user.dosesNumber = oldUser.dosesNumber;
	user.gender = oldUser.gender;
	user.government = oldUser.government;
}

void UserProfileView::getInformation()
{
	string firstName = "", secondName = "";
	bool First = true;
	for (int i = 0; i < user.fullName.size(); i++)
	{
		if (user.fullName[i] == ' ')
		{
			First = false;
		}
		else
		{
			if (First)
			{
				firstName += user.fullName[i];
			}
			else
			{
				secondName += user.fullName[i];
			}
		}
	}
	firstNameInput->setText(firstName.c_str());
	lastNameInput->setText(secondName.c_str());
	nationalIdInput->setText(user.nationalID.c_str());
	passwordInput->setText(user.password.c_str());
	isVaccinatedCheck->setChecked((user.isVaccinated));
	if (isVaccinatedCheck->isChecked())
	{
		if (user.dosesNumber==1)
		{
			oneDoseRadioBtn->setChecked(true);
			twoDoseRadioBtn->setChecked(false);
		}
		else
		{
			oneDoseRadioBtn->setChecked(false);
			twoDoseRadioBtn->setChecked(true);

		}
	}
	toggleIsVaccinatedCheck();
	if (user.gender=="Male")
	{
		genderComboBox->setCurrentIndex(0);
	}
	else
	{
		genderComboBox->setCurrentIndex(1);
	}
	ageSpinBox->setValue(user.age);
	int indx=0;
	for (int i = 0; i < sizeof(governments); i++)
	{
		if (user.government==governments[i])
		{
			indx = i;
			break;
		}
	}
	if (user.country=="Egypt")
	{
		handleAbroad("Egypt");
		countryComboBox->setCurrentIndex(0);
		governmentComboBox->setCurrentIndex(indx);
	}
	else
	{
		handleAbroad("Abroad");
		countryComboBox->setCurrentIndex(1);
	}
	fullNameError->hide();
	passwordError->hide();
}

/*********************  Edit and View    ****************/

void UserProfileView::Edit()
{
	view = false;
	EditAndCloseBtn->setText("Close");
	firstNameInput->setReadOnly(false);
	lastNameInput->setReadOnly(false);
	passwordInput->setReadOnly(false);
	ageSpinBox->setReadOnly(false);
	genderComboBox->setEnabled(true);
	countryComboBox->setEnabled(true);
	governmentComboBox->setEnabled(true);
	isVaccinatedCheck->setEnabled(true);
	oneDoseRadioBtn->setEnabled(true);
	twoDoseRadioBtn->setEnabled(true);
	saveBtn->setEnabled(true);
	backBtn->setEnabled(false);
	toggleIsVaccinatedCheck();
}

void UserProfileView::View()
{
	getInformation();
	view = true;
	EditAndCloseBtn->setText("Edit");
	firstNameInput->setReadOnly(true);
	lastNameInput->setReadOnly(true);
	passwordInput->setReadOnly(true);
	ageSpinBox->setReadOnly(true);
	genderComboBox->setEnabled(false);
	countryComboBox->setEnabled(false);
	governmentComboBox->setEnabled(false);
	isVaccinatedCheck->setEnabled(false);
	oneDoseRadioBtn->setEnabled(false);
	twoDoseRadioBtn->setEnabled(false);
	saveBtn->setEnabled(false);
	backBtn->setEnabled(true);
}

/*********************  Buttons    ****************/

void UserProfileView::CloseButton()
{
	if (view)
	{
		Edit();
	}
	else
	{
		View();
	}
}

void UserProfileView::SaveButton()
{
	User old = user;
	setInformation();
	bool valid = handleErrors(x.edit(user));
	if (valid)
	{
		View();
	}
	else
	{
		setInformation(old);
	}
}

void UserProfileView::LogOutButton()
{
	cout << "Log Out" << endl;
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
	if (isVaccinatedCheck->isChecked())
	{
		oneDoseRadioBtn->setEnabled(true);
		twoDoseRadioBtn->setEnabled(true);
	}
	else
	{
		oneDoseRadioBtn->setEnabled(false);
		twoDoseRadioBtn->setEnabled(false);
	}
}

void UserProfileView::ShowPassword()
{
	if (ShowPasswordCheck->isChecked())
	{
		passwordInput->setEchoMode(QLineEdit::Normal);
	}
	else
	{
		passwordInput->setEchoMode(QLineEdit::Password);
	}
}

UserProfileView::~UserProfileView()
{
}
