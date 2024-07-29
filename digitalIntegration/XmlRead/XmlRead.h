#pragma once
#include "tinyxml.h"
#include <map>
#include "Util/UtilTool.h"
#include <string>
using namespace std;

struct IPINFO{
	string  Name;
	int Port;
	string IP;
};


class IPINFOFactory
{

public:
	typedef map<UINT,IPINFO*>::iterator  ipiterator;
	IPINFOFactory::IPINFOFactory(void)
	{
		string FileName=UtilTool::getPath();
		FileName+="config\\";
		FileName+="config.xml";
		LoadIPInfo(FileName);
	}

	IPINFOFactory::~IPINFOFactory(void)
	{

	}

	inline void LoadIPInfo(string FileName)
	{
		TiXmlElement *space, *data;

		TiXmlDocument doc(FileName.c_str());
		if (!doc.LoadFile()) return;
		TiXmlElement *root = doc.RootElement();
		for(space = root->FirstChildElement(); space; space = space->NextSiblingElement())
		{
			for(data = space->FirstChildElement(); data; data = data->NextSiblingElement())
			{
				unsigned char IPArrary[4];
				unsigned int *i=NULL;
				i=(unsigned int  *)IPArrary;
				IPINFO * pipinfo=new IPINFO(); 
				pipinfo->IP=data->Attribute("IP");
				pipinfo->Name=data->Attribute("Name");
				pipinfo->Port=atoi(data->Attribute("NodePort"));
				ipinfos[pipinfo->Name]=pipinfo;
			}
		}
	}


	

	inline IPINFO * GetIPInfo(string infoname){
		if (ipinfos.find(infoname)!=ipinfos.end())
		{
			return ipinfos[infoname];
		}else
			return NULL;
	}
  
	 inline DWORD GetIP(string infoname){
		 IPINFO * pipinfo=GetIPInfo(infoname);
		 if (pipinfo)
		 {
			 return inet_addr(pipinfo->IP.c_str());
		 }else
			 return 0;
	 }
private:

	map<string,IPINFO*>  ipinfos;
};

