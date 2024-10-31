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

    // ����Ƕ�봰�ڵĴ�СΪ QWidget �Ĵ�С
	void adjustEmbeddedWindowSize();

protected:
    // ��д resizeEvent���Է� QWidget �Ĵ�С�ı�ʱ��Ҫ���µ����ⲿ���ڵĴ�С
	void resizeEvent(QResizeEvent* event) override;

private:
    HWND m_hwnd;                   // �ⲿ���ھ��
    QWidget *m_windowContainer;     // ���ڷ�װԭ�����ڵ� QWidget
};

//class CWidget : public QWidget
//{
//	Q_OBJECT
//public:
//	CWidget(HWND hwnd, QWidget* parent = nullptr);
//protected:
//	void mousePressEvent(QMouseEvent* event) override;
//private:
//	HWND m_hwnd;                   // �ⲿ���ھ��
//	QWidget* m_windowContainer;     // ���ڷ�װԭ�����ڵ� QWidget
//};
/*!
* \class	QssAutoLoader
* \brief	�޸�qss�ļ�ʱ ʹ����������Ч��ʾ.
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

	// ����ģ�鹤��ͼ��;
	void slot_updateModuleToolIcon(int module);

	void slot_downlaodFinsh();

	void slot_tabModule1closeTab(int index);
	void slot_tabModule2closeTab(int index);
	void slot_tabModule3closeTab(int index);
	void slot_tabModule4closeTab(int index);

	void slot_one_load_tools(int moduleNum,const QString &toolsName);//һ�����صĲۺ���
private:
	void updateModuleToolIcon(int module);
	void startUdpRdp(const QString ip);
	void startLongDistanceSoftware(const QString tabName ,const std::string strIp, const std::string strAccaunt, const std::string pwd, const  std::string path,QTabWidget* tabWidget=nullptr);
	
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
	InformationConfihurationDialog* m_inforConfihurationDialog = nullptr;

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
	CCtrlNetwork* m_udp;
	//fingerDlg *m_fingerDlg = nullptr;
 //  <ip,<��� ���û���int
	//QMap<QString, QMap<QString, int>> m_mapAccaunt;
//	<ip, < ��� ���û���>
	QMap<QString, QMap<QString, QVector<QString>>> m_mapAccauntData;
	QVector<QString> m_vecAccount; //user 1 2 3��4 5 6
	  // <module   <tabIndex,userName>
	QMap<int , QMap<int , st_account_data>> m_usedAccaunt;

};

extern MainWindow* g_pMainWindow;
#endif // MAINWINDOW_H
