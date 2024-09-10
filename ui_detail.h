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
    QGridLayout *gridLayout_2;
    QWidget *wgtDescriptors;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayoutD;
    QLabel *lbDescriptors;
    QTreeWidget *treeDescriptors;
    QGridLayout *gridLayoutD;
    QPushButton *btnDSelectAll;
    QPushButton *btnDRefresh;
    QPushButton *btnDClearAll;
    QHBoxLayout *horizontalLayoutD;
    QPushButton *pushButton_9;
    QPushButton *pushButton_6;
    QWidget *wgtEntities;
    QGridLayout *gridLayout_6;
    QVBoxLayout *verticalLayoutE;
    QLabel *lbEntities;
    QTreeWidget *treeEntities;
    QGridLayout *gridLayoutE;
    QPushButton *btnESelectAll;
    QPushButton *btnEClearAll;
    QPushButton *btnEFilter;
    QPushButton *btnERefresh;
    QTableWidget *tableDetail;

    void setupUi(QWidget *detail)
    {
        if (detail->objectName().isEmpty())
            detail->setObjectName(QStringLiteral("detail"));
        detail->resize(686, 517);
        gridLayout = new QGridLayout(detail);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        wgtDescriptors = new QWidget(detail);
        wgtDescriptors->setObjectName(QStringLiteral("wgtDescriptors"));
        gridLayout_3 = new QGridLayout(wgtDescriptors);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayoutD = new QVBoxLayout();
        verticalLayoutD->setObjectName(QStringLiteral("verticalLayoutD"));
        lbDescriptors = new QLabel(wgtDescriptors);
        lbDescriptors->setObjectName(QStringLiteral("lbDescriptors"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        lbDescriptors->setFont(font);

        verticalLayoutD->addWidget(lbDescriptors);

        treeDescriptors = new QTreeWidget(wgtDescriptors);
        treeDescriptors->setObjectName(QStringLiteral("treeDescriptors"));

        verticalLayoutD->addWidget(treeDescriptors);

        gridLayoutD = new QGridLayout();
        gridLayoutD->setObjectName(QStringLiteral("gridLayoutD"));
        btnDSelectAll = new QPushButton(wgtDescriptors);
        btnDSelectAll->setObjectName(QStringLiteral("btnDSelectAll"));

        gridLayoutD->addWidget(btnDSelectAll, 1, 1, 1, 1);

        btnDRefresh = new QPushButton(wgtDescriptors);
        btnDRefresh->setObjectName(QStringLiteral("btnDRefresh"));

        gridLayoutD->addWidget(btnDRefresh, 0, 1, 1, 1);

        btnDClearAll = new QPushButton(wgtDescriptors);
        btnDClearAll->setObjectName(QStringLiteral("btnDClearAll"));

        gridLayoutD->addWidget(btnDClearAll, 1, 2, 1, 1);

        horizontalLayoutD = new QHBoxLayout();
        horizontalLayoutD->setObjectName(QStringLiteral("horizontalLayoutD"));
        pushButton_9 = new QPushButton(wgtDescriptors);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        horizontalLayoutD->addWidget(pushButton_9);

        pushButton_6 = new QPushButton(wgtDescriptors);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayoutD->addWidget(pushButton_6);


        gridLayoutD->addLayout(horizontalLayoutD, 0, 2, 1, 1);


        verticalLayoutD->addLayout(gridLayoutD);


        gridLayout_3->addLayout(verticalLayoutD, 0, 0, 1, 1);


        gridLayout_2->addWidget(wgtDescriptors, 0, 0, 1, 1);

        wgtEntities = new QWidget(detail);
        wgtEntities->setObjectName(QStringLiteral("wgtEntities"));
        gridLayout_6 = new QGridLayout(wgtEntities);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalLayoutE = new QVBoxLayout();
        verticalLayoutE->setObjectName(QStringLiteral("verticalLayoutE"));
        lbEntities = new QLabel(wgtEntities);
        lbEntities->setObjectName(QStringLiteral("lbEntities"));
        lbEntities->setFont(font);

        verticalLayoutE->addWidget(lbEntities);

        treeEntities = new QTreeWidget(wgtEntities);
        treeEntities->setObjectName(QStringLiteral("treeEntities"));

        verticalLayoutE->addWidget(treeEntities);

        gridLayoutE = new QGridLayout();
        gridLayoutE->setObjectName(QStringLiteral("gridLayoutE"));
        btnESelectAll = new QPushButton(wgtEntities);
        btnESelectAll->setObjectName(QStringLiteral("btnESelectAll"));

        gridLayoutE->addWidget(btnESelectAll, 0, 1, 1, 1);

        btnEClearAll = new QPushButton(wgtEntities);
        btnEClearAll->setObjectName(QStringLiteral("btnEClearAll"));

        gridLayoutE->addWidget(btnEClearAll, 0, 2, 1, 1);

        btnEFilter = new QPushButton(wgtEntities);
        btnEFilter->setObjectName(QStringLiteral("btnEFilter"));

        gridLayoutE->addWidget(btnEFilter, 1, 2, 1, 1);

        btnERefresh = new QPushButton(wgtEntities);
        btnERefresh->setObjectName(QStringLiteral("btnERefresh"));

        gridLayoutE->addWidget(btnERefresh, 1, 1, 1, 1);


        verticalLayoutE->addLayout(gridLayoutE);


        gridLayout_6->addLayout(verticalLayoutE, 0, 0, 1, 1);


        gridLayout_2->addWidget(wgtEntities, 1, 0, 1, 1);

        tableDetail = new QTableWidget(detail);
        tableDetail->setObjectName(QStringLiteral("tableDetail"));

        gridLayout_2->addWidget(tableDetail, 0, 1, 2, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 3);

        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(detail);

        QMetaObject::connectSlotsByName(detail);
    } // setupUi

    void retranslateUi(QWidget *detail)
    {
        detail->setWindowTitle(QApplication::translate("detail", "Form", nullptr));
        lbDescriptors->setText(QApplication::translate("detail", "Descriptors", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeDescriptors->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("detail", "\346\217\217\350\277\260\347\254\246", nullptr));
        btnDSelectAll->setText(QApplication::translate("detail", "\345\205\250\351\200\211", nullptr));
        btnDRefresh->setText(QApplication::translate("detail", "\345\210\267\346\226\260", nullptr));
        btnDClearAll->setText(QApplication::translate("detail", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        pushButton_9->setText(QApplication::translate("detail", "/\\", nullptr));
        pushButton_6->setText(QApplication::translate("detail", "\\/", nullptr));
        lbEntities->setText(QApplication::translate("detail", "Entities", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeEntities->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("detail", "\345\256\236\344\275\223ID", nullptr));
        btnESelectAll->setText(QApplication::translate("detail", "\345\205\250\351\200\211", nullptr));
        btnEClearAll->setText(QApplication::translate("detail", "\346\270\205\351\231\244\346\211\200\346\234\211", nullptr));
        btnEFilter->setText(QApplication::translate("detail", "\350\277\207\346\273\244\345\231\250", nullptr));
        btnERefresh->setText(QApplication::translate("detail", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class detail: public Ui_detail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAIL_H
