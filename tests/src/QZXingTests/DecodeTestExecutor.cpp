#include "DecodeTestExecutor.h"
#include <QDebug>
#include <QDir>
#include <QFileInfoList>

int DecodeTestExecutor::fileCount = 0;

DecodeTestExecutor::DecodeTestExecutor(QString dirPath, QObject* parent) : QObject(parent){
    m_datasetPath = dirPath;

    decoder.setTryHarder(true);

    connect(&decoder, SIGNAL(tagFoundAdvanced(const QString&, const QString&, const QString&)),
            this, SLOT(tagFound(const QString&, const QString&, const QString&)));

    connect(&decoder, SIGNAL(decodingFinished(bool)),
            this, SLOT(decodingFinished(bool)));
}

void DecodeTestExecutor::executeTest() {
    QFileInfo dirInfo(m_datasetPath);
    if (!dirInfo.isDir()) {
        qDebug() << m_datasetPath << "Doesnt seem to be valid directory";
        return;
    }

    QDir folder(m_datasetPath);

    QFileInfoList l = folder.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    qDebug() << "Fetching files to decode... ";
    for (int i = 0; i < l.count(); i++) {
        QFileInfo info = l.at(i);
        qDebug() << "Reading folder: " << info.absoluteFilePath();
        fetchFilesToDecode(info.absoluteFilePath());
    }
    qDebug() << "started decoding "<< fileCount<<" files.. ";
    startDecoding();
}

void DecodeTestExecutor::fetchFilesToDecode(QString path) {
    QDir curPath(path);
    curPath.setFilter(QDir::NoDotAndDotDot);
    QStringList images =
        curPath.entryList(QStringList() << "*.png", QDir::Files);

    foreach (QString file, images) {
        fileCount++;
        QString imgPath = curPath.path() + "/" + file;
        allFiles.enqueue(imgPath);
    }
}

void DecodeTestExecutor::startDecoding() {
    //dequeue a file and start decoding.
    if (!allFiles.isEmpty()) {
        QString file = allFiles.dequeue();
        QString exp = file.left(file.lastIndexOf('.')).append(".txt");
        QFile expected(exp);
        if (expected.open(QFile::ReadOnly)) {
            m_curentExpectedData = expected.readAll();
        }
        m_currentFile = file;
        decoder.decodeImageFromFile(file);
    } else {
        printResults();
    }
}

void DecodeTestExecutor::printResults() {
    qDebug() << "Decoded Results";

    qDebug() << "Total Files : " << DecodeTestExecutor::fileCount;
    qDebug() << "Decode Success count : " << m_successResults.count();
    qDebug() << "Decode Failure count : " << m_failedResults.count();
    qDebug() << "-----------------------------";
}

void DecodeTestExecutor::tagFound(const QString& tag, const QString& format,
                            const QString& charSet) {
    Q_UNUSED(charSet);

    if (m_curentExpectedData == tag || format != "") {
        qDebug() << m_currentFile << " Format : "<< format << "Decode Success";
        m_successResults.append(TestResult(m_currentFile, format, true));
    }
}

void DecodeTestExecutor::decodingFinished(bool result) {
    if (!result) {
        qDebug() << m_currentFile << " Format : UNKNOWN" << "Decode Failure";
        m_failedResults.append(TestResult(m_currentFile,QString(""),false));
    }

    //After decoding a file has finished, fetch the next available file in the queue to decode.
    startDecoding();
}
