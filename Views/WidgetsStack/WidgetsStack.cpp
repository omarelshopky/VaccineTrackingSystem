#include "WidgetsStack.h"

WidgetsStack::WidgetsStack(QWidget *parent)
    : QStackedWidget(parent)
{
    setupUi(this);

    this->addWidget(new HomeView);
}


WidgetsStack::~WidgetsStack()
{
}