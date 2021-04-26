// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlattributionsdialog.h"
#include "ui_wnlattributionsdialog.h"

WNLAttributionsDialog::WNLAttributionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WNLAttributionsDialog)
{
    ui->setupUi(this);
    this->setFixedSize(530, 225);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

WNLAttributionsDialog::~WNLAttributionsDialog()
{
    delete ui;
}

void WNLAttributionsDialog::on_attributionsLabel_linkActivated(const QString &link)
{
    // xdg-open has to be launched instead of Qt's default link-opening code, as it does not work with AppImages
    QProcess* linkOpen = new QProcess();
    QStringList arguments;
    arguments << link;
    linkOpen->start("xdg-open", arguments);
}
