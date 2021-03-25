#ifndef WNLMAINWINDOW_H
#define WNLMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WNLMainWindow; }
QT_END_NAMESPACE

class WNLMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WNLMainWindow(QWidget *parent = nullptr);
    ~WNLMainWindow();

private:
    Ui::WNLMainWindow *ui;
};
#endif // WNLMAINWINDOW_H
