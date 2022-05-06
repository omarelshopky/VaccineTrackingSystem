#include "WidgetsStack.h"

WidgetsStack::WidgetsStack(QWidget *parent)
    : QStackedWidget(parent)
{
    setupUi(this);

    // Add system windows to the Widgets stack
    this->addWidget(new LoginView);
    this->addWidget(new RegisterView);
    this->addWidget(new UserProfileView);
    this->addWidget(new AdminDashboardView);
    this->addWidget(new StatisticsView(this));
    this->addWidget(new AdminPrivilageView);

    // Set the first window when the app startup
    this->setCurrentIndex(4);
}


WidgetsStack::~WidgetsStack()
{
}