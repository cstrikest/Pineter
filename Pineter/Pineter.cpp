#include "Pineter.h"

namespace Pineter
{
	namespace Program
	{
		Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
		{
			ui_.setupUi(this);

			//绑定信号槽
			connect(ui_.action_Open, &QAction::triggered, this, &Pineter::menuOpen);
			connect(ui_.action_Save, &QAction::triggered, this, &Pineter::menuSave);
			connect(ui_.actionSave_as, &QAction::triggered, this, &Pineter::menuSaveAs);
			connect(ui_.action_Close, &QAction::triggered, this, &Pineter::menuClose);
			connect(ui_.action_Quit, &QAction::triggered, this, &Pineter::menuQuit);
			connect(ui_.actionVertical_Flip, &QAction::triggered, this, &Pineter::menuQuit);
			//connect(ui_.actionHorizontal_Flip, &QAction::triggered, this, &Pineter::menuQuit);
			//connect(ui_.actionPineapple, &QAction::triggered, this, &Pineter::menuQuit);
			//初始化
			image_ = nullptr;
			file_path_ = "";
			is_changed_ = false;
			ui_.stateLabel->setText("no pic");
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

				ui_.actionVertical_Flip->setEnabled(false);
				ui_.actionHorizontal_Flip->setEnabled(false);

				return;
			}

			//有打开的图片 没有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(false);

				ui_.actionVertical_Flip->setEnabled(true);
				ui_.actionHorizontal_Flip->setEnabled(true);
				return;
			}

			//有打开的图片 有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(true);

				ui_.actionVertical_Flip->setEnabled(true);
				ui_.actionHorizontal_Flip->setEnabled(true);
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