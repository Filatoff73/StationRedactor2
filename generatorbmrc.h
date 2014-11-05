#ifndef GENERATORBMRC_H
#define GENERATORBMRC_H

#include "qxmlstream.h"
#include "QXmlStreamAttributes"
#include "blockrelay.h"

class GeneratorBMRC
{
public:
    GeneratorBMRC();
    GeneratorBMRC(QXmlStreamReader* reader, QXmlStreamWriter* writer);
    ~GeneratorBMRC();

    void Generate();

    void ReadOneChain(QXmlStreamReader* reader, QVector<int>& posx, QVector<int>& posy);

    void DeleteElements();


private:
    QXmlStreamReader* reader;
    QXmlStreamWriter* writer;
    QVector<MainElement*> element;
    static int scaleCoef;


};

#endif // GENERATORBMRC_H
