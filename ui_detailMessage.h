/********************************************************************************
** Form generated from reading UI file 'detailMessage.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILMESSAGE_H
#define UI_DETAILMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detailMessage
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_7;
    QTableView *tableWidget;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QTreeWidget *treeWidget_2;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;

    void setupUi(QWidget *detailMessage)
    {
        if (detailMessage->objectName().isEmpty())
            detailMessage->setObjectName(QStringLiteral("detailMessage"));
        detailMessage->resize(829, 552);
        gridLayout = new QGridLayout(detailMessage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        tableWidget = new QTableView(detailMessage);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_7->addWidget(tableWidget, 0, 1, 2, 1);

        widget_3 = new QWidget(detailMessage);
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
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        pushButton_7 = new QPushButton(widget_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 0, 2, 1, 1);

        pushButton_8 = new QPushButton(widget_3);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_5->addWidget(pushButton_8, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_5);


        gridLayout_3->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_7->addWidget(widget_3, 0, 0, 1, 1);

        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 3);

        gridLayout->addLayout(gridLayout_7, 0, 0, 1, 1);


        retranslateUi(detailMessage);

        QMetaObject::connectSlotsByName(detailMessage);
    } // setupUi

    void retranslateUi(QWidget *detailMessage)
    {
        detailMessage->setWindowTitle(QApplication::translate("detailMessage", "detailMessage", nullptr));
        label_5->setText(QApplication::translate("detailMessage", "\351\242\206\345\237\237", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("detailMessage", "\346\217\217\350\277\260\347\254\246", nullptr));
        pushButton_7->setText(QApplication::translate("detailMessage", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton_8->setText(QApplication::translate("detailMessage", "\345\205\250\351\200\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class detailMessage: public Ui_detailMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILMESSAGE_H
