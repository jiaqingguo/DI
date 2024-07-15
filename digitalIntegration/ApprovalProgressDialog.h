#ifndef APPROVALPROGRESSDIALOG_H
#define APPROVALPROGRESSDIALOG_H

#include <QDialog>
#include <QMessageBox>

struct table_user;
struct table_dataApproval;
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
    void flushUserTableShow(std::list<table_user> &listUser);
    void flushDataTableShow(std::list<table_dataApproval>& listData,const int &offsetRows);
  /*  std::list<table_user> processList(const std::list<table_user>& listUser, const int& num, const int& offsetRows);
    std::list<table_dataApproval> processList(const std::list<table_dataApproval>& listUser, const int& num, const int& offsetRows);*/
    template<typename T>
    std::list<T> processList(const std::list<T>& listData, const int& num, const int& offsetRows);
private slots:

    void slot_btnDataShow();
    void slot_btnUserShow();


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
    void slot_dataApprovalQuery();
    void slot_userQuery();

    void slot_spinBoxEnter();
    //void slot_user_time_select();
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

    std::list<table_user> m_listUser;
    std::list<table_dataApproval> m_listDataApproval;
    QString qssBlue = R"(
        QPushButton {
            background-color: lightblue;
            border: 2px solid gray;
            border-radius: 5px;
            padding: 5px;
        }
    )";
    QString qssGray = R"(
        QPushButton {
            background-color: lightgray;
            border: 2px solid gray;
            border-radius: 5px;
            padding: 5px;
        }
    )";
   
};

#endif // APPROVALPROGRESSDIALOG_H

