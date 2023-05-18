//#include "ip.h"
//
//IP::IP(std::string path)
//{
//	std::string format = path.substr(path.find_last_of(".") + 1);
//	if (format == "bmp")
//	{
//		image_ = new Bmp(path.c_str())->getImageBgr24b();
//		name_ = path.substr(path.find_last_of("/\\") + 1);
//	}
//	else
//	{
//		throw LoadImageFailedException();
//	}
//}
//
//IP::IP()
//{
//	image_ = new LinearRgb24b(100, 100);
//	name_ = "untitle";
//}
