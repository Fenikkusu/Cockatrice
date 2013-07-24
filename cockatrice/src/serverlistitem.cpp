#include "serverlistitem.h"

ServerListItem::ServerListItem(const QString &strName, const QString &strHost, const int &intPort, const QString &strUser, const QString &strPass) : _strName(strName), _strHost(strHost), _intPort(intPort), _strUser(strUser), _strPass(strPass) {
    //this->_strName = strName;
    //this->_strHost = strHost;
    //this->_intPort = intPort;
    //this->_strUser = strUser;
    //this->_strPass = strPass;
}

QString ServerListItem::getHost() const { return this->_strHost; }
QString ServerListItem::getName() const { return this->_strName; }
int     ServerListItem::getPort() const { return this->_intPort; }
QString ServerListItem::getUser() const { return this->_strUser; }
QString ServerListItem::getPass() const { return this->_strPass; }
