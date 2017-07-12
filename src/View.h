#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>

class QWidget;

class QGraphicsScene;

class AudioDevice;

class QMouseEvent;

class QAudioInput;


/**
 * @brief The View class is used to graphically represent the items in the scene
 * @property scene Abstractally containd the items in the screen
 * @property m_device IO device that processes the information from the audioInput
 * @property m_audioInput Takes information from the default audio recording device and gives it to @a m_device
 */
class View : public QGraphicsView
{

	Q_OBJECT

public:
	View(int visualizationCode, QWidget *parent = 0);
	~View();

protected:
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	QGraphicsScene * scene;
	AudioDevice *m_device;
	QAudioInput *m_audioInput;
};

#endif // WIDGET_H
