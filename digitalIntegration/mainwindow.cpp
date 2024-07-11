
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globel.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"
#include "ResourceManageDialog.h"
#include "InformationConfihurationDialog.h"
#include "DataManageDialog.h"
#include "ApprovalProgressDialog.h"
#include "AddToolDialog.h"
#include "OneClickSaveDialog.h"
#include "OneClickLoadDialog.h"
#include "databaseDI.h"
#include "CustomButton.h"
#include "common.h"

#include <QtWidgets/QApplication>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <qwidget.h>
#include <QtWebEngineWidgets>
#include "windows.h"

// 定义一个接口类，用于传递数据给HTML
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

    setWindowTitle(GBK_STRING("数字样机硬件一体化平台"));
    setWindowIcon(QIcon(":/image/tubiao.png"));

    // qss文件监控类
    m_pQssAutoLoader = new QssAutoLoader;
    QString strQssPath = QApplication::applicationDirPath() + "/qss/default.qss";
    strQssPath.replace("/", "\\\\");
    m_pQssAutoLoader->setAutoloadQss(strQssPath);
    
    //ui->btnFunction->setStyleSheet(
    //    "QPushButton {color: red; }"
    //    "QPushButton:hover {"
    //    "background-color: #87CEFA; /* 浅蓝色背景 */"
    //    "color: black; /* 悬浮状态下的文字颜色 */"
    //    "}"
    //    "QPushButton:checked {"
    //    "background-color: #17C1FF; /* 红色背景 */"
    //    "color: white; /* 选中状态下的文字颜色 */"
    //    "}"
    //);
    initInitface();

    

    


  //  hide();
   
    //WId winId = (WId)FindWindow(NULL, L"QQ");
    //QWindow* window = QWindow::fromWinId(winId);
    //QWidget* widget = QWidget::createWindowContainer(window);
    //widget->show();

 
 /*   QWebEngineView* view = new QWebEngineView();
    
    auto str = qApp->applicationDirPath() + "/eChartFile.html";
    view->load(qApp->applicationDirPath() + "/eChartFile.html");
    ui->gridLayout->addWidget(view);

    using NameVec = std::vector<std::string>;
    NameVec _names = { "衬衫", "羊毛衫", "雪纺衫", "裤子", "高跟鞋", "袜子" ,"庆国" };

    using ValueVec = std::vector<int>;
    ValueVec __values = { 5, 20, 36, 10, 10, 20 ,100 };

    QJsonArray  _data;
    for (size_t i = 0; i < _names.size(); i++)
    {
        QJsonObject itemData;
        itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
        itemData.insert("itemValue", __values[i]);
        _data.append(itemData);
    }*/
    if (0)
    {
       // _view = new QWebEngineView();
       // QString path = qApp->applicationDirPath() + "/eChartFile.html";
       // _view->load(QUrl(path));
       //ui->gridLayout->addWidget(_view);

       // using NameVec = std::vector<std::string>;
       // NameVec _names = { "衬衫", "羊毛衫", "雪纺衫", "裤子", "高跟鞋", "袜子" ,"庆国" };

       // using ValueVec = std::vector<int>;
       // ValueVec __values = { 5, 20, 36, 10, 10, 20 ,100 };


       // QJsonArray  _data;
       // for (size_t i = 0; i < _names.size(); i++)
       // {
       //     QJsonObject itemData;
       //     itemData.insert("itemName", QString::fromLocal8Bit(_names[i].c_str()));
       //     itemData.insert("itemValue", __values[i]);
       //     _data.append(itemData);
       // }
       // _jsonData.insert("titleName", QString::fromLocal8Bit("测试titleName"));
       // _jsonData.insert("data", _data);
       // // 折线图（line）
       // // 柱状图（Bar）
       // // 饼图（pie）
       // // 散点图（scatter）
       // // 地图（map）
       // // 雷达图（radar） 
       // // 词云图（wordCloud）
       // // 图片地图（imageMap）
       // // 组合图（compose）
       // // 漏斗图（funnel）
       // // 仪表盘（gauge）
       // // 列表图（list）
       // _jsonData.insert("type", "line");

       // //QTimer* _timer = new QTimer;
       // //_timer->setInterval(2000);
       // //QObject::connect(_timer, &QTimer::timeout, [&]() {
       // //    QString optionStr = QJsonDocument(_jsonData).toJson();
       // //    //用到js中init() 函数
       // //    QString js = QString("setData(%1)").arg(optionStr);
       // //    qDebug() << js;
       // //    _view->page()->runJavaScript(js);
       // //    _timer->stop();
       // //   }
       // // );
       // //_timer->start();

       // QObject::connect(_view, &QWebEngineView::loadFinished, [&]() {
       //     QString optionStr = QJsonDocument(_jsonData).toJson();
       //     //用到js中init() 函数
       //     QString js = QString("setData(%1)").arg(optionStr);
       //     qDebug() << js;
       //     _view->page()->runJavaScript(js);
       //     });
    }
   



}


MainWindow::~MainWindow()
{
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

    delete ui;
}

void MainWindow::initInitface()
{
    m_LoginDialog = new LoginDialog(this);
   

    m_RegisterDialog = new RegisterDialog(this);

    m_ResourceManageDialog = new ResourceManageDialog(this);

    m_InforConfihurationDialog = new InformationConfihurationDialog(this);
    connect(m_InforConfihurationDialog, &InformationConfihurationDialog::signal_updateToolIcon, this, &MainWindow::slot_updateModuleToolIcon);

    m_DataManageDialog = new DataManageDialog(this);

    m_ApprovalProgressDialog = new ApprovalProgressDialog(this);

//    m_AddToolDialog = new AddToolDialog(this);

    m_OneClickLoadDialog = new OneClickLoadDialog(this);

    m_OneClickSaveDialog = new OneClickSaveDialog(this);
   /* QButtonGroup* buttonGroup = new QButtonGroup(this);

    buttonGroup->addButton(ui->btnFunction, 1);
    buttonGroup->addButton(ui->btnModule1, 2);
    buttonGroup->addButton(ui->btnModule2, 3);
    buttonGroup->addButton(ui->btnModule3, 4);
    buttonGroup->addButton(ui->btnModule4, 5);*/

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
        });
    connect(ui->btnModule2, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(2);
        });
    connect(ui->btnModule3, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(3);
        });
    connect(ui->btnModule4, &QPushButton::clicked, [this]() {
        ui->stackedWidget->setCurrentIndex(4);
        });


    ui->btnResourceManage->setCheckable(true);
    ui->btnInformationConfihuration->setCheckable(true);
    ui->btnDataManage->setCheckable(true);
    ui->btnApprovalProgress->setCheckable(true);
    connect(ui->btnResourceManage, &QPushButton::clicked, this, &MainWindow::slot_btnResourceManageClicked);
    connect(ui->btnInformationConfihuration, &QPushButton::clicked, this, &MainWindow::slot_btnInformationConfihurationClicked);
    connect(ui->btnDataManage, &QPushButton::clicked, this, &MainWindow::slot_btnDataManageClicked);
    connect(ui->btnApprovalProgress, &QPushButton::clicked, this, &MainWindow::slot_btnApprovalProgressClicked);

    // 初始化模块1-4界面;
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
    

    //common::clearLayout(ui->layoutM1ToolIcon);
    //std::list<table_tools> listTools;
    //if (db::databaseDI::Instance().get_tools(listTools, 1))
    //{
    //    for (const auto& stTool : listTools)
    //    {
    //        QToolButton* pBtn = new QToolButton();
    //        //QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
    //        pBtn->setIcon(QIcon(QString::fromStdString(stTool.icoPath)));
    //        pBtn->setIconSize(QSize(52, 46));
    //        pBtn->setText(QString::fromStdString(stTool.name));
    //        pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //        pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
    //        pBtn->setFocusPolicy(Qt::NoFocus);
    //        pBtn->setFixedSize(55, 60);
    //        pBtn->setEnabled(true);

    //        ui->layoutM1ToolIcon->addWidget(pBtn);
    //    }
    //}
    updateModuleToolIcon(1);
    updateModuleToolIcon(2);
    updateModuleToolIcon(3);
    updateModuleToolIcon(4);

    // 创建
    //QToolButton* pBtn = new QToolButton();
    ////QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
    //pBtn->setIcon(QIcon("D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\adobe_xd.png"));
    //pBtn->setIconSize(QSize(52, 46));
    //pBtn->setText(QString::fromLocal8Bit("XD"));
    //pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
    //pBtn->setFocusPolicy(Qt::NoFocus);
    //pBtn->setFixedSize(55, 60);
    //pBtn->setEnabled(true);
  
    //ui->layoutM1ToolIcon->addWidget(pBtn);
    if (m_LoginDialog->exec() == QDialog::Accepted)
    {
        ui->labelUserName->setText(m_LoginDialog->GetUser());
        if (m_LoginDialog->GetPop())
        {
            ui->btnApprovalProgress->hide();
        }
        this->showMaximized();
    }
    else
    {
        this->close();
    }
}

void MainWindow::showRegisterDialog()
{
    m_RegisterDialog->exec();
}
void MainWindow::setUserNameText(const QString& userName)
{
    ui->labelUserName->setText(userName);
}
void MainWindow::slot_btnResourceManageClicked()
{
    m_ResourceManageDialog->exec();
    ui->btnResourceManage->setChecked(false);
}
void MainWindow::slot_btnInformationConfihurationClicked()
{
    m_InforConfihurationDialog->exec();
    ui->btnInformationConfihuration->setChecked(false);
}

void MainWindow::slot_btnDataManageClicked()
{
    m_DataManageDialog->exec();
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
        addToooDialog.getToolData(tabName,toolName, mode);
        QWidget* pWidget = new QWidget;
        if (moduleNumber == 1)
        { 
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                //  widget->show();

                 // QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel1->addTab(widget, tabName);
            }
            else
            {
                QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel1->addTab(pWidget, tabName);
            }
           
        }
        else if (moduleNumber == 2)
        {
            WId winId = (WId)FindWindow(NULL, L"VMware Workstation");
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                //  widget->show();

                 // QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel2->addTab(widget, tabName);
            }
        }
        else if (moduleNumber == 3)
        {
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                //  widget->show();

                 // QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel3->addTab(widget, tabName);
            }
            else
            {
                QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel3->addTab(pWidget, tabName);
            }
        }
        else if (moduleNumber == 4)
        {
            WId winId = (WId)FindWindow(NULL, reinterpret_cast<LPCWSTR>(toolName.constData()));
            if (winId != 0)
            {
                QWindow* window = QWindow::fromWinId(winId);
                QWidget* widget = QWidget::createWindowContainer(window);
                //  widget->show();

                 // QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel4->addTab(widget, tabName);
            }
            else
            {
                QWidget* pWidget = new QWidget;
                ui->tabWidgetModulel4->addTab(pWidget, tabName);
            }

        }

    }
    
}

void MainWindow::slot_btnOneClickLoad()
{
   
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
    std::list<table_tools> listTools;
    if (db::databaseDI::Instance().get_tools(listTools, module))
    {
        for (const auto& stTool : listTools)
        {
            QToolButton* pBtn = new QToolButton();
            //QPushButton* pBtn = new QPushButton(QString::fromLocal8Bit("测试"));
            pBtn->setIcon(QIcon(QString::fromStdString(stTool.icoPath)));
            pBtn->setIconSize(QSize(52, 46));
            pBtn->setText(QString::fromStdString(stTool.name));
            pBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            pBtn->setStyleSheet("background-color:rgba(0,0,0,0);font-size: 12px;");
            pBtn->setFocusPolicy(Qt::NoFocus);
            pBtn->setFixedSize(55, 60);
            pBtn->setEnabled(true);

            pLayout->addWidget(pBtn);
        }
    }
}

