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
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "detail.h"

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
    QWidget *tab_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QTableView *tableView;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QTreeWidget *treeWidget_2;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QWidget *widget_2;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QTreeWidget *treeWidget;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    detail *tab_3;
    detail *tab_4;

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
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_8 = new QGridLayout(tab_2);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_7->addWidget(tableView, 0, 1, 2, 1);

        widget_3 = new QWidget(tab_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);

        verticalLayout_2->addWidget(label_5);

        treeWidget_2 = new QTreeWidget(widget_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));

        verticalLayout_2->addWidget(treeWidget_2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_5->addWidget(pushButton_5, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 1, 2, 1, 1);

        pushButton_8 = new QPushButton(widget_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_5->addWidget(pushButton_8, 1, 1, 1, 1);

        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_5->addWidget(pushButton_6, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_5);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_3, 0, 0, 1, 1);

        widget_2 = new QWidget(tab_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_6 = new QGridLayout(widget_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        treeWidget = new QTreeWidget(widget_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem1);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_4->addWidget(pushButton_3, 0, 1, 1, 1);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_4->addWidget(pushButton_2, 0, 2, 1, 1);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_4->addWidget(pushButton, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_4->addWidget(pushButton_4, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_4);


        gridLayout_6->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_2, 1, 0, 1, 1);

        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 3);

        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new detail();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new detail();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(1);


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
        label_5->setText(QApplication::translate("Widget", "Descriptors", nullptr));
        pushButton_5->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", nullptr));
        pushButton_7->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton_8->setText(QApplication::translate("Widget", "\345\205\250\351\200\211", nullptr));
        pushButton_6->setText(QApplication::translate("Widget", "PushButton", nullptr));
        label_4->setText(QApplication::translate("Widget", "Entities", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "\345\205\250\351\200\211", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\350\277\207\346\273\244\345\231\250", nullptr));
        pushButton_4->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "Tab 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Widget", "Tab3", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Widget", "Tab4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
