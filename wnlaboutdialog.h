#ifndef WNLABOUTDIALOG_H
#define WNLABOUTDIALOG_H

#include <QDialog>
#include <QSize>

namespace Ui {
class WNLAboutDialog;
}

class WNLAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WNLAboutDialog(QWidget *parent = nullptr);
    ~WNLAboutDialog();

private:
    Ui::WNLAboutDialog *ui;
};

#endif // WNLABOUTDIALOG_H
