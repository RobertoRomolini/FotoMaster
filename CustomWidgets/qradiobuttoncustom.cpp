#include "qradiobuttoncustom.h"

QRadioButtonCustom::QRadioButtonCustom(QWidget *parent) : QRadioButton(parent)
{
    setStyleSheet(
                "QRadioButton {font: 10pt 'Helvetica'; }"
                "QRadioButton::indicator:unchecked             { border: 1px solid black; background-color: #FDFDFD; border-radius: 2px;}"
                "QRadioButton::indicator:unchecked:hover   { border: 2px solid black; background-color: #FDFDFD; border-radius: 2px;}"
                "QRadioButton::indicator:unchecked:pressed{ border: 2px solid black; background-color: #F0F0F0; border-radius: 2px; }"
                "QRadioButton::indicator:checked                 { border: 1px solid black; background-color: #6C6C6C; border-radius: 2px;}"
                "QRadioButton::indicator:checked:hover       { border: 2px solid black; background-color: #7D7D7D; border-radius: 2px;}"
                     );
}
