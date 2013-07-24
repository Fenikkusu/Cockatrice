#ifndef SERVERLIST_H
#define SERVERLIST_H

#include <QHash>

class ServerListItem;
class QString;
class QXmlStreamReader;

class ServerList : public QObject {
    Q_OBJECT
    public:
        ServerList(const QString &strServerList = "");
        QHash<QString, ServerListItem*> getServers();
    protected:
        void _parseServer(QXmlStreamReader &objDoc);
        QHash<QString, ServerListItem*> _lstServers;
        QString _strPath;
};

#endif // SERVERLIST_H
