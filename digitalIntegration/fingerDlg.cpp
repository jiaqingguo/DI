//#pragma comment (lib, "User32.lib")

#include "fingerDlg.h"
#include "MainWindow.h"
#include "common.h"
#include <QTimer>

HANDLE m_hDevice = NULL;
bool m_bRegister = FALSE;
bool m_bIdentify = FALSE;
int m_enrollIdx = 0;
int m_score = 0;



fingerDlg::fingerDlg(QDialog* pParent)
{
	hDBCache = NULL;
	//hDevice=NULL;
	bStopThread = FALSE;
	//bRegister = FALSE;
	hThreadWork = NULL;
	pImgBuf = NULL;
	Tid = 1;   //ָ�� ID��>0 �� 32 λ�޷���������

	//m_zkfinger = new ZkFinger();

}

fingerDlg::~fingerDlg()
{
	if (m_hDevice)
	{
		if (NULL != pImgBuf)
		{
			delete[] pImgBuf;
			pImgBuf = NULL;
		}
		bStopThread = TRUE;
		if (NULL != hThreadWork)
		{
			WaitForSingleObject(hThreadWork, INFINITE);
			CloseHandle(hThreadWork);
			hThreadWork = NULL;
		}
		if (NULL != hDBCache)
		{
			ZKFPM_DBFree(hDBCache);
			hDBCache = NULL;
		}
		ZKFPM_CloseDevice(m_hDevice);
		ZKFPM_Terminate();
		m_hDevice = NULL;
		Tid = 1;
	}
}

void fingerDlg::finger_init()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (NULL == m_hDevice)
	{
		if (ZKFPM_Init() != ZKFP_ERR_OK)
		{
			qDebug() << "Init ZKFPM fail";
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Init ZKFPM fail"));
			return;
		}
		if ((m_hDevice = ZKFPM_OpenDevice(0)) == NULL)
		{
			qDebug() << "Open sensor fail";
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Open sensor fail"));
			ZKFPM_Terminate();
			return;
		}
		hDBCache = ZKFPM_DBInit();   //�����㷨������������ֵ�ǻ������ľ��
		if (NULL == hDBCache)
		{
			qDebug() << "Create DBCache fail";
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Create DBCache fail"));
			ZKFPM_CloseDevice(m_hDevice);
			ZKFPM_Terminate();
			return;
		}
		/*int nDPI = 750;
		ZKFPM_SetParameters(m_hDevice, 3, (unsigned char*)&nDPI, sizeof(int));*/
		//Set FakeFun On
		nFakeFunOn = 1;
		//���òɼ�������  2002���� ��д   ���ٿ��أ�1��0�أ�
		ZKFPM_SetParameters(m_hDevice, 2002, (unsigned char*)&nFakeFunOn, sizeof(int));

		/*TZKFPCapParams zkfpCapParams = {0x0};
		ZKFPM_GetCaptureParams(m_hDevice, &zkfpCapParams);
		m_imgFPWidth = zkfpCapParams.imgWidth;
		m_imgFPHeight = zkfpCapParams.imgHeight;*/
		unsigned int size = 4;
		//��ȡ�ɼ�������   1���� ͼ���  2���� ͼ���
		ZKFPM_GetParameters(m_hDevice, 1, (unsigned char*)&imgFPWidth, &size);
		size = 4;
		ZKFPM_GetParameters(m_hDevice, 2, (unsigned char*)&imgFPHeight, &size);
		pImgBuf = new unsigned char[imgFPWidth*imgFPHeight];
		//nLastRegTempLen = 0;


		hThreadWork = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadCapture, this, 0, NULL);
		/*QTimer *captrueTimer = new QTimer(this);
		captrueTimer->setInterval(100);
		connect(captrueTimer, &QTimer::timeout, this, &fingerDlg::onCapture);
		captrueTimer->start();*/



		//memset(&szLastRegTemplate, 0x0, sizeof(szLastRegTemplate));
		qDebug() << "Init ZKFPM success";

		Tid = 1;
		m_enrollIdx = 0;
		m_bRegister = FALSE;


		//�򿪽�����
		//hmutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("MutexTest"));
		////����������
		//if (hmutex == NULL)
		//{
		//	std::cout << "Create MutexTest!" << endl;
		//	hmutex = CreateMutex(NULL, false, TEXT("MutexTest"));
		//}
	}
	else
	{
		qDebug() << "Already Init";
		//SetDlgItemText(IDC_EDIT_RESULT, _T("Already Init"));
	}


}


DWORD WINAPI fingerDlg::ThreadCapture(LPVOID lParam)
{
	fingerDlg* pDlg = (fingerDlg*)lParam;
	if (NULL != pDlg)
	{
		pDlg->bStopThread = FALSE;
		while (!pDlg->bStopThread)
		{
			unsigned char szTemplate[MAX_TEMPLATE_SIZE] = { 0x0 }; //���ص�ָ��ģ��
			unsigned int tempLen = MAX_TEMPLATE_SIZE;    //Ԥ���� fpTemplate �ڴ��С2048

			memset(szTemplate, 0, MAX_TEMPLATE_SIZE);
			//�ɼ�ָ�ƣ�ָ��ģ��
			int ret = ZKFPM_AcquireFingerprint(m_hDevice, pDlg->pImgBuf, pDlg->imgFPWidth*pDlg->imgFPHeight, szTemplate, &tempLen);
			if (ZKFP_ERR_OK == ret)
			{
				if (1 == pDlg->nFakeFunOn)	//FakeFinger Test�ٵ�
				{
					int nFakeStatus = 0;
					unsigned int retLen = sizeof(int);
					//��ȡ�ɼ������� ����λȫΪ 1 ��ʾ��  ��ָ(value & 31 == 31)
					if (0 == ZKFPM_GetParameters(m_hDevice, 2004, (unsigned char*)&nFakeStatus, &retLen))
					{
						if ((nFakeStatus & 31) != 31)
						{
							//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Is Fake Finger?"));
							//pDlg->SetDlgItemText(IDC_EDIT_RESULT, _T("Is Fake Finger?"));
							continue;
						}
					}
				}
				//pDlg->ShowImage(pDlg->m_pImgBuf);
				if (m_bRegister)
				{
					pDlg->DoRegister(szTemplate, tempLen);  //ע��
				}
				else
				{
					pDlg->DoVerify(szTemplate, tempLen);   //��֤
				}
			}

			Sleep(100);
		}
	}
	return 0;
}


//void fingerDlg::onCapture()
//{
//	if (m_zkfinger == nullptr) {
//		return;
//	}
//
//	if (m_hDevice == nullptr) {
//		return;
//	}
//
//	unsigned char szTemplate[MAX_TEMPLATE_SIZE];
//	unsigned int tempLen = MAX_TEMPLATE_SIZE;
//	// �ɼ�ָ��ͼ���ģ��
//	int ret = m_zkfinger->AcquireFingerprint(m_hDevice, pImgBuf, imgFPWidth * imgFPHeight, szTemplate, &tempLen);
//	if (ZKFP_ERR_OK == ret) {
//		//FakeFinger Test
//		if (1 == nFakeFunOn) {
//			int nFakeStatus = 0;
//			unsigned int retLen = sizeof(int);
//			if (0 == m_zkfinger->GetParameters(m_hDevice, 2004, (unsigned char*)&nFakeStatus, &retLen)) {
//				if ((nFakeStatus & 0x1F) != 0x1F) {
//					QString log = QString("��ָ�����Ч, Is Fake Finger?");
//					qWarning() << log;
//					//emit sigMessage(LOG_MSG_TYPE, log);
//					return;
//				}
//			}
//		}
//
//		//ShowFpImage(m_pImgBuf, m_imgFPWidth, m_imgFPHeight);
//		if (m_bRegister) {
//			qInfo() << QString("��ʼָ��ע��");
//			DoRegister2(szTemplate, tempLen);
//		}
//		else {
//			qDebug() << QString("��ʼָ����֤");
//			DoVerify2(szTemplate, tempLen);
//		}
//	}
//	else {
//		// qDebug() << "AcquireFingerprint failed, ret =" << ret;
//	}
//}


void fingerDlg::DoRegister(unsigned char* temp, int len)
{
	int id = 0;
	//CString strLog;
	//bool succ2 = false;
	unsigned char szLastRegTemplate[MAX_TEMPLATE_SIZE] = { 0x0 };
	int nLastRegTempLen = MAX_TEMPLATE_SIZE;

	if (m_enrollIdx >= ENROLLCNT)  //3
	{
		m_enrollIdx = 0;	//restart enroll
		return;
	}
	if (m_enrollIdx > 0)
	{
		//�Ա���öָ���Ƿ�ƥ��
		if (0 >= ZKFPM_DBMatch(hDBCache, arrPreRegTemps[m_enrollIdx - 1], arrPreTempsLen[m_enrollIdx - 1], temp, len))
		{
			m_enrollIdx = 0;
			m_bRegister = FALSE;
			//AfxMessageBox(_T("�밴��ͬ����ָ"), MB_OK);
			//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Please press the same finger while registering"));
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Please press the same finger while registering"));
			return;
		}
	}
	arrPreTempsLen[m_enrollIdx] = len;
	memcpy(arrPreRegTemps[m_enrollIdx], temp, len);
	if (++m_enrollIdx >= ENROLLCNT)
	{
		int ret = 0;
		unsigned char szRegTemp[MAX_TEMPLATE_SIZE] = { 0x0 };
		unsigned int cbRegTemp = MAX_TEMPLATE_SIZE;          //ģ�峤��

		//�� 3 öԤ�Ǽ�ָ��ģ��ϲ�Ϊһö�Ǽ�ָ��
		ret = ZKFPM_DBMerge(hDBCache, arrPreRegTemps[0], arrPreRegTemps[1], arrPreRegTemps[2], szRegTemp, &cbRegTemp);
		//m_enrollIdx = 0;
		m_bRegister = FALSE;
		if (ZKFP_ERR_OK == ret)   //ZKFP_ERR_OK=�����ɹ�
		{
			//��ӵǼ�ָ��ģ�嵽������
			ret = ZKFPM_DBAdd(hDBCache, Tid++, szRegTemp, cbRegTemp);
			if (ZKFP_ERR_OK == ret)
			{
				memcpy(szLastRegTemplate, szRegTemp, cbRegTemp);

				nLastRegTempLen = cbRegTemp;

				/*delete[] szRegTemp;
				szRegTemp = nullptr;*/
				if (!db::databaseDI::Instance().add_user_info(common::stUser))
				{
					QMessageBox::warning(this, QString::fromLocal8Bit("���ݿ�"), QString::fromLocal8Bit("�û�ע��ʧ��!"));
					return;
				}

				if (!db::databaseDI::Instance().get_new_regist_user(id))
				{
					return;
				}
				QString str;
				str = CharToQString(szLastRegTemplate, nLastRegTempLen);
				if (db::databaseDI::Instance().add_user_finger(str, nLastRegTempLen, id))
				//if (db::databaseDI::Instance().add_user_finger(szLastRegTemplate, nLastRegTempLen, id))
				{
					MessageBox(NULL, TEXT("ע����ɣ���ȴ�����Ա���!"), TEXT("��ʾ"), 0);
					emit regist_succ();

				}


				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Register success"));
				//SetDlgItemText(IDC_EDIT_RESULT, _T("Register succ"));
			}
			else
			{
				///strLog.Format(_T("Register fail, because add to db fail, ret=%d"), ret);
				//SetDlgItemText(IDC_EDIT_RESULT, strLog);
				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromWCharArray(strLog.GetString()));
				return;
			}
		}
		else
		{
			//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Register fail"));
			//SetDlgItemText(IDC_EDIT_RESULT, _T("Register fail"));
			return;
		}
	}
	else
	{
		//strLog.Format(_T("You still need press %d times finger"), ENROLLCNT - m_enrollIdx);
		//SetDlgItemText(IDC_EDIT_RESULT, strLog);
		//qDebug() << strLog;
		//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromWCharArray(strLog.GetString()));
		return;
	}
}

void fingerDlg::DoVerify(unsigned char *temp, int len)
{
	//if (m_nLastRegTempLen > 0)	//have enroll one more template
	//{
	if (m_bIdentify)   //ʶ��ť�����
	{
		//unsigned char szLastLogTemplate2[MAX_TEMPLATE_SIZE] = { 0x0 };
		int nLastLogTempLen2 = MAX_TEMPLATE_SIZE;

		int ret = ZKFP_ERR_OK;

		int approval = 0;
		bool success = false;

		QString str;
		QByteArray date;

		//std::vector<std::pair<unsigned char *, int>> vec_finger;

		db::databaseDI::Instance().get_approval(approval, common::iUserID);

		if (approval == 1)
		{
			
			//db::databaseDI::Instance().get_user_finger2(szLastLogTemplate2, nLastLogTempLen2, common::iUserID);
			db::databaseDI::Instance().get_user_finger2(str, nLastLogTempLen2, common::iUserID);
			date = QStringToChar(str);
			
			if (!str.isEmpty() && nLastLogTempLen2 != 0)
			{
				
					//ZKFPM_DBAdd(hDBCache, Tid++, szLastLogTemplate2, nLastLogTempLen2);
					//ret = ZKFPM_DBIdentify(hDBCache, temp, len, &tid, &score);

					ret = ZKFPM_DBMatch(hDBCache, reinterpret_cast<unsigned char*>(date.data()), nLastLogTempLen2, temp, len);
					//ret = ZKFPM_DBMatch(hDBCache, szLastLogTemplate2, nLastLogTempLen2, temp, len);
					if (ZKFP_ERR_OK < ret)  //��ʾ����ʧ��  0��ʾ�ɹ�
					{
						success = true;
					}
				if (success)
				{
					//MessageBox(NULL, TEXT("��¼�ɹ�"), TEXT("��ʾ"), 0);
					emit login_succ();
					bStopThread = TRUE;

				}
				else
				{
					MessageBox(NULL, TEXT("ָ����֤ʧ��,����ָ��֤"), TEXT("��ʾ"), 0);
				}
			}
			else
			{
				MessageBox(NULL, TEXT("���û�û��ע��ָ��,������û���¼"), TEXT("��ʾ"), 0);
				emit no_regist_finger();
			}
		}
		else if (approval == 2)
		{
			//���δͨ�����߼������Ǻ��񲢲���Ҫ
		}
	}
	else  //��֤��ť���
	{//�ȶ���öָ���Ƿ�ƥ��  ָ��ģ��1 ����  ָ��ģ��2 ����       ����ֵ ���  ���ڵ���0�Ļ����ǱȶԷ���  С��0����
		//int ret = ZKFPM_DBMatch(hDBCache, szLastRegTemplate, nLastRegTempLen, temp, len);
		//if (ZKFP_ERR_OK > ret)  //ret��ʾ���ǱȶԷ���
		{
			//strLog.Format(_T("Match finger fail, ret = %d"), ret);
			//SetDlgItemText(IDC_EDIT_RESULT, strLog);
		}
		//else
		{
			//strLog.Format(_T("Match succ, score=%d"), ret);
			//SetDlgItemText(IDC_EDIT_RESULT, strLog);
		}
	}
	//}
	//else
	//{
		//SetDlgItemText(IDC_EDIT_RESULT, _T("You need enroll a reg-template first!"));
		//MessageBox(NULL, TEXT("You need enroll a reg-template first!"), TEXT("��ʾ"), 0);
	//}
}
//void fingerDlg::DoRegister2(unsigned char *pTemplate, int len)
//{
//	if (m_zkfinger == nullptr) {
//		return;
//	}
//
//	unsigned int fingerId = 0;
//	unsigned int score = 0;
//	int ret = m_zkfinger->DBIdentify(pTemplate, len, &fingerId, &score);
//	if (ZKFP_ERR_OK == ret) {
//		qDebug() << QString("���󣬵�ǰ��ָ�ѵǼ�! fingerId=%1, score=%2").arg(fingerId).arg(score);
//		//emit sigMessage(LOG_MSG_TYPE, QString("���󣬵�ǰ��ָ�ѵǼ�!"));
//		//m_preRegTempList.clear();
//		m_bRegister = false;
//		return;
//	}
//	int id = 0;
//	//CString strLog;
//	//bool succ2 = false;
//	unsigned char szLastRegTemplate[MAX_TEMPLATE_SIZE] = { 0x0 };
//	int nLastRegTempLen = MAX_TEMPLATE_SIZE;
//
//	if (m_enrollIdx >= ENROLLCNT)  //3
//	{
//		m_enrollIdx = 0;	//restart enroll
//		return;
//	}
//	if (m_enrollIdx > 0)
//	{
//		//�Ա���öָ���Ƿ�ƥ��
//		if (0 >= ZKFPM_DBMatch(hDBCache, arrPreRegTemps[m_enrollIdx - 1], arrPreTempsLen[m_enrollIdx - 1], pTemplate, len))
//		{
//			m_enrollIdx = 0;
//			m_bRegister = FALSE;
//			//AfxMessageBox(_T("�밴��ͬ����ָ"), MB_OK);
//			//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Please press the same finger while registering"));
//			//SetDlgItemText(IDC_EDIT_RESULT, _T("Please press the same finger while registering"));
//			return;
//		}
//	}
//	arrPreTempsLen[m_enrollIdx] = len;
//	memcpy(arrPreRegTemps[m_enrollIdx], pTemplate, len);
//	if (++m_enrollIdx >= ENROLLCNT)
//	{
//		int ret = 0;
//		unsigned char szRegTemp[MAX_TEMPLATE_SIZE] = { 0x0 };
//		unsigned int cbRegTemp = MAX_TEMPLATE_SIZE;          //ģ�峤��
//
//		//�� 3 öԤ�Ǽ�ָ��ģ��ϲ�Ϊһö�Ǽ�ָ��
//		ret = ZKFPM_DBMerge(hDBCache, arrPreRegTemps[0], arrPreRegTemps[1], arrPreRegTemps[2], szRegTemp, &cbRegTemp);
//		//m_enrollIdx = 0;
//		m_bRegister = FALSE;
//		if (ZKFP_ERR_OK == ret)   //ZKFP_ERR_OK=�����ɹ�
//		{
//			//��ջ�����
//			//ret = ZKFPM_DBClear(hDBCache);
//
//			//��ӵǼ�ָ��ģ�嵽������
//			ret = ZKFPM_DBAdd(hDBCache, Tid++, szRegTemp, cbRegTemp);
//			if (ZKFP_ERR_OK == ret)
//			{
//				memcpy(szLastRegTemplate, szRegTemp, cbRegTemp);
//
//				nLastRegTempLen = cbRegTemp;
//
//				/*delete[] szRegTemp;
//				szRegTemp = nullptr;*/
//
//				if (!db::databaseDI::Instance().get_new_regist_user(id))
//				{
//					return;
//				}
//				if (db::databaseDI::Instance().add_user_finger(szLastRegTemplate, nLastRegTempLen, id))
//				{
//					MessageBox(NULL, TEXT("ע����ɣ���ȴ�����Ա���!"), TEXT("��ʾ"), 0);
//					emit regist_succ();
//
//					//delete[] szLastRegTemplate;
//					//szLastRegTemplate = nullptr;
//					//return;
//				}
//
//
//				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Register success"));
//				//SetDlgItemText(IDC_EDIT_RESULT, _T("Register succ"));
//			}
//			else
//			{
//				///strLog.Format(_T("Register fail, because add to db fail, ret=%d"), ret);
//				//SetDlgItemText(IDC_EDIT_RESULT, strLog);
//				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromWCharArray(strLog.GetString()));
//				return;
//			}
//		}
//		else
//		{
//			//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Register fail"));
//			//SetDlgItemText(IDC_EDIT_RESULT, _T("Register fail"));
//			return;
//		}
//	}
//	else
//	{
//		//strLog.Format(_T("You still need press %d times finger"), ENROLLCNT - m_enrollIdx);
//		//SetDlgItemText(IDC_EDIT_RESULT, strLog);
//		//qDebug() << strLog;
//		//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromWCharArray(strLog.GetString()));
//		return;
//	}
//}
//
//void fingerDlg::DoVerify2(unsigned char *pTemplate, int len)
//{
//	if (m_zkfinger == nullptr) {
//		return;
//	}
//
//	//if (m_nLastRegTempLen > 0) // have enroll one more template
//	{
//		if (m_bIdentify) {
//
//			unsigned char szLastLogTemplate2[MAX_TEMPLATE_SIZE] = { 0x0 };
//			int nLastLogTempLen2 = MAX_TEMPLATE_SIZE;
//
//			int ret = ZKFP_ERR_OK;
//			unsigned int tid = 0;
//			unsigned int score = 0;
//
//			int approval = 0;
//			bool success = false;
//			db::databaseDI::Instance().get_approval(approval, common::iUserID);
//			if (approval == 1)
//			{
//				db::databaseDI::Instance().get_user_finger2(szLastLogTemplate2, nLastLogTempLen2, common::iUserID);
//				if (szLastLogTemplate2 && nLastLogTempLen2 != 0)
//				{
//					//QByteArray temp = QStringToChar(QString::fromUtf8(reinterpret_cast<const char*>(szLastLogTemplate2)));
//					//int ret = m_zkfinger->DBMatch(reinterpret_cast<unsigned char*>(temp.data()), QString::fromUtf8(reinterpret_cast<const char*>(nLastLogTempLen2)).length(), pTemplate, len);
//					int ret = m_zkfinger->DBMatch(szLastLogTemplate2, nLastLogTempLen2, pTemplate, len);
//					if (ZKFP_ERR_OK < ret)  //��ʾ����ʧ��  0��ʾ�ɹ�
//					{
//						success = true;
//					}
//				}
//
//				if (success)
//				{
//					emit login_succ();
//					bStopThread = TRUE;
//				}
//				else
//				{
//					MessageBox(NULL, TEXT("ָ����֤ʧ��,����ָ��֤"), TEXT("��ʾ"), 0);
//				}
//			}
//			else
//			{
//				MessageBox(NULL, TEXT("���û�û��ע��ָ��"), TEXT("��ʾ"), 0);
//			}
//		}
//	}
//}

// QString ת unsigned char ����
QByteArray fingerDlg::QStringToChar(const QString& str)
{
	/* ����ֵ��ͨ�����·�ʽʹ�ã� reinterpret_cast<unsigned char*>(byteArray.data()) */
	QByteArray baStr = str.toLatin1();
	QByteArray byteArray = QByteArray::fromBase64(baStr.data());
	return byteArray;
}

// unsigned char ����ת QString
QString fingerDlg::CharToQString(const unsigned char* buffer, int length)
{
	QByteArray ba(reinterpret_cast<const char*>(buffer), length);
	QString str = ba.toBase64();
	return str;
}
