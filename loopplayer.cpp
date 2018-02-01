#include "loopplayer.h"

#include <iostream>

LoopPlayer::LoopPlayer(QObject *parent) : QThread(parent)
{
    stop = true;
}

LoopPlayer::~LoopPlayer()
{
    mutex.lock();
    stop = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool LoopPlayer::loadVideo(std::string filename)
{
    cv::VideoCapture capture;
    capture.open(filename);
    if (capture.isOpened())
    {
        frameRate = (int)capture.get(CV_CAP_PROP_FPS);

        cv::Mat frame;
        while (capture.read(frame))
        {
            if (frame.channels() == 3)
            {
                cv::cvtColor(frame, frame, CV_BGR2RGB);
            }
            frames.push_back(frame.clone());
        }

        capture.release();
        return true;
    }

    return false;
}

void LoopPlayer::play()
{
    if (!isRunning())
    {
        if (isStopped())
        {
            stop = false;
        }

        start(LowPriority);
    }
}

void LoopPlayer::run()
{
    int delay = 1000.0 / frameRate;

    auto it = frames.begin();
    while (!stop) {
        if (it == frames.end())
        {
            it = frames.begin();
        }

        cv::Mat frame = *it;
        if (frame.channels() == 3)
        {
            img = QImage((const unsigned char*)(frame.data),
                         frame.cols,
                         frame.rows,
                         QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                         frame.cols,
                         frame.rows,
                         QImage::Format_Indexed8);
        }

        emit processedImage(img);
        this->msleep(delay);

        it++;
    }
}

void LoopPlayer::pause()
{
    stop = true;
}

void LoopPlayer::msleep(int ms)
{
    struct timespec ts =
    {
        ms / 1000, (ms % 1000) * 1000 * 1000
    };

    nanosleep(&ts, NULL);
}

bool LoopPlayer::isStopped() const
{
    return stop;
}

