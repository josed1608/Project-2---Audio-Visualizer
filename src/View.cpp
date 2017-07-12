#include "View.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QMouseEvent>

#include "AudioDevice.h"
#include "ChoiceWidget.h"

/**
 * @brief Default constructor for the View class that initializes all of the required members of the class to present the audio visualization
 * @param parent Pointer to a QWidget that is required by the parent class constructor
 */
View::View(int visualizationCode, QWidget *parent): QGraphicsView(parent),
      m_device(0),
      m_audioInput(0)
{
	// create the scene
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,1920,1080); //Set the screen size to 1080p

	this->setScene(scene);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setFixedSize(1920,1080);
	scene->setBackgroundBrush(QBrush(QColor(QRgb(0000)))); //Set background to black


	//Format the audio input
	QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
	formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

	QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice(); //Get the default microphone interfaces given by the OS
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

	m_device = new AudioDevice(visualizationCode, scene, this); //IO device that receives the information from the mic
    m_device->open(QIODevice::WriteOnly);

	m_audioInput->start(m_device); //start recording
}

/**
 * @brief Destructor that deletes the contents of the View
 */
View::~View()
{
    m_audioInput->stop();
    m_device->close();
	scene->deleteLater();
}

/**
 * @brief Override of the QWidget mouseMoveEvent in order to pass the mouse possition to the controller and draw squares where the mouse is dragged
 * @param event Current mouse event being proccesed
 */
void View::mouseMoveEvent(QMouseEvent *event)
{
	m_device->drawRectFromMouse(event->pos().x(), event->pos().y());
}

/**
 * @brief Override of the QWidget mouseDOubleClickEvent in order to change the visualization when desired
 * @param event Contains the information regarding the current state of the mouse. Unused in this case
 */
void View::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event);
	m_device->changeVisualization();
}
