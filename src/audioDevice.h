#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QtCore/QIODevice>

class AudioCircle;
class AudioFace;
class AudioChart;
class QGraphicsScene;

/**
 * @brief The AudioDevice class is the controller between the View and the audioInput. Transferes the information from each actor the respective class in order to represent the desired visualization
 * @property scene Pointer to the GraphicsScene linked to teh View
 * @property circle Pointer to an AudioCircle used for visualization
 * @property face Pointer to an AudioFace used for visualization
 * @property visualization Integer that indicates the current visualization mode
 */
class AudioDevice : public QIODevice
{
    Q_OBJECT
public:
        AudioDevice(int visualizationCode, QGraphicsScene* scene, QObject* parent = 0);
        ~AudioDevice();

        void drawRectFromMouse(qreal x, qreal y);

protected:
        qint64 readData(char * data, qint64 maxSize) override;
        qint64 writeData(const char * data, qint64 maxSize) override;

private:
        QGraphicsScene* scene;
        AudioCircle* circle;
        AudioFace* face;
        AudioChart* chart;
        int visualization;

public slots:
        void changeVisualization();
};

#endif // AUDIODEVICE_H
