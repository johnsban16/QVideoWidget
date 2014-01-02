#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>

namespace Ui
{
    class VideoWidget;
}

class QVideoWidget;
class QMediaPlayer;

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void slotPlay();
    void slotPause(bool);
    void slotStop();
    void slotDurationChanged(qint64);
    void slotPlaybackSliderMoved(int);

private:
    void connectSignals(bool establish);

private:
    Ui::VideoWidget *mUi;
    QVideoWidget *mVideoWidget;
    QMediaPlayer *mMediaPlayer;
    QWidget *mVideoContainer;
};

#endif // VIDEOWIDGET_H
