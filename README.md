# qzxing [![Build Status](https://travis-ci.com/ftylitak/qzxing.svg?branch=master)](https://travis-ci.com/ftylitak/qzxing) [![Build Status](https://ci.appveyor.com/api/projects/status/0033p4dyo49iy5jq?svg=true)](https://ci.appveyor.com/project/ftylitak/qzxing) [![Total alerts](https://img.shields.io/lgtm/alerts/g/ftylitak/qzxing.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ftylitak/qzxing/alerts/) [![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/ftylitak/qzxing.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ftylitak/qzxing/context:cpp)

Qt/QML wrapper library for the [ZXing](https://github.com/zxing/zxing) barcode image processing library.

Supports barcode decoding for the following types:

-   UPC-A
-   UPC-E
-   EAN-8
-   EAN-13
-   ITF
-   Code 39
-   Code 93
-   Code 128 (GS1)
-   Codabar
-   QR Code
-   Data Matrix
-   Aztec (beta)
-   PDF 417

Supports barcode encoding for the following types:

-   QR Code

# Table of contents

1. [How to include](#howToInclude)
    1. [Embed the source code](#embedInSourceCode)
    1. [Compile the project as an external library](#externalLibrary)
    1. [Control dependencies](#controlDependencies)
        1. [QZXing (core)](#controlDependenciesCore)
        1. [QZXing (core + QML)](#controlDependenciesCoreQML)
        1. [QZXing + QZXingFilter](#controlDependenciesCoreQMLQZXingFilter)
1. [How to use](#howTo)
    1. [Decoding operation](#howToDecoding)
        1. [C++/Qt](#howToDecodingCPP)
        1. [Qt Quick](#howToDecodingQtQuick)
    1. [Encoding operation](#howToEncoding)
        1. [C++/Qt](#howToEncodingCPP)
        1. [Qt Quick](#howToEncodingQtQuick)
    1. [Encoded text format Information](#howToEncodingFormatExamples)
1. [Unit test dependency](#unitTestDependency)
1. [Qt 6 limitations](#qt6limitations)
1. [Contact](#contact)

<a name="howToInclude"></a>

# How to include

The project can be used in two ways:
<a name="embedInSourceCode"></a>

## Embed the source code.

Copy source code folder of QZXing to the root of your project. Add the following line to your .pro file. For more information see [here](https://github.com/ftylitak/qzxing/wiki/Using-the-QZXing-through-the-source-code).

```qmake
include(QZXing/QZXing.pri)
```

<a name="externalLibrary"></a>

## Compile the project as an external library

Open QZXing project (QZXing.pro) and compile. If it is needed to compile as static library, uncomment the following line in the .pro file.

```qmake
CONFIG += staticlib
```

<a name="controlDependencies"></a>

## Control dependencies

Project file config tags are now introduced to be able to control the dependencies of the library accoring to the needs.
The core part requires only "core" and "gui" Qt modules. Though for backward compatibility "quick" Qt module is also required.
The 3 level of dependencies are:

<a name="controlDependenciesCore"></a>

### QZXing (core)

By including QZXing.pri or by building QZXing.pro you get the core functionality of QZXing which requires only QtCore and QtGui (because of QImage).

Warning! The initial default configuration till 20/03/2017 was including qzxing_qml. This tag could not be removed once added, so it was needed to be removed from the defaults.

<a name="controlDependenciesCoreQML"></a>

### QZXing (core + QML)

If an application is going to use QML functionality, it is now possible to add the dependency to it. This can be done by adding the folloing line to the .pro file of its project:

```qmake
CONFIG += qzxing_qml
```

<a name="controlDependenciesCoreQMLQZXingFilter"></a>

### QZXing + QZXingFilter

QZXing includes QZXingFilter, an implementation to provide live feed to the decoding library. It automatically includes QML implementation as well.
This option requires "multimedia" Qt module this is why it is considered as a separate configuration. It can be used by adding the following line to the .pro file of a project:

```qmake
CONFIG += qzxing_multimedia
```

For examples on how to use QZXingFilter, it is advised to see [QZXingLive](https://github.com/ftylitak/qzxing/tree/master/examples/QZXingLive) example project. For Qt 5.x versions check [main.qml](https://github.com/ftylitak/qzxing/tree/master/examples/QZXingLive/main.qml) file, whereas for Qt 6.2 (or newer) check [main_qt6_2.qml](https://github.com/ftylitak/qzxing/tree/master/examples/QZXingLive/main_qt6_2.qml).

(Pending task: a wiki page should be written to better explain the usage of the QZXingFilter component)

<a name="howTo"></a>

# How to use

Follows simple code snippets that briefly show the use of the library. For more details advise the examples included in the repository and the [wiki](https://github.com/ftylitak/qzxing/wiki).

<a name="howToDecoding"></a>

## Decoding operation

<a name="howToDecodingCPP"></a>

### C++/Qt

```cpp
#include "QZXing.h"

int main()
{
	QImage imageToDecode("file.png");
	QZXing decoder;
        //mandatory settings
	decoder.setDecoder( DecoderFormat_QR_CODE | DecoderFormat_EAN_13 );

        //optional settings
        //decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal | QZXing::SourceFilter_ImageInverted);
        decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
        decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning | QZXing::TryHarderBehaviour_Rotate);

        //trigger decode
	QString result = decoder.decodeImage(imageToDecode);
}
```

<a name="howToDecodingQtQuick"></a>

### Qt Quick

First register QZXing type to the QML engine.

```cpp
#include "QZXing.h"

int main()
{
	...
	QZXing::registerQMLTypes();
	...
}
```

The in the QML file

```qml
import QZXing 3.3

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

        /////////////
        //optional
        tryHarderType: QZXing.TryHarderBehaviour_ThoroughScanning | QZXing.TryHarderBehaviour_Rotate

        imageSourceFilter: QZXing.SourceFilter_ImageNormal //| QZXing.SourceFilter_ImageInverted
        /////////////

	onDecodingStarted: console.log("Decoding of image started...")

	onTagFound: console.log("Barcode data: " + tag)

	onDecodingFinished: console.log("Decoding finished " + (succeeded==true ? "successfully" :    "unsuccessfully") )
}
```

<a name="howToEncoding"></a>

## Encoding operation

To begin with, make sure the Encoder feature is enabled. If **QZXing.pri** is used, then the feature is already enabled. If your project uses **QZXing-compoents.pri** instead, do add the following CONFIG in your .pro file:

```pro
CONFIG += enable_encoder_qr_code

include(QZXing/QZXing-components.pri)
```

<a name="howToEncodingCPP"></a>

### C++/Qt

The encoding function has been written as static as it does not have any dependencies to data other than the ones provided by the arguments.

Use the encoding function with its default settings:

-   Format: QR Code
-   Size: 240x240
-   Error Correction Level: Low (L)

```cpp
#include "QZXing.h"

int main()
{
    QString data = "text to be encoded";
    QImage barcode = QZXing::encodeData(data);
}
```

Or use the encoding function with custom settings:

```cpp
QString data = "text to be encoded";
QImage barcode = QZXing::encodeData(data, QZXing::EncoderFormat_QR_CODE,
								QSize(width.toInt(), height.toInt()), QZXing::EncodeErrorCorrectionLevel_H);
```

<a name="howToEncodingQtQuick"></a>

### Qt Quick

The encoding function can be easily used in QML through QZXing's Image Provider: "image://QZXing/encode/<data_to_be_encoded>". As with the C++ example, it can either be used with the default settings or with custom settings.

First register the custom Image Provider in the **main.cpp**:

```cpp
QQmlApplicationEngine engine;

QZXing::registerQMLTypes();
QZXing::registerQMLImageProvider(engine);
```

Default settings:

```qml
import QZXing 3.3

TextField {
	id: inputField
	text: "Hello world!"
}

Image{
	source: "image://QZXing/encode/" + inputField.text;
	cache: false;
}
```

Or use the encoding function with the optional custom settings that are passed like URL query parameters:

| attribute name  | value       | description                                          |
| --------------- | ----------- | ---------------------------------------------------- |
| border          | true, false | image has border (white 1px)                         |
| correctionLevel | L, M, Q, H  | the error correction level                           |
| format          | qrcode      | the encode formatter. Currently only QR Code.        |
| transparent     | true, false | whether the black pixels are transparent             |
| explicitSize    | int         | if provided, it will be the size of the Qr rectangle |

the size of the image can be adjusted by using the Image.sourceWidth and Image.sourceHeight properties of Image QML element.

```qml
import QZXing 3.3

TextField {
	id: inputField
	text: "Hello world!"
}

Image{
	source: "image://QZXing/encode/" + inputField.text +
					"?correctionLevel=M" +
					"&format=qrcode"
	sourceSize.width: 320
	sourceSize.height: 320
}
```

<a name="howToEncodingFormatExamples"></a>

### Encoded text format Information

Here is a list of contents that have been encoded and tested to be recognizable by the Android ZXing decoding application:
[QR Code encoding wiki page](https://github.com/ftylitak/qzxing/wiki/QR-Code-encoding)

<a name="unitTestDependency"></a>

# Unit test dependency

In order to run Unit tests in /test folder, the git submodule containing the test resoucres needs to be initialized and/or updated:

```bash
cd qzxing
git submodule update --init --recursive
```

<a name="qt6limitations"></a>

# Qt 6 limitations

On Qt 6, a number of modules have been removed or not yet supported. The [list of removed modules](https://doc.qt.io/qt-6/whatsnew60.html#removed-modules-in-qt-6-0)
includes two important features that directly affect QZXing:

## Text codecs

QZXing used [QTextCodec](https://doc.qt.io/qt-6/qtextcodec.html) to re-interpret the parsed strings into their proper encoding. In Qt6, QTextCodec has been moved to **core5compat** module.
After testing, it seems that QTextCodec, if used through core5compat in Qt 6, it does not support many of the encoding that it did in Qt 5 (for instance, Shift-JIS encoding).
To avoid the dependency of an extra module (that also does not work as supposed to), QTextCodec has been replaced by [QStringDecoder](https://doc.qt.io/qt-6/qstringdecoder.html) only when building for Qt 6.
If QZXing if build for Qt 5, QTextCodec is used as it was.

<a name="contact"></a>

# Contact

In case of bug reports or feature requests feel free to open an [issue](https://github.com/ftylitak/qzxing/issues).
