#ifndef BLOCKRELAY_H
#define BLOCKRELAY_H

#include "mainelement.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneContextMenuEvent>

class BlockRelay : public MainElement
{
public:
    BlockRelay(QGraphicsObject* parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void DrawBlock(QPainter* painter);

    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );
    static int getSiezeBlockX();
    static void setSiezeBlockX(int value);

    static int getSiezeBlockY();
    static void setSiezeBlockY(int value);

private:
    static int SiezeBlockX;
    static int SiezeBlockY;

};

#endif // BLOCKRELAY_H
