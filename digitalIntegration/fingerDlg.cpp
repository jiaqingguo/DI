//#pragma comment (lib, "User32.lib")

#include "fingerDlg.h"

//HANDLE m_hDBCache = NULL;
HANDLE m_hDevice = NULL;
//HANDLE m_hThreadWork = NULL;
bool m_bRegister = FALSE;
//bool m_bStopThread = FALSE;
//unsigned char* m_pImgBuf = NULL;
//int m_imgFPWidth;
//int m_imgFPHeight;

bool m_bIdentify = FALSE;
int m_enrollIdx=0;
int m_score=0;

//unsigned char m_arrPreRegTemps[ENROLLCNT][MAX_TEMPLATE_SIZE];  //3  2048   �洢ָ��
//unsigned int m_arrPreTempsLen[3];
//int m_Tid = 1;   //ָ�� ID��>0 �� 32 λ�޷���������


//Last register template, use for verify   ��һ��ע��ģ�壬������֤
//unsigned char m_szLastRegTemplate[MAX_TEMPLATE_SIZE];
//int m_nLastRegTempLen;
//int m_nFakeFunOn;




fingerDlg::fingerDlg(QDialog* pParent /*=NULL*/)
{
	hDBCache=NULL;
	//hDevice=NULL;
	bStopThread = FALSE;
	//bRegister = FALSE;
	hThreadWork = NULL;
	pImgBuf=NULL;
	Tid=1;   //ָ�� ID��>0 �� 32 λ�޷���������
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
		nLastRegTempLen = 0;
		//GetDlgItem(IDC_BTN_CONN)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_DISCONN)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_REG)->EnableWindow(TRUE);
		//(IDC_BTN_DBCLEAR)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_VERIFY)->EnableWindow(TRUE);
		//GetDlgItem(IDC_BTN_IDENTIFY)->EnableWindow(TRUE);
		hThreadWork = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadCapture, this, 0, NULL);
		memset(&szLastRegTemplate, 0x0, sizeof(szLastRegTemplate));
		qDebug() << "Init ZKFPM success";
		////SetDlgItemText(IDC_EDIT_RESULT, _T("Init Succ"));
		Tid = 1;
		m_enrollIdx = 0;
		m_bRegister = FALSE;
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
			unsigned char szTemplate[MAX_TEMPLATE_SIZE]; //���ص�ָ��ģ��
			unsigned int tempLen = MAX_TEMPLATE_SIZE;    //Ԥ���� fpTemplate �ڴ��С2048

			//�ɼ�ָ�ƣ�ָ��ģ��
			int ret = ZKFPM_AcquireFingerprint(m_hDevice, pDlg->pImgBuf, pDlg->imgFPWidth*pDlg->imgFPHeight, szTemplate, &tempLen);
			//qDebug() << "1111111111111111111111111111111" << ret;
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


/*void fingerDlg::finger_passing_arguments(HANDLE &hDevice, bool bRegister)
{
	hDevice = m_hDevice;
	bRegister = m_bRegister;
}*/


void fingerDlg::DoRegister(unsigned char* temp, int len)
{
	//CString strLog;

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
		unsigned char szRegTemp[MAX_TEMPLATE_SIZE] = { 0x0 };  //�Ǽ�ģ��
		unsigned int cbRegTemp = MAX_TEMPLATE_SIZE;          //ģ�峤��

		//�� 3 öԤ�Ǽ�ָ��ģ��ϲ�Ϊһö�Ǽ�ָ��
		ret = ZKFPM_DBMerge(hDBCache, arrPreRegTemps[0], arrPreRegTemps[1], arrPreRegTemps[2], szRegTemp, &cbRegTemp);
		m_enrollIdx = 0;
		m_bRegister = FALSE;
		if (ZKFP_ERR_OK == ret)   //ZKFP_ERR_OK=�����ɹ�
		{
			//��ӵǼ�ָ��ģ�嵽������
			ret = ZKFPM_DBAdd(hDBCache, Tid++, szRegTemp, cbRegTemp);
			if (ZKFP_ERR_OK == ret)
			{
				memcpy(szLastRegTemplate, szRegTemp, cbRegTemp);
				
				nLastRegTempLen = cbRegTemp;    
				//�ֽ���ת����Base64�ַ���
				//unsigned int base64str_len = (cbRegTemp * 4 + 4) / 3;
				//char *base_str = new char[base64str_len + 1];
				//memset(base_str, 0, base64str_len + 1);
				//int ret = 0;

				//Base64�ַ���ת�����ֽ���
				//const char *base_str;

				//if(ret = ZKFPM_BlobToBase64(reinterpret_cast<unsigned char *>(szRegTemp), cbRegTemp,base_str, base64str_len + 1))
				//{
				//if (ret = ZKFPM_Base64ToBlob(base_str, szLastRegTemplate, nLastRegTempLen))
				//{
					table_fingerprint stfinger;
					//memset(&stfinger, 0, sizeof(stfinger));
					//std::string a(reinterpret_cast<const char*>(szLastRegTemplate), nLastRegTempLen);
				    //memcpy(szLastRegTemplate2, reinterpret_cast<const char*>(a.data()), nLastRegTempLen);

					//stfinger.fingerdata = std::string(reinterpret_cast<const char*>(szLastRegTemplate),nLastRegTempLen);


					//memcpy(stfinger.fingerdata, szLastRegTemplate, nLastRegTempLen);
					//memcpy(stfinger.fingerdata, szRegTemp, cbRegTemp);


					//stfinger.fingerlen = nLastRegTempLen;


					//char temp[] = {0};
					//sprintf(temp, "insert into t_fingerprint(fingerData,fingerLen) values(\'%s\',\'%d\')");

					if (!db::databaseDI::Instance().add_user_finger(szLastRegTemplate, nLastRegTempLen))
					{
						return;
					}
					//}
				//}

				MessageBox(NULL, TEXT("ע����ɣ���ȴ�����Ա���!"), TEXT("��ʾ"), 0);
				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("Register success"));
				//SetDlgItemText(IDC_EDIT_RESULT, _T("Register succ"));
			}
			else
			{
				///strLog.Format(_T("Register fail, because add to db fail, ret=%d"), ret);
				//SetDlgItemText(IDC_EDIT_RESULT, strLog);
				//QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromWCharArray(strLog.GetString()));
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
	}
}

void fingerDlg::DoVerify(unsigned char *temp, int len)
{	
	//if (m_nLastRegTempLen > 0)	//have enroll one more template
	//{
		//CString strLog;
		if (m_bIdentify)   //ʶ��ť�����
		{
			int ret = ZKFP_ERR_OK;
			unsigned int tid = 0;
			unsigned int score = 0;
			//ret = ZKFPM_DBIdentify(hDBCache, temp, len, &tid, &score);//ָ�� 1:N ʶ��tempָ��ģ��  ���� ָ��id���Աȷ���

			//ret = ZKFPM_DBAdd(hDBCache, Tid++, temp, len);

			std::list<table_fingerprint> m_finger;
			//m_finger.clear();
			db::databaseDI::Instance().get_user_finger(m_finger);
			for (auto &m_f : m_finger)
			{
				memcpy(szLastRegTemplate2, reinterpret_cast<const char*>(m_f.fingerdata.c_str()), m_f.fingerlen);
				nLastRegTempLen2 = m_f.fingerlen;
				szLastRegTemplate2[nLastRegTempLen2 + 1] = '\0';
				
				//std::string a(reinterpret_cast<const char*>(szLastRegTemplate), nLastRegTempLen);
				//memcpy(szLastRegTemplate2, reinterpret_cast<const char*>(a.data()), nLastRegTempLen);
				//ret = ZKFPM_DBMatch(hDBCache, szLastRegTemplate2, nLastRegTempLen2, szLastRegTemplate, nLastRegTempLen);

				//ret = ZKFPM_DBMatch(hDBCache, szLastRegTemplate2, nLastRegTempLen2, temp,len);
				//ret = ZKFPM_DBIdentify(hDBCache, m_f.fingerdata, m_f.fingerlen, &tid, &score);
				if (ZKFP_ERR_OK >= ret)  //��ʾ����ʧ��  0��ʾ�ɹ�
				{
					//strLog.Format(_T("Identify fail, ret = %d"), ret);
					//SetDlgItemText(IDC_EDIT_RESULT, strLog);
					MessageBox(NULL, TEXT("��¼ʧ��"), TEXT("��ʾ"), 0);
				}
				else
				{
				//	strLog.Format(_T("Identify succ, tid=%d, score=%d"), tid, m_score);
					//SetDlgItemText(IDC_EDIT_RESULT, strLog);
					MessageBox(NULL, TEXT("��¼�ɹ�"), TEXT("��ʾ"), 0);
				}
			}
			
		}
		else  //��֤��ť���
		{//�ȶ���öָ���Ƿ�ƥ��  ָ��ģ��1 ����  ָ��ģ��2 ����       ����ֵ ���  ���ڵ���0�Ļ����ǱȶԷ���  С��0����
			int ret = ZKFPM_DBMatch(hDBCache, szLastRegTemplate, nLastRegTempLen, temp, len);
			if (ZKFP_ERR_OK > ret)  //ret��ʾ���ǱȶԷ���
			{
				//strLog.Format(_T("Match finger fail, ret = %d"), ret);
				//SetDlgItemText(IDC_EDIT_RESULT, strLog);
			}
			else
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