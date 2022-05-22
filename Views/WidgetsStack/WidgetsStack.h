#pragma once

#include <QStackedWidget>
#include "ui_WidgetsStack.h"

//************ System Views **************//
#include "../LoginView/LoginView.h"
#include "../RegisterView/RegisterView.h"
#include "../UserProfileView/UserProfileView.h"
#include "../AdminDashboardView/AdminDashboardView.h"
#include "../StatisticsView/StatisticsView.h"
#include "../AdminPrivilageView/AdminPrivilageView.h"
#include "../WaitingListView/WaitingListView.h"
//****************************************//


class WidgetsStack : public QStackedWidget, public Ui::WidgetsStackClass
{
    Q_OBJECT

public:
    WidgetsStack(QWidget *parent = Q_NULLPTR);
    ~WidgetsStack();
};
