#ifndef AUDIOCHART_H
#define AUDIOCHART_H

#include <QObject>
#include <list>

class QGraphicsRectItem;
class QGraphicsScene;

/**
 * @brief The AudioChart class creates a graphic chart representation of the values read from the microphone
 * @property info Vector of rects in the chart
 * @property rectWidth width of the rects drawn
 * @property maxRects Max ammount of rects than can be drawn on screen
 * @property scene Scene where the chart will be drawn
 * @property currentColor Indicator of the current color that the next rect to be drawn will have
 */
class AudioChart: public QObject
{

	Q_OBJECT

public:
	AudioChart(QGraphicsScene* scene, QObject* parent = 0);
	void update(int value);

private:
	std::list<QGraphicsRectItem*> info;
	QGraphicsScene* scene;
	qreal rectWidth;
	size_t maxRects;
	int currentColor;
};

#endif // AUDIOCHART_H
