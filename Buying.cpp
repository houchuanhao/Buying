
#include "stdafx.h"
#include "Buying.h"
Buying::Buying()
{
	connect();
	applyNumber = "";
	viewName = _T(ViewName);
	next = NULL;
	applyTime = "";
	teaNum=""; //��ʦ���
	ISBN="";
    num="";    //����ͼ������
    state="";  //����״̬(ͬ�⣬�ܾ���δ����)
    handleTime=""; //����Ա��������

}
void Buying::connect()
{
	::CoInitialize(NULL);
	pConnection.CreateInstance(__uuidof(Connection));
	pRecordset.CreateInstance(__uuidof(Recordset));
	CString user_id = _T(User_ID);
	CString source = _T(Source);
	CString password = _T(PassWord);
	CString str = L"Provider=OraOLEDB.Oracle.1;Data Source=" + source + L";User ID=" + user_id + L";Password=" + password;
//	_bstr_t strConnect = _T("Provider=OraOLEDB.Oracle.1;Data Source=orcl2;User ID=h;Password=h");
	_bstr_t strConnect = str;
	try
	{
		pConnection->Open(strConnect, _T(""), _T(""), adModeUnknown);
		AfxMessageBox(L"���ӳɹ�");
	}
	catch (_com_error e)
	{
		AfxMessageBox(L"����ʧ��");
		exit(0);
	}
}
Buying::Buying(CString TeaNum, CString ISBN1, CString Num, CString ApplyTime, CString State, CString HandleTime)
{
	connect();
	applyNumber = "";
	viewName = _T(ViewName);
	teaNum = TeaNum;
	ISBN = ISBN1;
	num = Num;
	applyTime = ApplyTime;
	state = State;
	handleTime = HandleTime;
}
void Buying::orderApply() //�ύ���룬viewName�ǹ��������ı�����Ĭ��ΪBuy
{
	if (applyTime == L"")
		applyTime = getTime();
	if (state == L"")
		state = "δ����";
		CString sql;
	sql = _T("insert into ") + viewName  + _T("(TeaNum,ISBN,Num,applyTime,state,handleTime) values ('")+ teaNum + _T("','") + ISBN + _T("','") + num + _T("','") + applyTime + _T("','") + state +_T("','")+handleTime+_T("')");
	connect();
	try
	{
		pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		AfxMessageBox(L"������ݳɹ���");
	}
	catch (_com_error &e)
	{
		AfxMessageBox(L"�������ʧ�ܣ�");
	}





}
CString Buying::getTime()
{
	CTime tm; tm = CTime::GetCurrentTime();
	//applyTime = tm.Format("%Y-%m-%d");
	CString str;
	str = tm.Format("%Y-%m-%d");
	return str;
}
Buying * Buying::getApplyBySql(CString sql,int number) //��ȡ�����ʦ�ύ���������룬����ʱ���������������ʽ�����ڴ棬numberΪҪ��ȡ������������numberС��0ʱ��ȡ�������룬numberĬ��Ϊ1
{
	Buying * head = NULL;
	Buying * p = NULL;
	CString view = _T(ViewName);
	CString TeaNum, ISBN1, Num, ApplyTime, State,HandleTime,ApplyNumber;
	//CString SQL = L"Select * from " + view;
	//-------------------------------------------------
	_ConnectionPtr pConnection;//����  
	_RecordsetPtr  pRecordset;//��¼��
	::CoInitialize(NULL);
	pConnection.CreateInstance(__uuidof(Connection));
	pRecordset.CreateInstance(__uuidof(Recordset));
	CString user_id = _T(User_ID);
	CString source = _T(Source);
	CString password = _T(PassWord);
	CString str = L"Provider=OraOLEDB.Oracle.1;Data Source=" + source + L";User ID=" + user_id + L";Password=" + password;
	//	_bstr_t strConnect = _T("Provider=OraOLEDB.Oracle.1;Data Source=orcl2;User ID=h;Password=h");
	_bstr_t strConnect = str;
	try
	{
		pConnection->Open(strConnect, _T(""), _T(""), adModeUnknown);
	}
	catch (_com_error e)
	{
		exit(0);
	}
	//------------------�����������������ݿ�------------------------------
	//���ݿ�����
	//
	_bstr_t bstrPointSQL(sql);
	try
	{
		pRecordset->Open(bstrPointSQL, pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		_variant_t var;
		CString str;
		int count = 0;
		for (int i = 0; i != number; i++)
		{
			if (pRecordset->EndOfFile)
				break;
			count++;
			//CString TeaNum, ISBN, Num, time, state;
			//ApplyNumber = pRecordset->GetCollect(_bstr_t("ApplyNumber"));
			TeaNum = pRecordset->GetCollect(_bstr_t("teaNum"));
			ISBN1 = pRecordset->GetCollect(_bstr_t("ISBN"));
			Num = pRecordset->GetCollect(_bstr_t("Num"));
			ApplyTime = pRecordset->GetCollect(_bstr_t("applyTime"));
			State = pRecordset->GetCollect(_bstr_t("state"));
			HandleTime = pRecordset->GetCollect(_bstr_t("handleTime"));

			str = var.bstrVal;
			str += _T('/n');
			Buying * s = new Buying(TeaNum, ISBN1, Num, ApplyTime, State, HandleTime);
			s->applyNumber = ApplyNumber;
			if (head == NULL)
				head = s;
			else
				p->next = s;
			p = s;
			pRecordset->MoveNext();
		}
		pRecordset->Close();
		return head;
	}
	catch (_com_error  e)
	{
		AfxMessageBox(_T("��ѯʧ��"));
	}
	return p;
}
void Buying::set_teaNum(CString TeaNum)
{
	teaNum = TeaNum;
}
void Buying::set_ISBN(CString ISBN1)
{
	ISBN = ISBN1;
}
void Buying::set_num(CString Num)
{
	num = Num;
}
void Buying::set_State(CString State)
{
	state = State;
}
CString Buying::getTeaNum()
{
	return teaNum;
}
CString Buying::get_TeaNum()
{
	return teaNum;
}
CString Buying::get_ISBN()
{
	return ISBN;
}
CString Buying::get_Num()
{
	return num;
}
CString Buying::get_ApplyTime()
{
	return applyTime;
}
CString Buying::get_State()
{
	return state;
}
CString Buying::get_HandleTime()
{
	return handleTime;
}
CString Buying::getApplyNumber()
{
	return applyNumber;
}
Buying * Buying::getApplyByISBN(CString ISBN1, int number )
{
	CString vname = _T(ViewName);
	Buying * p = NULL;
	CString Sql = L"select * from " + vname + L" where ISBN ='" + ISBN1+L"'";
	p=getApplyBySql(Sql, number);
	return p;
}
Buying * Buying::getApplyByTeaNum(CString TeaNum, int number )
{
	CString vname = _T(ViewName);
	Buying * p = NULL;
	CString Sql = L"select * from " + vname + L" where TeaNum ='" + TeaNum+L"'";

	p = getApplyBySql(Sql, number);
	return p;
}
void Buying::setSql(CString sql,CString str1,CString str2)
{
	//���캯�����Ѿ��������ݿ�
	try
	{
		pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		AfxMessageBox(str1);
	}
	catch (_com_error &e)
	{
		AfxMessageBox(str2);
	}
}
void Buying::drop(CString ApplyNumber)
{
	_ConnectionPtr pConnection;//����  
	_RecordsetPtr  pRecordset;//��¼��
	::CoInitialize(NULL);
	pConnection.CreateInstance(__uuidof(Connection));
	pRecordset.CreateInstance(__uuidof(Recordset));
	CString user_id = _T(User_ID);
	CString source = _T(Source);
	CString password = _T(PassWord);
	CString str = L"Provider=OraOLEDB.Oracle.1;Data Source=" + source + L";User ID=" + user_id + L";Password=" + password;
	//	_bstr_t strConnect = _T("Provider=OraOLEDB.Oracle.1;Data Source=orcl2;User ID=h;Password=h");
	_bstr_t strConnect = str;
	try
	{
		pConnection->Open(strConnect, _T(""), _T(""), adModeUnknown);
	}
	catch (_com_error e)
	{
		exit(0);
	}
	//-----------------���������ݿ����ӣ��Ժ���ܻ�Ҫ�Ż�
	CString sql = L"delete from Buying where ApplyNumber='" + ApplyNumber + "'";

	try
	{
		pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		AfxMessageBox(L"ɾ�����ݳɹ���");
	}
	catch (_com_error &e)
	{
		AfxMessageBox(L"ɾ������ʧ�ܣ�");
	}
}
void Buying::Modify(CString ApplyNumber)
{
	/*
	CString teaNum; //��ʦ���
	CString ISBN;   
	CString applyTime;  //���빺������
	CString num;    //����ͼ������
	CString state;  //����״̬(ͬ�⣬�ܾ���δ����,����)
	CString handleTime; //����Ա��������*/
	CString sql;
	sql = L"Update " + viewName + L" set TeaNum='" + teaNum + L"',ISBN='" + ISBN + L"',ApplyTime='" + applyTime + L"',num='" + num + L"',state='" + state + L"',handleTime='" + handleTime + L"' where ApplyNumber='" + ApplyNumber + L"'";
	setSql(sql,L"�޸ĳɹ�",L"�޸�ʧ��");

}
