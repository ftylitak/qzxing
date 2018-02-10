#include "stdafx.h"
#include "ReadQrcode.h"

#include "QZXing.h"

ReadQrcode::ReadQrcode(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pbtnDecodeImage, SIGNAL(clicked()), this, SLOT(OnDecodeImage()));
	connect(ui.pbtnClear, SIGNAL(clicked()), this, SLOT(OnClear()));
}

//识别二维码
void ReadQrcode::OnDecodeImage()
{
	OnClear();

	QString fileName = QFileDialog::getOpenFileName(this
		, QStringLiteral("获取图片文件")
		, QCoreApplication::applicationDirPath()
		, QStringLiteral("图片 (*.png *.xpm *.jpg *.ico *.bmp)"));

	if (fileName.isEmpty() || fileName.isNull())
	{
		return;
	}

	ui.labelImage->setPixmap(QPixmap(fileName));

	ui.textFileName->setPlainText(fileName);
	QString str = GetBarcode(fileName);
	ui.tedtBarcode->setPlainText(str);
}

//清空
void ReadQrcode::OnClear()
{
	ui.labelImage->setPixmap(QPixmap());
	ui.textFileName->setPlainText("");
	ui.tedtBarcode->setPlainText("");
}


bool ReadQrcode::IsBarcodeFile(const QString & strFileName)
{
	if (strFileName.trimmed().size() <= 0)
	{
		return false;
	}

	if (!QFile::exists(strFileName))
	{
		return false;
	}

	QImage qif(strFileName);
	if (qif.isNull())
	{
		return false;
	}

	QZXing decoder;
	decoder.setDecoder(QZXing::DecoderFormat_QR_CODE 
		| QZXing::DecoderFormat_PDF_417 
		| QZXing::DecoderFormat_MAXICODE 
		| QZXing::DecoderFormat_Aztec);

	if (decoder.decodeImage(qif).isEmpty())
	{
		return false;
	}

	return true;
}

QString ReadQrcode::GetBarcode(const QString& strFileName)
{
	QString str = "";

	if (strFileName.trimmed().size() <= 0)
	{
		return QStringLiteral("file name is empty %1").arg(strFileName);
	}

	if (!QFile::exists(strFileName))
	{
		return QStringLiteral("file is not exist %1").arg(strFileName);
	}

	QImage qif(strFileName);
	if (qif.isNull())
	{
		return QStringLiteral("file is not image %1").arg(strFileName);
		return str;
	}

	QZXing decoder;
	decoder.setDecoder(
		QZXing::DecoderFormat_QR_CODE
		| QZXing::DecoderFormat_PDF_417
		| QZXing::DecoderFormat_MAXICODE
		| QZXing::DecoderFormat_Aztec

		| QZXing::DecoderFormat_CODABAR
		| QZXing::DecoderFormat_CODE_39
		| QZXing::DecoderFormat_CODE_93
		| QZXing::DecoderFormat_CODE_128
		| QZXing::DecoderFormat_DATA_MATRIX

		| QZXing::DecoderFormat_EAN_8
		| QZXing::DecoderFormat_EAN_13
		| QZXing::DecoderFormat_ITF
		| QZXing::DecoderFormat_RSS_14
		| QZXing::DecoderFormat_RSS_EXPANDED
		| QZXing::DecoderFormat_UPC_A
		| QZXing::DecoderFormat_UPC_E
		| QZXing::DecoderFormat_UPC_EAN_EXTENSION
		| QZXing::DecoderFormat_CODE_128_GS1
	);

	//DecoderFormat_None = 0,
	//DecoderFormat_Aztec = 1 << 1,
	//DecoderFormat_CODABAR = 1 << 2,
	//DecoderFormat_CODE_39 = 1 << 3,
	//DecoderFormat_CODE_93 = 1 << 4,
	//DecoderFormat_CODE_128 = 1 << 5,
	//DecoderFormat_DATA_MATRIX = 1 << 6,
	//DecoderFormat_EAN_8 = 1 << 7,
	//DecoderFormat_EAN_13 = 1 << 8,
	//DecoderFormat_ITF = 1 << 9,
	//DecoderFormat_MAXICODE = 1 << 10,
	//DecoderFormat_PDF_417 = 1 << 11,
	//DecoderFormat_QR_CODE = 1 << 12,
	//DecoderFormat_RSS_14 = 1 << 13,
	//DecoderFormat_RSS_EXPANDED = 1 << 14,
	//DecoderFormat_UPC_A = 1 << 15,
	//DecoderFormat_UPC_E = 1 << 16,
	//DecoderFormat_UPC_EAN_EXTENSION = 1 << 17

	//str = decoder.decodeImage(qif, 524, 479, true);
	str = decoder.decodeImageFromFile(strFileName);

	return str;
}