/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QPushButton *talkButton;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QListWidget *listWidget_2;
    QPushButton *addButton;
    QPushButton *groupButton;
    QLabel *label_3;
    QPushButton *removeButton;

    void setupUi(QDialog *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName(QString::fromUtf8("MenuWindow"));
        MenuWindow->resize(400, 600);
        MenuWindow->setStyleSheet(QString::fromUtf8("background-color:\"#408cff\";"));
        talkButton = new QPushButton(MenuWindow);
        talkButton->setObjectName(QString::fromUtf8("talkButton"));
        talkButton->setGeometry(QRect(10, 540, 121, 21));
        talkButton->setStyleSheet(QString::fromUtf8("background-color:grey;\n"
"font:bold;\n"
"font-color:  black;"));
        listWidget = new QListWidget(MenuWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 120, 180, 401));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: \"#b06fff\";\n"
"border: 2px solid black;\n"
""));
        label = new QLabel(MenuWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 401, 111));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/images/utfpr.png")));
        label_2 = new QLabel(MenuWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 100, 71, 20));
        label_2->setStyleSheet(QString::fromUtf8("font:bold;\n"
"font-color:black;"));
        listWidget_2 = new QListWidget(MenuWindow);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(210, 120, 180, 401));
        listWidget_2->setStyleSheet(QString::fromUtf8("background-color: \"#b06fff\";\n"
"border: 2px solid black;\n"
""));
        addButton = new QPushButton(MenuWindow);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(210, 540, 41, 21));
        addButton->setStyleSheet(QString::fromUtf8("background-color:grey;\n"
"font:bold;\n"
"font-color:  black;"));
        groupButton = new QPushButton(MenuWindow);
        groupButton->setObjectName(QString::fromUtf8("groupButton"));
        groupButton->setGeometry(QRect(270, 540, 121, 21));
        groupButton->setStyleSheet(QString::fromUtf8("background-color:grey;\n"
"font:bold;\n"
"font-color:  black;"));
        label_3 = new QLabel(MenuWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 100, 71, 20));
        label_3->setStyleSheet(QString::fromUtf8("font:bold;\n"
"font-color:black;"));
        removeButton = new QPushButton(MenuWindow);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(150, 540, 41, 21));
        removeButton->setStyleSheet(QString::fromUtf8("background-color:grey;\n"
"font:bold;\n"
"font-color:  black;"));
        talkButton->raise();
        label->raise();
        label_2->raise();
        listWidget->raise();
        listWidget_2->raise();
        addButton->raise();
        groupButton->raise();
        label_3->raise();
        removeButton->raise();

        retranslateUi(MenuWindow);

        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QDialog *MenuWindow)
    {
        MenuWindow->setWindowTitle(QApplication::translate("MenuWindow", "Dialog", nullptr));
        talkButton->setText(QApplication::translate("MenuWindow", "Conversar", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("MenuWindow", "Online:", nullptr));
        addButton->setText(QApplication::translate("MenuWindow", ">>", nullptr));
        groupButton->setText(QApplication::translate("MenuWindow", "Enviar para grupo", nullptr));
        label_3->setText(QApplication::translate("MenuWindow", "Grupo:", nullptr));
        removeButton->setText(QApplication::translate("MenuWindow", "<<", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuWindow: public Ui_MenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
