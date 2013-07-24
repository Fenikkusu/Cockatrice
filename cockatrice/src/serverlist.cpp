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
    if (_strPath == "") {
        _strPath = settingsCache->getServerListPath();
    }
/*
    QString strSchema(_strPath);
    strSchema.replace(".xml", ".xsd");

    QXmlSchema objSchema;
    objSchema.load(QUrl(strSchema));
    if (!objSchema.isValid()) {
        qDebug() << "Server List Schema Invalid: " << strSchema;
        return;
    }

    QXmlSchemaValidator objValidator(objSchema);
    if (!objValidator.validate(QUrl(_strPath))) {
        qDebug() << "Server List Does Not Validate Against Schema";
        return;
    }
*/
    QFile hndFile(_strPath);
    hndFile.open(QIODevice::ReadOnly);
    if (!hndFile.isOpen()) {
        return;
    }

    QXmlStreamReader objDoc(&hndFile);

    while(!objDoc.atEnd()) {
        if (objDoc.readNext() == QXmlStreamReader::EndElement) {
            break;
        }

        if (objDoc.name() == "server") {
            this->_parseServer(objDoc);
        }
    }
}

void ServerList::_parseServer(QXmlStreamReader &objDoc) {
    QString strName, strHost, strUser, strPass;
    QStringList lstNames;
    lstNames << "name" << "host" << "user" << "pass" << "port";

    int intPort;

    while(!objDoc.atEnd()) {
        if (objDoc.readNext() == QXmlStreamReader::EndElement) {
            break;
        }

        strName = strHost = strUser = strPass = "";
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
        }
    }

    this->_lstServers.insert(strName, new ServerListItem(strName, strHost, intPort, strUser, strPass));

    //return *this;
}

QHash<QString, ServerListItem*> ServerList::getServers() { return this->_lstServers; }
