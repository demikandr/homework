#include "mainwindow.h"

MainWindow::MainWindow(QGraphicsView *widget, QWidget *parent) : QMainWindow(parent)
{
    MainWindow::widget = widget;
    setCentralWidget(widget);
    createActions();
    createToolBars();
    createStatusBar();
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::createActions() {
    nextStepAct = new QAction(QIcon(":/pictures/next.png"),tr("step forward"), this);
    nextStepAct->setStatusTip(tr("do next step of algorithm"));
    connect(nextStepAct, SIGNAL(triggered()), widget, SLOT(doNextStep()));
    previousStepAct = new QAction(QIcon(":/pictures/previous.png"), tr("step back"), this);
    previousStepAct->setStatusTip(tr("do step back in the algorithm"));
    connect(previousStepAct, SIGNAL(triggered()), widget, SLOT(doPreviousStep()));
}


void MainWindow::createToolBars() {
    maxFlowToolBar = addToolBar(tr("max flow"));
    maxFlowToolBar->addAction(nextStepAct);
    maxFlowToolBar->addAction(previousStepAct);

}

void MainWindow::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}
