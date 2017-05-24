/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *compress;
    QPushButton *extract;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuICompress;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(455, 349);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        compress = new QPushButton(centralWidget);
        compress->setObjectName(QStringLiteral("compress"));
        compress->setGeometry(QRect(50, 240, 89, 25));
        extract = new QPushButton(centralWidget);
        extract->setObjectName(QStringLiteral("extract"));
        extract->setGeometry(QRect(310, 240, 89, 25));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 50, 291, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(360, 50, 71, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 141, 17));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(100, 130, 81, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 110, 67, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 455, 26));
        menuICompress = new QMenu(menuBar);
        menuICompress->setObjectName(QStringLiteral("menuICompress"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuICompress->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        compress->setText(QApplication::translate("MainWindow", "compress", Q_NULLPTR));
        extract->setText(QApplication::translate("MainWindow", "extract", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "browse", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Please choose a file:", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 thread", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7 threads", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8 threads(max)", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("MainWindow", "Threads :", Q_NULLPTR));
        menuICompress->setTitle(QApplication::translate("MainWindow", "ICompress", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
