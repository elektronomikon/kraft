/***************************************************************************
             documentsaverxml - save documents to the an xml file
                             -------------------
    begin                : 2013-01-02
    copyright            : (C) 2013 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _DOCUMENTSAVERXML_H
#define _DOCUMENTSAVERXML_H

#include "documentsaverbase.h"

class KraftDoc;
class dbID;
class QString;

class DocumentSaverXML : public DocumentSaverBase
{
    Q_OBJECT

public:
    DocumentSaverXML();
    virtual ~DocumentSaverXML();

    virtual bool saveDocument( KraftDoc* );
    virtual void load( const QString& , KraftDoc * );
private:
    const QString PosTypePosition;
    const QString PosTypeExtraDiscount;
    const QString PosTypeHeader;

};

#endif

/* END */
