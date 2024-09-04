#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qjsonobject.h>
#include <QFile>
#include <QFileSystemWatcher>
#include <QApplication>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class QWebEngineView;
class LoginDialog;
class RegisterDialog;
class ResourceManageDialog;
class InformationConfihurationDialog;
class ApprovalProgressDialog;
class DataManageDialog;
class AddToolDialog;
class OneClickSaveDialog;
class OneClickLoadDialog;
class FilemangageDialog;
class GifDialog;

class fingerDlg;

/*!
* \class	QssAutoLoader
* \brief	�޸�qss�ļ�ʱ ʹ����������Ч��ʾ.
* \author	Jiaqg
* \date	2021/1/21
*/

class QssAutoLoader : public QObject
{
	Q_OBJECT
public:
	QssAutoLoader()
	{
		connect(&m_fileWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(slot_autoLoad(const QString&)));
	}

	/*!
	* \fn	void QssAutoLoader::setAutoloadQss(const QString &strQssPath)
	* \brief	����qss�ļ�.
	* \author	Jiaqg
	* \date	2021/1/21
	* \param	strQssPath	Full pathname of the qss file.
	*/

	void setAutoloadQss(const QString& strQssPath)
	{
		m_fileWatcher.addPath(strQssPath);
		slot_autoLoad(strQssPath);
	}

protected slots:

	/*!
	* \fn	void QssAutoLoader::slot_autoLoad(const QString &strQssPath)
	* \brief	��̬���ӣ��ļ��޸�������Ч.
	* \author	Jiaqg
	* \date	2021/1/21
	* \param	strQssPath	Full pathname of the qss file.
	*/

	void slot_autoLoad(const QString& strQssPath)
	{
		//QFile* qssFile = new QFile(strQssPath);
		QScopedPointer<QFile> qssFile(new QFile(strQssPath));
		if (!qssFile->open(QFile::ReadOnly))
		{
			QString  str = qssFile->errorString();
			return;
		}

		qApp->setStyleSheet(qssFile->readAll());

		qssFile->close();
	}

private:
	QFileSystemWatcher m_fileWatcher;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void initInitface();
	void showRegisterDialog();
	void setUserNameText(const QString& userName);
	
	void showGif();
	void closeGif();
private slots:
	void slot_btnResourceManageClicked();
	void slot_btnInformationConfihurationClicked();
	void slot_btnDataManageClicked(); 
	void slot_btnApprovalProgressClicked();

	void slot_btnAddToolTab();

	void slot_btnOneClickLoad();

	void slot_btnOneClickSave();

	// ����ģ�鹤��ͼ��;
	void slot_updateModuleToolIcon(int module);

	void slot_downlaodFinsh();
private:
	void updateModuleToolIcon(int module);
private:
    Ui::MainWindow *ui;

    QJsonObject _jsonData;
    QWebEngineView* _view;

	// �Զ����qss�ļ���
	QssAutoLoader* m_pQssAutoLoader;
    LoginDialog* m_LoginDialog = nullptr;   // ��¼����;

	RegisterDialog* m_RegisterDialog = nullptr; // ע�����;

	ResourceManageDialog* m_ResourceManageDialog = nullptr; // ��Դ�������;

	InformationConfihurationDialog* m_InforConfihurationDialog = nullptr;// ��Ϣ���ý���;

	DataManageDialog* m_DataManageDialog = nullptr; // ���ݹ������;

	FilemangageDialog* m_FilemangageDialog = nullptr; // �ļ��������;

	ApprovalProgressDialog* m_ApprovalProgressDialog = nullptr; // ��������ҳ��;


//	AddToolDialog* m_AddToolDialog = nullptr; // ���ӹ��߱�ǩ����;

	OneClickSaveDialog* m_OneClickSaveDialog = nullptr;// һ���������;
	OneClickLoadDialog* m_OneClickLoadDialog = nullptr; // һ�����ؽ���;

	QWindow* windowQQ = nullptr;
	QWidget * widgetQQ = nullptr;
	WId winIdQQ;

	GifDialog* m_GifDialog = nullptr;

	bool bUserIp = true;

	//ָ��
	fingerDlg *m_fingerDlg = nullptr;

public slots:
	void slot_login_succ();



};

extern MainWindow* g_pMainWindow;
#endif // MAINWINDOW_H
