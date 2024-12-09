

#include <QMenu>
#include <QSettings>
#include <QFileDialog>
#include <QContextMenuEvent>
#include <QTextCodec>

#include "FtpClientWidget.h"
#include "ui_FtpClientWidget.h"


#include "Global.h"
#include "common.h"
#include "GifDialog.h"
//#include "qftp.h"

FtpClientWidget::FtpClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FtpClientWidget)
{
    ui->setupUi(this);
    initVar();
 //   loadFmIni();

    m_pGifDialog = new GifDialog();
   // m_pGifDialog->show();
  //  QApplication::processEvents(QEventLoop::ExcludeSocketNotifiers);

    // 设置表格列宽
    ui->tableWidget->setColumnWidth(0, 140);
    ui->tableWidget->setColumnWidth(1, 120);
    ui->tableWidget->setColumnWidth(2, 90);
    ui->tableWidget->setColumnWidth(3, 70);

    // 去除选中的虚线框
    ui->tableWidget->setItemDelegate((QStyledItemDelegate *)new MyStyledItemDelegate);

    // 设置进度条
    progress.hide();
    progress.setFixedHeight(10);
    progress.setAlignment(Qt::AlignCenter);
 //   statusBar()->addWidget(&progress, width());

    // 信号槽
    connect(&ftp, SIGNAL(listInfo(QUrlInfo)), SLOT(listInfo(QUrlInfo)));
    connect(&ftp, SIGNAL(commandFinished(int,bool)), SLOT(commandFinished(int,bool)));
    connect(&ftp, SIGNAL(dataTransferProgress(qint64,qint64)), SLOT(dataTransferProgress(qint64,qint64)));

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
   connect(ui->tableWidget, &QTableWidget::doubleClicked, this,&FtpClientWidget::slot_tableWidget_doubleClicked);
   connect(ui->tableWidget, &QTableWidget::itemClicked, this,&FtpClientWidget::slot_tableWidget_itemClicked);
   connect(ui->tableWidget, &QTableWidget::customContextMenuRequested,this, &FtpClientWidget::slot_customContextMenuRequested);
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

void FtpClientWidget::connectToFtpServer(const QString& strAddr, const QString& strAccount, const QString& strPwd, const int& port)
{
   // ftp.setAutoTimeout(-1);
    m_strAccount = strAddr;
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

    // 保存到配置文件
    saveToIni();
}

QString FtpClientWidget::fromFtpCodec(const QString& str)
{
    return QString();
}

QString FtpClientWidget::toFtpCodec(const QString& strLocal)
{
    return QString::fromLatin1(strLocal.toUtf8());
}

void FtpClientWidget::createDir(const QString& strDirPath)
{
   

}

//void FtpClientWidget::downloadDirectory(const QUrlInfo& urlInfo, const QString& localPath, const QString& remotePath)
//{
// 
//    if (urlInfo.isFile()) 
//    {
//        m_bDownloadDir = true;
//        // 下载文件
//        qDebug() << "Downloading file:" << localPath << "to" << localPath;
//        m_downloadDirCommandID= ftp.get(remotePath, new QFile(localPath));
//
//
//    }
//    else if (urlInfo.isDir()) 
//    {
//        // 创建本地目录
//        QDir dir;
//        //QString newLocalDirPath = dir.absoluteFilePath(urlInfo.fileName());
//        dir.mkpath(localPath);
//        m_bDownloadDir = true;
//        // 继续列出目录
//        m_downloadDirCommandID = ftp.list(remotePath); // 列出子目录内容
//    }
//
//}

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

//void FtpClientWidget::contextMenuEvent(QContextMenuEvent *event)
//{
//    Q_UNUSED(event);
//    if (ui->tableWidget->rowCount() <= 0) return;
//
//    // 如果有未关闭的编辑项则先关闭
//    closePersistentEditor();
//
//    QMenu menu;
//    menu.addAction(QString::fromLocal8Bit("上传文件"), this, &FtpClientWidget::onUpload);
//    menu.addAction(QString::fromLocal8Bit("上传文件夹"), this, &FtpClientWidget::slot_UploadDir);
//    menu.addAction(QString::fromLocal8Bit("下载文件"), this, &FtpClientWidget::onDownload);
//    menu.addAction(QString::fromLocal8Bit("下载文件夹"), this, &FtpClientWidget::slot_downloadDirectory);
//    menu.addSeparator();
//    menu.addAction(/*folderIcon(),*/ QString::fromLocal8Bit("新建文件夹"), this, &FtpClientWidget::onCreateFolder);
// //   menu.addSeparator();
//    menu.addAction(QString::fromLocal8Bit("重命名"), this, &FtpClientWidget::onRename);
//    menu.addAction(QString::fromLocal8Bit("删除文件"), this, &FtpClientWidget::onRemove);
//    menu.addAction(QString::fromLocal8Bit("刷新"), this, &FtpClientWidget::onRefresh);
//
//    menu.exec(QCursor::pos());
//}

void FtpClientWidget::slot_customContextMenuRequested(const QPoint& pos)
{
   
    if (ui->tableWidget->rowCount() <= 0) return;

    // 如果有未关闭的编辑项则先关闭
    closePersistentEditor();

    QMenu menu;
    menu.addAction(QString::fromLocal8Bit("上传文件"), this, &FtpClientWidget::onUpload);
    menu.addAction(QString::fromLocal8Bit("上传文件夹"), this, &FtpClientWidget::slot_UploadDir);
    menu.addAction(QString::fromLocal8Bit("下载文件"), this, &FtpClientWidget::onDownload);
    menu.addAction(QString::fromLocal8Bit("下载文件夹"), this, &FtpClientWidget::slot_downloadDirectory);
    menu.addSeparator();
    menu.addAction(/*folderIcon(),*/ QString::fromLocal8Bit("新建文件夹"), this, &FtpClientWidget::onCreateFolder);
    //   menu.addSeparator();
    menu.addAction(QString::fromLocal8Bit("重命名"), this, &FtpClientWidget::onRename);
    menu.addAction(QString::fromLocal8Bit("删除文件"), this, &FtpClientWidget::onRemove);
    menu.addAction(QString::fromLocal8Bit("刷新"), this, &FtpClientWidget::onRefresh);

    menu.exec(QCursor::pos());

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
        m_downloadDirCommandID =ftp.list(remoteDownloadDirPath);
        m_iDoloadDirCommandTotal++;
       
        m_mapLoaclDownloadDirPath[m_downloadDirCommandID] = loaclDownloadDirPath;
        m_mapRemoteDownloadDirPath[m_downloadDirCommandID] = remoteDownloadDirPath;
       
    }
    //else     // 文件
    //{
    //    QString path = QFileDialog::getSaveFileName(NULL, "", QString("C:/Users/Pangs/Desktop/%1").arg(name));
    //    if (path.isEmpty()) return;

    //    file.setFileName(path);
    //    if (!file.open(QIODevice::WriteOnly)) return;

    //    // 解决中文乱码问题
    //    path = QString("%1/%2").arg(currentPath).arg(name);
    //    ftp.get(QString::fromLatin1(path.toLocal8Bit()), &file);
    //}
}

void FtpClientWidget::onCreateFolder()
{
    QString name = createFolderName();

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
    oldName = name;
    createFolder = true;
    ftp.mkdir(QString::fromLatin1(oldName.toUtf8()));
   // ftp.mkdir(QString::fromLatin1(oldName.toLocal8Bit()));

    editRow = row;
    listPath[oldName] = true;
    listType[oldName] = type;

    // 打开编辑
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    ui->tableWidget->setCurrentCell(row, 0);
    ui->tableWidget->openPersistentEditor(item);    // 打开编辑
    ui->tableWidget->editItem(item);
}

void FtpClientWidget::onRename()
{
    // 如果是多级目录，则选中的第一级就不给重命名
    int row = ui->tableWidget->currentIndex().row();
    if (currentPath.indexOf("/") >= 0 && row <= 0) return;

    editRow = row;
    oldName = ui->tableWidget->item(row, 0)->text();

    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    ui->tableWidget->setCurrentCell(row, 0);
    ui->tableWidget->openPersistentEditor(item);    // 打开编辑
    ui->tableWidget->editItem(item);
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
        ftp.rmdir(QString::fromLatin1(name.toLocal8Bit()));
    }
    else
    {
        ftp.remove(QString::fromLatin1(name.toLocal8Bit()));
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
    if (editRow < 0 || editRow >= ui->tableWidget->rowCount()) return;

    QTableWidgetItem *item = ui->tableWidget->item(editRow, 0);
    ui->tableWidget->closePersistentEditor(item);   // 关闭编辑

    // 重命名
    QString newname = ui->tableWidget->item(editRow, 0)->text();
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString name = ui->tableWidget->item(i, 0)->text();
        if ((name == newname) && (listType[oldName] == listType[newname]))
        {
            if (!createFolder)
                //statusBar()->showMessage(QString::fromLocal8Bit("文件名已存在!"), 2000);

            ui->tableWidget->item(editRow, 0)->setText(oldName);
            editRow = -1;
            createFolder = false;
            return;
        }
    }

    editRow = -1;
    //QString::fromLatin1(oldName.toUtf8())
  //  ftp.rename(QString::fromLatin1(oldName.toLocal8Bit()),QString::fromLatin1(newname.toLocal8Bit()));
    ftp.rename(QString::fromLatin1(oldName.toUtf8()), QString::fromLatin1(newname.toLocal8Bit()));

    listPath[newname] = listPath[oldName];
    listPath.remove(oldName);
    listType[newname] = listType[oldName];
    listType.remove(oldName);
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
    QString name = QString::fromUtf8(str11111.toUtf8()).toLatin1();
 
 //  QString name= QString::fromLocal8Bit(url.name().toUtf8());
     // 假设服务器使用 UTF-8 编码，转换为本地环境的编码
   /* QString name = QTextCodec::codecForName("UTF-8")->toUnicode(url.name().toUtf8());*/
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
            ftp.list();   // 成功则显示列表
        }
       // statusBar()->showMessage(err ? ftp.errorString() : QString::fromLocal8Bit("服务器连接成功!"), 2000);
        break;

    case QFtp::Close:
        if (!err) 
        { clear(); currentPath.clear(); }     // 清除列表
        //statusBar()->showMessage(err ? ftp.errorString() : QString::fromLocal8Bit("断开服务器连接!"), 2000);
        break;

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
        if (!createFolder)
        {

        }
           
        createFolder = false;
        break;

    case QFtp::Remove:
        if (!err) ui->tableWidget->removeRow(removeRow);
        
        break;

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

void FtpClientWidget::dataTransferProgress(qint64 readBytes, qint64 totalBytes)
{
    progress.setVisible(readBytes != totalBytes);
    progress.setMaximum(totalBytes);
    progress.setValue(readBytes);
}

