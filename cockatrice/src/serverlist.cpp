#include "serverlist.h"
#include "settingscache.h"
#include "serverlistitem.h"
/*#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>*/
#include <QtXml/QXmlStreamReader>
#include <QHash>
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QStringList>

ServerList::ServerList(const QString &strServerList) : QObject(), _strPath(strServerList) {
    if (this->_strPath == "") {
        this->_strPath = settingsCache->getServerListPath();
    }
/*
    QString strSchema(this->_strPath);
    strSchema.replace(".xml", ".xsd");

    QXmlSchema objSchema;
    objSchema.load(QUrl(strSchema));
    if (!objSchema.isValid()) {
        qDebug() << "Server List Schema Invalid: " << strSchema;
        return;
    }

    QXmlSchemaValidator objValidator(objSchema);
    if (!objValidator.validate(QUrl(this->_strPath))) {
        qDebug() << "Server List Does Not Validate Against Schema";
        return;
    }
*/
    qDebug() << "ServerList Path: " << this->_strPath;

    QFile hndFile(this->_strPath);
    hndFile.open(QIODevice::ReadOnly);
    if (!hndFile.isOpen()) {
        qDebug() << "Server List File Not Opened: " << this->_strPath;
        return;
    }

    QXmlStreamReader objDoc(&hndFile);
    while(!objDoc.atEnd()) {
        objDoc.readNext();
        if (objDoc.name() == "server") {
            this->_parseServer(objDoc);
        }
    }
}

void ServerList::_parseServer(QXmlStreamReader &objDoc) {
    QString strName, strHost, strUser, strPass;
    int intPort;
    QStringList lstNames;
    lstNames << "name" << "host" << "user" << "pass" << "port";

    while(!objDoc.atEnd()) {
        if (objDoc.readNext() == QXmlStreamReader::EndElement) {
            break;
        }

        strUser = "";
        strPass = "";
        intPort = 0;

        switch(lstNames.indexOf(objDoc.name().toString())) {
            case 0: //"name":
                strName = objDoc.readElementText();
                break;
            case 1: //"host":
                strHost = objDoc.readElementText();
                break;
            case 2: //"user":
                strUser = objDoc.readElementText();
                break;
            case 3: //"pass":
                strPass = objDoc.readElementText();
                break;
            case 4: //"port":
                intPort = objDoc.readElementText().toInt();
                break;
            default:
                qDebug() << "ServerList::_parseServer::" << objDoc.name() << " Not Found";
        }
    }

    this->_lstServers.insert(strName, new ServerListItem(strName, strHost, intPort, strUser, strPass));
}

bool ServerList::hasServer(QString strName) {
    return this->_lstServers.contains(strName);
}

ServerListItem* ServerList::getServer(QString strName) {
    if (!this->hasServer(strName)) {
        return NULL;
    }

    return this->_lstServers.value(strName);
}

QHash<QString, ServerListItem*> ServerList::getServers() { return this->_lstServers; }
