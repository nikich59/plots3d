/********************************************************************************
** Form generated from reading UI file 'argumentsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARGUMENTSDIALOG_H
#define UI_ARGUMENTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_ArgumentsDialog
{
public:
    QScrollBar *verticalScrollBar;
    QPushButton *pushButton;

    void setupUi(QDialog *ArgumentsDialog)
    {
        if (ArgumentsDialog->objectName().isEmpty())
            ArgumentsDialog->setObjectName(QStringLiteral("ArgumentsDialog"));
        ArgumentsDialog->resize(310, 220);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ArgumentsDialog->sizePolicy().hasHeightForWidth());
        ArgumentsDialog->setSizePolicy(sizePolicy);
        ArgumentsDialog->setWindowOpacity(1);
        verticalScrollBar = new QScrollBar(ArgumentsDialog);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(290, 0, 20, 201));
        verticalScrollBar->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(ArgumentsDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 200, 21, 21));

        retranslateUi(ArgumentsDialog);

        QMetaObject::connectSlotsByName(ArgumentsDialog);
    } // setupUi

    void retranslateUi(QDialog *ArgumentsDialog)
    {
        ArgumentsDialog->setWindowTitle(QApplication::translate("ArgumentsDialog", "Arguments", Q_NULLPTR));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ArgumentsDialog: public Ui_ArgumentsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARGUMENTSDIALOG_H
