#include "AudioRect.h"
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QTimer>
#include <iostream>

/**
 * @brief Constructor for an AudioRect that requires a scene for the rect to be put in, an intensity value and a parent. The animator inmediately adds the rect to the scene, and animates it
 * @param scene QGraphicsScene for the rect to be put in
 * @param value Intensity value to give the Rect it's dimensions and speed
 * @param parent Qobject pointer for the QObject constructor
 */
AudioRect::AudioRect(QGraphicsScene *scene, int value, QObject* parent)
	: QObject(parent)
{
	this->setBrush(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256))); //random color
	this->setRect(0, 0,value*3,value*3); //size respective to the intensity
	this->setPos(rand() % 1820, rand() % 980); //random starting position

	scene->addItem(this);

	//The speed of the aniimations depend on the intensity. Larger rects move and fade slower than smaller ones
	QPropertyAnimation *opacityAnimation = new QPropertyAnimation(this, "opacity");
	opacityAnimation->setDuration((100*value));
	opacityAnimation->setStartValue(1.0);
	opacityAnimation->setEndValue(0.0);

	QPropertyAnimation *posAnimation = new QPropertyAnimation(this, "pos");
	posAnimation->setDuration((100*value));
	posAnimation->setStartValue(this->pos());
	int randomMovement = rand()%4;
	//randomly sets the movement direction
	if(randomMovement == 0){
		posAnimation->setEndValue(QPointF(1920/2, 0)); // arriba
	}
	if(randomMovement == 1){
		posAnimation->setEndValue(QPointF(1920, 1080/2)); // derecha
	}
	if(randomMovement == 2){
		posAnimation->setEndValue(QPointF(1920/2,1080)); // abajo
	}
	if(randomMovement == 3){
		posAnimation->setEndValue(QPointF(0,1080/2)); // izquierda
	}

	opacityAnimation->start();
	posAnimation->start();

	deletionTimer = new QTimer; //Timer for deleting the rect once it fades
	connect(deletionTimer, SIGNAL(timeout()), this, SLOT(removeRect()));
	deletionTimer->start(100*value);
	
}

/**
 * @brief Constructor that creates a rect that fades on the given position
 * @param x Desired x position
 * @param y Desired y position
 * @param parent QObject pointer required by the base class constructor
 */
AudioRect::AudioRect(qreal x, qreal y, QObject *parent): QObject(parent)
{
	this->setBrush(QBrush(QColor(rand() % 256, rand() % 256, rand() % 256)));
	this->setRect(0, 0,20,20); 
	this->setPos(x, y); 
	
	QPropertyAnimation *opacityAnimation = new QPropertyAnimation(this, "opacity");
	opacityAnimation->setDuration(1000);
	opacityAnimation->setStartValue(1.0);
	opacityAnimation->setEndValue(0.0);
	
	opacityAnimation->start();
	
	deletionTimer = new QTimer; //Timer for deleting the rect once it fades
	connect(deletionTimer, SIGNAL(timeout()), this, SLOT(removeRect()));
	deletionTimer->start(1000);
}

/**
 * @brief Slot method connected to the deletionTimer once the rect has faded away
 */
void AudioRect::removeRect()
{
	//std::cerr << "deleted" << std::endl;
	deletionTimer->deleteLater();
	this->deleteLater();
}
