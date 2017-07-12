#include "ChoiceWidget.h"
#include "ui_ChoiceWidget.h"
#include <View.h>

/**
 * @brief Constructor that connects each button from the ui to its respective view mode
 * @param parent QObject parent for OBject constructor
 */
ChoiceWidget::ChoiceWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChoiceWidget)
{
	ui->setupUi(this);
	ui->allThree->pressed();
	connect(ui->allThree,SIGNAL(pressed()), this, SLOT(startVisualizationAllThree()));
	connect(ui->audioCircle,SIGNAL(pressed()), this, SLOT(startVisualizationAudioCircle()));
	connect(ui->audioFace,SIGNAL(pressed()), this, SLOT(startVisualizationAudioFace()));
	connect(ui->audioRectangles,SIGNAL(pressed()), this, SLOT(startVisualizationAudioRectangles()));
	connect(ui->commandLinkButton, SIGNAL(pressed()), this, SLOT(startVisualizationAudioChart()));
}

/**
 * @brief Destructor that deletes elements in dynamic memory
 */
ChoiceWidget::~ChoiceWidget()
{
	delete ui;
	view->deleteLater();
}

/**
 * @brief Start visualization with All four types
 */
void ChoiceWidget::startVisualizationAllThree()
{
	view = new View(-1);
	view->show();
	this->setVisible(false);
}

/**
 * @brief Only Audio Face visualization
 */
void ChoiceWidget::startVisualizationAudioFace()
{
	view = new View(2);
	view->show();
	this->setVisible(false);
}

/**
 * @brief Only Audio Rectangles visualization
 */
void ChoiceWidget::startVisualizationAudioRectangles()
{
	view = new View(1);
	view->show();
	this->setVisible(false);
}

/**
 * @brief Only Audio Circle Visualization
 */
void ChoiceWidget::startVisualizationAudioCircle()
{
	view = new View(0);
	view->show();
	this->setVisible(false);
}

/**
 * @brief Only audio Chart visualization
 */
void ChoiceWidget::startVisualizationAudioChart()
{
	view = new View(3);
	view->show();
	this->setVisible(false);
}
