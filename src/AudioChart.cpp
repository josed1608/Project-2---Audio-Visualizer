#include "AudioChart.h"
#include <vector>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

AudioChart::AudioChart(QGraphicsScene *scene, QObject *parent): QObject(parent),
	scene(scene),
	rectWidth(5),
	maxRects(1920/rectWidth - 2)
{}

void AudioChart::update(int value)
{

	if(info.size() < maxRects){
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
	else{
		//delete the first one and move all the remaining rects to the left
		delete info.front();
		info.pop_front();
		for(std::list<QGraphicsRectItem*>::iterator itr = info.begin(); itr != info.end(); ++itr){
			(*itr)->setX((*itr)->x()-rectWidth);
		}
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
