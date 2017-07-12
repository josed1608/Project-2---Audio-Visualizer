#ifndef AUDIOCIRCLE_H
#define AUDIOCIRCLE_H

#include <QObject>
#include <QGraphicsEllipseItem>

class QGraphicsScene;

/**
 * @brief The AudioCircle class represents a circle that changes its color and size based on audio intensity
 * @property scene QGraphicsScene this circle is added to
 */
class AudioCircle : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ getColor WRITE setColor)
	Q_PROPERTY(QRectF geometry READ rect WRITE setRect)

protected:
	QGraphicsScene* scene;

public:
	explicit AudioCircle(QGraphicsScene* scene, QObject *parent = 0);
	void update(int value);

	QColor getColor() const;

	void setColor(const QColor& newColor);
};

#endif // AUDIOCIRCLE_H
