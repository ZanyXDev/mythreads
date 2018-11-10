#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "cpuworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void enableButton(bool flag);
    void testSlot();
private:
    Ui::MainWindow *ui;
    QThread workThread;
    CPUWorker* m_worker;
};

#endif // MAINWINDOW_H
