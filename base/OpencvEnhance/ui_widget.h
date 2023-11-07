/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *labelView;
    QSlider *verticalSliderContrast;
    QSlider *verticalSliderBrightness;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(671, 410);
        labelView = new QLabel(Widget);
        labelView->setObjectName(QString::fromUtf8("labelView"));
        labelView->setGeometry(QRect(11, 11, 551, 391));
        labelView->setFrameShape(QFrame::Box);
        labelView->setFrameShadow(QFrame::Sunken);
        verticalSliderContrast = new QSlider(Widget);
        verticalSliderContrast->setObjectName(QString::fromUtf8("verticalSliderContrast"));
        verticalSliderContrast->setGeometry(QRect(578, 11, 28, 351));
        verticalSliderContrast->setMaximum(100);
        verticalSliderContrast->setSingleStep(5);
        verticalSliderContrast->setValue(33);
        verticalSliderContrast->setOrientation(Qt::Vertical);
        verticalSliderContrast->setInvertedAppearance(false);
        verticalSliderContrast->setInvertedControls(false);
        verticalSliderContrast->setTickPosition(QSlider::TicksBothSides);
        verticalSliderBrightness = new QSlider(Widget);
        verticalSliderBrightness->setObjectName(QString::fromUtf8("verticalSliderBrightness"));
        verticalSliderBrightness->setGeometry(QRect(630, 11, 28, 351));
        verticalSliderBrightness->setMaximum(100);
        verticalSliderBrightness->setSingleStep(5);
        verticalSliderBrightness->setOrientation(Qt::Vertical);
        verticalSliderBrightness->setTickPosition(QSlider::TicksBothSides);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(578, 379, 45, 20));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(630, 379, 30, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        labelView->setText(QString());
        label_2->setText(QCoreApplication::translate("Widget", "\345\257\271\346\257\224\345\272\246", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\344\272\256\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
