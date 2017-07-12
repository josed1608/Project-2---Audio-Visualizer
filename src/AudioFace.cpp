#include "AudioFace.h"
#include <QGraphicsScene>
#include "AudioCircle.h"
#include <QPropertyAnimation>

/**
 * @brief Constructor for the Audioface that draws and positions it
 * @param scene Scene where it'll be drawn
 * @param parent Parent used by the base class constructor
 */
AudioFace::AudioFace(QGraphicsScene *scene, QObject *parent): QObject(parent),
	QGraphicsPathItem(QPainterPath(startPoint)),
	faceSide(500),
	controlPoint(QPointF(1920/2, 1080/2 + faceSide/2)),
	startPoint(QPointF(1920/2-faceSide/4, 1080/2+faceSide/5)),
	endPoint(QPointF(1920/2+faceSide/4, 1080/2+faceSide/5)),
	scene(scene),
	faceBackground(new AudioCircle(this->scene))
{
	//Position face in the center of the screen
	faceBackground->setRect(1920/2-faceSide/2, 1080/2-faceSide/2, faceSide, faceSide);
	faceBackground->setBrush(QBrush(QColor(0,255,0)));

	AudioCircle* eye1 = new AudioCircle(scene);
	AudioCircle* eye2 = new AudioCircle(scene);

	//Position eyes
	eye1->setRect(1920/2-faceSide/5 - faceSide/8, 1080/2-faceSide/3, faceSide/4, faceSide/4);
	eye1->setBrush(QBrush(QColor(0,0,0)));

	eye2->setRect(1920/2+faceSide/5 - faceSide/8, 1080/2-faceSide/3, faceSide/4, faceSide/4);
	eye2->setBrush(QBrush(QColor(0,0,0)));

	//Draw mouth
	this->path().quadTo(controlPoint, endPoint);
	this->setPen(QPen(QBrush(QColor(0,0,0)), 20.0));
	this->scene->addItem(this);
}
/**
 * @brief Method called in the AudioDevice everytime a new intensity value is processed. Turns the mouth and changes color in order to represent  different emotions
 * @param value intensity value provided by the IO device
 */
void AudioFace::update(int value){
	QPropertyAnimation* colorAnimation = new QPropertyAnimation(faceBackground, "color");
	colorAnimation->setDuration(200);
	colorAnimation->setStartValue(faceBackground->getColor());
	int newGreen = 255-6*value, newRed = value*6;
	if(newGreen < 0){
		newGreen = 0;
		newRed = 255;
	}
	colorAnimation->setEndValue(QColor(newRed, newGreen, 0));

	QPropertyAnimation* beizerAnimation = new QPropertyAnimation(this, "bezier");
	beizerAnimation->setDuration(100);
	beizerAnimation->setStartValue(this->getBezier());
	beizerAnimation->setEndValue(QPointF(1920/2, (1080/2 + faceSide/2) - value*5)); //Moves the control point of the bezier curver accordingly to the intensity

	colorAnimation->start();
	beizerAnimation->start();
}

/**
 * @brief Method used by the bezier animation. This and the setBezier where created because Qt doesn't a way of chnanging the controll point of a QPainterPath's quadTo method
 * @return returns current controll point
 */
QPointF AudioFace::getBezier() const
{
	return controlPoint;
}

/**
 * @brief Sets a new controll point for the animation
 * @param controlPoint Controll point to be set
 */
void AudioFace::setBezier(const QPointF &controlPoint)
{
	QPainterPath* newPath =  new QPainterPath(startPoint);
	newPath->quadTo(controlPoint, endPoint);
	this->setPath(*newPath);
	this->controlPoint = controlPoint;
}
