/********************************************************************************
** Form generated from reading ui file 'HelloSignal.ui'
**
** Created: Wed Aug 28 18:35:49 2013
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_HELLOSIGNAL_H
#define UI_HELLOSIGNAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelloSignal
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QComboBox *comboBox;
    QToolButton *toolButton;

    void setupUi(QWidget *HelloSignal)
    {
    if (HelloSignal->objectName().isEmpty())
        HelloSignal->setObjectName(QString::fromUtf8("HelloSignal"));
    HelloSignal->resize(349, 75);
    vboxLayout = new QVBoxLayout(HelloSignal);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    frame = new QFrame(HelloSignal);
    frame->setObjectName(QString::fromUtf8("frame"));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    hboxLayout = new QHBoxLayout(frame);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label = new QLabel(frame);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy);
    label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

    hboxLayout1->addWidget(label);

    comboBox = new QComboBox(frame);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    QFont font;
    font.setFamily(QString::fromUtf8("Courier"));
    comboBox->setFont(font);
    comboBox->setEditable(true);

    hboxLayout1->addWidget(comboBox);

    toolButton = new QToolButton(frame);
    toolButton->setObjectName(QString::fromUtf8("toolButton"));

    hboxLayout1->addWidget(toolButton);


    hboxLayout->addLayout(hboxLayout1);


    vboxLayout->addWidget(frame);


    retranslateUi(HelloSignal);

    QMetaObject::connectSlotsByName(HelloSignal);
    } // setupUi

    void retranslateUi(QWidget *HelloSignal)
    {
    HelloSignal->setWindowTitle(QApplication::translate("HelloSignal", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("HelloSignal", "root[]:", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_WHATSTHIS
    comboBox->setWhatsThis(QApplication::translate("HelloSignal", "USe this field to enter the ROO command", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS


#ifndef QT_NO_TOOLTIP
    toolButton->setToolTip(QApplication::translate("HelloSignal", "Terminate the ROOT session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP


#ifndef QT_NO_WHATSTHIS
    toolButton->setWhatsThis(QApplication::translate("HelloSignal", "THis button allow you to terminate your ROOT session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS

    toolButton->setText(QApplication::translate("HelloSignal", "quit", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(HelloSignal);
    } // retranslateUi

};

namespace Ui {
    class HelloSignal: public Ui_HelloSignal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOSIGNAL_H
