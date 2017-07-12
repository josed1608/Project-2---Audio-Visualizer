#include <QtWidgets/QApplication>
#include "ChoiceWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ChoiceWidget choice;
	choice.show();
    
    return a.exec();
}
