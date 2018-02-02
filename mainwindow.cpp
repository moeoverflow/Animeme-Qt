#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    player = new LoopPlayer();
    QObject::connect(player, SIGNAL(processedImage(QImage)), this, SLOT(updateLoopPlayerUI(QImage)));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::updateLoopPlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->playerScreen->setAlignment(Qt::AlignCenter);
        ui->playerScreen->setPixmap(QPixmap::fromImage(img)
                             .scaled(
                                 ui->playerScreen->size(),
                                 Qt::KeepAspectRatio,
                                 Qt::FastTransformation)
                             );
    }
}

void MainWindow::on_openFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"),
                                                    ".",
                                                    tr("Video Files (*.avi *.mpg *.mp4")
                                                    );

    if (!filename.isEmpty())
    {
        if (!player->loadVideo(filename.toStdString().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }

        player->play();
    }
}

void MainWindow::on_playPauseButton_clicked()
{
    if (player->isStopped())
    {
        player->play();
//        ui->playPauseButton->setText(tr("Pause"));
    }
    else
    {
        player->pause();
//        ui->playPauseButton->setText(tr("Play"));
    }
}
