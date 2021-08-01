#include "qpushbuttonred.h"

QPushButtonRed::QPushButtonRed(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(
                "QPushButton                 { font: 10pt 'Helvetica'; font-weight:bold; background-color:#FF2626; border-radius:4px; border:1px solid #000000; }"
                "QPushButton:hover       { background-color:#FF0000; border:2px solid #000000;}"
                     );

}
