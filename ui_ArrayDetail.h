/********************************************************************************
** Form generated from reading UI file 'ArrayDetail.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRAYDETAIL_H
#define UI_ARRAYDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CArrayDetail
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;

    void setupUi(QWidget *CArrayDetail)
    {
        if (CArrayDetail->objectName().isEmpty())
            CArrayDetail->setObjectName(QStringLiteral("CArrayDetail"));
        CArrayDetail->resize(426, 421);
        verticalLayout = new QVBoxLayout(CArrayDetail);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableWidget = new QTableWidget(CArrayDetail);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);


        retranslateUi(CArrayDetail);

        QMetaObject::connectSlotsByName(CArrayDetail);
    } // setupUi

    void retranslateUi(QWidget *CArrayDetail)
    {
        CArrayDetail->setWindowTitle(QApplication::translate("CArrayDetail", "CArrayDetail", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CArrayDetail: public Ui_CArrayDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARRAYDETAIL_H
