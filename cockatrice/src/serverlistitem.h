#ifndef SERVERLISTITEM_H
#define SERVERLISTITEM_H

#include <QString>
#include <QObject>

class ServerListItem;

class ServerListItem : QObject {
    Q_OBJECT
    public:
        ServerListItem(const QString &strName, const QString &strHost, const int &intPort, const QString &strUser, const QString &strPass);
        QString getName() const;
        QString getHost() const;
        int getPort() const;
        QString getUser() const;
        QString getPass() const;
    protected:
        QString _strName, _strHost, _strUser, _strPass;
        int _intPort;
};

#endif // SERVERLISTITEM_H
