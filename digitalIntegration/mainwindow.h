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
* \brief	修改qss文件时 使程序立刻生效显示.
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
	* \brief	加载qss文件.
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
	* \brief	动态监视，文件修改立刻生效.
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

	// 更新模块工具图标;
	void slot_updateModuleToolIcon(int module);

	void slot_downlaodFinsh();
private:
	void updateModuleToolIcon(int module);
private:
    Ui::MainWindow *ui;

    QJsonObject _jsonData;
    QWebEngineView* _view;

	// 自动监控qss文件类
	QssAutoLoader* m_pQssAutoLoader;
    LoginDialog* m_LoginDialog = nullptr;   // 登录界面;

	RegisterDialog* m_RegisterDialog = nullptr; // 注册界面;

	ResourceManageDialog* m_ResourceManageDialog = nullptr; // 资源管理界面;

	InformationConfihurationDialog* m_InforConfihurationDialog = nullptr;// 信息配置界面;

	DataManageDialog* m_DataManageDialog = nullptr; // 数据管理界面;

	FilemangageDialog* m_FilemangageDialog = nullptr; // 文件管理界面;

	ApprovalProgressDialog* m_ApprovalProgressDialog = nullptr; // 审批进度页面;


//	AddToolDialog* m_AddToolDialog = nullptr; // 增加工具标签界面;

	OneClickSaveDialog* m_OneClickSaveDialog = nullptr;// 一键保存界面;
	OneClickLoadDialog* m_OneClickLoadDialog = nullptr; // 一键加载界面;

	QWindow* windowQQ = nullptr;
	QWidget * widgetQQ = nullptr;
	WId winIdQQ;

	GifDialog* m_GifDialog = nullptr;

	bool bUserIp = true;

	//指纹
	fingerDlg *m_fingerDlg = nullptr;

public slots:
	void slot_login_succ();



};

extern MainWindow* g_pMainWindow;
#endif // MAINWINDOW_H
