#include "Pineter.h"
//https://subingwen.cn/qt/qt-signal-slot/
//https://www.xinbaoku.com/archive/8yc8sMF5.html
//https://www.w3cschool.cn/learnroadqt/edlr1j3y.html
//https://wizardforcel.gitbooks.io/qt-beginning/content/5.html
//https://qtguide.ustclug.org/
Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
{
	ip = nullptr;
	is_image_open_ = false;
	ui.setupUi(this);
	connect(ui.action_Open, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.bh, SIGNAL(clicked()), this, SLOT(bhc()));
	connect(ui.bw, SIGNAL(clicked()), this, SLOT(bwc()));
}

Pineter::~Pineter()
{
	delete ip;
}

void Pineter::openFile()
{
	QFileDialog dlg(this, "Open a Bitmap file.", "c:\\", "Bitmap Files (*.bmp)");
	while (dlg.exec())
	{
		try
		{
			ip = new IP(dlg.selectedFiles().first().toStdString());
			ui.label->setText(QString::number(ip->image_->getArea()));
			is_image_open_ = true;
			break;
		}
		catch (std::exception& e)
		{
			ip = nullptr;
			delete ip;
			QMessageBox::warning
			(
				this,
				"Failed to load",
				QString::fromStdString("Failed to load image file.\n") + 
				dlg.selectedFiles().first() + "\n" + QString::fromStdString(e.what()),
				QMessageBox::Ok
			);
		}
	}
}

void Pineter::bhc()
{
	ui.label->setText(QString::number(ip->image_->height_));
}

void Pineter::bwc()
{
	ui.label->setText(QString::number(ip->image_->width_));
}
