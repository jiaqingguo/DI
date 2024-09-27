#pragma comment  (lib, "User32.lib")
#include "fingerDlg.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globel.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "ResourceManageDialog.h"
#include "InformationConfihurationDialog.h"
#include "DataManageDialog.h"
#include "FilemangageDialog.h"
#include "ApprovalProgressDialog.h"
#include "AddToolDialog.h"
#include "OneClickSaveDialog.h"
#include "OneClickLoadDialog.h"
#include "databaseDI.h"
#include "CustomButton.h"
#include "common.h"
#include "GifDialog.h"

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include <QProcess>
#include "windows.h"


std::vector<HWND> windowHandles; // �洢���ھ��������

// ö�ٴ��ڵĻص�����
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);

    // ��鴰���Ƿ�ɼ�����Ŀ����� ID ƥ��
    if (IsWindowVisible(hwnd) && processId == static_cast<DWORD>(lParam)) {
        windowHandles.push_back(hwnd);
    }
    return TRUE; // ����ö��
}

// ��ȡ���ڱ���
std::wstring GetWindowTitle(HWND hwnd) {
    const int length = GetWindowTextLength(hwnd);
    std::wstring title(length, L'\0'); // �����㹻��С���ַ���
    GetWindowText(hwnd, &title[0], length + 1); // ��ȡ���ڱ���
    return title;
}
// ����һ���ӿ��࣬���ڴ������ݸ�HTML
//class EChartsBridge : public QObject {
//    Q_OBJECT
//public:
//    explicit EChartsBridge(QObject* parent = nullptr) : QObject(parent) {}
//
//signals:
//    void sendData(const QString& data);
//
//public slots:
//    void receiveMessage(const QString& message) {
//        qDebug() << "Received message from JavaScript:" << message;
//    }
//};

MainWindow* g_pMainWindow = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pMainWindow = this;

    setWindowTitle(GBK_STRING("��������Ӳ��һ�廯ƽ̨"));
    setWindowIcon(QIcon(":/image/tubiao.png"));
    QString command = "cmdkey /add:192.168.1.247 /user:Administrator /pass:Ate123";

    // ���� QProcess ����
    QProcess process;

    // ���� cmd ���̲�ִ������
    process.start("cmd.exe", QStringList() << "/C" << command);

    // �ȴ�����ִ�����
    if (process.waitForFinished())
    {
        // ��ȡ������������ڵ��Ի�鿴�����
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        // ��ӡ���������̨
        qDebug() << "Output:" << output;
        qDebug() << "Error:" << error;
    }
    else
    {
        qDebug() << "Process failed to start or execute.";
    }
    // qss�ļ������
    m_pQssAutoLoader = new QssAutoLoader;
    QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
    strQssPath.replace("/", "\\\\");
    m_pQssAutoLoader->setAutoloadQss(strQssPath);

	initInitface();

    QString target = "\\\\192.168.0.250\\"; // ʵ��·��
    QString username = "share"; // ʵ���û���
    QString password = "Share123"; // ʵ������

    common::addNetworkCredential(target, username, password);

   
}


MainWindow::~MainWindow()
{
    int loginStatus = 0;
    int userId = m_LoginDialog->GetUserID();
    db::databaseDI::Instance().update_user_LoginStatus(userId, loginStatus);

    /*if (!db::databaseDI::Instance().updata_ipusername(m_LoginDialog->GetUser().toStdString()))
        return;*/

    if (!db::databaseDI::Instance().update_ip_all_status())
        return;

    if (m_LoginDialog != nullptr)
        delete m_LoginDialog;
    if (m_RegisterDialog != nullptr)
        delete m_RegisterDialog;
    
    if (m_ResourceManageDialog != nullptr)
        delete m_ResourceManageDialog;
    if (m_DataManageDialog != nullptr)
        delete m_DataManageDialog;
    if (m_InforConfihurationDialog != nullptr)
        delete m_InforConfihurationDialog;
    if (m_ApprovalProgressDialog != nullptr)
        delete m_ApprovalProgressDialog; 
    if (m_FilemangageDialog != nullptr)
        delete m_FilemangageDialog;
    delete ui;
}

void MainWindow::initInitface()
{
	this->m_fingerDlg = new fingerDlg();
	this->m_fingerDlg->finger_init();
	connect(this->m_fingerDlg, &fingerDlg::login_succ, this, &MainWindow::slot_login_succ);


    m_LoginDialog = new LoginDialog(this);
  
    m_GifDialog = new GifDialog;
    
    m_RegisterDialog = new RegisterDialog(this);

    m_ResourceManageDialog = new ResourceManageDialog(this);

    m_InforConfihurationDialog = new InformationConfihurationDialog(this);
    connect(m_InforConfihurationDialog, &InformationConfihurationDialog::signal_updateToolIcon, this, &MainWindow::slot_updateModuleToolIcon);

    m_DataManageDialog = new DataManageDialog(this);

    m_FilemangageDialog = new FilemangageDialog(this);
  
    m_ApprovalProgressDialog = new ApprovalProgressDialog(this);

    m_OneClickLoadDialog = new OneClickLoadDialog(this);

    m_OneClickSaveDialog = new OneClickSaveDialog(this);

    ui->btnFunction->setCheckable(true);
    ui->btnModule1->setCheckable(true);
    ui->btnModule2->setCheckable(true);
    ui->btnModule3->setCheckable(true);
    ui->btnModule4->setCheckable(true);

    ui->btnFunction->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->btnFunction, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(0);
        });
    connect(ui->btnModule1, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
		updateModuleToolIcon(1);
        });
    connect(ui->btnModule2, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
		updateModuleToolIcon(2);
        });
    connect(ui->btnModule3, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
		updateModuleToolIcon(3);
        });
    connect(ui->btnModule4, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(4);
		updateModuleToolIcon(4);
        });

    ui->btnResourceManage->setCheckable(true);
    ui->btnInformationConfihuration->setCheckable(true);
    ui->btnDataManage->setCheckable(true);
    ui->btnApprovalProgress->setCheckable(true);
    connect(ui->btnResourceManage, &QPushButton::clicked, this, &MainWindow::slot_btnResourceManageClicked);
    connect(ui->btnInformationConfihuration, &QPushButton::clicked, this, &MainWindow::slot_btnInformationConfihurationClicked);
    connect(ui->btnDataManage, &QPushButton::clicked, this, &MainWindow::slot_btnDataManageClicked);
    connect(ui->btnApprovalProgress, &QPushButton::clicked, this, &MainWindow::slot_btnApprovalProgressClicked);

    // ��ʼ��ģ��1-4����;
    ui->tabWidgetModulel1->removeTab(1);
    ui->tabWidgetModulel2->removeTab(1);
    ui->tabWidgetModulel3->removeTab(1);
    ui->tabWidgetModulel4->removeTab(1);
    ui->btnAddTab1->setProperty("module", 1);
    ui->btnAddTab2->setProperty("module", 2);
    ui->btnAddTab3->setProperty("module", 3);
    ui->btnAddTab4->setProperty("module", 4);
    connect(ui->btnAddTab1, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab2, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab3, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);
    connect(ui->btnAddTab4, &QPushButton::clicked, this, &MainWindow::slot_btnAddToolTab);

    ui->btnM1Load->setCheckable(true);
    ui->btnM2Load->setCheckable(true);
    ui->btnM3Load->setCheckable(true);
    ui->btnM4Load->setCheckable(true);
    ui->btnM1Load->setProperty("module", 1);
    ui->btnM2Load->setProperty("module", 2);
    ui->btnM3Load->setProperty("module", 3);
    ui->btnM4Load->setProperty("module", 4);
    ui->btnM1Save->setCheckable(true);
    ui->btnM2Save->setCheckable(true);
    ui->btnM3Save->setCheckable(true);
    ui->btnM4Save->setCheckable(true);
    ui->btnM1Save->setProperty("module", 1);
    ui->btnM2Save->setProperty("module", 2);
    ui->btnM3Save->setProperty("module", 3);
    ui->btnM4Save->setProperty("module", 4);
    connect(ui->btnM1Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM2Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM3Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM4Load, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickLoad);
    connect(ui->btnM1Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM2Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM3Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    connect(ui->btnM4Save, &QPushButton::clicked, this, &MainWindow::slot_btnOneClickSave);
    

    /*updateModuleToolIcon(1);
    updateModuleToolIcon(2);
    updateModuleToolIcon(3);
    updateModuleToolIcon(4);
*/
    //if (m_LoginDialog->exec() == QDialog::Accepted)
    //{
    //    ui->labelUserName->setText(m_LoginDialog->GetUser());
    //    if (m_LoginDialog->GetPop())
    //    {
    //        ui->btnApprovalProgress->hide();
    //    }
    //    this->showMaximized();
    //    m_FilemangageDialog->initTableViewDownload();
    //}
    //else
    //{
    //    this->close();
    //    //exit(1);
    //}

   
}

void MainWindow::showRegisterDialog()
{
    m_RegisterDialog->exec();
}
void MainWindow::setUserNameText(const QString& userName)
{
    ui->labelUserName->setText(userName);
}
void MainWindow::showGif()
{
   // m_FilemangageDialog->hide();
    m_GifDialog->show();
    //m_GifDialog->update();
}
void MainWindow::closeGif()
{
    m_GifDialog->close();
   // m_FilemangageDialog->exec();
}
bool MainWindow::showLoginDialog()
{
    if (m_LoginDialog->exec() == QDialog::Accepted)
    {
        ui->labelUserName->setText(m_LoginDialog->GetUser());
        if (m_LoginDialog->GetPop())
        {
            ui->btnApprovalProgress->hide();
        }
        this->showMaximized();
        m_FilemangageDialog->initTableViewDownload();
        connect(m_OneClickSaveDialog, &OneClickSaveDialog::signals_zipMultPath, m_FilemangageDialog, &FilemangageDialog::slot_compressMultPath);
        return true;
    }
    else
    {
        this->close();
        return false;
    }
    return false;
}

void MainWindow::slot_btnResourceManageClicked()
{
    m_ResourceManageDialog->startWebFlushTimer();
    m_ResourceManageDialog->exec();
    m_ResourceManageDialog->stopWebFlushTimer();
    ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
	m_InforConfihurationDialog->initFaceData();
    m_InforConfihurationDialog->exec();
    ui->btnInformationConfihuration->setChecked(false);
}

void MainWindow::slot_btnDataManageClicked()
{
    //m_DataManageDialog->exec();
    m_FilemangageDialog->exec();
    ui->btnDataManage->setChecked(false);
}

void MainWindow::slot_btnApprovalProgressClicked()
{
    m_ApprovalProgressDialog->init();
    m_ApprovalProgressDialog->exec();
    ui->btnApprovalProgress->setChecked(false);
}

void MainWindow::slot_btnAddToolTab()
{
    QPushButton* pButton = (QPushButton*)sender();
    int moduleNumber= pButton->property("module").toInt();

    
    AddToolDialog addToooDialog(moduleNumber);
    if (addToooDialog.exec() == QDialog::Accepted)
    {
        QString toolName;
        QString tabName;
        int mode = -1;
        int displayMode = 0;
        addToooDialog.getToolData(tabName,toolName, mode, displayMode);
        QWidget* pWidget = new QWidget;

        if (0)
        {

       
        if (moduleNumber == 1)
        { 
            QString exeDir = QCoreApplication::applicationDirPath();
			qDebug() << exeDir;
            QString strDspPath = exeDir + "\\dsp\\"+QString::number(common::iLoginNum)+ "\\"+toolName+".bsp";


            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                    ui->tabWidgetModulel1->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
            }
            else
            {
                QWidget* pWidget = new QWidget;
                pWidget->setWindowTitle(tabName);
                ui->tabWidgetModulel1->addTab(pWidget, tabName);
            }
           
        }
        else if (moduleNumber == 2)
        {


            //TCHAR userName[] = TEXT("Administrator");
            //TCHAR password[] = TEXT("Ate123");
            //TCHAR localDrive[] = TEXT("Y");  //����������ӳ��
            //TCHAR remotePath[] = TEXT("\\192.168.1.247");  // ������Դ��·��

            //std::wstring target = L"\\\\192.168.1.247"; // Զ��Ŀ¼·��
            //std::wstring username = L"Administrator"; // �û���
            //std::wstring password = L"Ate123"; // ����

            
           // TCHAR userName[] = TEXT("share");
           // TCHAR password[] = TEXT("Share123");
           // TCHAR localDrive[] = TEXT("Y");  //����������ӳ��
           // TCHAR remotePath[] = TEXT("\\\\192.168.1.253\\share");  // ������Դ��·��

           //common::InitResource(userName, password, localDrive, remotePath);

            // C:\Windows\System32\drivers\etc\hosts
            // ����Ҫִ�е�����
            QString command = "cmdkey /add:192.168.1.247 /user:Administrator /pass:Ate123";

            // ���� QProcess ����
            QProcess process;

            // ���� cmd ���̲�ִ������
            process.start("cmd.exe", QStringList() << "/C" << command);

            // �ȴ�����ִ�����
            if (process.waitForFinished())
            {
                // ��ȡ������������ڵ��Ի�鿴�����
                QString output = process.readAllStandardOutput();
                QString error = process.readAllStandardError();

                // ��ӡ���������̨
                qDebug() << "Output:" << output;
                qDebug() << "Error:" << error;
            }
            else
            {
                qDebug() << "Process failed to start or execute.";
            }

            QString str = "D:\\Visual Studio 2017.rdp";
            // ����bsp 
            common::startDspExe(str);
            //QProcess *process = new QProcess;
            //// �����ⲿ����
            //QString program = "D:\\tools\\EVCapture\\EVCapture.exe"; // �滻Ϊ�����ⲿ����·��
           

            //std::wstring wStr = program.toStdWString();

            //// ��std::wstring��ȡLPCWSTR
            //LPCWSTR lpwstr = wStr.c_str();
            // // ��������
            //STARTUPINFO si = { sizeof(si) };
            //PROCESS_INFORMATION pi;

            //if (CreateProcess(wStr.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            //    std::cout << "Process started!" << std::endl;

            //    // �ȴ�һ��ʱ�䣬�ô��ڴ���
            //    Sleep(1000); // �����������������Ҫ����

            //    // ��ȡ���ھ��
            //   // HWND hwnd = common::FindWindowByProcessId(pi.dwProcessId);
            //    auto hwndvec =common::getWindowHandlesByProcessId(pi.dwProcessId);
            //  /*  if (hwnd) {
            //        std::cout << "Window handle: " << hwnd << std::endl;
            //    }
            //    else {
            //        std::cout << "No top-level window found for the process." << std::endl;
            //    }*/

            //    // �رս��̾��
            //    CloseHandle(pi.hProcess);
            //    CloseHandle(pi.hThread);
            //}
            //else {
            //    std::cout << "Failed to start process. Error: " << GetLastError() << std::endl;
            //}

           // WId winId2 = (WId)hnnVec[0];
            // ��ȡ���ڱ���
          //  QString windowTitle = common::GetWindowTitle(processId);
     
        //    qDebug() << "External program window title:" << windowTitle;
       //   WId winId = (WId)FindWindow(NULL, L"EV¼��"); Visual Studio 2017
              WId winId = (WId)FindWindow(NULL, L"Microsoft Visual Studio");
          // WId winId = (WId)FindWindow(NULL, L"QQ"); 
             //  WId winId = (WId)FindWindow(NULL, L"Microsoft Visual Studio"); 
           // ��ȡ���ھ��
           //auto WNID = common::FindMainWindow(processID);

           //winId = (WId)WNID;
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                  
                    ui->tabWidgetModulel2->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
               
            }
        }
        else if (moduleNumber == 3)
        {
             HANDLE hProcess;
             if (1)// ���Դ���
             {
                 //DWORD bufferSize = MAX_PATH;
                 //wchar_t currentDirectory[MAX_PATH];

                 //// ��ȡ��ǰ����Ŀ¼
                 //if (GetCurrentDirectoryW(bufferSize, currentDirectory)) {
                 //    std::wcout << L"Current Directory: " << currentDirectory << std::endl;

                 //    // Ӧ�ó���·��
                 //    LPCWSTR applicationPath = L"D:\\tools\\EVCapture\\EVCapture.exe"; // ȷ��·����ʽ��ȷ

                 //    // ����������Ϣ
                 //    SHELLEXECUTEINFOW sei = { 0 }; // ʹ�ÿ��ַ��汾
                 //    sei.cbSize = sizeof(SHELLEXECUTEINFO);
                 //    sei.fMask = SEE_MASK_NOCLOSEPROCESS; // �� ShellExecuteEx ���ؽ��̾��
                 //    sei.hwnd = NULL;
                 //    sei.lpVerb = NULL;
                 //    sei.lpFile = applicationPath;
                 //    sei.lpParameters = NULL;
                 //    sei.lpDirectory = currentDirectory;
                 //    sei.nShow = SW_SHOW;

                 //    // ���� ShellExecuteEx ����Ӧ�ó���
                 //    if (ShellExecuteExW(&sei)) 
                 //    { // ʹ�ÿ��ַ��汾
                 //        std::wcout << L"Application opened successfully." << std::endl;

                 //        // ��ȡ���̾��
                 //         hProcess = sei.hProcess;
                 //       // std::wcout << L"Process handle: " << hProcess << std::endl;

                 //        // �ȴ����̽���
                 //        //WaitForSingleObject(hProcess, INFINITE); // �ȴ�ֱ�����̽���

                 //        // �رս��̾��
                 //      //  CloseHandle(hProcess);
                 //    }
                 //    else {
                 //        std::wcerr << L"Failed to open application. Error code: " << GetLastError() << std::endl;
                 //    }
                 //}
                 //else {
                 //    std::wcerr << L"Failed to get current directory. Error code: " << GetLastError() << std::endl;
                 //}


                 // ��ǰ����Ŀ¼��Ӧ�ó���·��
                 wchar_t currentDirectory[MAX_PATH];
                 if (GetCurrentDirectoryW(MAX_PATH, currentDirectory)) {
                     std::wcout << L"Current Directory: " << currentDirectory << std::endl;

                     LPCWSTR applicationPath = L"D:\\Visual Studio 2017.rdp"; // ȷ��·����ʽ��ȷ

                     // ����������Ϣ
                     SHELLEXECUTEINFOW sei = { 0 };
                     sei.cbSize = sizeof(SHELLEXECUTEINFOW);
                     sei.fMask = SEE_MASK_NOCLOSEPROCESS; // �� ShellExecuteEx ���ؽ��̾��
                     sei.hwnd = NULL;
                     sei.lpVerb = NULL;
                     sei.lpFile = applicationPath;
                     sei.lpParameters = NULL;
                     sei.lpDirectory = currentDirectory;
                     sei.nShow = SW_SHOW;

                     // ���� ShellExecuteEx ����Ӧ�ó���
                     if (ShellExecuteExW(&sei)) {
                         std::wcout << L"Application opened successfully." << std::endl;

                         // �ȴ�һ��ʱ�䣬ȷ�������Ѵ���
                         std::this_thread::sleep_for(std::chrono::seconds(1));

                         // ö�ٴ��ڣ��������½�����صĴ���
                         EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(sei.hProcess));

                         // ����ҵ��Ĵ��ھ���ͱ���
                         for (HWND hwnd : windowHandles) {
                             std::wstring title = GetWindowTitle(hwnd);
                             std::wcout << L"Found window handle: " << hwnd << L", Title: " << title << std::endl;
                         }

                         // �ȴ����̽���
                         WaitForSingleObject(sei.hProcess, INFINITE);
                         CloseHandle(sei.hProcess);
                     }
                     else {
                         std::wcerr << L"Failed to open application. Error code: " << GetLastError() << std::endl;
                     }
                 }
                 else {
                     std::wcerr << L"Failed to get current directory. Error code: " << GetLastError() << std::endl;
                 }
             }

            WId  winId = 0;
            if (windowHandles.size() > 0)
            {
                winId = (WId)windowHandles[0];
            }

            //WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
           
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                    ui->tabWidgetModulel3->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
             
            }
            
        }
        else if (moduleNumber == 4)
        {
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                widget->setWindowTitle(tabName);
                if (displayMode == 0)
                {
                   
                    ui->tabWidgetModulel4->addTab(widget, tabName);
                }
                else
                {
                    widget->show();
                }
               
            }
        }
         };

        if (moduleNumber == 1)
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/" + toolName + ".rdp";

            // ����bsp 
            common::startDspExe(strDspPath);
           // Ƕ��
        }
        else
        {
            QString exeDir = QCoreApplication::applicationDirPath();
            int i = common::iSoftStartHostNum %3;
            if (common::setHostIps.size() >= i)
            {
                auto it = std::next(common::setHostIps.begin(), i); // �ƶ�����i��Ԫ��
                std::string strValue = *it;


                QString strDspPath = exeDir + "/dsp/" + QString::number(common::iLoginNum) + "/"
                    +QString::fromStdString(strValue) + "/"+toolName + ".rdp";

               
                common::iSoftStartHostNum++;
                // ����bsp 
                common::startDspExe(strDspPath);
                // Ƕ��
            }

        }

    }
    
}

void MainWindow::slot_btnOneClickLoad()
{
	if (!m_OneClickLoadDialog->m_model->rowCount())
	{
		std::list<table_one_load_software> listData;
		if (db::databaseDI::Instance().get_load_software(listData))
		{
			for (auto &stData : listData)
			{
				if (stData.userID == common::iUserID)
				{
					int newRowIndex = m_OneClickLoadDialog->m_model->rowCount(); // ��ȡ��ǰ����
					m_OneClickLoadDialog->m_model->insertRow(newRowIndex); // ��������

					QStandardItem* item = new QStandardItem(QString::number(newRowIndex + 1));
					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 0, item);
					QModelIndex index = m_OneClickLoadDialog->m_model->index(newRowIndex, 0);
					// item->setTextAlignment(Qt::AlignCenter);  // �����ı����ж���
					//m_model->setData(index, stIp.id, Qt::UserRole);  // ����id;

					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 1, new QStandardItem(QString::fromStdString(stData.projectPath)));
					m_OneClickLoadDialog->m_model->setItem(newRowIndex, 2, new QStandardItem(QString::number(stData.module)));
				}
			}
		}
	}
   
    m_OneClickLoadDialog->exec();
    QPushButton* pButton = (QPushButton*)sender();
    int module=pButton->property("module").toInt();
    if (module == 1)
    {
        ui->btnM1Load->setChecked(false);
    }
    else if (module == 2)
    {
        ui->btnM2Load->setChecked(false);
    }
    else if (module == 3)
    {
        ui->btnM3Load->setChecked(false);
    }
    else if (module == 4)
    {
        ui->btnM4Load->setChecked(false);
    }

}

void MainWindow::slot_btnOneClickSave()
{
    m_OneClickSaveDialog->exec();
    QPushButton* pButton = (QPushButton*)sender();
    int module = pButton->property("module").toInt();
    if (module == 1)
    {
        ui->btnM1Save->setChecked(false);
    }
    else if (module == 2)
    {
        ui->btnM2Save->setChecked(false);
    }
    else if (module == 3)
    {
        ui->btnM3Save->setChecked(false);
    }
    else if (module == 4)
    {
        ui->btnM4Save->setChecked(false);
    }
}

void MainWindow::slot_updateModuleToolIcon(int module)
{

    updateModuleToolIcon(module);

}

void MainWindow::slot_downlaodFinsh()
{
    closeGif();
}

void MainWindow::updateModuleToolIcon(int module)
{
 
    QLayout* pLayout = nullptr;
    if (module == 1)
    {
        pLayout = ui->layoutM1ToolIcon;
    }
    else if (module == 2)
    {
        pLayout = ui->layoutM2ToolIcon;
    }
    else if (module == 3)
    {
        pLayout = ui->layoutM3ToolIcon;
    }
    else if (module == 4)
    {
        pLayout = ui->layoutM4ToolIcon;
    }

    common::clearLayout(pLayout);
	std::map<std::string, table_ip> ipMap;
    if (db::databaseDI::Instance().get_ip_data(ipMap, module,common::iLoginNum))
    {
        for (const auto& stTool : ipMap)
        {
			const std::string& software = stTool.first;
			const table_ip& data = stTool.second;
			//if (stTool.username == std::to_string(common::iUserID))
			{
				QToolButton* pBtn = new QToolButton();
				//QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("����"));
				pBtn->setIcon(QIcon(QString::fromStdString(data.icoPath)));
				pBtn->setIconSize(QSize(50, 46));
				pBtn->setText(QString::fromStdString(software));
				pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
				pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
				pBtn->setFocusPolicy(Qt::NoFocus);
				pBtn->setFixedSize(55, 64);
				//   pBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);  // ���ð�ť�Ĵ�С����

				pBtn->setEnabled(true);

				pLayout->addWidget(pBtn);
			}
        }
    }
}

void MainWindow::slot_login_succ()
{
    int loginStatus = 1;
    db::databaseDI::Instance().update_user_LoginStatus(common::iUserID, loginStatus);

	db::databaseDI::Instance().get_user_login_number(common::iLoginNum);
    db::databaseDI::Instance().get_ip_data_by_number(common::setHostIps, common::iLoginNum);

	this->m_LoginDialog->accept();

	if (m_fingerDlg != nullptr)
		delete m_fingerDlg;
}

