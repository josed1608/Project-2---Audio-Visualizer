#include "ChoiceWidget.h"
#include "ui_ChoiceWidget.h"
#include <View.h>

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

ChoiceWidget::~ChoiceWidget()
{
	delete ui;
	view->deleteLater();
}

void ChoiceWidget::startVisualizationAllThree()
{
	view = new View(-1);
	view->show();
	this->setVisible(false);
}

void ChoiceWidget::startVisualizationAudioFace()
{
	view = new View(2);
	view->show();
	this->setVisible(false);
}

void ChoiceWidget::startVisualizationAudioRectangles()
{
	view = new View(1);
	view->show();
	this->setVisible(false);
}

void ChoiceWidget::startVisualizationAudioCircle()
{
	view = new View(0);
	view->show();
	this->setVisible(false);
}

void ChoiceWidget::startVisualizationAudioChart()
{
	view = new View(3);
	view->show();
	this->setVisible(false);
}
