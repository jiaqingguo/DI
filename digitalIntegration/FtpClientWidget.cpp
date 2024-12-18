

#include <QMenu>
#include <QSettings>
#include <QFileDialog>
#include <QContextMenuEvent>
#include <QTextCodec>
#include <QInputDialog>
#include <qmessagebox.h>

#include "FtpClientWidget.h"
#include "ui_FtpClientWidget.h"


#include "Global.h"
#include "common.h"
#include "GifDialog.h"
#include "CtrlNetwork.h"
#include "common.h"
#include "databaseDI.h"

FtpClientWidget::FtpClientWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FtpClientWidget)
{
    ui->setupUi(this);
    initVar();
    //   loadFmIni();

    m_pGifDialog = new GifDialog();
    m_pUdp = new CCtrlNetwork;
    // m_pGifDialog->show();
   //  QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);

     // 设置表格列宽
    ui->tableWidget->setColumnWidth(0, 140);
    ui->tableWidget->setColumnWidth(1, 120);
    ui->tableWidget->setColumnWidth(2, 90);
    ui->tableWidget->setColumnWidth(3, 70);

    // 去除选中的虚线框
    ui->tableWidget->setItemDelegate((QStyledItemDelegate*)new MyStyledItemDelegate);

    // 设置进度条
    progress.hide();
    progress.setFixedHeight(10);
    progress.setAlignment(Qt::AlignCenter);
    //   statusBar()->addWidget(&progress, width());

       // 信号槽
    connect(&ftp, SIGNAL(listInfo(QUrlInfo)), SLOT(listInfo(QUrlInfo)));
    connect(&ftp, SIGNAL(commandFinished(int, bool)), SLOT(commandFinished(int, bool)));
    //  connect(&ftp, SIGNAL(dataTransferProgress(qint64,qint64)), SLOT(dataTransferProgress(qint64,qint64)));
    connect(&ftp, &QFtp::stateChanged, this, &FtpClientWidget::slot_stateChanged);

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &FtpClientWidget::slot_tableWidget_doubleClicked);
    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &FtpClientWidget::slot_tableWidget_itemClicked);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &FtpClientWidget::slot_customContextMenuRequested);

    connect(&m_ftpAdmin, SIGNAL(commandFinished(int, bool)), SLOT(slot_ftpAdminCommandFinished(int, bool)));


  

}
  

FtpClientWidget::~FtpClientWidget()
{
    qDeleteAll(m_mapFileDownload);
    delete ui;
}



void FtpClientWidget::initVar()
{
    editRow = -1;
    renameRow = -1;
    removeRow = -1;
    createFolder = false;

    oldName = "";
    uploadPath = "";
    currentPath = "";

    this->setWindowIcon(QPixmap(":/Icon/logo.jpg"));
}

void FtpClientWidget::saveToIni()
{
  /*  QSettings ini("./setting.ini", QSettings::IniFormat);

    ini.setValue("login/serverAddress", ui->leServerAddress->text());
    ini.setValue("login/port", ui->lePort->text());
    ini.setValue("login/account", ui->leAccount->text());
    ini.setValue("login/password", ui->lePassword->text());
    ini.sync();*/
}

void FtpClientWidget::loadFmIni()
{
  /*   QSettings ini("./setting.ini", QSettings::IniFormat);

     if (ini.childGroups().indexOf("login") >= 0)
     {
         ui->leServerAddress->setText(ini.value("login/serverAddress").toString());
         ui->lePort->setText(ini.value("login/port").toString());
         ui->leAccount->setText(ini.value("login/account").toString());
         ui->lePassword->setText(ini.value("login/password").toString());
     }*/
}

void FtpClientWidget::clear()
{
    listPath.clear();
    listType.clear();
    ui->tableWidget->setRowCount(0);
}

QString FtpClientWidget::createFolderName()
{
    int count = 0;
    int rowCount = ui->tableWidget->rowCount();
    for (int row = 0; row < rowCount; row++)
    {
        QString name = ui->tableWidget->item(row, 0)->text();
        if (name.compare(QString::fromLocal8Bit("新建文件夹"), Qt::CaseSensitive) >= 0)
        {
            name = name.remove(0, 5);
            if (name.isEmpty())
            {
                if (count == 0) ++count;
                continue;
            }

            int index = name.indexOf("(");
            if (index != 0) continue;

            name = name.mid(index + 1);
            index = name.indexOf(")");
            name = name.left(index);

            int toInt = name.toInt();
            if (toInt > count) count = toInt;
        }
    }

    return QString::fromLocal8Bit("新建文件夹") + (count ? QString("(%1)").arg(count + 1) : "");
}

void FtpClientWidget::connectToFtpServer(const QString& strHostName, const QString& strAddr, const QString& strAccount, const QString& strPwd, const int& port)
{
    m_strHostName = strHostName;
   // ftp.setAutoTimeout(-1);
    m_strAccount = strAccount;
    m_strPwd = strPwd;
    m_strAddr = strAddr;
    m_iPort = port;

    if (m_strAddr.isEmpty())
    {
        //statusBar()->showMessage(QString::fromLocal8Bit("服务器地址为空!"), 2000);
        return;
    }
    // 如果已经登录了就不需要重复登录
    if (ftp.state() != QFtp::LoggedIn)
    {
        ftp.connectToHost(m_strAddr, m_iPort);
        ftp.login(m_strAccount, m_strPwd);
    }

    if (m_ftpAdmin.state() != QFtp::LoggedIn)
    {
        m_ftpAdmin.connectToHost(m_strAddr, m_iPort);
        m_ftpAdmin.login(common::strFtpAccount,common::strFtpAdminPwd );
    }
    if (common::bAdministrator) // 管理员;
    {
        // 隐藏第二个标签页
      // 移除 Tab 2
        m_strDolwnloadText = QString::fromLocal8Bit("下载");
    }

    m_pMenu = new QMenu;
    m_actionPutFile = m_pMenu->addAction(QString::fromLocal8Bit("上传文件"));
    m_actionPutDir = m_pMenu->addAction(QString::fromLocal8Bit("上传文件夹"));
    
    if (common::bAdministrator) // 管理员;
    {
        m_actionGetFile = m_pMenu->addAction(QString::fromLocal8Bit("下载文件"));
        m_actionGetDir = m_pMenu->addAction(QString::fromLocal8Bit("下载文件夹"));
    }
    else 
    {
        m_actionGetFile = m_pMenu->addAction(QString::fromLocal8Bit("申请下载文件"));
        m_actionGetDir = m_pMenu->addAction(QString::fromLocal8Bit("申请下载文件夹"));
    }
    m_pMenu->addSeparator();
    m_actionMkdir = m_pMenu->addAction(QString::fromLocal8Bit("新建文件夹"));
    m_actionDel = m_pMenu->addAction(QString::fromLocal8Bit("删除文件"));
    // m_actionDownload = m_pMenu->addAction(m_strDolwnloadText);
    m_actionRename = m_pMenu->addAction(QString::fromLocal8Bit("重命名"));
    m_actionCompress = m_pMenu->addAction(QString::fromLocal8Bit("压缩"));
    m_actionUnCompress = m_pMenu->addAction(QString::fromLocal8Bit("解压"));
    // m_actionCopyPath = m_pMenu->addAction(QString::fromLocal8Bit("复制路径"));
    m_actionFlush = m_pMenu->addAction(QString::fromLocal8Bit("刷新界面"));
    connect(m_actionPutFile, &QAction::triggered, this, &FtpClientWidget::onUpload);
    connect(m_actionPutDir, &QAction::triggered, this, &FtpClientWidget::slot_UploadDir);
    connect(m_actionGetFile, &QAction::triggered, this, &FtpClientWidget::onDownload);
    connect(m_actionGetDir, &QAction::triggered, this, &FtpClientWidget::slot_downloadDirectory);

    connect(m_actionMkdir, &QAction::triggered, this, &FtpClientWidget::slot_newDir);
    connect(m_actionDel, &QAction::triggered, this, &FtpClientWidget::onRemove);
    //  connect(m_actionDownload, &QAction::triggered, this, &FtpClientWidget::slot_actionDownload);
    connect(m_actionRename, &QAction::triggered, this, &FtpClientWidget::slot_rename);
    connect(m_actionCompress, &QAction::triggered, this, &FtpClientWidget::slot_actionCompress);
    connect(m_actionUnCompress, &QAction::triggered, this, &FtpClientWidget::slot_actionUnCompress);
    //  connect(m_actionCopyPath, &QAction::triggered, this, &FtpClientWidget::slot_actionCopyPath);
    connect(m_actionFlush, &QAction::triggered, this, &FtpClientWidget::onRefresh);
}

void FtpClientWidget::Flush()
{
    if (ftp.state() != QFtp::LoggedIn)
    {
        ftp.connectToHost(m_strAddr, m_iPort);
        ftp.login(m_strAccount, m_strPwd);
    }
    else
    {
        // 清除表格
        clear();

        // 如果当前目录不是根目录，则先插入一行用来双击返回上一级
        if (currentPath.indexOf("/") >= 0)
        {
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(folderIcon(), "..."));
            listType["..."] = folderType();
        }

        ftp.list();
    }
    
}

void FtpClientWidget::createUserDir(const QString& strDirName)
{
    if (m_ftpAdmin.state() != QFtp::LoggedIn)
    {
        m_ftpAdmin.connectToHost(m_strAddr, m_iPort);
        m_ftpAdmin.login("shareadmin", "123456");
    }

    m_ftpAdmin.mkdir(QString::fromLatin1(strDirName.toUtf8()));
}

void FtpClientWidget::setIsLinuxFtpServer(const bool& b)
{
    m_bLinuxFtpServer = b;
}

QString FtpClientWidget::fromFtpCodec(const QString& str)
{
    if (m_bLinuxFtpServer)
    {
        return QString::fromUtf8(str.toUtf8()).toLatin1();
    }
    else
    {
        QByteArray data = str.toLatin1();
        QTextCodec* codec = QTextCodec::codecForName("GBK");
        QString name = codec->toUnicode(data);
        return name;
    }
   
   // 
}

QString FtpClientWidget::toFtpCodec(const QString& strLocal)
{
    if (m_bLinuxFtpServer)
    {
        return QString::fromLatin1(strLocal.toUtf8());
    }
    else
    {

    }
}

void FtpClientWidget::ApprovalDownload(const QString& strName, const QString& strPath, const bool& bDir)
{
    if (bDir)  // 目录;
    {
        // 显示选择下载目录的对话框
        QString  loaclDownloadDirPath = QFileDialog::getExistingDirectory(nullptr, "选择下载目录", QDir::homePath());
        if (loaclDownloadDirPath.isEmpty())
        {
            return;
        }
        loaclDownloadDirPath = loaclDownloadDirPath + "/" + strName;  //cs/chat
        // 创建本地目录
        QDir directory;
        bool success = directory.mkpath(loaclDownloadDirPath);


        QString  remoteDownloadDirPath = strPath; // jqg/chat
        // 列出远程目录内容

        //m_downloadDirPath= 
        m_vecListInfo.clear();

        m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在下载文件夹"));
        m_pGifDialog->show();

        m_bDownloadDir = true;
        setDisableUI();
        m_downloadDirCommandID = ftp.list(remoteDownloadDirPath);
        m_iDoloadDirCommandTotal++;

        m_mapLoaclDownloadDirPath[m_downloadDirCommandID] = loaclDownloadDirPath;
        m_mapRemoteDownloadDirPath[m_downloadDirCommandID] = remoteDownloadDirPath;

    }
    else     // 文件
    {
        QString path = QFileDialog::getSaveFileName(NULL, "", QString("C:/Users/Pangs/Desktop/%1").arg(strName));
        if (path.isEmpty()) return;
        QFile* file = new QFile;
        file->setFileName(path);
        if (!file->open(QIODevice::WriteOnly))
        {
            return;
        }

        // 解决中文乱码问题
        QString  remoteDownloadDirPath = strPath;
        m_bDownloadDir = false;
        m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在下载文件"));
        m_pGifDialog->show();

        int id = ftp.get(QString::fromLatin1(remoteDownloadDirPath.toLocal8Bit()), file);

        m_mapFileDownload[id] = file;
    }
}

void FtpClientWidget::createDir(const QString& strDirPath)
{
   

}

void FtpClientWidget::downloadDirectory( QVector<QUrlInfo>& vecurlInfo, const QString& m_loaclDownloadDirPath, const QString& m_remoteDownloadDirPath)
{

    for (auto urlInfo : vecurlInfo)
    {

         QString newRemote = QString("%1/%2").arg(m_remoteDownloadDirPath).arg(urlInfo.name());
        //QString  path

        // 使用远程路径的文件名构建本地路径
        /*QString localPath = m_loaclDownloadDirPath + m_remoteDownloadDirPath;*/
         QString newLoacl = QString("%1/%2").arg(m_loaclDownloadDirPath).arg(urlInfo.name());

        if (urlInfo.isFile())
        {
            m_bDownloadDir = true;
            // 下载文件
            qDebug() << "Downloading file:" << newRemote << "to" << newLoacl;
            QFile* file = new QFile;
            file->setFileName(newLoacl);
            if (!file->open(QIODevice::WriteOnly))
            {
                return;
            }
            int id = ftp.get(newRemote, file);
            m_iDoloadDirCommandTotal++;
            m_mapFileDownload[id] = file;

        }
        else if (urlInfo.isDir())
        {
            // 创建本地目录
            QDir dir;
            //QString newLocalDirPath = dir.absoluteFilePath(urlInfo.fileName());
            dir.mkpath(newLoacl);
         
            m_bDownloadDir = true;
            // 继续列出目录
            m_downloadDirCommandID = ftp.list(newRemote); // 列出子目录内容
            m_iDoloadDirCommandTotal++;
           
            m_mapLoaclDownloadDirPath[m_downloadDirCommandID] = newLoacl;
            m_mapRemoteDownloadDirPath[m_downloadDirCommandID] = newRemote;
        }

    }
    vecurlInfo.clear();
}

void FtpClientWidget::setDisableUI()
{
    disconnect(ui->tableWidget, &QTableWidget::doubleClicked, this, &FtpClientWidget::slot_tableWidget_doubleClicked);
    disconnect(ui->tableWidget, &QTableWidget::itemClicked, this, &FtpClientWidget::slot_tableWidget_itemClicked);
    disconnect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &FtpClientWidget::slot_customContextMenuRequested);

    emit signal_ableUI(false);
}

void FtpClientWidget::setAbleUI()
{
    connect(ui->tableWidget, &QTableWidget::doubleClicked, this, &FtpClientWidget::slot_tableWidget_doubleClicked);
    connect(ui->tableWidget, &QTableWidget::itemClicked, this, &FtpClientWidget::slot_tableWidget_itemClicked);
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested, this, &FtpClientWidget::slot_customContextMenuRequested);
    emit signal_ableUI(true);
}

void FtpClientWidget::uploadDirectory(const QString& localDirPath, const QString& remoteDirPath) 
{
    QDir localDir(localDirPath);

    // 创建远程目录
    QString remoteDir = remoteDirPath + "//" + localDir.dirName();
  //  ftp.mkdir(remoteDir); // 在 FTP 服务器上创建目录
    ftp.mkdir(QString::fromLatin1(remoteDir.toUtf8()));
    m_iUploadDirCommandTotal++;

    // 上传所有文件
    foreach(const QString & file, localDir.entryList(QDir::Files))
    {
        QString filePath = localDir.absoluteFilePath(file);
        QString remoteFilePath = remoteDir + "/" + file;
        qDebug() << "Uploading file:" << filePath << "to" << remoteFilePath;
        QFile * pfile = new QFile(filePath);

        int id=ftp.put(pfile, remoteFilePath); // 上传文件
        m_iUploadDirCommandTotal++;
        m_mapFileUpload[id] = pfile;
    }

    // 递归上传所有子目录
    foreach(const QString & subDir, localDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) 
    {
        QString subDirPath = localDir.absoluteFilePath(subDir);
        uploadDirectory(subDirPath, remoteDir); // 递归上传子目录
    }
}



void FtpClientWidget::on_tbDisconnent_clicked()
{
    if (ftp.state() == QFtp::LoggedIn)
    {
        ftp.close();
    }
}

void FtpClientWidget::slot_tableWidget_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    if (row < 0)
    {
        return;
    }
    QString name = ui->tableWidget->item(row, 0)->text();

    // 如果双击的是第0行，并且不是根目录，因为根目录没有返回上一级项，表示返回上一级
    if (row == 0 && currentPath.indexOf("/") >= 0)
    {
        // 将当前目录减少一级
        currentPath = currentPath.left(currentPath.lastIndexOf("/"));

        // 清除表格
        clear();

        // 如果当前目录不是根目录，则先插入一行用来双击返回上一级
        if (currentPath.indexOf("/") >= 0)
        {
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(folderIcon(), "..."));
            listType["..."] = folderType();
        }

        // 发送命令返回上一级，然后列出所有项
        ftp.cd("../");
        ftp.list();
    }
    // 如果双击的是其他行，并且是目录行，表示进入下一级
    else if (listPath[name])
    {
        if (currentPath == "")
        {
            if (name != common::strLoginUserName)
            {
                return;
            }
        }
        // 当前目录进入下一级
        currentPath += QString("/%1").arg(name);

        // 清除表格
        clear();

        // 如果当前目录不是根目录，则先插入一行用来双击返回上一级
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(folderIcon(), "..."));
        listType["..."] = folderType();

        // 发送命令进入下一级，然后列出所有项
        //ftp.cd(QString::fromLatin1(currentPath.toLocal8Bit()));
        ftp.cd(toFtpCodec(currentPath));
        ftp.list();
    }
}

void FtpClientWidget::slot_tableWidget_itemClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
    closePersistentEditor();
}


void FtpClientWidget::slot_customContextMenuRequested(const QPoint& pos)
{
   
    if (ui->tableWidget->rowCount() <= 0) return;


    m_pMenu->exec(QCursor::pos());

    // 如果有未关闭的编辑项则先关闭
    //closePersistentEditor();

    //QMenu menu;
    //menu.addAction(QString::fromLocal8Bit("上传文件"), this, &FtpClientWidget::onUpload);
    //menu.addAction(QString::fromLocal8Bit("上传文件夹"), this, &FtpClientWidget::slot_UploadDir);
    //menu.addAction(QString::fromLocal8Bit("下载文件"), this, &FtpClientWidget::onDownload);
    //menu.addAction(QString::fromLocal8Bit("下载文件夹"), this, &FtpClientWidget::slot_downloadDirectory);
    //menu.addSeparator();
    //menu.addAction(/*folderIcon(),*/ QString::fromLocal8Bit("新建文件夹"), this, &FtpClientWidget::slot_newDir);
    //menu.addAction(QString::fromLocal8Bit("重命名"), this, &FtpClientWidget::slot_rename);
    //menu.addAction(QString::fromLocal8Bit("删除文件"), this, &FtpClientWidget::onRemove);
    ////   menu.addSeparator();
    //menu.addSeparator();
    //menu.addAction(QString::fromLocal8Bit("压缩"), this, &FtpClientWidget::slot_actionCompress);
    //menu.addAction(QString::fromLocal8Bit("解压"), this, &FtpClientWidget::slot_actionUnCompress);
  
    //menu.addAction(QString::fromLocal8Bit("刷新"), this, &FtpClientWidget::onRefresh);

    //menu.exec(QCursor::pos());

}

void FtpClientWidget::onUpload()
{
    QString path = QFileDialog::getOpenFileName(NULL, "", QString("C:/Users/Pangs/Desktop/"));
    if (path.isEmpty()) return;
    QFile *pfile = new QFile;
    pfile->setFileName(path);
    if (!pfile->open(QIODevice::ReadOnly)) return;

    uploadPath = path;

    // 解决中文乱码问题
    QString name = path.mid(path.lastIndexOf("/") + 1);
    path = QString("%1/%2").arg(currentPath).arg(name);
    m_bUploadDir = false;
    m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在上传文件"));
    m_pGifDialog->show();
    int id= ftp.put(pfile, QString::fromLatin1(path.toUtf8()));
   
    m_mapFileUpload[id] = pfile;
}

void FtpClientWidget::slot_UploadDir()
{
    QString directory = QFileDialog::getExistingDirectory(
        nullptr,               // 父窗口
        QString::fromLocal8Bit("选择一个目录"),      // 对话框标题
        "",                   // 默认目录
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks // 选项
    );

    if (directory.isEmpty()) {
        return;
    }
  
    m_bUploadDir = true;
    setDisableUI();
    uploadPath = directory;
    uploadDirectory(directory,currentPath);

    m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在上传文件夹"));
    m_pGifDialog->show();

}

void FtpClientWidget::onDownload()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) return;

    QString name = ui->tableWidget->item(row, 0)->text();
    if (listPath[name]) {

    }
    else 
    {
        QString path = QFileDialog::getSaveFileName(NULL, "", QString("C:/Users/Pangs/Desktop/%1").arg(name));
        if (path.isEmpty()) return;
        QFile* file = new QFile;
        file->setFileName(path);
        if (!file->open(QIODevice::WriteOnly))
        {
            return;
        }

        // 解决中文乱码问题
       path = QString("%1/%2").arg(currentPath).arg(name);
       m_bDownloadDir = false;
       m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在下载文件"));
       m_pGifDialog->show();
       
       int id= ftp.get(QString::fromLatin1(path.toLocal8Bit()), file);

      
       m_mapFileDownload[id] = file;
    }
}

void FtpClientWidget::slot_downloadDirectory()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) return;

    QString name = ui->tableWidget->item(row, 0)->text();

    if (common::bAdministrator)
    {
        if (listPath[name])  // 目录;
        {
            // 显示选择下载目录的对话框
            QString  loaclDownloadDirPath = QFileDialog::getExistingDirectory(nullptr, "选择下载目录", QDir::homePath());
            if (loaclDownloadDirPath.isEmpty())
            {
                return;
            }
            loaclDownloadDirPath = loaclDownloadDirPath + "/" + name;  //cs/chat
            // 创建本地目录
            QDir directory;
            bool success = directory.mkpath(loaclDownloadDirPath);


            QString  remoteDownloadDirPath = QString("%1/%2").arg(currentPath).arg(name); // jqg/chat
            // 列出远程目录内容

            //m_downloadDirPath= 
            m_vecListInfo.clear();


            m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在下载文件夹"));
            m_pGifDialog->show();

            m_bDownloadDir = true;
            setDisableUI();
            m_downloadDirCommandID = ftp.list(remoteDownloadDirPath);
            m_iDoloadDirCommandTotal++;

            m_mapLoaclDownloadDirPath[m_downloadDirCommandID] = loaclDownloadDirPath;
            m_mapRemoteDownloadDirPath[m_downloadDirCommandID] = remoteDownloadDirPath;

        }
        else     // 文件
        {
            QString path = QFileDialog::getSaveFileName(NULL, "", QString("C:/Users/Pangs/Desktop/%1").arg(name));
            if (path.isEmpty()) return;
            QFile* file = new QFile;
            file->setFileName(path);
            if (!file->open(QIODevice::WriteOnly))
            {
                return;
            }

            // 解决中文乱码问题
            path = QString("%1/%2").arg(currentPath).arg(name);
            m_bDownloadDir = false;
            m_pGifDialog->setTitleText(QString::fromLocal8Bit("正在下载文件"));
            m_pGifDialog->show();

            int id = ftp.get(QString::fromLatin1(path.toLocal8Bit()), file);


            m_mapFileDownload[id] = file;
        }
    }
    else
    {
        QString  remoteDownloadDirPath = QString("%1/%2").arg(currentPath).arg(name); // jqg/chat

        table_DownloadApproval stDownloadApproval;
        stDownloadApproval.userID = common::iUserID;
        //stDownloadApproval.filePath = dirPath.toLocal8Bit().toStdString();
        stDownloadApproval.filePath = remoteDownloadDirPath.toStdString();
        if (listPath[name])
        {
            stDownloadApproval.fileType = "dir";
        }
        else
        {
            stDownloadApproval.fileType = name.mid(name.lastIndexOf(".") + 1).toStdString();  // 返回点之后的部分
        }
       
        stDownloadApproval.fileTime = ui->tableWidget->item(row, 1)->text().toStdString();

        stDownloadApproval.applicationTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        stDownloadApproval.status = 0;

        stDownloadApproval.ftpIp = m_strAddr.toStdString();
        stDownloadApproval.ftpName = m_strHostName.toStdString();
        db::databaseDI::Instance().add_download_approval_info(stDownloadApproval);
    }
   
}

void FtpClientWidget::onCreateFolder()
{
   // QString name = createFolderName();
   // // 在底部插入
   // int row = ui->tableWidget->rowCount();
   // // 插入新的一行
   // ui->tableWidget->insertRow(row);
   // // 名称
   // ui->tableWidget->setItem(row, 0, new QTableWidgetItem(folderIcon(), name));
   // // 日期
   // ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm")));
   // // 类型
   // QString type = folderType();
   // ui->tableWidget->setItem(row, 2, new QTableWidgetItem(type));

   // // 创建目录 解决中文乱码问题
   // oldName = name;
   // createFolder = true;
   // ftp.mkdir(QString::fromLatin1(oldName.toUtf8()));
   //// ftp.mkdir(QString::fromLatin1(oldName.toLocal8Bit()));

   // editRow = row;
   // listPath[oldName] = true;
   // listType[oldName] = type;

   // // 打开编辑
   // QTableWidgetItem *item = ui->tableWidget->item(row, 0);
   // ui->tableWidget->setCurrentCell(row, 0);
   // ui->tableWidget->openPersistentEditor(item);    // 打开编辑
   // ui->tableWidget->editItem(item);
}

void FtpClientWidget::slot_newDir()
{
    QString name = QInputDialog::getText(this, QString::fromLocal8Bit("新建"), QString::fromLocal8Bit("输入新建文件夹名称："));
    if (name.isEmpty())
    {
        return;
    }
    // 在底部插入
    int row = ui->tableWidget->rowCount();

    // 插入新的一行
    ui->tableWidget->insertRow(row);

    // 名称
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(folderIcon(), name));

    // 日期
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm")));

    // 类型
    QString type = folderType();
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(type));

    // 创建目录 解决中文乱码问题

    createFolder = true;
    ftp.mkdir(QString::fromLatin1(oldName.toUtf8()));
    // ftp.mkdir(QString::fromLatin1(oldName.toLocal8Bit()));

    listPath[oldName] = true;
    listType[oldName] = type;
}

void FtpClientWidget::onRename()
{

}

void FtpClientWidget::slot_rename()
{
    // 如果是多级目录，则选中的第一级就不给重命名
    auto index = ui->tableWidget->currentIndex();
    int row = ui->tableWidget->currentIndex().row();
    if (currentPath.indexOf("/") >= 0 && row <= 0) return;

    m_strRename = QInputDialog::getText(this, QString::fromLocal8Bit("重命名"), QString::fromLocal8Bit("请输入文件新名称："));
    if (m_strRename.isEmpty())
    {
        return;
    }

    m_oldName = ui->tableWidget->item(row, 0)->text();

    m_iRenameRow = row;
    //m_strRename = ui->tableWidget->item(row, 0)->text();

    ftp.rename(QString::fromLatin1(m_oldName.toUtf8()), QString::fromLatin1(m_strRename.toLocal8Bit()));

   

}

void FtpClientWidget::onRemove()
{
    // 如果是多级目录，则选中的第一级就不给删
    int row = ui->tableWidget->currentIndex().row();
    if (currentPath.indexOf("/") >= 0 && row <= 0) return;

    removeRow = row;

    // 解决中文乱码问题
    QString name = ui->tableWidget->item(row, 0)->text();

    if (listPath[name])
    {
        ftp.rmdir(toFtpCodec(name));
    }
    else
    {
        ftp.remove(toFtpCodec(name));
    }
}

void FtpClientWidget::onRefresh()
{
    // 清除表格
    clear();

    // 如果当前目录不是根目录，则先插入一行用来双击返回上一级
    if (currentPath.indexOf("/") >= 0)
    {
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(folderIcon(), "..."));
        listType["..."] = folderType();
    }

    ftp.list();
}

void FtpClientWidget::onInsertRow()
{
    int row = ui->tableWidget->rowCount();
    if (row <= 0) return;


    QString name = uploadPath.mid(uploadPath.lastIndexOf("/") + 1);
    QString type = fileType(name);
    QFileInfo fileInfo(uploadPath);

    if (listPath.contains(name)) // 判断是否已存在 ，是因为下载文件夹时，会触发多个get的完成信号，导致根目录添加多次
    {
        return;
    }
    // 记录是否为目录
    listType[name] = type;
    listPath[name] = fileInfo.isDir();

    // 插入新的一行
    ui->tableWidget->insertRow(row);

    // 名称
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fileInfo.isDir() ? folderIcon() : fileIcon(name), name));

    // 日期
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(fileInfo.lastModified().toString("yyyy/MM/dd hh:mm")));

    // 类型
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(type));

    // 大小
    if (fileInfo.isDir()) return;
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString("%1 KB").arg(qMax(int(fileInfo.size() / 1000), 1))));
}

void FtpClientWidget::closePersistentEditor()
{
  //  if (editRow < 0 || editRow >= ui->tableWidget->rowCount()) return;

  //  QTableWidgetItem *item = ui->tableWidget->item(editRow, 0);
  //  ui->tableWidget->closePersistentEditor(item);   // 关闭编辑

  //  // 重命名
  //  QString newname = ui->tableWidget->item(editRow, 0)->text();
  //  for (int i = 0; i < ui->tableWidget->rowCount(); i++)
  //  {
  //      QString name = ui->tableWidget->item(i, 0)->text();
  //      if ((name == newname) && (listType[oldName] == listType[newname]))
  //      {
  //          if (!createFolder)
  //              //statusBar()->showMessage(QString::fromLocal8Bit("文件名已存在!"), 2000);

  //          ui->tableWidget->item(editRow, 0)->setText(oldName);
  //          editRow = -1;
  //          createFolder = false;
  //          return;
  //      }
  //  }

  //  editRow = -1;
  //  //QString::fromLatin1(oldName.toUtf8())
  ////  ftp.rename(QString::fromLatin1(oldName.toLocal8Bit()),QString::fromLatin1(newname.toLocal8Bit()));
  //  ftp.rename(QString::fromLatin1(oldName.toUtf8()), QString::fromLatin1(newname.toLocal8Bit()));

  //  listPath[newname] = listPath[oldName];
  //  listPath.remove(oldName);
  //  listType[newname] = listType[oldName];
  //  listType.remove(oldName);
}

void FtpClientWidget::slot_actionCompress()
{
    // 如果是多级目录，则选中的第一级就不给删
    int row = ui->tableWidget->currentIndex().row();
    if (currentPath.indexOf("/") >= 0 && row <= 0) return;


    QString name = ui->tableWidget->item(row, 0)->text();
    QString strPath = currentPath + "/" + name;

    QString NewZipName = QInputDialog::getText(this, QString::fromLocal8Bit("压缩"), QString::fromLocal8Bit("压缩包名称："));
    if (NewZipName.isEmpty())
        return;
    if (!NewZipName.endsWith(".zip", Qt::CaseInsensitive))
    {
        NewZipName = NewZipName + ".zip";  // 添加 .zip 后缀
    }
    QString  newZipPath = currentPath + "/" + NewZipName; 
 
  
    QString strOrder = "compress "+ strPath + " "+ newZipPath;
    emit signal_compress(m_bLinuxFtpServer,m_strAddr, strOrder);
}

void FtpClientWidget::slot_actionUnCompress()
{
    // 如果是多级目录，则选中的第一级就不给删
    int row = ui->tableWidget->currentIndex().row();
    if (currentPath.indexOf("/") >= 0 && row <= 0) return;
    QString name = ui->tableWidget->item(row, 0)->text();
    if (!name.endsWith(".zip", Qt::CaseInsensitive))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请选择.zip文件"));
        return;
    }
    QString strPath = currentPath + "/" + name;
    QString strOrder = "unCompress " + strPath ;
    emit signal_compress(m_bLinuxFtpServer, m_strAddr, strOrder);
}

std::string string_To_UTF82(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char* pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete[]pwBuf;
    delete[]pBuf;

    pwBuf = NULL;
    pBuf = NULL;

    return retStr;
}
void FtpClientWidget::listInfo(QUrlInfo url)
{
    if (m_bDownloadDir)
    {
     
        m_vecListInfo.append(url);
       
        return;
    }
    QString str11111 = url.name();
   // QString name = QString::fromUtf8(str11111.toUtf8()).toLatin1();
    QString name = fromFtpCodec(url.name());
 
    QString type = url.isDir() ? folderType() : fileType(name);

    // 记录是否为目录
    listType[name] = type;
    listPath[name] = url.isDir();

    int row = ui->tableWidget->rowCount();

    // 插入新的一行
    ui->tableWidget->insertRow(row);

    // 名称
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(url.isDir() ? folderIcon() : fileIcon(name), name));

    // 日期
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(url.lastModified().toString("yyyy/MM/dd hh:mm")));

    // 类型
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(type));

    // 大小
    if (url.isDir()) return;
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString("%1 KB").arg(qMax(int(url.size() / 1000), 1))));
}

void FtpClientWidget::commandFinished(int id, bool err)
{
    QString strErr;
    if (err)
    {
       strErr = ftp.errorString();
       int errfrp = ftp.error();
      if (errfrp == QFtp::Error::NotConnected)
      {
         // ftp.connect();
          int a = 0;
      }
    }
  
    int cmd = ftp.currentCommand();
    switch (cmd)
    {
    case QFtp::Login:
        if (!err)
        {
            //if (currentPath!="")
            //{
            //    // 如果当前目录不是根目录，则先插入一行用来双击返回上一级
            //    ui->tableWidget->insertRow(0);
            //    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(folderIcon(), "..."));
            //    listType["..."] = folderType();
            //    ftp.list(toFtpCodec(currentPath));   // 成功则显示列表
            //}
            //else
            {
                ftp.list();
            }
            
        }
       // statusBar()->showMessage(err ? ftp.errorString() : QString::fromLocal8Bit("服务器连接成功!"), 2000);
        break;

    case QFtp::Close:
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("ftp断开连接"));
        if (!err)
        {
           
           // clear(); 
            //currentPath.clear();
          //  ftp.list(currentPath);
        }     // 清除列表

        break;

    }
       
    case QFtp::Get:
    {
        /*if (file.isOpen())
        {
            file.flush();
            file.close();
        }*/
        if (m_mapFileDownload.contains(id))
        {
            if (m_mapFileDownload[id]->isOpen())
            {
                m_mapFileDownload[id]->flush();
                m_mapFileDownload[id]->close();

                delete m_mapFileDownload[id]; 
                m_mapFileDownload.remove(id);  
            }
        }
        if (m_bDownloadDir) //下载文件夹完成 判断是否下载文件夹完成
        {
            m_iDoloadDirCommandTotal--;
            if (m_iDoloadDirCommandTotal == 0)
            {
                m_bDownloadDir = false;
                m_pGifDialog->close();
                setAbleUI();
            }
        }
        else // 下载文件
        {
            m_pGifDialog->close();
            setAbleUI();
        }
            //  statusBar()->showMessage(err ? ftp.errorString() : QString::fromLocal8Bit("文件下载成功!"), 2000);
         break;
    } 
    case QFtp::List :
    {
       // if (!err)
        {
            if (m_bDownloadDir)
            {
                m_iDoloadDirCommandTotal--;
                downloadDirectory(m_vecListInfo,m_mapLoaclDownloadDirPath[id],m_mapRemoteDownloadDirPath[id]);
                m_mapLoaclDownloadDirPath.remove(id);
                m_mapRemoteDownloadDirPath.remove(id);

                if (m_iDoloadDirCommandTotal == 0) // 判断是否下载文件夹完成
                {
                    m_bDownloadDir = false;
                    m_pGifDialog->close();
                    setAbleUI();
                }
            }
            
        }
       
        break;
    }
    case QFtp::Cd:
    {
       
        break;
    }
    case QFtp::Put:
    {
        if (m_mapFileUpload.contains(id))
        {
            if (m_mapFileUpload[id]->isOpen())
            {
                m_mapFileUpload[id]->flush();
                m_mapFileUpload[id]->close();

                delete m_mapFileUpload[id];
                m_mapFileUpload.remove(id);
            }
        }
        if (m_bUploadDir) // 上传文件夹完成
        {
            m_iUploadDirCommandTotal--;
            if (m_iUploadDirCommandTotal == 0) // 判断是否下载文件夹完成
            {
                m_bUploadDir = false;
                m_pGifDialog->close();
                setAbleUI();
            }
        }
        else  // 上传文件完成
        {
            m_pGifDialog->close();
            setAbleUI();
        }
        if (!err)
        {
            onInsertRow();
        }
    }
       
        break;

    case QFtp::Rename:
    {
        if (!err)
        {
            if (m_iRenameRow >= 0)
            {
                ui->tableWidget->item(m_iRenameRow, 0)->setText(m_strRename);
                m_iRenameRow = -1;

                listPath[m_strRename] = listPath[m_oldName];
                listPath.remove(m_oldName);
                listType[m_strRename] = listType[m_oldName];
                listType.remove(m_oldName);
            }
        }
       
           
        createFolder = false;
        break;
    }
    case QFtp::Remove:
    {
        if (!err)
        {
            ui->tableWidget->removeRow(removeRow);
        }
        break;
    }
    case QFtp::Mkdir:
    {
        if (m_bUploadDir)
        {
            m_iUploadDirCommandTotal--;
            if (m_iUploadDirCommandTotal == 0) // 判断是否上传文件夹完成
            {
                m_bUploadDir = false;
                m_pGifDialog->close();
                setAbleUI();
            }
        }
        break;
    }
    case QFtp::Rmdir:
        if (!err) ui->tableWidget->removeRow(removeRow);
      
        break;
    /*case QFtp::Put:*/

    }
   

}

void FtpClientWidget::slot_ftpAdminCommandFinished(int id, bool err)
{
    int cmd = m_ftpAdmin.currentCommand();
    switch (cmd)
    {
    case QFtp::Mkdir:
    {
        if (!err)
        {
            int  a = 0;
        }
        break;
    }
    }
}

void FtpClientWidget::dataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    progress.setVisible(readBytes != totalBytes);
    progress.setMaximum(totalBytes);
    progress.setValue(readBytes);
}

void FtpClientWidget::slot_stateChanged(int state)
{
    if (state == QFtp::State::Unconnected)
    {
        if (ftp.state() != QFtp::LoggedIn)
        {
            // 清除表格
            clear();
            currentPath = "";
            ftp.connectToHost(m_strAddr, m_iPort);
            ftp.login(m_strAccount, m_strPwd);

        }
    }
}

void FtpClientWidget::on_tbConnent_clicked()
{
    //QString serverAddress = ui->leServerAddress->text();
    //if (serverAddress.isEmpty())
    //{
    //    //statusBar()->showMessage(QString::fromLocal8Bit("服务器地址为空!"), 2000);
    //    return;
    //}

    //QString port = ui->lePort->text();
    //if (port.isEmpty())
    //{
    //   // statusBar()->showMessage(QString::fromLocal8Bit("端口号为空!"), 2000);
    //    return;
    //}

    //QString account = ui->leAccount->text();
    //QString password = ui->lePassword->text();
    //int commandID = -1;
    //// 如果已经登录了就不需要重复登录
    //if (ftp.state() != QFtp::LoggedIn)
    //{
    //    commandID = ftp.connectToHost(serverAddress, port.toInt());
    //    commandID = ftp.login(account, password);
    //}

    //// 保存到配置文件
    //saveToIni();
}