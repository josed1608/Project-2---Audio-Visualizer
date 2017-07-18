#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>

#include "AudioChart.h"

/**
 * @brief Default constructor that sets the rectangles dimensions and maximum ammount of rects that can be drawn
 * @param scene Scene where chart will be drawn
 * @param parent QObject parent for OBject constructor
 */
AudioChart::AudioChart(QGraphicsScene *scene, QObject *parent): QObject(parent),
    scene(scene),
    rectWidth(2),
    maxRects(1920/rectWidth - 2), //minus two to avoid rects off screen
    currentColor(0)
{}

/**
 * @brief Method that updates the chart. Adds new rects to the scene and vector
 * @param value current value of instensity
 */
void AudioChart::update(int value)
{
    QColor color = QColor(255,255,255);
    if(currentColor == 0){
        color = QColor(255,0,0);
    }
    else if(currentColor == 1){
        color = QColor(0,255,0);
    }
    else{
        color = QColor(0,0,255);
    }

    //If maxRects hasn't been reached, just add the new rect to end of vector
    QGraphicsRectItem* newRect = 0;
    if(info.size() < maxRects){
        //Pos the rect correctly for positive value
        if(value > 0){
            newRect = new QGraphicsRectItem(info.size()*rectWidth, 1080/2-value*2, rectWidth, value*2);
        }
        //Pos the rect correctly for negative value
        else{
            newRect = new QGraphicsRectItem(info.size()*rectWidth, 1080/2, rectWidth, abs(value*2));
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
            newRect = new QGraphicsRectItem(info.size()*rectWidth, 1080/2-value*2, rectWidth, value*2);
        }
        else{
            newRect = new QGraphicsRectItem(info.size()*rectWidth, 1080/2, rectWidth, abs(value*2));
        }
    }

    newRect->setBrush(QBrush(color));
    scene->addItem(newRect);
    info.push_back(newRect);

    currentColor++;
    currentColor %= 3;
}
