#include "Pineter.h"

namespace Pineter
{
	namespace Program
	{
		Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
		{
			image_ = nullptr;
			file_path_ = "";
			ui_.setupUi(this);
			connect(ui_.action_Open, &QAction::triggered, this, &Pineter::fileOpen);
			connect(ui_.action_Save, &QAction::triggered, this, &Pineter::fileSave);
			connect(ui_.actionSave_as, &QAction::triggered, this, &Pineter::fileSaveAs);
			connect(ui_.action_Close, &QAction::triggered, this, &Pineter::fileClose);
		}


		//
		//void Pineter::paintEvent(QPaintEvent* event)
		//{
		//	QPainter p(this);
		//	p.setPen(QColor(255, 0, 0));
		//	p.drawPoint(100, 200);
		//	p.drawLine(0, 0, 300, 400);
		//}
	}
}