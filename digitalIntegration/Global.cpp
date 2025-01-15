#include "Global.h"

//#include <QtWin>
//
//
//
//QIcon folderIcon()
//{
//    SHFILEINFOA info;
//    if (SHGetFileInfoA(QString("folder").toUtf8(),
//                   FILE_ATTRIBUTE_DIRECTORY,
//                   &info,
//                   sizeof(info),
//                   SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES))
//    {
//        return QIcon(QtWin::fromHICON(info.hIcon));
//    }
//
//    return QIcon();
//}
//
//QIcon fileIcon(QString fileName)
//{
//    if (fileName.isEmpty())
//        return QIcon();
//
//    int index = fileName.lastIndexOf(".");
//    QString suffix = fileName.mid(index);
//    std::string stdSuffix = suffix.toUtf8().constData();
//
//    SHFILEINFOA info;
//    if (SHGetFileInfoA(stdSuffix.c_str(),
//                   FILE_ATTRIBUTE_NORMAL,
//                   &info,
//                   sizeof(info),
//                   SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES))
//    {
//        return QIcon(QtWin::fromHICON(info.hIcon));
//    }
//
//    return QIcon();
//}
//
//QString folderType()
//{
//    SHFILEINFOA info;
//    if(SHGetFileInfoA(QString("folder").toUtf8(),
//                      FILE_ATTRIBUTE_DIRECTORY,
//                      &info,
//                      sizeof(info),
//                      SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES))
//    {
//        return QString::fromLocal8Bit(info.szTypeName);
//    }
//
//    return QString();
//}

//QString fileType(QString fileName)
//{
//    if (fileName.isEmpty())
//        return QString();
//
//    int index = fileName.lastIndexOf(".");
//    QString suffix = fileName.mid(index);
//    std::string szSuffix = suffix.toUtf8().constData();
//
//    SHFILEINFOA info;
//    if(SHGetFileInfoA(szSuffix.c_str(),
//                      FILE_ATTRIBUTE_NORMAL,
//                      &info,
//                      sizeof(info),
//                      SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES))
//    {
//        return QString::fromLocal8Bit(info.szTypeName);
//    }
//
//    return QString();
//}


