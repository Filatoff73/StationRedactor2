#ifndef RELAYRELAY_H
#define RELAYRELAY_H
#include "mainelement.h"

class RelayContact;

class RelayRelay : public MainElement
{
public:
    RelayRelay(QGraphicsObject* parent=0);
    RelayRelay(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent=0);

    ~RelayRelay();

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );

    bool getIsVoltage() const;
    void setIsVoltage(bool value);

    int getDelay() const;
    void setDelay(int value);
    void SaveToXml(QXmlStreamWriter& writer);

private:

    bool isVoltage;
    int delay;

};

#endif // RELAYRELAY_H
