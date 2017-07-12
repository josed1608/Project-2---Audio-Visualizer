#ifndef AUDIOFACE_H
#define AUDIOFACE_H

#include <QObject>
#include <QGraphicsPathItem>

class AudioCircle;
class QGraphicsScene;

/**
 * @brief The AudioFace class is used to represent a face that reacts to the intensity values. It gets madder as the intensity rises.
 * @property faceSide Size of the face bounding rect. Saved for making the geometry calculations more readable
 * @property controlPoint Describes the position of the control point used by the QPainterPath to draw the bezier curve
 * @property startPoint Start point of the bezier curve
 * @property endPoint End point of the bezier curve
 * @property scene Scene where the face will be located
 * @property faceBackground AudioCircle that will serve as the face itself
 */
class AudioFace: public QObject, public QGraphicsPathItem
{

	Q_OBJECT
	Q_PROPERTY(QPointF bezier READ getBezier WRITE setBezier)

protected:
	int faceSide;
	QPointF controlPoint;
	QPointF startPoint;
	QPointF endPoint;
	QGraphicsScene* scene;
	AudioCircle* faceBackground;

public:
	AudioFace(QGraphicsScene* scene, QObject*  parent = 0);

	void update(int value);

	QPointF getBezier() const;

	void setBezier(const QPointF& controlPoint);
};

#endif // AUDIOFACE_H
