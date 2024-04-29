/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QFormLayout *formLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnclose;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView_1;
    QTableView *tableView_2;
    QTableView *tableView_3;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(967, 736);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalSpacer = new QSpacerItem(820, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(0, QFormLayout::LabelRole, horizontalSpacer);

        btnclose = new QPushButton(widget);
        btnclose->setObjectName(QStringLiteral("btnclose"));

        formLayout->setWidget(0, QFormLayout::FieldRole, btnclose);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabBarAutoHide(false);
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        gridLayout_2 = new QGridLayout(tab_1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(tab_1);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        gridLayout_2->addWidget(label_3, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView_1 = new QTableView(tab_1);
        tableView_1->setObjectName(QStringLiteral("tableView_1"));

        horizontalLayout->addWidget(tableView_1);

        tableView_2 = new QTableView(tab_1);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        horizontalLayout->addWidget(tableView_2);

        tableView_3 = new QTableView(tab_1);
        tableView_3->setObjectName(QStringLiteral("tableView_3"));

        horizontalLayout->addWidget(tableView_3);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 3);

        label = new QLabel(tab_1);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(tab_1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);

        tabWidget->addTab(tab_1, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        btnclose->setText(QApplication::translate("Widget", "PushButton", nullptr));
        label_3->setText(QApplication::translate("Widget", "Descriptors", nullptr));
        label->setText(QApplication::translate("Widget", "Entities", nullptr));
        label_2->setText(QApplication::translate("Widget", "Messages", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("Widget", "Tab 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
