/*
 * Copyright 2017 QZXing authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef QZXingFilter_H
#define QZXingFilter_H

#include <QObject>
#include <QDebug>
#include <QFuture>
#include "QZXing.h"
#include <QtMultimedia/QVideoSink>
#include <QtMultimedia/QVideoFrame>

/// Video filter is the filter that has to be registered in C++, instantiated and attached in QML
class QZXingFilter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool decoding READ isDecoding NOTIFY isDecodingChanged)
    Q_PROPERTY(QZXing* decoder READ getDecoder)
    Q_PROPERTY(QRectF captureRect MEMBER captureRect NOTIFY captureRectChanged)
    Q_PROPERTY(QObject* videoSink WRITE setVideoSink)
    Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

    signals:
        void isDecodingChanged();
        void decodingFinished(bool succeeded, int decodeTime);
        void decodingStarted();
        void captureRectChanged();
        void orientationChanged(int orientation);

    private slots:
        void handleDecodingStarted();
        void handleDecodingFinished(bool succeeded);
        void processFrame(const QVideoFrame &frame);
        void setOrientation(int orientation);
        int orientation() const;

    private: /// Attributes
        QZXing decoder;
        bool decoding;
        QRectF captureRect;
        int orientation_;

        QVideoSink *m_videoSink;
        QFuture<void> processThread;

    public:  /// Methods
        explicit QZXingFilter(QObject *parent = 0);
        void setVideoSink(QObject *videoSink);
        virtual ~QZXingFilter();

        bool isDecoding() {return decoding; }
        QZXing* getDecoder() { return &decoder; }
};

#endif // QZXingFilter_H
