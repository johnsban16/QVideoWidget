#include "videowidget.h"
#include "ui_videowidget.h"

#include <QMediaPlayer>
#include <QVideoWidget>

static const QString VideoStr = QString("http://your_site.com/video.mp4");

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::VideoWidget)
{
    mUi->setupUi(this);

    mVideoContainer = new QWidget(this);
    mVideoContainer->setStyleSheet("background-color: black;");

    mMediaPlayer = new QMediaPlayer;
    mMediaPlayer->setMedia(QMediaContent(QUrl(VideoStr)));

    mVideoWidget = new QVideoWidget(mVideoContainer);
    mMediaPlayer->setVideoOutput(mVideoWidget);

    mUi->buttonPause->setCheckable(true);

    connectSignals(true);
}
/**
****************************************************************************************************
**/
VideoWidget::~VideoWidget()
{
    mMediaPlayer->stop();
    connectSignals(false);

    delete mUi;
}
/**
****************************************************************************************************
**/
void VideoWidget::resizeEvent(QResizeEvent *)
{
    mVideoContainer->setGeometry(0, 0, width(), height() - 50);
    mVideoWidget->setGeometry(0, 0, mVideoContainer->width(), mVideoContainer->height());
}
/**
****************************************************************************************************
**/
void VideoWidget::slotPlay()
{
    mMediaPlayer->play();
    mUi->sliderVolume->setMinimum(0);
    mUi->sliderVolume->setMaximum(mMediaPlayer->duration());
}
/**
****************************************************************************************************
**/
void VideoWidget::slotPause(bool isPaused)
{
    if (isPaused)
    {
        mMediaPlayer->pause();
    }
    else
    {
        mMediaPlayer->play();
    }
}
/**
****************************************************************************************************
**/
void VideoWidget::slotStop()
{
    mMediaPlayer->stop();
}
/**
****************************************************************************************************
**/
void VideoWidget::slotDurationChanged(qint64 duration)
{
    mUi->sliderVolume->setValue(duration);
}
/**
****************************************************************************************************
**/
void VideoWidget::slotPlaybackSliderMoved(int position)
{
    mMediaPlayer->setPosition(position);
}
/**
****************************************************************************************************
**/
void VideoWidget::connectSignals(bool establish)
{
    if (establish)
    {
        connect(mUi->buttonPlay, SIGNAL(clicked()), this, SLOT(slotPlay()), Qt::UniqueConnection);
        connect(mUi->buttonPause, SIGNAL(clicked(bool)), this, SLOT(slotPause(bool)), Qt::UniqueConnection);
        connect(mUi->buttonStop, SIGNAL(clicked()), this, SLOT(slotStop()), Qt::UniqueConnection);
        connect(mMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(slotDurationChanged(qint64)), Qt::UniqueConnection);
        connect(mUi->sliderVolume, SIGNAL(sliderMoved(int)), this, SLOT(slotPlaybackSliderMoved(int)), Qt::UniqueConnection);
    }
    else
    {
        disconnect(mUi->buttonPlay, SIGNAL(clicked()), this, SLOT(slotPlay()));
        disconnect(mUi->buttonPause, SIGNAL(clicked(bool)), this, SLOT(slotPause(bool)));
        disconnect(mUi->buttonStop, SIGNAL(clicked()), this, SLOT(slotStop()));
        disconnect(mMediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(slotDurationChanged(qint64)));
        disconnect(mUi->sliderVolume, SIGNAL(sliderMoved(int)), this, SLOT(slotPlaybackSliderMoved(int)));
    }
}
