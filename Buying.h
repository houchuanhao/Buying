#include "stdafx.h"
#define ViewName "Buying"    //作用的视图/表的名
#define Source "orcl2"      //安装数据库时让输入的那个Source
#define User_ID "h"         //数据库的用户名
#define PassWord "h"        //数据库密码
// 1.教师申请购买图书   2.查看申请状态(自己提出了哪些申请，哪些被处于什么状态)   3.撤销申请  
/*
教师申请记录存在一张表里，表包括以下6个属性，(其中申请日期，处理日期，申请状态用触发器实现)
教师编号 图书ISBN 图书数量  申请日期  申请状态(同意，拒绝，未处理) 处理日期
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
//在函数 orderApply和getApply中用到了视图(表)的名称  Buying
class Buying  //购买记录
{

	_ConnectionPtr pConnection;//连接  
	_RecordsetPtr  pRecordset;//记录集
	CString viewName;  //视图名，值为宏定义中的ViewName
	CString teaNum; //教师编号
	CString ISBN;   
	CString applyTime;  //申请购买日期
	CString num;    //购买图书数量
	CString state;  //申请状态(同意，拒绝，未处理,撤销)
	CString handleTime; //管理员处理日期
	CString applyNumber;
	void set_State(CString State);  //设置申请状态，仅管理员可以操作
	//CTimeSpan BuyingTime;
public:
	Buying * next;
	static CString getTime(); //获取当前时间
	void connect();  //用于连接数据库
	void setSql(CString str,CString str1=L"",CString str2=L""); //执行sql语句
	Buying();
	//如果不设置，applyTime(申请时间)默认为当前时间   注:getTime()返回字符串类型的当前时间
	Buying( CString TeaNum, CString ISBN1, CString Num,CString applyTime,CString state,CString handleTime);
	void get(CString &TeaNum, CString &ISBN1, CString &Num, CString &ApplyTime,CString &State,CString HandleTime);//通过引用获取当前对象的各个属性
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
	static Buying * getApplyBySql(CString sql, int number = -1);//按照sql语句查询 例如getApplyBySql(_L"select * from Buying where ISBN='3'")
	//下面是增删改查
	void orderApply();  //增，将当前申请信息提交，申请信息包括(教师号，ISBN,数量，申请时间，处理状态，处理时间),数据库自动生成申请编号
	static void drop(CString ApplyNumber); //删，删除申请号为ApplyNumber的申请
	void Modify(CString ApplyNumber);//改，将申请号为applyNumber的值修改为this对应的值，申请号不变.
	//下面是查
	static Buying * getApplyByISBN(CString ISBN1,int number=-1);//将isbn值符合条件的元组保存到链表中，返回链表的头节点,number为要获取的申请数量，number小于0时获取所有申请，number默认为-1
	static Buying * getApplyByTeaNum(CString TeaNum, int number = -1);//将TeaNum值符合条件的元组保存到链表中，返回链表的头节点,number为要获取的申请数量，number小于0时获取所有申请，number默认为-1
	
};