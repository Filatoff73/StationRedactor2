#ifndef RELAYCONTACT_H
#define RELAYCONTACT_H
#include "mainelement.h"

class RelayRelay;

class RelayContact : public MainElement
{
public:
    RelayContact(QGraphicsObject* parent=0);
    RelayContact(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent=0);

    void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );
    void ReDrawContact();
    void RemoveAssociatedRelay(void);

    RelayRelay *getAssociatedRelay() const;
    void setAssociatedRelay(RelayRelay *value);

    bool getIsLinked() const;
    void setIsLinked(bool value);

    bool getIsProcessLinked() const;
    void setIsProcessLinked(bool value);
    void SaveToXml(QXmlStreamWriter& writer);

private:
    bool isLinked;
    bool isProcessLinked;
    RelayRelay * associatedRelay;
};

#endif // RELAYCONTACT_H
