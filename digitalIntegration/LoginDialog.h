#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class fingerDlg;
class RegisterDialog;
namespace Ui {
class LoginDialog;
}

class QTimer;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
	/*!
	 * \enum	eLoginState
	 * \brief	登录状态.
	 */
	enum eLoginState
	{
		eLogin_Start = 0,				// 开始登录
		eLogin_Timeout,					// 登录超时
		eLogin_End,						// 结束登录
	};

	/*!
	 * \enum	eLoginResult
	 * \brief	登录结果.
	 */
	enum eLoginResult
	{
		eLogin_Succee = 0,				// 成功
		eLogin_Faild = -1,				// 失败
		eLogin_DBFaild = 1,				// 数据库连接失败
		eLogin_UserFaild = 2,			// 用户名或密码错误
	};

	
	void Init(bool bClearPwd = false);

	int GetUserID();
	int GetLoginState();
	int GetPop();
	
	QString GetUser();


	void UpdateLoginResult(short iRes);


	void setWindowTitle(QString strTitle);
private slots:


	void slot_btnLoginClicked();


	void slot_btnExitClicked();
	void slot_btnForgetPassClicked();
	void slot_btnFingerprintClicked();

	
	void slot_timeout();

	
	void slot_leUserTextChanged(const QString& text);

	
	void slot_leUserEditingFinished();

	
	void slot_lePwdTextChanged(const QString& text);

	
	void slot_lePwdEditingFinished();
private:
	
	void clearTimer();
private:

	int m_userID;
	// 当前登录状态
	int m_iState;

	// 登录定时器
	//QTimer m_Timer;
	int m_pop = 1; // 用户权限;
	// 当前登录用户
	QString m_sUser;
private:
    Ui::LoginDialog *ui;

	//指纹
	fingerDlg *m_fingerDlg = nullptr;
	
	RegisterDialog *registerDialog = nullptr;
public slots:
	void slot_login_succ();
	void slot_regist_succ();
	void slot_no_regist_finger();
};

#endif // LOGINDIALOG_H
