#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>


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
	 * \brief	��¼״̬.
	 */
	enum eLoginState
	{
		eLogin_Start = 0,				// ��ʼ��¼
		eLogin_Timeout,					// ��¼��ʱ
		eLogin_End,						// ������¼
	};

	/*!
	 * \enum	eLoginResult
	 * \brief	��¼���.
	 */
	enum eLoginResult
	{
		eLogin_Succee = 0,				// �ɹ�
		eLogin_Faild = -1,				// ʧ��
		eLogin_DBFaild = 1,				// ���ݿ�����ʧ��
		eLogin_UserFaild = 2,			// �û������������
	};

	
	void Init(bool bClearPwd = false);


	int GetLoginState();

	
	QString GetUser();


	void UpdateLoginResult(short iRes);


	void setWindowTitle(QString strTitle);
private slots:


	void slot_btnLoginClicked();


	void slot_btnExitClicked();

	void slot_btnFingerprintClicked();

	
	void slot_timeout();

	
	void slot_leUserTextChanged(const QString& text);

	
	void slot_leUserEditingFinished();

	
	void slot_lePwdTextChanged(const QString& text);

	
	void slot_lePwdEditingFinished();
private:
	
	void clearTimer();
private:


	// ��ǰ��¼״̬
	int m_iState;

	// ��¼��ʱ��
	//QTimer m_Timer;

	// ��ǰ��¼�û�
	QString m_sUser;
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
