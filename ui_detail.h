/********************************************************************************
** Form generated from reading UI file 'detail.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAIL_H
#define UI_DETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detail
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_7;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QTreeWidget *treeWidget_2;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_9;
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
    QTableWidget *tableWidget;

    void setupUi(QWidget *detail)
    {
        if (detail->objectName().isEmpty())
            detail->setObjectName(QStringLiteral("detail"));
        detail->resize(686, 517);
        gridLayout = new QGridLayout(detail);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        widget_3 = new QWidget(detail);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);

        verticalLayout_2->addWidget(label_5);

        treeWidget_2 = new QTreeWidget(widget_3);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));

        verticalLayout_2->addWidget(treeWidget_2);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pushButton_8 = new QPushButton(widget_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_5->addWidget(pushButton_8, 1, 1, 1, 1);

        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_5->addWidget(pushButton_5, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_9 = new QPushButton(widget_3);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        horizontalLayout->addWidget(pushButton_9);

        pushButton_6 = new QPushButton(widget_3);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout->addWidget(pushButton_6);


        gridLayout_5->addLayout(horizontalLayout, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_5);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_3, 0, 0, 1, 1);

        widget_2 = new QWidget(detail);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_6 = new QGridLayout(widget_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        treeWidget = new QTreeWidget(widget_2);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        gridLayout_4 = new QGridLayout();
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

        tableWidget = new QTableWidget(detail);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_7->addWidget(tableWidget, 0, 1, 2, 1);

        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 3);

        gridLayout->addLayout(gridLayout_7, 0, 0, 1, 1);


        retranslateUi(detail);

        QMetaObject::connectSlotsByName(detail);
    } // setupUi

    void retranslateUi(QWidget *detail)
    {
        detail->setWindowTitle(QApplication::translate("detail", "Form", nullptr));
        label_5->setText(QApplication::translate("detail", "Descriptors", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("detail", "\346\217\217\350\277\260\347\254\246", nullptr));
        pushButton_8->setText(QApplication::translate("detail", "\345\205\250\351\200\211", nullptr));
        pushButton_5->setText(QApplication::translate("detail", "\345\210\267\346\226\260", nullptr));
        pushButton_7->setText(QApplication::translate("detail", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton_9->setText(QApplication::translate("detail", "/\\", nullptr));
        pushButton_6->setText(QApplication::translate("detail", "/\\", nullptr));
        label_4->setText(QApplication::translate("detail", "Entities", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("detail", "\345\256\236\344\275\223ID", nullptr));
        pushButton_3->setText(QApplication::translate("detail", "\345\205\250\351\200\211", nullptr));
        pushButton_2->setText(QApplication::translate("detail", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton->setText(QApplication::translate("detail", "\350\277\207\346\273\244\345\231\250", nullptr));
        pushButton_4->setText(QApplication::translate("detail", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class detail: public Ui_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAIL_H
