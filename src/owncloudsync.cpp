#include "owncloudsync.h"
#include "mirall/owncloudfolder.h"
#include "mirall/credentialstore.h"
#include "mirall/mirallconfigfile.h"

#include <QApplication>

ownCloudSync::ownCloudSync(QObject *parent) :
    QObject(parent),
    _syncFolder(0)
{
    qApp->setApplicationName( QLatin1String("ownCloud")); // FIXME!
}

void ownCloudSync::slotCredentialsFetched(bool res )
{
    if( _srcPath.isEmpty() ) {
        qDebug() << "No src-path given!";
        return;
    }

    if( res ) {

        qDebug() << "Successfully fetched credentials!";
        MirallConfigFile cfg;

        QString oCUrl = cfg.ownCloudUrl(QString::null, true);

        QString kraftPath("kraft");
        _syncFolder = new ownCloudFolder(QLatin1String("KraftFolder"), _srcPath, oCUrl+kraftPath );

        connect(_syncFolder, SIGNAL(syncFinished(SyncResult)),
                SLOT(slotSyncFinished(SyncResult)));

        _syncFolder->startSync( QStringList() );
    } else {
        qDebug() << " XX Failed to fetch credentials for ownCloud";
    }

}

bool ownCloudSync::startSync( const QString& path )
{
    _srcPath = path;
    connect( CredentialStore::instance(), SIGNAL(fetchCredentialsFinished(bool)),
             SLOT(slotCredentialsFetched(bool)));

    CredentialStore::instance()->fetchCredentials();
    return true;
}

void ownCloudSync::slotSyncFinished( const SyncResult& result )
{
    qDebug() << " *** ownCloud Sync-Result: " << result.statusString();

    _syncFolder->deleteLater();
}
