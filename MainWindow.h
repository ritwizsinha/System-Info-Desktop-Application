#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "CpuWidget.h"
#include "MemoryWidget.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CpuWidget mCpuWidget;
    MemoryWidget mMemoryWidget;
};

#endif // MAINWINDOW_H
