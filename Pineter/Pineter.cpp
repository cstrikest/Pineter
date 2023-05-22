#include "Pineter.h"

namespace Pineter
{
	namespace Program
	{
		Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
		{
			ui_.setupUi(this);

			//绑定信号槽
			connect(ui_.action_Open, &QAction::triggered, this, &Pineter::fileOpen);
			connect(ui_.action_Save, &QAction::triggered, this, &Pineter::fileSave);
			connect(ui_.actionSave_as, &QAction::triggered, this, &Pineter::fileSaveAs);
			connect(ui_.action_Close, &QAction::triggered, this, &Pineter::fileClose);

			//初始化
			image_ = nullptr;
			file_path_ = "";
			is_changed_ = false;
			updateState();
		}

		void Pineter::updateState()
		{
			//没有打开的图片
			if (image_ == nullptr)
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(false);
				ui_.actionSave_as->setEnabled(false);
				ui_.action_Save->setEnabled(false);
				return;
			}

			//有打开的图片 没有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(false);
				return;
			}

			//有打开的图片 有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(true);
				return;
			}
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