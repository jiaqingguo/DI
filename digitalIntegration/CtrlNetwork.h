/*!
 * \file CtrlNetwork.h
 * \date 2018/11/23 14:14
 *
 * \author Mr.Lu
 *
 * \brief 三维观察席与控制软件通信;
 *
 * TODO: long description
 *
 * \note
*/
class CCtrlNetwork
{
public:
	CCtrlNetwork();
	~CCtrlNetwork();
	// 本地监听端口;
	int init(int nLocalPort);
	int recvData(char* recvbuf, int size);
	int sendDataTo(const char* sendbuf, int size, const struct sockaddr* to);
protected:
	unsigned __int64 m_socket;
private:
};