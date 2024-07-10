#ifndef APPROVALPROGRESSDIALOG_H
#define APPROVALPROGRESSDIALOG_H

#include <QDialog>

struct table_user;
struct table_dataApproval;
class QStandardItemModel;

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
    void flushUserTableShow(std::list<table_user> &listUser);
    void flushDataTableShow(std::list<table_dataApproval>& listData,const int &offsetRows);
private slots:

    void slot_DataItemBtnClicked();
    void slot_ItemBtnClicked();


    void slot_DataApprovalBtnLast();
    void slot_DataApprovalBtnNext();
    void slot_DataApprovalPageTo();

    void slot_btnLast();
    void slot_btnNext();
    void slot_pageTo();
    void slot_scrollMove(int value);
    void slot_combocUserCurrentIndexChanged(int index);
    void slot_userQuery();

private:
   // void hideTableRows(Q)
private:
    Ui::ApprovalProgressDialog *ui;

    QStandardItemModel* m_modelDataApproval;
    QStandardItemModel* m_modelUser;

    int m_DataApprovalTatalPage = 0;
    int m_DataApprovalTotalRows = 0;

    int m_UserTotalpage = 0;
    int m_UserTotalRows = 0;
};

#endif // APPROVALPROGRESSDIALOG_H
