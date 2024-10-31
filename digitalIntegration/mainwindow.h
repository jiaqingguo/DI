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
class CCtrlNetwork;

struct st_account_data;
//class fingerDlg;

class EmbeddedWidget : public QWidget {
    Q_OBJECT

public:
	EmbeddedWidget(HWND hwnd, QWidget* parent = nullptr) ;

    // 调整嵌入窗口的大小为 QWidget 的大小
	void adjustEmbeddedWindowSize();

protected:
    // 重写 resizeEvent，以防 QWidget 的大小改变时需要重新调整外部窗口的大小
	void resizeEvent(QResizeEvent* event) override;

private:
    HWND m_hwnd;                   // 外部窗口句柄
    QWidget *m_windowContainer;     // 用于封装原生窗口的 QWidget
};

//class CWidget : public QWidget
//{
//	Q_OBJECT
//public:
//	CWidget(HWND hwnd, QWidget* parent = nullptr);
//protected:
//	void mousePressEvent(QMouseEvent* event) override;
//private:
//	HWND m_hwnd;                   // 外部窗口句柄
//	QWidget* m_windowContainer;     // 用于封装原生窗口的 QWidget
//};
/*!
* \class	QssAutoLoader
* \brief	修改qss文件时 使程序立刻生效显示.
* \author	Jiaqg
* \date		2021/1/21
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
	void initUdp();
	void udpStartExeThread(const QString strData,const QString strIp,const int port);
	void showRegisterDialog();
	void setUserNameText(const QString& userName);
	
	void showGif();
	void closeGif();

	bool showLoginDialog();

	void initAccount();
	QString  getAccaunt(const QString& strIP,const QString strSoft);
	void     addAccaunt(const int &module, const int& index);
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

	void slot_tabModule1closeTab(int index);
	void slot_tabModule2closeTab(int index);
	void slot_tabModule3closeTab(int index);
	void slot_tabModule4closeTab(int index);

	void slot_one_load_tools(int moduleNum,const QString &toolsName);//一键加载的槽函数
private:
	void updateModuleToolIcon(int module);
	void startUdpRdp(const QString ip);
	void startLongDistanceSoftware(const QString tabName ,const std::string strIp, const std::string strAccaunt, const std::string pwd, const  std::string path,QTabWidget* tabWidget=nullptr);
	
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
	InformationConfihurationDialog* m_inforConfihurationDialog = nullptr;

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
	CCtrlNetwork* m_udp;
	//fingerDlg *m_fingerDlg = nullptr;
 //  <ip,<软件 ，用户名int
	//QMap<QString, QMap<QString, int>> m_mapAccaunt;
//	<ip, < 软件 ，用户名>
	QMap<QString, QMap<QString, QVector<QString>>> m_mapAccauntData;
	QVector<QString> m_vecAccount; //user 1 2 3或4 5 6
	  // <module   <tabIndex,userName>
	QMap<int , QMap<int , st_account_data>> m_usedAccaunt;

};

extern MainWindow* g_pMainWindow;
#endif // MAINWINDOW_H
