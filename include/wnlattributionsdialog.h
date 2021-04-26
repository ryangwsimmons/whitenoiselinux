// Copyright 2021 Ryan Simmons
// This program is distributed under the terms of the GNU General Public License Version 3

#ifndef WNLATTRIBUTIONSDIALOG_H
#define WNLATTRIBUTIONSDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QStringList>
#include <Qt>

namespace Ui {
class WNLAttributionsDialog;
}

class WNLAttributionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WNLAttributionsDialog(QWidget *parent = nullptr);
    ~WNLAttributionsDialog();

private slots:
    void on_attributionsLabel_linkActivated(const QString &link);

private:
    Ui::WNLAttributionsDialog *ui;
};

#endif // WNLATTRIBUTIONSDIALOG_H
