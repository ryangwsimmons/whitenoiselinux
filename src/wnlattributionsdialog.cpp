// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlattributionsdialog.h"
#include "ui_wnlattributionsdialog.h"

WNLAttributionsDialog::WNLAttributionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WNLAttributionsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(530, 150);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

WNLAttributionsDialog::~WNLAttributionsDialog()
{
    delete ui;
}
