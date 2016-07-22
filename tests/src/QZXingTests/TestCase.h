#ifndef TESTCASE_H
#define TESTCASE_H

#include <QZXing.h>
#include <zxing/Exception.h>
#include <QtGlobal>
#include <zxing/qrcode/decoder/Mode.h>

namespace zxing{

class TestCase {

private:
    static QString itemToString(std::string item) {
        return QString::fromStdString(item);
    }

    static QString itemToString(int item) {
        return QString::number(item);
    }

    static QString itemToString(long unsigned item) {
        return QString::number(item);
    }

    static QString itemToString(byte item) {
        return QString::number(item);
    }

    static QString itemToString(qrcode::Mode& item) {
        return QString::fromStdString(item.toString());
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

    void assertSame(qrcode::Mode &expected, qrcode::Mode &actual){
        assertEquals(expected, actual);
    }

    void assertSame(void *expected, void *actual) {
        assertEquals((int)expected, (int)actual);
    }

    void assertTrue(bool actual) {
        assertEquals(1, (int)actual);
    }

    void assertFalse(bool actual) {
        assertEquals(0, (int)actual);
    }

public:
    virtual void execute()=0;
};

}

#endif // TESTCASE_H
