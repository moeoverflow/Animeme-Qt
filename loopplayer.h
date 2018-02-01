#ifndef LOOPPLAYER_H
#define LOOPPLAYER_H

#include <vector>
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class LoopPlayer : public QThread
{   Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    std::vector<cv::Mat> frames;
    int frameRate;
    QImage img;

signals:
    void processedImage(const QImage &image);

protected:
    void run();
    void msleep(int ms);
public:
    LoopPlayer(QObject *parent = 0);
    ~LoopPlayer();
    bool loadVideo(std::string filename);
    void play();
    void pause();
    bool isStopped() const;
};

#endif // LOOPPLAYER_H
