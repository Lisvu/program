/********************************************************************************
** Form generated from reading UI file 'gamescreen.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCREEN_H
#define UI_GAMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameScreen
{
public:
    QPushButton *shopButton;
    QPushButton *exitButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *scoreLabel;

    void setupUi(QWidget *GameScreen)
    {
        if (GameScreen->objectName().isEmpty())
            GameScreen->setObjectName("GameScreen");
        GameScreen->resize(887, 585);
        shopButton = new QPushButton(GameScreen);
        shopButton->setObjectName("shopButton");
        shopButton->setGeometry(QRect(470, 550, 91, 31));
        exitButton = new QPushButton(GameScreen);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(740, 550, 91, 31));
        gridLayoutWidget = new QWidget(GameScreen);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(400, 120, 451, 401));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scoreLabel = new QLabel(GameScreen);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setGeometry(QRect(150, 60, 111, 61));

        retranslateUi(GameScreen);

        QMetaObject::connectSlotsByName(GameScreen);
    } // setupUi

    void retranslateUi(QWidget *GameScreen)
    {
        GameScreen->setWindowTitle(QCoreApplication::translate("GameScreen", "Form", nullptr));
        shopButton->setText(QCoreApplication::translate("GameScreen", "\345\225\206\345\272\227", nullptr));
        exitButton->setText(QCoreApplication::translate("GameScreen", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        scoreLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameScreen: public Ui_GameScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCREEN_H
