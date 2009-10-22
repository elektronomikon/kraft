/***************************************************************************
                      kraftview.h  - view of kraft documents
                             -------------------
    begin                : Mit Dez 31 19:24:05 CET 2003
    copyright            : (C) 2003 by Klaas Freitag
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

#ifndef KRAFTVIEW_H
#define KRAFTVIEW_H

// include files for Qt
#include <qwidget.h>
#include <qmap.h>
#include <qtabwidget.h>
#include <QResizeEvent>
#include <QLabel>

#include <kdialog.h>
#include <kabc/addressee.h>

#include "kraftdoc.h"

/** The KraftView class provides the view widget for the KraftApp instance.
 * The View instance inherits QWidget as a base class and represents
 * the view object of a KTMainWindow. As KraftView is part of the
 * docuement-view model, it needs a reference to the document object
 * connected with it by the KraftApp class to manipulate and display
 * the document structure provided by the KraftDoc class.
 *
 * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
 * @version KDevelop version 0.4 code generation
 */
#include <q3ptrlist.h>

#include "positionviewwidget.h"
#include "catalogtemplate.h"
#include "ui_docheader.h"
#include "ui_docfooter.h"

class Q3ScrollView;
class PositionViewWidget;
class DocPosition;
class QLabel;
class QResizeEvent;
class QSignalMapper;
class QStackedWidget;
class KVBox;
class QSplitter;
class DocPostCard;
class QTimer;
class CatalogSelection;
class HeaderSelection;
class KPushButton;
class DocAssistant;
class CalcPartList;

class Katalog;

using namespace KABC;

class KraftViewScroll : public Q3ScrollView
{
  Q_OBJECT

public:
  KraftViewScroll( QWidget* );
  ~KraftViewScroll() { }

  void viewportResizeEvent( QResizeEvent* );
  void addChild( QWidget *child, int x=0, int y=0 );
  // the removeChild method is not virtual for scrollview, so
  // our own needs to be implemented.
  void kraftRemoveChild( PositionViewWidget *child );

public slots:
  void resizeContents( int, int );

private:
  Q3PtrList<PositionViewWidget> mWidgetList;
};

// ###########################################################################

class KraftView : public KDialog
{
  Q_OBJECT
    public:
  /** Constructor for the main view */
  KraftView(QWidget *parent);
  /** Destructor for the main view */
  virtual ~KraftView();

  /** returns a pointer to the document connected to the view
      instance. Mind that this method requires a KraftApp instance as a
      parent * widget to get to the window document pointer by calling
      the KraftApp::getDocument() method.
      *
      * @see KraftApp#getDocument
      */
  KraftDoc *getDocument() const;

  /** contains the implementation for printing functionality */
  void print(QPrinter *pPrinter);

  void setup( DocGuardedPtr );


  typedef QMap<DocPositionBase*, PositionViewWidget*> PositionMap;

  DocPositionList currentPositionList();
  DocPositionBase::TaxType currentTaxSetting();

  public slots:
  void slotNewAddress( const Addressee& contact = Addressee() );
  void redrawDocument( );
  void slotModifiedPositions();
  void slotModifiedHeader();
  void slotModifiedFooter();
  void slotAddPosition( Katalog*, void* );
  void slotAddPosition();
  void slotAddExtraPosition();
  void slotImportItems();
  void slotFocusPosition( PositionViewWidget*,  int );
  void slotNewHeaderText( const QString& );
  void slotNewFooterText( const QString&  );
  void slotSwitchToPage( int );
  
  protected slots:
  void slotOk();
  void slotCancel();
  void redrawDocPositions( );
  void done( int );
  void slotMovePositionUp( int );
  void slotMovePositionDown( int );
  void slotDeletePosition( int );
  void slotUnlockPosition( int );
  void slotLockPosition( int );
  void slotPositionModified( int );
  void slotAboutToShow( QWidget* );
  void refreshPostCard( );
  void slotShowCatalog( bool );
  void slotShowTemplates( bool );

  void slotDocTypeChanged( const QString& );
  void slotLanguageSettings();

signals:
  void selectPage( int );
  void viewClosed( bool, DocGuardedPtr );
  void positionSelected( Katalog*, void* );
private:
  void setupDocHeaderView();
  void setupPositions();
  void setupFooter();
  void setupTextsView();
  void setMappingId( QWidget *, int );
  void setupMappers();

  PositionViewWidget *createPositionViewWidget( DocPositionBase*, int );

  QStringList generateLetterHead( Addressee adr );

  KraftViewScroll *m_positionScroll;
  Ui::DocHeaderEdit *m_headerEdit;
  Ui::DocFooterEdit *m_footerEdit;

  PositionViewWidgetList mPositionWidgetList;

  QString mContactUid;
  DocGuardedPtr m_doc;
  QSignalMapper *mDeleteMapper;
  QSignalMapper *mMoveUpMapper;
  QSignalMapper *mMoveDownMapper;
  QSignalMapper *mUnlockPositionMapper;
  QSignalMapper *mLockPositionMapper;
  QSignalMapper *mModifiedMapper;

  QLabel *mDetailHeader;
  QSplitter *mCSplit;
  KPushButton *mCatalogToggle;
  QLabel *mHelpLabel;

  QWidget *mSumSpacer;
  QStackedWidget *mViewStack;
  KVBox *mGlobalVBox;
  int mHeaderId;
  DocAssistant *mAssistant;
  double mRememberAmount;
  QMap<dbID, CalcPartList> mCalculationsMap;
  CatalogTemplateList      mNewTemplates;
  bool mModified;
};

#endif // KRAFTVIEW_H
