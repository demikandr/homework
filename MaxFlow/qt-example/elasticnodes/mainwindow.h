#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtWidgets>

class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QGraphicsView *widget, QWidget *parent = 0);

private:
    QAction *nextStepAct;
    QAction *previousStepAct;
    QToolBar *maxFlowToolBar;
    QGraphicsView *widget;
    void createActions();
    void createToolBars();
    void nextStep();
    void createStatusBar();
    void testMethod(){}


signals:

public slots:
};

#endif // MAINWINDOW_H
