#ifndef WNLMAINWINDOW_H
#define WNLMAINWINDOW_H

#include <QMainWindow>

#include "wnlaboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WNLMainWindow; }
QT_END_NAMESPACE

class WNLMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WNLMainWindow(QWidget *parent = nullptr);
    ~WNLMainWindow();

private slots:
    void on_aboutButton_clicked();

private:
    Ui::WNLMainWindow *ui;
};
#endif // WNLMAINWINDOW_H
