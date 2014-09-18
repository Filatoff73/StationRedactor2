#ifndef CHAINPOINT_H
#define CHAINPOINT_H
#include "mainelement.h"

class ChainPoint : public MainElement
{
public:
    ChainPoint(QGraphicsObject* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // CHAINPOINT_H
