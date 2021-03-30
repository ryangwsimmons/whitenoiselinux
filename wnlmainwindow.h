#ifndef WNLMAINWINDOW_H
#define WNLMAINWINDOW_H

#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QVariant>

#include "wnlaboutdialog.h"
#include "wnlsoundgrabber.h"

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

    void on_addSoundButton_clicked();

    void on_rmSoundButton_clicked();

    void on_currSoundsSelect_itemSelectionChanged();

    void on_availSoundsSelect_itemSelectionChanged();

private:
    Ui::WNLMainWindow *ui;
};
#endif // WNLMAINWINDOW_H
