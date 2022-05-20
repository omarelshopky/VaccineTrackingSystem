#include "AdminPrivilageView.h"
#include "ui_AdminPrivilageView.h"


AdminPrivilageView::AdminPrivilageView(QStackedWidget* widgetStack, QWidget* parent)
	: QMainWindow(parent)
{
	this->widgetStack = widgetStack;
	setupUi(this);

	// Initialize components prop
	nationalID_input->setValidator(new QDoubleValidator(0, 100, 2, this)); //nationalId accept only numbers
	clearView();
	

	// Attach signals function
	connect(give_priv_Btn, &QPushButton::clicked, this, &AdminPrivilageView::giveAdminPrivilage);
	connect(backBtn, &QPushButton::clicked, this, &AdminPrivilageView::goBack);
}

AdminPrivilageView::~AdminPrivilageView() {}


void AdminPrivilageView::giveAdminPrivilage() {

	string state =  adminController.giveAdminPrivilage(nationalID_input->text().toStdString(), password_input->text().toStdString());

	if (state == "") {
		clearView();
		successMsg->show();
	}
	else {
		idError->setText(QString::fromStdString(state));
		idError->show();
		successMsg->hide();
	}
}


void AdminPrivilageView::goBack() {
	clearView();
	this->widgetStack->setCurrentIndex(3);
}


void AdminPrivilageView::clearView() {
	idError->hide();
	successMsg->hide();
	nationalID_input->clear();
	password_input->clear();
}
