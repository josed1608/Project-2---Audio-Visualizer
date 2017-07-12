#include "AudioCircle.h"
#include <QGraphicsScene>
#include <QPropertyAnimation>

/**
 * @brief Constructor for the AudioCircle that adds the Circle to the scene given
 * @param scene QGraphicsScene where the circle will be added
 * @param parent QObject pointer required by the base class constructor
 */
AudioCircle::AudioCircle(QGraphicsScene* scene, QObject *parent) : QObject(parent),
	scene(scene)
{
	this->scene->addItem(this);
}

/**
 * @brief Method called in the AudioDevice everytime a new intensity value is processed. Creates a size and color animation to transition to new state indicated by the intensity value
 * @param value intensity value provided by the IO device
 */
void AudioCircle::update(int value){
	QPropertyAnimation* colorAnimation = new QPropertyAnimation(this, "color");
	colorAnimation->setDuration(200);
	colorAnimation->setStartValue(this->getColor());
	int newGreen = 255-6*value, newRed = value*6; //New green and red RGB values based on the instensity
	//If the green value becomes negative, make it 0 and max the red value. This is to avoid RGB out range warnings during execution
	if(newGreen < 0){
		newGreen = 0;
		newRed = 255;
	}
	colorAnimation->setEndValue(QColor(newRed, newGreen, 0));

	//This animation keeps the circle centered and makes it larger or smaller depending on the new intensity
	QPropertyAnimation* geometryAnimation = new QPropertyAnimation(this, "geometry");
	geometryAnimation->setDuration(200);
	geometryAnimation->setStartValue(this->rect());
	geometryAnimation->setEndValue(QRectF(1920.0/2.0 - (value*10)/2.0, 1080.0/2.0 - (value*10)/2.0, value*10, value*10));

	colorAnimation->start();
	geometryAnimation->start();
}

/**
 * @brief Method used by the color animation. This method and setColor where created because Qt doesn't have methods for switching between colors in an animation
 * @return returns current color of the circle
 */
QColor AudioCircle::getColor() const
{
	return this->brush().color();
}

/**
 * @brief Method used by the color animation to set a new Color
 * @param newColor New color to be set
 */
void AudioCircle::setColor(const QColor& newColor)
{
	this->setBrush(QBrush(newColor));
}

