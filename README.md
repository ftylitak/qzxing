# qzxing
Qt/QML wrapper library for the [ZXing](https://github.com/zxing/zxing) decoding library. 

Supports barcode decoding for the following types: 

 * UPC-A 	
 * UPC-E 	
 * EAN-8 	
 * EAN-13 	
 * ITF 	
 * Code 39 
 * Code 93 	
 * Code 128 (GS1) 	
 * Codabar 	
 * QR Code
 * Data Matrix
 * Aztec (beta)
 * PDF 417

# How to include

The project can be used in two ways:
## Embed the source code. 
Copy source code folder of QZXing to the root of your project. Add the following line to your .pro file. For more information see [here](https://github.com/ftylitak/qzxing/wiki/Using-the-QZXing-through-the-source-code).

```qmake
include(QZXing/QZXing.pri)
```

## Compile the project as an external library
Open QZXing project (QZXing.pro) and compile. If it is needed to compile as static library, uncomment the following line in the .pro file.

```qmake
CONFIG += staticlib
```

## Control dependencies
Project file config tags are now introduced to be able to control the dependencies of the library accoring to the needs.
The core part requires only "core" and "gui" Qt modules. Though for backward compatibility "quick" Qt module is also required. 
The 3 level of dependencies are:

### QZXing (core)
By including QZXing.pri or by building QZXing.pro you get the core functionality of QZXing which requires only QtCore and QtGui (because of QImage).

Warning! The initial default configuration till 20/03/2017 was including qzxing_qml. This tag could not be removed once added, so it was needed to be removed from the defaults. 

### QZXing (core + QML)
If an application is going to use QML functionality, it is now possible to add the dependency to it. This can be done by adding the folloing line to the .pro file of its project:
	
```qmake
CONFIG += qzxing_qml
```
	
### QZXing + QZXingFilter
QZXing includes QZXingFilter, a QAbstractVideoFilter implementation to provide a mean of providing live feed to the decoding library. It automatically includes QML implementation as well.
This option requires "multimedia" Qt module this is why it is considered as a separate configuration. It can be used by adding the folloing line to the .pro file of a project:

```qmake
CONFIG += qzxing_multimedia
```
	
# How to use

Follows simple code snippets that brefly show the use of the library. For more details advise the examples included in the repository and the [wiki](https://github.com/ftylitak/qzxing/wiki).

## C++/Qt

```cpp
#include <QZXing.h>

int main() 
{
	QImage imageToDecode("file.png");
	QZXing decoder;
	decoder.setDecoder( DecoderFormat_QR_CODE | DecoderFormat_EAN_13 );
	QString result = decoder.decodeImage(imageToDecode);
}
```
	
## QML

First register QZXing type to the QML engine.

```cpp
#include <QZXing.h>

int main() 
{
	...
	QZXing::registerQMLTypes();
	...
}
```
	
The in the QML file 

```qml
import QZXing 2.3

function decode(preview) {
	imageToDecode.source = preview
	decoder.decodeImageQML(imageToDecode);
}

Image{
	id:imageToDecode
}

QZXing{
	id: decoder

	enabledDecoders: QZXing.DecoderFormat_QR_CODE

	onDecodingStarted: console.log("Decoding of image started...")

	onTagFound: console.log("Barcode data: " + tag)

	onDecodingFinished: console.log("Decoding finished " + (succeeded==true ? "successfully" :    "unsuccessfully") )
}
```
 
# contact
In case of bug reports or feature requests feel free to open an [issue](https://github.com/ftylitak/qzxing/issues). 
