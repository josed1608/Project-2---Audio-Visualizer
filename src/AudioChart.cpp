#include "AudioChart.h"
#include <vector>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

/**
 * @brief Default constructor that sets the rectangles dimensions and maximum ammount of rects that can be drawn
 * @param scene Scene where chart will be drawn
 * @param parent QObject parent for OBject constructor
 */
AudioChart::AudioChart(QGraphicsScene *scene, QObject *parent): QObject(parent),
	scene(scene),
	rectWidth(5),
	maxRects(1920/rectWidth - 2) //minus two to avoid rects off screen
{}

/**
 * @brief Method that updates the chart. Adds new rects to the scene and vector
 * @param value current value of instensity
 */
void AudioChart::update(int value)
{
	//If maxRects hasn't been reached, just add the new rect to end of vector
	if(info.size() < maxRects){
		//Pos the rect correctly for positive value
		if(value > 0){
			QGraphicsRectItem* newRect = new QGraphicsRectItem(0, 0, rectWidth, value*2);
			newRect->setPos(info.size()*rectWidth, 1080/2-value*2);
			newRect->setBrush(QBrush(QColor(255,255,255)));
			scene->addItem(newRect);
			info.push_back(newRect);
		}
		//Pos the rect correctly for negative value
		else{
			QGraphicsRectItem* newRect = new QGraphicsRectItem(0, 0, rectWidth, abs(value*2));
			newRect->setPos(info.size()*rectWidth, 1080/2);
			newRect->setBrush(QBrush(QColor(255,255,255)));
			scene->addItem(newRect);
			info.push_back(newRect);
		}
	}
	else{
		//delete the first one and move all the remaining rects to the left
		delete info.front();
		info.pop_front();
		for(std::list<QGraphicsRectItem*>::iterator itr = info.begin(); itr != info.end(); ++itr){
			(*itr)->setX((*itr)->x()-rectWidth);
		}
		//Add new rect correctly
		if(value > 0){
			QGraphicsRectItem* newRect = new QGraphicsRectItem(0, 0, rectWidth, value*2);
			newRect->setPos(info.size()*rectWidth, 1080/2-value*2);
			newRect->setBrush(QBrush(QColor(255,255,255)));
			scene->addItem(newRect);
			info.push_back(newRect);
		}
		else{
			QGraphicsRectItem* newRect = new QGraphicsRectItem(0, 0, rectWidth, abs(value*2));
			newRect->setPos(info.size()*rectWidth, 1080/2);
			newRect->setBrush(QBrush(QColor(255,255,255)));
			scene->addItem(newRect);
			info.push_back(newRect);
		}
	}
}
