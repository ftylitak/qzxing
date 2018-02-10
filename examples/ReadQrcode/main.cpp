#include "stdafx.h"
#include "ReadQrcode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ReadQrcode w;
	w.show();
	return a.exec();
}
