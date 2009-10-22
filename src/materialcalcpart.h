/***************************************************************************
             materialcalcpart  -
                             -------------------
    begin                : 2004-09-05
    copyright            : (C) 2004 by Klaas Freitag
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

#ifndef _MATERIALCALCPART_H
#define _MATERIALCALCPART_H

// include files
#include<q3ptrdict.h>
#include<qvariant.h>

#include "calcpart.h"

/**
 *
 */
class StockMaterial;
class StockMaterialList;

class MaterialCalcPart : public CalcPart
{

public:
  MaterialCalcPart();
    MaterialCalcPart( long mCalcID, const QString& name, int percent );
    MaterialCalcPart( const QString& name, int percent);
    ~MaterialCalcPart();

    void addMaterial( double amount, long materialID );
    void addMaterial( double amount, StockMaterial* mat );
    void removeMaterial( StockMaterial *mat );

    virtual Geld basisKosten();
    QString getType() const;
    bool containsMaterial( long materialID );
    StockMaterialList getCalcMaterialList();
    double getCalcAmount( StockMaterial* );
    bool   setCalcAmount( StockMaterial*, double );
    Geld getCostsForMaterial( StockMaterial *mat );
    Geld getPriceForMaterial( StockMaterial *mat );
private:
    long m_calcID;
    QHash<StockMaterial*, QVariant> m_amounts;
};

#endif

/* END */

