#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "processmanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getPidButtonPushed();
    void readMemoryButtonPushed();


private:
    Ui::MainWindow *ui;
    ProcessManager processManager;
    int pidUnderObservation = -1;
    long addressUnderObservation = -1;

};
#endif // MAINWINDOW_H
