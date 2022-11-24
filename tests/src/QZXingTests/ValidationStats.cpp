#include "ValidationStats.h"

bool ValidationStats::getOperationSuccess() const
{
    return operationSuccess;
}

void ValidationStats::setOperationSuccess(bool value)
{
    operationSuccess = value;
}

bool ValidationStats::getResultMatch() const
{
    return resultMatch;
}

void ValidationStats::setResultMatch(bool value)
{
    resultMatch = value;
}

QString ValidationStats::getErrorMessage() const
{
    return errorMessage;
}

void ValidationStats::setErrorMessage(const QString &value)
{
    errorMessage = value;
}

int64_t ValidationStats::getElaspedTime() const
{
    return elaspedTime;
}

void ValidationStats::setElaspedTime(const int64_t &value)
{
    elaspedTime = value;
}

QString ValidationStats::getExpectedOutput() const
{
    return expectedOutput;
}

void ValidationStats::setExpectedOutput(const QString &value)
{
    expectedOutput = value;
}

QString ValidationStats::getImagePath() const
{
    return imagePath;
}

QString ValidationStats::getDecodedFormat() const {
    return decodedFormat;
}

QString ValidationStats::getExpectedFormat() const {
    return expectedFormat;
}

void ValidationStats::setImagePath(const QString &value)
{
    imagePath = value;
}

void ValidationStats::setExpectedFormat(QString &fmt)
{
    expectedFormat = fmt;
}

void ValidationStats::setDecodedFormat(QString decFmt) {
    decodedFormat = decFmt;
}

ValidationStats::ValidationStats():
    imagePath(""),
    expectedOutput(""),
    operationSuccess(false),
    resultMatch(false),
    errorMessage(""),
    elaspedTime(0)
{
    
}

