#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ReadQrcode.h"

class ReadQrcode : public QMainWindow
{
	Q_OBJECT

public:
	ReadQrcode(QWidget *parent = Q_NULLPTR);

private slots:
	//识别二维码
	void OnDecodeImage();
	//清空
	void OnClear();

private:
	bool IsBarcodeFile(const QString & strFileName);

	QString GetBarcode(const QString& strFileName);

private:
	Ui::ReadQrcodeClass ui;
};
