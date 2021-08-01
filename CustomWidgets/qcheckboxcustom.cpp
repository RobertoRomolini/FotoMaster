#include "qcheckboxcustom.h"

QCheckboxCustom::QCheckboxCustom(QWidget *parent) : QCheckBox(parent)
{

    setStyleSheet(
                "QCheckBox {font: 10pt 'Helvetica'; }"
                "QCheckBox::indicator:unchecked             { border: 1px solid black; background-color: #FDFDFD; border-radius: 2px;}"
                "QCheckBox::indicator:unchecked:hover   { border: 2px solid black; background-color: #FDFDFD; border-radius: 2px;}"
                "QCheckBox::indicator:unchecked:pressed{ border: 2px solid black; background-color: #F0F0F0; border-radius: 2px; }"
                "QCheckBox::indicator:checked                 { border: 1px solid black; background-color: #6C6C6C; border-radius: 2px;}"
                "QCheckBox::indicator:checked:hover       { border: 2px solid black; background-color: #7D7D7D; border-radius: 2px;}"
                     );
}
