/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *Translator;
    QVBoxLayout *verticalLayout_2;
    QListWidget *TRANSLATED_listWidget;
    QLineEdit *lineEdit;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *word_find;
    QToolButton *upButton;
    QToolButton *downButon;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QListWidget *ALL_WORDS_listWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QWidget *Word;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_2;
    QPushButton *wordEditButton;
    QLineEdit *lineEdit_2;
    QTextEdit *wordTextEdit;
    QListWidget *transListWidget;
    QVBoxLayout *verticalLayout_5;
    QPushButton *editTransButon;
    QPushButton *addTransButton;
    QPushButton *delTransButon;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(789, 663);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(100, 100));
        tabWidget->setMaximumSize(QSize(16777215, 16777211));
        tabWidget->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(true);
        Translator = new QWidget();
        Translator->setObjectName("Translator");
        Translator->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(Translator->sizePolicy().hasHeightForWidth());
        Translator->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(Translator);
        verticalLayout_2->setObjectName("verticalLayout_2");
        TRANSLATED_listWidget = new QListWidget(Translator);
        TRANSLATED_listWidget->setObjectName("TRANSLATED_listWidget");

        verticalLayout_2->addWidget(TRANSLATED_listWidget);

        lineEdit = new QLineEdit(Translator);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_2->addWidget(lineEdit);

        tabWidget->addTab(Translator, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        word_find = new QLineEdit(tab_2);
        word_find->setObjectName("word_find");

        horizontalLayout_2->addWidget(word_find);

        upButton = new QToolButton(tab_2);
        upButton->setObjectName("upButton");

        horizontalLayout_2->addWidget(upButton);

        downButon = new QToolButton(tab_2);
        downButon->setObjectName("downButon");

        horizontalLayout_2->addWidget(downButon);

        horizontalSpacer_4 = new QSpacerItem(100, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_2->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        ALL_WORDS_listWidget = new QListWidget(tab_2);
        ALL_WORDS_listWidget->setObjectName("ALL_WORDS_listWidget");

        verticalLayout->addWidget(ALL_WORDS_listWidget);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        spinBox = new QSpinBox(tab_3);
        spinBox->setObjectName("spinBox");
        spinBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(spinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox_2 = new QCheckBox(tab_3);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(checkBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        checkBox = new QCheckBox(tab_3);
        checkBox->setObjectName("checkBox");

        horizontalLayout->addWidget(checkBox);

        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(tab_3);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setMinimumSize(QSize(500, 0));

        verticalLayout_4->addWidget(tableWidget);

        tabWidget->addTab(tab_3, QString());
        Word = new QWidget();
        Word->setObjectName("Word");
        verticalLayout_6 = new QVBoxLayout(Word);
        verticalLayout_6->setObjectName("verticalLayout_6");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        wordEditButton = new QPushButton(Word);
        wordEditButton->setObjectName("wordEditButton");

        gridLayout_2->addWidget(wordEditButton, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(Word);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout_2->addWidget(lineEdit_2, 2, 0, 1, 1);

        wordTextEdit = new QTextEdit(Word);
        wordTextEdit->setObjectName("wordTextEdit");

        gridLayout_2->addWidget(wordTextEdit, 0, 0, 1, 1);

        transListWidget = new QListWidget(Word);
        transListWidget->setObjectName("transListWidget");

        gridLayout_2->addWidget(transListWidget, 1, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        editTransButon = new QPushButton(Word);
        editTransButon->setObjectName("editTransButon");

        verticalLayout_5->addWidget(editTransButon);

        addTransButton = new QPushButton(Word);
        addTransButton->setObjectName("addTransButton");

        verticalLayout_5->addWidget(addTransButton);

        delTransButon = new QPushButton(Word);
        delTransButon->setObjectName("delTransButon");

        verticalLayout_5->addWidget(delTransButon);


        gridLayout_2->addLayout(verticalLayout_5, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);

        tabWidget->addTab(Word, QString());

        horizontalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 789, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Translator), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        word_find->setText(QString());
        upButton->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        downButon->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Details", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Ukraine", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Check Answers", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        wordEditButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        editTransButon->setText(QCoreApplication::translate("MainWindow", "Edit Translation", nullptr));
        addTransButton->setText(QCoreApplication::translate("MainWindow", "Add Translation", nullptr));
        delTransButon->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Word), QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
