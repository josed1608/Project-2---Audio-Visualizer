#ifndef AUDIOCHART_H
#define AUDIOCHART_H

#include <QObject>
#include <list>

class QGraphicsRectItem;
class QGraphicsScene;

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
