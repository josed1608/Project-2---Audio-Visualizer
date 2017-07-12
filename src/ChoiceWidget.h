#ifndef CHOICEWIDGET_H
#define CHOICEWIDGET_H

#include <QWidget>

class View;

namespace Ui {
class ChoiceWidget;
}

class ChoiceWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ChoiceWidget(QWidget *parent = 0);
	~ChoiceWidget();

private:
	Ui::ChoiceWidget *ui;
	View* view;

public slots:
	void startVisualizationAllThree();
	void startVisualizationAudioFace();
	void startVisualizationAudioRectangles();
	void startVisualizationAudioCircle();
	void startVisualizationAudioChart();
};

#endif // CHOICEWIDGET_H
