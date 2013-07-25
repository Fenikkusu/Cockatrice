#include <QSettings>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include "dlg_connect.h"
#include "settingscache.h"
#include "serverlist.h"
#include "serverlistitem.h"
#include <QDebug>

DlgConnect::DlgConnect(QWidget *parent)
	: QDialog(parent)
{
	QSettings settings;
	settings.beginGroup("server");

	hostLabel = new QLabel(tr("&Host:"));
	hostEdit = new QLineEdit(settings.value("hostname", "cockatrice.woogerworks.com").toString());
	hostLabel->setBuddy(hostEdit);

	portLabel = new QLabel(tr("&Port:"));
	portEdit = new QLineEdit(settings.value("port", "4747").toString());
	portLabel->setBuddy(portEdit);

	playernameLabel = new QLabel(tr("Player &name:"));
	playernameEdit = new QLineEdit(settings.value("playername", "Player").toString());
	playernameLabel->setBuddy(playernameEdit);

	passwordLabel = new QLabel(tr("P&assword:"));
	passwordEdit = new QLineEdit(settings.value("password").toString());
	passwordLabel->setBuddy(passwordEdit);
	passwordEdit->setEchoMode(QLineEdit::Password);
	
	savePasswordCheckBox = new QCheckBox(tr("&Save password"));
	savePasswordCheckBox->setChecked(settings.value("save_password", 1).toInt());

    QLabel *lblServer = new QLabel(tr("Server"));
    this->_loadServers();

	QGridLayout *grid = new QGridLayout;
    grid->addWidget(lblServer, 0, 0);
    grid->addWidget(cboServerSelect, 0, 1);
    grid->addWidget(hostLabel, 1, 0);
    grid->addWidget(hostEdit, 1, 1);
    grid->addWidget(portLabel, 2, 0);
    grid->addWidget(portEdit, 2, 1);
    grid->addWidget(playernameLabel, 3, 0);
    grid->addWidget(playernameEdit, 3, 1);
    grid->addWidget(passwordLabel, 4, 0);
    grid->addWidget(passwordEdit, 4, 1);
    grid->addWidget(savePasswordCheckBox, 5, 0, 1, 2);
	
	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(actOk()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	     
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(grid);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);

	setWindowTitle(tr("Connect to server"));
	setFixedHeight(sizeHint().height());
	setMinimumWidth(300);
}

void DlgConnect::actOk()
{
	QSettings settings;
	settings.beginGroup("server");
	settings.setValue("hostname", hostEdit->text());
	settings.setValue("port", portEdit->text());
	settings.setValue("playername", playernameEdit->text());
	settings.setValue("password", savePasswordCheckBox->isChecked() ? passwordEdit->text() : QString());
	settings.setValue("save_password", savePasswordCheckBox->isChecked() ? 1 : 0);
	settings.endGroup();

	accept();
}

void DlgConnect::_loadServers() {
    _lstServers = new ServerList();

    cboServerSelect = new QComboBox();
    connect(cboServerSelect, SIGNAL(currentIndexChanged(QString)), this, SLOT(onServerSelectChange(QString)));

    cboServerSelect->addItem("");
    foreach(ServerListItem* objServer, _lstServers->getServers()) {
        cboServerSelect->addItem(objServer->getName());
    }
}

void DlgConnect::onServerSelectChange(const QString &strText) {
    if (strText == "" || !this->_lstServers->hasServer(strText)) {
        return;
    }

    ServerListItem* objItem = this->_lstServers->getServer(strText);
    qDebug() << objItem->getHost();
    hostEdit->setText(objItem->getHost());
    portEdit->setText(QString::number(objItem->getPort()));
    playernameEdit->setText(objItem->getUser());
    passwordEdit->setText(objItem->getUser());
}
