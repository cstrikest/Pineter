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
			connect(ui_.actionVertical_Flip, &QAction::triggered, this, &Pineter::menuEVF);
			connect(ui_.actionHorizontal_Flip, &QAction::triggered, this, &Pineter::menuEHF);
			connect(ui_.actionRandom_Magenta, &QAction::triggered, this, &Pineter::menuERM);
			connect(ui_.actionChaos, &QAction::triggered, this, &Pineter::menuEC);
			connect(ui_.actionVertical_Mosaic, &QAction::triggered, this, &Pineter::menuEVM);
			connect(ui_.actionFull_Reverse, &QAction::triggered, this, &Pineter::menuEFR);
			connect(ui_.actionPineapple, &QAction::triggered, this, &Pineter::menuPineapple);

			//初始化
			image_ = nullptr;
			file_path_ = "";
			is_changed_ = false;
			ui_.stateLabel->setText("no pic");
			grayOutScreen();
			updateState();
		}
	}
}