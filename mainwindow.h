#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "loopplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateLoopPlayerUI(QImage img);
    void on_openFileButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    LoopPlayer *player;
};

#endif // MAINWINDOW_H
