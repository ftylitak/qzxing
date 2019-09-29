#ifndef QXZINGPLUGIN_H
#define QXZINGPLUGIN_H
#include <QtQml/QQmlExtensionPlugin>
#include <QQmlEngine>

class QZXingPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;
};

#endif // QXZINGPLUGIN_H
