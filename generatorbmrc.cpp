#include "generatorbmrc.h"
#include "mainelement.h"
#include <QMessageBox>

#include <QDebug>

int GeneratorBMRC::scaleCoef = 6;

GeneratorBMRC::GeneratorBMRC()
{
    reader = NULL;
    writer = NULL;
}

GeneratorBMRC::GeneratorBMRC(QXmlStreamReader *reader1, QXmlStreamWriter *writer1)
{
    reader = reader1;
    writer = writer1;
}

GeneratorBMRC::~GeneratorBMRC()
{
    DeleteElements();
}

void GeneratorBMRC::Generate()
{

    writer->setAutoFormatting(true);
    writer->writeStartDocument("1.0");



    writer->writeStartElement("Station");
    writer->writeAttribute("STEP_GRID", QString::number(MainElement::GetStepGrid()));
    writer->writeAttribute("RadContact", QString::number(MainElement::getRad()));
    writer->writeAttribute("widthLinesElements", QString::number(MainElement::getWidthLinesElements()));
    writer->writeAttribute("widthLinesContacts", QString::number(MainElement::getWidthLinesContacts()));

     QVector<int> posx, posy;

    while(!reader->atEnd() && !reader->hasError())
    {
        QXmlStreamReader::TokenType token = reader->readNext();


        if(token == QXmlStreamReader::StartElement)
        {
            if(reader->name() == "Chain")
            {
                QXmlStreamAttributes attrib = reader->attributes();
                int idChain;

                if(attrib.hasAttribute("id"))
                    idChain = attrib.value("id").toInt();


              ReadOneChain(reader, posx, posy);

            }

        }


    }




    for(int i=0;i<element.size();i++)
    {
        element[i]->SaveToXml(*writer);
    }


    writer->writeEndElement();//Station
    writer->writeEndDocument();

    reader->clear();
}

void GeneratorBMRC::ReadOneChain(QXmlStreamReader *reader, QVector<int>& posx, QVector<int> &posy )
{
    while( !reader->hasError() &&  !(reader->isEndElement() && reader->name() == "Chain") )
    {
         QXmlStreamReader::TokenType token = reader->readNext();

         if(token == QXmlStreamReader::StartElement)
         {
             if(reader->name() == "DeadEnd" || reader->name() == "PathPart" || reader->name() == "Commutator" || reader->name() == "Approximation" || reader->name() == "Path")
             {
                 QXmlStreamAttributes attrib = reader->attributes();
                 int id=0;
                 QString center = "";
                 QString label = "";

                 int sizeX=4;
                 int sizeY=6;

                 if(attrib.hasAttribute("id"))
                     id = attrib.value("id").toInt();

                 if(attrib.hasAttribute("Center"))
                     center = attrib.value("Center").toString();

                 if(attrib.hasAttribute("ChainLabel"))
                     label = attrib.value("ChainLabel").toString();

                 QStringList stringList = center.split(", ");
                 posx.append(stringList.value(0).replace(",",".").toFloat() * MainElement::GetStepGrid()*scaleCoef);
                 posy.append(stringList.value(1).replace(",",".").toFloat() * MainElement::GetStepGrid()*scaleCoef);


                 element.append(new BlockRelay(id, MainElement::getTYPE_BLOCK_RELAY(), posx.last(), posy.last(), false, false,sizeX ,sizeY,1,1,1,1,reader->name().toString()));

                 element.last()->setLabelElement(label);


             }


             if(reader->name() == "Signal" )
             {
                 QXmlStreamAttributes attrib = reader->attributes();
                 int id=0;
                 QString center = "";
                 QString label = "";

                 int sizeX=3;
                 int sizeY=3;

                 if(attrib.hasAttribute("id"))
                     id = attrib.value("id").toInt();

                 if(attrib.hasAttribute("Center"))
                     center = attrib.value("Center").toString();

                 if(attrib.hasAttribute("semLabel"))
                     label = attrib.value("semLabel").toString();

                 QStringList stringList = center.split(", ");
                 posx.append( stringList.value(0).replace(",",".").toFloat()*scaleCoef); //* MainElement::GetStepGrid() / 25.93*scaleCoef;
                 posy.append( stringList.value(1).replace(",",".").toFloat()*scaleCoef/25.98*MainElement::GetStepGrid()); //* MainElement::GetStepGrid() / 25.93*scaleCoef;

                 qDebug()<<stringList;


                 element.append(new BlockRelay(id, MainElement::getTYPE_BLOCK_RELAY(), posx.last(), posy.last(), false, false,sizeX ,sizeY,1,1,1,1,reader->name().toString()));

                 element.last()->setLabelElement(label);

                 //element->SaveToXml(*writer);
             }

        }


    }
}

void GeneratorBMRC::DeleteElements()
{
    for(int i=0;i<element.size();i++)
    {
        delete element[i];
    }

    element.clear();
}
