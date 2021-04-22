// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLABOUTDIALOG_H
#define WNLABOUTDIALOG_H

#include <QDialog>
#include <QSize>
#include <Qt>

#include "config.h"
#include "wnlattributionsdialog.h"

namespace Ui {
class WNLAboutDialog;
}

class WNLAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WNLAboutDialog(QWidget *parent = nullptr);
    ~WNLAboutDialog();

private slots:
    void on_attributionsLabel_linkActivated(const QString &link);

private:
    Ui::WNLAboutDialog *ui;
};

#endif // WNLABOUTDIALOG_H
