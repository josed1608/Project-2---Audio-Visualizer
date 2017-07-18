#include <QGraphicsScene>


#include <QGraphicsEllipseItem>

#include "AudioChart.h"
#include "AudioCircle.h"
#include "AudioDevice.h"
#include "AudioFace.h"
#include "AudioRect.h"

/**
 * @brief Default constructor that starts the visualization
 * @param scene QGraphicsScene connected to the View
 * @param parent QObject required by the parent class constructor
 */
AudioDevice::AudioDevice(int visualizationCode, QGraphicsScene* scene, QObject *parent) :
        QIODevice(parent),
        scene(scene),
        visualization(1)
{
        //Start with the visualization specified by the visualizationCode and stick to iy
        visualization = visualizationCode;
        if(visualization == 0){
                circle = new AudioCircle(scene);
        }
        else if(visualization == 2){
                face = new AudioFace(scene);
        }
        else if(visualization == 3){
                chart = new AudioChart(scene);
        }

}

/**
 * @brief Pure virtual function inherited from QIODevice taht needs to be declared. Because the device is opened on WRITE_MODE, this method musn't be used
 * @param data Read data buffer
 * @param maxSize Max size of the data buffer
 * @return 0 to fulfill the method scheme
 */
qint64 AudioDevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
        return 0;
}

/**
 * @brief Method that processes the data from the audioInput
 * @param data Data given by the audioInput
 * @param maxSize Max size of the data buffer
 * @return Returns @a maxSize because it's used by the readData method
 */
qint64 AudioDevice::writeData(const char * data, qint64 maxSize)
{
        if(visualization != 3){
                int value = 0; //Var used to store the max amplitude recorded
                bool higherThan10 = false;
                //10 is used as a threshhold value in order to avoid unnecesary noise. The for loop checks for the highest value recorded
                for(int counter = 0; counter < maxSize; ++counter){
                        int currentValue = (quint8)data[counter] - 128;
                        if(currentValue > 10 || currentValue < -10){
                                higherThan10 = true;
                                if(abs(currentValue) > abs(value))
                                        value = currentValue;
                        }
                }

                //Visualizes the audio with the method indicated by the visualization var

                if(visualization == 0){
                        circle->update(abs(value));
                }

                else if(visualization == 1 ){
                        if(higherThan10)
                                new AudioRect(scene, abs(value));
                }

                else if(visualization == 2){
                        face->update(abs(value));
                }
        }

        else{
                int resolution = 40; //Determines how many of the data points are gonna be drawn
                for(int k = 0; k < maxSize/resolution; k++){
                        chart->update((quint8)data[resolution * k] - 128);
                }
        }
        return maxSize;
}

/**
 * @brief This slot method is the response to the double click mouse press on scene. Changes the visualization mode
 */
void AudioDevice::changeVisualization(){
        if(visualization == 0){
                circle->deleteLater();
        }
        else if(visualization == 2){
                face->deleteLater();
        }
        else if(visualization == 3){
                chart->deleteLater();
        }

        scene->clear();
        ++visualization;
        visualization %= 4;

        if(visualization == 0){
                circle = new AudioCircle(scene);
        }
        else if(visualization == 2){
                face = new AudioFace(scene);
        }
        else if(visualization == 3){
                chart = new AudioChart(scene);
        }
}

/**
 * @brief Destructor thats deletes the memebers located in dynamic memory
 */
AudioDevice::~AudioDevice(){
        circle->deleteLater();
        face->deleteLater();
        chart->deleteLater();
}

/**
 * @brief Creates a Rect where the mouse was pressed
 * @param x X pos of the mouse
 * @param y Y pos of the mouse
 */
void AudioDevice::drawRectFromMouse(qreal x, qreal y)
{
        scene->addItem(new AudioRect(x,y));
}
