#include "wnlmainwindow.h"
#include "ui_wnlmainwindow.h"

WNLMainWindow::WNLMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WNLMainWindow)
{
    ui->setupUi(this);
}

WNLMainWindow::~WNLMainWindow()
{
    delete ui;
}

