#include "stdafx.h"
#define ViewName "Buying"    //���õ���ͼ/�����
#define Source "orcl2"      //��װ���ݿ�ʱ��������Ǹ�Source
#define User_ID "h"         //���ݿ���û���
#define PassWord "h"        //���ݿ�����
// 1.��ʦ���빺��ͼ��   2.�鿴����״̬(�Լ��������Щ���룬��Щ������ʲô״̬)   3.��������  
/*
��ʦ�����¼����һ�ű�����������6�����ԣ�(�����������ڣ��������ڣ�����״̬�ô�����ʵ��)
��ʦ��� ͼ��ISBN ͼ������  ��������  ����״̬(ͬ�⣬�ܾ���δ����) ��������
create table Buying
(
applyNumber char(20),
teaNum char(20),
ISBN char(20),
applyTime char(20),
num char(20),
state char(20),
handleTime char(20)
);
*/
//�ں��� orderApply��getApply���õ�����ͼ(��)������  Buying
class Buying  //�����¼
{

	_ConnectionPtr pConnection;//����  
	_RecordsetPtr  pRecordset;//��¼��
	CString viewName;  //��ͼ����ֵΪ�궨���е�ViewName
	CString teaNum; //��ʦ���
	CString ISBN;   
	CString applyTime;  //���빺������
	CString num;    //����ͼ������
	CString state;  //����״̬(ͬ�⣬�ܾ���δ����,����)
	CString handleTime; //����Ա��������
	CString applyNumber;
	void set_State(CString State);  //��������״̬��������Ա���Բ���
	//CTimeSpan BuyingTime;
public:
	Buying * next;
	static CString getTime(); //��ȡ��ǰʱ��
	void connect();  //�����������ݿ�
	void setSql(CString str,CString str1=L"",CString str2=L""); //ִ��sql���
	Buying();
	//��������ã�applyTime(����ʱ��)Ĭ��Ϊ��ǰʱ��   ע:getTime()�����ַ������͵ĵ�ǰʱ��
	Buying( CString TeaNum, CString ISBN1, CString Num,CString applyTime,CString state,CString handleTime);
	void get(CString &TeaNum, CString &ISBN1, CString &Num, CString &ApplyTime,CString &State,CString HandleTime);//ͨ�����û�ȡ��ǰ����ĸ�������
	CString getApplyNumber();
	CString get_TeaNum();
	CString get_ISBN();
	CString get_Num();
	CString get_ApplyTime();
	CString get_State();
	CString get_HandleTime();
//	void set_admNum(CString AdmNum);
	void set_teaNum(CString TeaNum);
	void set_ISBN(CString ISBN1);
	void set_num(CString Num);
	CString getTeaNum();
	static Buying * getApplyBySql(CString sql, int number = -1);//����sql����ѯ ����getApplyBySql(_L"select * from Buying where ISBN='3'")
	//��������ɾ�Ĳ�
	void orderApply();  //��������ǰ������Ϣ�ύ��������Ϣ����(��ʦ�ţ�ISBN,����������ʱ�䣬����״̬������ʱ��),���ݿ��Զ�����������
	static void drop(CString ApplyNumber); //ɾ��ɾ�������ΪApplyNumber������
	void Modify(CString ApplyNumber);//�ģ��������ΪapplyNumber��ֵ�޸�Ϊthis��Ӧ��ֵ������Ų���.
	//�����ǲ�
	static Buying * getApplyByISBN(CString ISBN1,int number=-1);//��isbnֵ����������Ԫ�鱣�浽�����У����������ͷ�ڵ�,numberΪҪ��ȡ������������numberС��0ʱ��ȡ�������룬numberĬ��Ϊ-1
	static Buying * getApplyByTeaNum(CString TeaNum, int number = -1);//��TeaNumֵ����������Ԫ�鱣�浽�����У����������ͷ�ڵ�,numberΪҪ��ȡ������������numberС��0ʱ��ȡ�������룬numberĬ��Ϊ-1
	
};