#include "Pineter.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Pineter::Program::Pineter w;
	w.show();
	return a.exec();
}
