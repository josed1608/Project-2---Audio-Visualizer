#ifndef RECT_H
#define RECT_H

#include <QObject>
#include <QGraphicsRectItem>

class QTimer;
class QGraphicsItem;

/**
 * @brief The AudioRect class is used to create rectangles whose properties depend on the intensity value given by the audioInput
 */
class AudioRect: public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
	AudioRect(QGraphicsScene* scene, int value, QObject *parent = 0);
	AudioRect(qreal x, qreal y, QObject* parent = 0);
	QTimer* deletionTimer;

public slots:
	void removeRect();
};

#endif // RECT_H
