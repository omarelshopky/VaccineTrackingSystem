#include "WidgetsStack.h"

WidgetsStack::WidgetsStack(QWidget *parent)
    : QStackedWidget(parent)
{
    setupUi(this);

    // Add system windows to the Widgets stack
    this->addWidget(new LoginView(this));
    this->addWidget(new RegisterView(this));
    this->addWidget(new UserProfileView);
    this->addWidget(new AdminDashboardView(this));
    this->addWidget(new StatisticsView(this));
    this->addWidget(new AdminPrivilageView(this));

    // Set the first window when the app startup
    this->setCurrentIndex(3);
}


WidgetsStack::~WidgetsStack() {}