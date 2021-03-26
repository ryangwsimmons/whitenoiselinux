#include "wnlaboutdialog.h"
#include "ui_wnlaboutdialog.h"

WNLAboutDialog::WNLAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WNLAboutDialog)
{
    ui->setupUi(this);
    this->setFixedSize(300, 300);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->ui->versionLabel->setText(QString("<html><head/><body><p align=\"center\">Version %1.%2</p></body></html>").arg(VERSION_MAJOR).arg(VERSION_MINOR));
}

WNLAboutDialog::~WNLAboutDialog()
{
    delete ui;
}
