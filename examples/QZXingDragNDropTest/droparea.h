#ifndef DROPAREA_H
#define DROPAREA_H

#include <qglobal.h>
//#include <QDeclarativeItem>
#include <QQuickItem>

/**
    An oversimplified prototype Item which accepts any drop that includes
    data with mime type of text/plain, and just emits the text.
*/
//class DropArea : public QDeclarativeItem
class DropArea : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool acceptingDrops READ isAcceptingDrops WRITE setAcceptingDrops NOTIFY acceptingDropsChanged)

public:
    DropArea(QQuickItem *parent=0);
    bool isAcceptingDrops() const { return m_accepting; }
    void setAcceptingDrops(bool accepting);

signals:
    void fileDroped(QString url);
    void acceptingDropsChanged();

protected:
    void	dropEvent(QDropEvent * event);
//    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
//    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    bool m_accepting;
};

#endif // DROPAREA_H
