#include "droparea.h"

#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QDebug>

DropArea::DropArea(QDeclarativeItem *parent) : QDeclarativeItem(parent),
    m_accepting(true)
{
    setAcceptDrops(m_accepting);
}

void DropArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->acceptProposedAction();
    setCursor(Qt::DragMoveCursor);
}

void DropArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    unsetCursor();
}

void DropArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug("File!");
    QList<QUrl> list = event->mimeData()->urls();
    for(int i=0; i<list.size(); i++)
    {
        QString path = list.at(i).path();
        emit fileDroped(path.right(path.size()-1));
    }
    unsetCursor();
}

void DropArea::setAcceptingDrops(bool accepting)
{
    if (accepting == m_accepting)
        return;

    m_accepting = accepting;

    setAcceptDrops(m_accepting);
    emit acceptingDropsChanged();
}
