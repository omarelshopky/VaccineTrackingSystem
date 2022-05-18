#include "LoginView.h"
#include "ui_LoginView.h"




LoginView::LoginView(QStackedWidget *widgetStack, QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetStack = widgetStack;

	setupUi(this);

	// Initialize components prop
	nationalIDInput->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	this->clearView();

	// Attach signals function
    connect(loginBtn, &QPushButton::clicked, this, &LoginView::login);
	connect(userTypeBtn, &QPushButton::clicked, this, &LoginView::changeUserType);
	connect(registerBtn, &QPushButton::clicked, this, &LoginView::goToRegister);
}


LoginView::~LoginView() {}


void LoginView::login() {
	bool state = false;
	if (isAdmin) {
		 state = adminController.login(nationalIDInput->text().toStdString(), passInput->text().toStdString());
	}
	else {
	     state = userController.login(nationalIDInput->text().toStdString(), passInput->text().toStdString());
	}

	if (state) {
		this->clearView();
		widgetStack->setCurrentIndex((isAdmin)? 3 : 2);
	}
	else {
		errorLbl->show();
	}
}


void LoginView::changeUserType() {
	this->clearView();

	if (isAdmin) {
		userTypeBtn->setText("As User");
		NoAccLbl->show();
		registerBtn->show();
	}
	else {
		userTypeBtn->setText("As Admin");
		NoAccLbl->hide();
		registerBtn->hide();
	}
	isAdmin = !isAdmin;
}


void LoginView::goToRegister() {
	this->clearView();

	widgetStack->setCurrentIndex(1);
}


void LoginView::clearView() {
	nationalIDInput->clear();
	passInput->clear();
	errorLbl->hide();
}
