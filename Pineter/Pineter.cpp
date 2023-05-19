#include "Pineter.h"

Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
{
	
	image_ = nullptr;

	file_path_ = "";
	ui_.setupUi(this);
	connect(ui_.action_Open, &QAction::triggered, this, &Pineter::fileOpen);
	connect(ui_.action_Save, &QAction::triggered, this, &Pineter::fileSave);
	connect(ui_.actionSave_as, &QAction::triggered, this, &Pineter::fileSaveAs);

}

Pineter::~Pineter()
{
	delete image_;
}

//
//void Pineter::paintEvent(QPaintEvent* event)
//{
//	QPainter p(this);
//	p.setPen(QColor(255, 0, 0));
//	p.drawPoint(100, 200);
//	p.drawLine(0, 0, 300, 400);
//}