/***************************************************************************
                   prefsdialog.cpp  - the preferences Dialog
                             -------------------
    begin                : Sun Jul 3 2004
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

#include<qlayout.h>
#include<qlineedit.h>
#include <qlineedit.h>
#include<qlabel.h>
#include<qframe.h>
#include <qhbox.h>
#include <qvbox.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qcombobox.h>
#include <qlayout.h>

#include<kdialog.h>
#include<klocale.h>
#include<kiconloader.h>
#include<kmessagebox.h>

#include "prefsdialog.h"
#include "katalogsettings.h"
#include "kraftdb.h"
#include "kraftdoc.h"
#include "defaultprovider.h"

PrefsDialog::PrefsDialog( QWidget *parent)
    : KDialogBase( IconList,  i18n("Configure Kraft"), Ok|Cancel, Ok, parent,
                   "PrefsDialog", true, true )
{
  databaseTab();
  entryTextTab();
  footerTextTab();
}

void PrefsDialog::entryTextTab()
{
  QVBox *vb = addVBoxPage( i18n( "Header Texts" ),
                           i18n( "Edit the Default Header Texts" ),
                           DesktopIcon( "gear" ) );
  QHBox *hb = new QHBox( vb );
  ( void ) new QLabel( i18n( "Used in document type:" ), hb );
  mTextTypeEntry = new QComboBox( hb );
  mTextTypeEntry->insertStringList( DefaultProvider::self()->docTypes() );
  connect( mTextTypeEntry, SIGNAL( activated( const QString& ) ),
           this, SLOT( slotHeaderDocTypeChanged( const QString& ) ) );

  mHeaderEdit = new QTextEdit( vb, "HeaderTextEdit" );
  mHeaderEdit->setTextFormat( Qt::PlainText );
  mHeaderDocType = mTextTypeEntry->currentText();
  mHeaderEdit->setText(
    DefaultProvider::self()->defaultText( mTextTypeEntry->currentText(),
                                          KraftDoc::Header ) );
}

void PrefsDialog::footerTextTab()
{
  QVBox *vb = addVBoxPage( i18n( "Footer Texts" ),
                           i18n( "Edit the Default Footer Texts" ),
                           DesktopIcon( "gear" ) );
  QHBox *hb = new QHBox( vb );
  ( void ) new QLabel( i18n( "Used in document type:" ), hb );
  mTextTypeFooter = new QComboBox( hb );
  mTextTypeFooter->insertStringList( DefaultProvider::self()->docTypes() );
  connect( mTextTypeFooter, SIGNAL( activated( const QString& ) ),
           this, SLOT( slotFooterDocTypeChanged( const QString& ) ) );

  mFooterEdit = new QTextEdit( vb, "FooterTextEdit" );
  mFooterEdit->setTextFormat( Qt::PlainText );
  mFooterDocType = mTextTypeFooter->currentText();
  mFooterEdit->setText( DefaultProvider::self()->defaultText( mFooterDocType, KraftDoc::Footer ) );

}

void PrefsDialog::slotFooterDocTypeChanged( const QString& newEntry )
{
  if ( newEntry != mFooterDocType ) {
    const QString origText = DefaultProvider::self()->defaultText( mFooterDocType, KraftDoc::Footer );
    kdDebug() << "Original text: <" << origText << "> and edit <" << mFooterEdit->text() << ">" << endl;

    if ( mFooterEdit->text() != origText ) {
      int answer = KMessageBox::Yes;

      // only ask if we are switching to another doc type and not if Ok was pressed to finish the dialog.
      if ( ! newEntry.isEmpty() ) {
        answer = KMessageBox::questionYesNo( this, i18n( "The default footer text for %1 was changed."
                                                         "Do you want to save the changed text?" ).arg( mFooterDocType ) );
      }

      if ( answer == KMessageBox::Yes ) {
        // DefaultProvider::self()->saveDocumentText( mFooterDocType, "Footer", mFooterEdit->text() );
      } else {
        kdDebug() << "Canceled change to default text" << endl;
      }
    } else {
      kdDebug() << "Footer text has not changed" << endl;
    }
  }
  mFooterDocType = newEntry;
  mFooterEdit->setText( DefaultProvider::self()->defaultText( mFooterDocType, KraftDoc::Footer ) );
}

void PrefsDialog::slotHeaderDocTypeChanged( const QString& newEntry )
{
  if ( newEntry != mHeaderDocType ) {
    const QString origText = DefaultProvider::self()->defaultText( mHeaderDocType, KraftDoc::Header );
    kdDebug() << "Original text: "<< origText << " and new: " << mHeaderEdit->text() <<endl;
    if ( mHeaderEdit->text() != origText ) {
      int answer = KMessageBox::Yes;
      if ( ! newEntry.isEmpty() ) {
        answer = KMessageBox::questionYesNo( this, i18n( "The default header text for %1 was changed."
                                                         "Do you want to save the changed text?" ).arg( mHeaderDocType ) );
      }

      if ( answer == KMessageBox::Yes ) {
        // DefaultProvider::self()->saveDocumentText( mHeaderDocType, "Header", mHeaderEdit->text() );
      } else {
        kdDebug() << "Canceled change to default text" << endl;
      }
    } else {
      kdDebug() << "Header text has not changed" << endl;
    }
  }
  mHeaderDocType = newEntry;
  mHeaderEdit->setText( DefaultProvider::self()->defaultText( mHeaderDocType, KraftDoc::Header ) );
}

void PrefsDialog::databaseTab()
{
  QLabel *label;
  QFrame *topFrame = addPage( i18n( "Database" ),
                              i18n( "Database Connection Settings" ),
                              DesktopIcon( "connect_no" ) );

  QVBoxLayout *vboxLay = new QVBoxLayout( topFrame );
  QGridLayout *topLayout = new QGridLayout( topFrame );
  vboxLay->addLayout( topLayout );

  topLayout->setSpacing( spacingHint() );
  topLayout->setColSpacing( 0, spacingHint() );

  label = new QLabel(i18n("Database Host:"), topFrame );
  topLayout->addWidget(label, 0,0);

  label = new QLabel(i18n("Database Name:"), topFrame );
  topLayout->addWidget(label, 1,0);

  label = new QLabel(i18n("Database User:"), topFrame );
  topLayout->addWidget(label, 2,0);

  label = new QLabel(i18n("Database Password:"), topFrame );
  topLayout->addWidget(label, 3,0);

  label = new QLabel(i18n("Connection Status:"), topFrame );
  topLayout->addWidget(label, 4,0);

  m_pbCheck = new QPushButton( i18n( "Check Connection" ), topFrame );
  m_pbCheck->setEnabled( false );
  topLayout->addWidget( m_pbCheck, 5, 1 );

  m_leHost = new QLineEdit( topFrame );
  connect( m_leHost, SIGNAL( textChanged( const QString& ) ),
           this, SLOT( slotTextChanged( const QString& ) ) );
  topLayout->addWidget(m_leHost, 0,1);

  m_leName = new QLineEdit( topFrame );
  connect( m_leName, SIGNAL( textChanged( const QString& ) ),
           this, SLOT( slotTextChanged( const QString& ) ) );
  topLayout->addWidget(m_leName, 1,1);

  m_leUser = new QLineEdit( topFrame );
  connect( m_leUser, SIGNAL( textChanged( const QString& ) ),
           this, SLOT( slotTextChanged( const QString& ) ) );
  topLayout->addWidget(m_leUser, 2,1);

  m_lePasswd = new QLineEdit( topFrame );
  m_lePasswd->setEchoMode(QLineEdit::Password);
  connect( m_lePasswd, SIGNAL( textChanged( const QString& ) ),
           this, SLOT( slotTextChanged( const QString& ) ) );
  topLayout->addWidget(m_lePasswd, 3,1);

  m_statusLabel = new QLabel( topFrame );
  topLayout->addWidget( m_statusLabel,  4, 1 );

  connect( m_pbCheck, SIGNAL( clicked() ),
           this, SLOT( slotCheckConnect() ) );

  vboxLay->addItem( new QSpacerItem( 1, 1 ) );

  readConfig();
  slotCheckConnect();
}

void PrefsDialog::slotTextChanged( const QString& )
{
  bool en = false;
  if ( !m_leName->text().isEmpty() ) {
    en = true;
  }

  m_pbCheck->setEnabled( en );
}

void PrefsDialog::readConfig()
{
    m_leHost->setText( KatalogSettings::dbServerName() );
    m_leName->setText( KatalogSettings::dbFile() );
    m_leUser->setText( KatalogSettings::dbUser() );
    m_lePasswd->setText( KatalogSettings::dbPassword() );
}

void PrefsDialog::writeConfig()
{
    KatalogSettings::setDbServerName(m_leHost->text());
    KatalogSettings::setDbFile(m_leName->text());
    KatalogSettings::setDbUser(m_leUser->text());
    KatalogSettings::setDbPassword( m_lePasswd->text());
    KatalogSettings::writeConfig();
}

PrefsDialog::~PrefsDialog()
{
}

void PrefsDialog::slotCheckConnect()
{
  kdDebug() << "Trying database connect to db " << m_leName->text() << endl;

  int x = KraftDB::self()->checkConnect( m_leHost->text(), m_leName->text(),
                                         m_leUser->text(), m_lePasswd->text() );
  kdDebug() << "Connection result: " << x << endl;
  if ( x == 0 ) {
    m_statusLabel->setText( i18n( "Good!" ) );
  } else {
    m_statusLabel->setText( i18n( "Failed" ) );
  }
}

void PrefsDialog::slotOk()
{
    writeConfig();
    slotHeaderDocTypeChanged( QString() );
    slotFooterDocTypeChanged( QString() );
    accept();
}

#include "prefsdialog.moc"
