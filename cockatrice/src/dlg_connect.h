#ifndef DLG_CONNECT_H
#define DLG_CONNECT_H

#include <QDialog>
#include <QLineEdit>

class QLabel;
class QPushButton;
class QCheckBox;
class QComboBox;
class QXmlStreamReader;
class ServerListItem;
class ServerList;

class DlgConnect : public QDialog {
	Q_OBJECT
public:
	DlgConnect(QWidget *parent = 0);
	QString getHost() const { return hostEdit->text(); }
	int getPort() const { return portEdit->text().toInt(); }
	QString getPlayerName() const { return playernameEdit->text(); }
	QString getPassword() const { return passwordEdit->text(); }
private slots:
	void actOk();
    void onServerSelectChange(const QString &strText);
private:
	QLabel *hostLabel, *portLabel, *playernameLabel, *passwordLabel;
	QLineEdit *hostEdit, *portEdit, *playernameEdit, *passwordEdit;
	QCheckBox *savePasswordCheckBox;
    QComboBox *cboServerSelect;
    ServerList *_lstServers;
    void _loadServers();
};

#endif
