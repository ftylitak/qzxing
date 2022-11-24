#ifndef DECODETESTEXECUTOR_H
#define DECODETESTEXECUTOR_H

#include <QDebug>
#include <QList>
#include <QObject>
#include <QQueue>
#include "QZXing.h"

struct TestResult {
    TestResult(QString file, QString fmt, bool res) {
        fileName = file;
        format = fmt;
        result = res;
    }
    QString fileName;
    QString format;
    bool result;
};

class DecodeTestExecutor : public QObject {
    Q_OBJECT

  public:
    explicit DecodeTestExecutor(QString dirPath, QObject* parent = nullptr);
    void executeTest();

  public slots:
    void tagFound(const QString& tag, const QString& format, const QString& charSet);
    void decodingFinished(bool);

  private:
    void fetchFilesToDecode(QString path);
    void startDecoding();
    void printResults();
    void initializeDecoderCorrelation();

    QString m_datasetPath = "";
    QZXing decoder;
    QString m_curentExpectedData, m_currentFile;
    QZXing::DecoderFormat m_expectedFormat{
        QZXing::DecoderFormat::DecoderFormat_None};
    QMap<QString, QZXing::DecoderFormat> m_decoderCorrelationMap;
    QQueue<QString> allFiles;
    QList<TestResult> m_successResults;
    QList<TestResult> m_failedResults;
    static int fileCount;
};
Q_DECLARE_METATYPE(QZXing::DecoderFormat)

#endif // DECODETESTEXECUTOR_H
