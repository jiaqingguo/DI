#ifndef APPROVALPROGRESSDIALOG_H
#define APPROVALPROGRESSDIALOG_H

#include <QDialog>
#include <QMessageBox>

struct table_user;
struct table_dataApproval;
struct table_DownloadApproval;

class QStandardItemModel;
class QSpinBox;

namespace Ui {
class ApprovalProgressDialog;
}

class ApprovalProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApprovalProgressDialog(QWidget *parent = nullptr);
    ~ApprovalProgressDialog();

    void init();
private:

    void getDownloadData(std::list<table_DownloadApproval>& listData);

   
    void flushUserTableShow(std::list<table_user> &listUser);
  //  void flushDataTableShow(std::list<table_dataApproval>& listData,const int &offsetRows);

    void autoFlushDownloadData();
    void autoFlushUserData();
    void flushDownloadTableShow(std::list<table_DownloadApproval>& listData, const int& offsetRows);
  /*  std::list<table_user> processList(const std::list<table_user>& listUser, const int& num, const int& offsetRows);
    std::list<table_dataApproval> processList(const std::list<table_dataApproval>& listUser, const int& num, const int& offsetRows);*/
    template<typename T>
    std::list<T> processList(const std::list<T>& listData, const int& num, const int& offsetRows);
signals:
    void signal_createFtpUserDir(const QString strDirName);
    void signal_ftpDownlaod(const QString strPath, const QString strFtpIP);
private slots:

    void slot_btnDataShow();
    void slot_btnUserShow();


    void slot_DataItemBtnClicked();
    void slot_DataItemDownloadBtnClicked();
    void slot_ItemBtnClicked();


    void slot_DataApprovalBtnLast();
    void slot_DataApprovalBtnNext();
    void slot_DataApprovalPageTo();

    void slot_btnLast();
    void slot_btnNext();
    void slot_pageTo();
    void slot_scrollMove(int value);
    void slot_combocUserCurrentIndexChanged(int index);
    void slot_dataApprovalQuery();
    void slot_userQuery();

    void slot_spinBoxEnter();

    void slot_btnFlushDownload();
    void slot_btnFlushUser();
private:
   // void hideTableRows(Q)
private:
    Ui::ApprovalProgressDialog *ui;

    QStandardItemModel* m_modelDataApproval = nullptr;
    QStandardItemModel* m_modelUser = nullptr;

    int m_DataApprovalTatalPage = 0;
    int m_DataApprovalTotalRows = 0;

    int m_UserTotalpage = 0;
    int m_UserTotalRows = 0;

    std::list<table_user> m_listUser;
   // std::list<table_dataApproval> m_listDataApproval;
    std::list<table_DownloadApproval> m_listDataApproval;
   
};

#endif // APPROVALPROGRESSDIALOG_H

