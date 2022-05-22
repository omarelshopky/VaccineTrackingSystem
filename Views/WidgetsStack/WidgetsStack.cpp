#include "WidgetsStack.h"

WidgetsStack::WidgetsStack(QWidget *parent)
    : QStackedWidget(parent)
{
    setupUi(this);

    // Add system windows to the Widgets stack
    this->addWidget(new LoginView(this));
    this->addWidget(new RegisterView(this));
    this->addWidget(new UserProfileView(this));
    this->addWidget(new AdminDashboardView(this));
    this->addWidget(new StatisticsView(this));
    this->addWidget(new AdminPrivilageView(this));
    this->addWidget(new WaitingListView(this));

    // Set the first window when the app startup
    this->setCurrentIndex(LOGIN_VIEW_INDEX);
}


WidgetsStack::~WidgetsStack() {}