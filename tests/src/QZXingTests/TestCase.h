#ifndef TESTCASE_H
#define TESTCASE_H

#include <QZXing.h>
#include <zxing/Exception.h>
#include <QtGlobal>

namespace zxing{

class TestCase {

private:
    static QString itemToString(std::string item) {
        return QString::fromStdString(item);
    }

    static QString itemToString(int item) {
        return QString::number(item);
    }

    static QString itemToString(byte item) {
        return QString::number(item);
    }

protected:
    template<class T> void assertEquals(T expected, T actual) {
        if(expected != actual) {
            QString message = QString("Expected: ") + itemToString(expected) +
                    QString(", Got: ") + itemToString(actual);
            Q_ASSERT_X(false, "assertEquals", message.toStdString().c_str());
            throw new zxing::Exception(message.toStdString().c_str());
        }
    }

    void assertSame(void *expected, void *actual) {
        if(expected != actual) {
            throw new zxing::Exception("expected != actual");
        }
    }
};

}

#endif // TESTCASE_H
