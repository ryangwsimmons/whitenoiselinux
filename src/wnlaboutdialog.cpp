// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#include "wnlaboutdialog.h"
#include "ui_wnlaboutdialog.h"

WNLAboutDialog::WNLAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WNLAboutDialog)
{
    ui->setupUi(this);
    this->setFixedSize(300, 600);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->ui->versionLabel->setText(QString("<html><head/><body><p align=\"center\" style=\"font-weight: 600;\">Version %1.%2.%3</p></body></html>").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_PATCH));
}

WNLAboutDialog::~WNLAboutDialog()
{
    delete ui;
}

void WNLAboutDialog::on_attributionsLabel_linkActivated(const QString &link)
{
    // Create new attributions dialog that deletes itself on close
    WNLAttributionsDialog* attributionsDialog = new WNLAttributionsDialog();
    attributionsDialog->setAttribute(Qt::WA_DeleteOnClose);

    // Position the attributions dialog in the centre of the parent window
    attributionsDialog->move(this->geometry().center() - attributionsDialog->rect().center());

    // Show the dialog (modal)
    attributionsDialog->exec();
}

void WNLAboutDialog::on_licenseInfoLabel_linkActivated(const QString &link)
{
    // xdg-open has to be launched instead of Qt's default link-opening code, as it does not work with AppImages
    QProcess* linkOpen = new QProcess();
    QStringList arguments;
    arguments << link;
    linkOpen->start("xdg-open", arguments);
}
