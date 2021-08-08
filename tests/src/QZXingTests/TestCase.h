#ifndef TESTCASE_H
#define TESTCASE_H

#include "QZXing.h"
#include <zxing/Exception.h>
#include <QtGlobal>
#include <zxing/qrcode/decoder/Mode.h>
#include "backward.hpp"
#include <QDebug>
#include <QStringList>

namespace zxing{

// TO-DO
// use macros  __FILE__, __LINE__

template<typename T, int sz>
static int getArrayLength(T(&)[sz])
{
    return sz;
}

#define ASSERT_THROWS(x) \
    try { \
        #x; \
        assertTrue(false); \
    } catch(zxing::Exception &/*e*/) { \
    }

class TestCase {

private:
    static QString itemToString(std::string item) {
        return QString::fromStdString(item);
    }

    static QString itemToString(int item) {
        return QString::number(item);
    }

    static QString itemToString(void* item) {
        return QString::number(reinterpret_cast<uintptr_t>(item));
    }

    static QString itemToString(long unsigned item) {
        return QString::number(item);
    }

    static QString itemToString(zxing::byte item) {
        return QString::number(item);
    }

    static QString itemToString(qrcode::Mode& item) {
        return QString::fromStdString(item.getName());
    }

    static QString itemToString(unsigned int item) {
        return QString::number(item);
    }

protected:
    template<class T> void assertEquals(T expected, T actual) {
        if(expected != actual) {
            QString message = QString("\nExpected: \n[") + itemToString(expected) +
                    QString("], \nGot: \n[") + itemToString(actual) + QString("]");

            backward::StackTrace st;
            st.load_here(32);

            backward::TraceResolver tr;
            tr.load_stacktrace(st);
            for (size_t i = 0; i < st.size(); ++i) {
                backward::ResolvedTrace trace = tr.resolve(st[i]);
                message += QString::fromStdString("\n#");
                message += QString::number(i);
                message += QString::fromStdString(trace.object_filename);
                message += QString::fromStdString(trace.object_function);
                message += QString("[");
                message += itemToString(trace.addr);
                message += QString("]\n");
            }

            throw zxing::Exception(message.toStdString().c_str());
        }
    }

    void assertEquals(const char* expected, const std::string &actual) {
        std::string expected_str(expected);
        assertEquals(expected_str, actual);
    }

//    void assertEquals(int expected, int actual) {
//        assertEquals(expected, actual);
//    }

    void assertSame(qrcode::Mode &expected, qrcode::Mode &actual){
        assertEquals(expected, actual);
    }

    void assertSame(void *expected, void *actual) {
        assertEquals(expected, actual);
    }

    void assertTrue(bool actual) {
        assertEquals(true, actual);
    }

    void assertFalse(bool actual) {
        assertEquals(false, actual);
    }

    void assertDataEquals(const std::string &message,
                            const std::vector<zxing::byte> &expected,
                            const std::vector<zxing::byte> & received)
    {
        if(expected.size() != received.size())
            assertTrue(false);

        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != received[i]) {
                qDebug() << QString::fromStdString(message) << ". Mismatch at " << QString::number(i) /*<< ". Expected " + arrayToString(expected) + ", got " +
                     arrayToString(Arrays.copyOf(received, expected.length)))*/;
                assertTrue(false);
            }
        }
    }

    void assertDataEquals(const std::string &message,
                            const std::vector<zxing::byte> &expected,
                            const QSharedPointer<std::vector<zxing::byte>> &received)
    {
        if(int(expected.size()) != received->size())
            assertTrue(false);

        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != (*received)[i]) {
                qDebug() << QString::fromStdString(message) << ". Mismatch at " << QString::number(i) /*<< ". Expected " + arrayToString(expected) + ", got " +
                     arrayToString(Arrays.copyOf(received, expected.length)))*/;
                assertTrue(false);
            }
        }
    }

    void assertDataEquals(const std::string &message,
                            const std::vector<zxing::byte> &expected,
                            const QSharedPointer<std::vector<int>> &received)
    {
        QSharedPointer<std::vector<zxing::byte>> received_copy(new std::vector<zxing::byte>(received->size()));
        for(int i=0; i<received_copy->size(); i++)
            (*received_copy)[i] = (*received)[i];

        assertDataEquals(message, expected, received_copy);
    }

    static void initializeRandom();
    static int generateRandomNumber(int range);

public:
    virtual ~TestCase() {}
    virtual void execute()=0;
};

}

#endif // TESTCASE_H
