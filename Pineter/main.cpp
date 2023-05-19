#include "Pineter.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Pineter::Program::Pineter w;
	w.show();
	return a.exec();
}

//throw出去之后有没有回收资源和return和关闭文件流对象和重置状态
//UI界面
//打开 保存 另存为 关闭 的逻辑