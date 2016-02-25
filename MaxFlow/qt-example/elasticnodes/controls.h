#ifndef CONTROLS_H
#define CONTROLS_H\

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE


class Controls:public QDialog
{
    Q_OBJECT

public:
    Controls();
private:
    void createHorizontalGroupBox();

    enum {  NumButtons = 4 };

    QGroupBox *horizontalGroupBox;
    QPushButton *buttons[NumButtons];

    QAction *exitAction;
};

#endif // CONTROLS_H
