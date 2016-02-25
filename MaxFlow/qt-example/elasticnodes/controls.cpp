#include "controls.h"
#include <QtWidgets>

Controls::Controls()
{
    createHorizontalGroupBox();

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(horizontalGroupBox);
}

void Controls::createHorizontalGroupBox()
{
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);

}
