// 大作业.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"iostream"
#include"string"
using namespace std;

class student{
private:
	int pnumber;
	string pname;
	string pgender;
	string pmajor;
	string pcourse1;
	int pxuefen1;
	int pscore1;
	string pcourse2;
	int pxuefen2;
	int pscore2;
	double pgpa;
public:
	
	student * next;
	
	student* zbset() {//建立总表
		int number;
		string name;
		string gender;
		string major;
		string course1;
		int xuefen1;
		int score1;
		string course2;
		int xuefen2;
		int score2;
		double gpa;
		student *head,*tail,*newstudent=new student;	
		head = new student;//哨兵
		tail = head;
		while (1) {
			cout << "请输入7位学号（输入9时结束建表）:";
			cin>>number;
			if (number == 9) {
				tail->next = NULL;
				break;
			}
			else {
				tail->next = newstudent;
				newstudent->pnumber = number;
				cout << "请输入姓名：";
				cin >> name;
				newstudent->pname= name;
				cout << "请输入性别：";
				cin >> gender;
				newstudent->pgender = gender;
				cout << "请输入专业：";
				cin >> major;
				newstudent->pmajor = major;
				cout << "请输入课程1名称：";
				cin >> course1;
				newstudent->pcourse1 = course1;
				cout << "请输入课程1学分：";
				cin >> xuefen1;
				newstudent->pxuefen1 = xuefen1;
				cout << "请输入成绩1：";
				cin >> score1;
				newstudent->pscore1 = score1;
				cout << "请输入课程2名称：";
				cin >> course2;
				newstudent->pcourse2 = course2;
				cout << "请输入课程2学分：";
				cin >> xuefen2;
				newstudent->pxuefen2 = xuefen2;
				cout << "请输入成绩2：";
				cin >> score2;
				newstudent->pscore2 = score2;
				newstudent->pgpa=((xuefen1*((score1 - 60) / 10 + 2)) + xuefen2*((score2 - 60) / 10 + 2))*1.00/(xuefen1+xuefen2);				
				tail = newstudent;
				newstudent = new student;
			}
		}
		return head;
	}


	student*xxbset(student*zbhead) {//建立信息表
		student *head, *tail, *newstudent = new student;
		head = new student;//哨兵
		student*q = zbhead;
		q = q->next;
		tail = head;
		while(q!=NULL){
			newstudent->pnumber = q->pnumber;
			newstudent->pname = q->pname;
			newstudent->pgender = q->pgender;
			newstudent->pmajor = q->pmajor;
			newstudent->pgpa = q->pgpa;
			tail->next = newstudent;
			tail = newstudent;
			newstudent = new student;
			q = q->next;
		}
		return head;
	}

	void xxbwrite(student*xxbhead){//信息表写入文件	
		FILE *fp1;
		if (fopen_s(&fp1, "信息表", "wb") != 0)
		{
			cout << "信息表文件保存失败" << endl;
			fclose(fp1);
		}
		student*q = xxbhead;
		while (q != NULL) {
			fwrite(q, sizeof(student), 1, fp1);
			q = q->next;
		}
		fclose(fp1);
	}

	student*cjbset(student*zbhead) {//建立成绩表
		student *head, *tail, *newstudent = new student;
		head = new student;//哨兵
		student*q = zbhead;
		q = q->next;
		tail = head;
		while (q != NULL) {
			newstudent->pnumber = q->pnumber;
			newstudent->pcourse1 = q->pcourse1;
			newstudent->pxuefen1 = q->pxuefen1;
			newstudent->pscore1 = q->pscore1;
			newstudent->pcourse2 = q->pcourse2;
			newstudent->pxuefen2 = q->pxuefen2;
			newstudent->pscore2 = q->pscore2;
			tail->next = newstudent;
			tail = newstudent;
			newstudent = new student;
			q = q->next;
		}
		return head;
		cout << "成绩表建立完毕" << endl;
	}

	void cjbwrite(student*cjbhead) {//成绩表写入文件	
		FILE *fp1;
		if (fopen_s(&fp1, "成绩表", "wb") != 0)
		{
			cout << "成绩表文件创立失败" << endl;
			fclose(fp1);
		}
		student*q = cjbhead;
		while (q != NULL) {
			fwrite(q, sizeof(student), 1, fp1);
			q = q->next;
		}
		fclose(fp1);
	}

	student* xxbread() {//从文件恢复信息表
		FILE*fp;
		student*head, *tail, *q;
		q = new student;
		head = q;
		tail = head;
		if ((fopen_s(&fp,"信息表", "rb")) != NULL)
		cout << "信息表文件读取成功！";
		rewind(fp);
		while (!feof(fp))
		{
			tail->next = q;
			fread(q, sizeof(student), 1, fp);
			tail= q;
			q = new student;						
		}
		student*p = head;
		p = p->next;
		student*n=head;
		while (p != NULL) {
			if (p->pnumber == 0) {
				n->next = p->next;
			}
			n = p;
			p = p->next;
		}
		fclose(fp);
		return head;
	}
	student* cjbread() {//从文件恢复成绩表
		FILE*fp;
		student*head, *tail, *q;
		q = new student;
		head = q;
		tail = head;
		if ((fopen_s(&fp, "成绩表", "rb")) != NULL)
		cout << "成绩表文件读取成功！";
		rewind(fp);
		while (!feof(fp))
		{
			tail->next = q;
			fread(q, sizeof(student), 1, fp);
			tail = q;
			q = new student;
		}
		student*p = head;
		p = p->next;
		student*n = head;
		while (p != NULL) {
			if (p->pnumber == 0) {
				n->next = p->next;
			}
			n = p;
			p = p->next;
		}
		fclose(fp);
		return head;
	}
	
	student*newset() {//建立插入学生总信息节点
		int number;
		string name;
		string gender;
		string major;
		string course1;
		int xuefen1;
		int score1;
		string course2;
		int xuefen2;
		int score2;
		double gpa;
		cout << "请输入7位学号:";
		cin >> number;
		if (number > 9999999 || number < 1000000)
		{
			cout << "学号输入无效" << endl;
			return NULL;
		}
		else {
			student*head = new student;
			head->pnumber = number;
			cout << "请输入姓名：";
			cin >> name;
			head->pname = name;
			cout << "请输入性别：";
			cin >> gender;
			head->pgender = gender;
			cout << "请输入专业：";
			cin >> major;
			head->pmajor = major;
			cout << "请输入课程1名称：";
			cin >> course1;
			head->pcourse1 = course1;
			cout << "请输入课程1学分：";
			cin >> xuefen1;
			head->pxuefen1 = xuefen1;
			cout << "请输入成绩1：";
			cin >> score1;
			head->pscore1 = score1;
			cout << "请输入课程2名称：";
			cin >> course2;
			head->pcourse2 = course2;
			cout << "请输入课程2学分：";
			cin >> xuefen2;
			head->pxuefen2 = xuefen2;
			cout << "请输入成绩2：";
			cin >> score2;
			head->pscore2 = score2;
			gpa = ((xuefen1*((score1 - 60) / 10 + 2)) + xuefen2 * ((score2 - 60) / 10 + 2))*1.00 / (xuefen1 + xuefen2);
			head->pgpa = gpa;
			head->next = NULL;
			return head;
		}	
	}

     student*add(student*chain,student*node) {//新节点筛选信息添加在信息表头
		 student*p= new student;
		 node->next = chain->next;
		 p->next = node;
		return p;
	}

	void xxbprint(student*head) {//显示信息表
		cout << "学号"<< '\t';
		cout <<"姓名"<< '\t';
		cout << "性别" << '\t';
		cout <<"专业" << '\t';
		cout <<"平均绩点" << endl;
		student*p = head;
		p = p->next;
		while (p != NULL) {
			cout <<p->pnumber << '\t';
			cout <<p->pname << '\t';
			cout << p->pgender << '\t';
			cout << p->pmajor<< '\t';
			cout << p->pgpa << endl;
			p = p->next;
		}
	}
	void cjbprint(student*head) {//显示成绩表
		cout << "学号" << '\t';
		cout << "课程1" << '\t';
		cout << "学分1" << '\t';
		cout << "成绩1" << '\t';
		cout << "课程2" << '\t';
		cout << "学分2" << '\t';
		cout << "成绩2" << endl;
		student*p = head;
		p = p->next;
		while (p != NULL) {
			cout << p->pnumber << '\t';
			cout << p->pcourse1 << '\t';
			cout << p->pxuefen1 << '\t';
			cout << p->pscore1 << '\t';
			cout << p->pcourse2 << '\t';
			cout << p->pxuefen2 << '\t';
			cout << p->pscore2 << endl;
			p = p->next;
		}
	}
	student* dismiss(student*head,int n) {//标记所有符合条件的记录，在下一次读取时跳过，实现删除功能
		student*p = head->next;
		student*q = head;
		while (p != NULL && p->pnumber != n){
			q = p;
			p = p->next;
		}
		if (p != NULL) {
			p->pnumber = 0;
			cout << "删除成功" << endl;
		}
		else
			cout << "未找到对应的记录" << endl;
		return head;
	 }

	void  arrange(student*chain) {
		student *p, *m, *n,*q,*temp=NULL;
		p = chain, m = chain,n=p->next,q=n->next;
		while (m != NULL) {
			while (q != NULL)
			{
				if ((n->pnumber) >(q->pnumber)) {
					temp = n;	
					temp->next = q->next;
					n=q;
					p->next = n;
					q = temp;
					n->next = q;
				}
				p =n;
				n = q;
				q = q->next;
			}
			m = m->next;
			p = chain;
			n = p->next;
			q = n->next;
		}
		cout << "排序成功！" << endl;
	}
	void cjbselect(student*head,int n) {
		student*p=head;
		while (p != NULL && p->pnumber != n) {
			p = p->next;
		}
		if (p != NULL) {
			cout << "已修总学分=";
			cout << p->pxuefen1 + p->pxuefen2 << endl;
		}
		else cout << "未找到该学号" << endl;
	}
	void xxbselect(student*head,int n) {
		student*p=head;
		while (p != NULL && p->pnumber != n) {
			p = p->next;
		}
		if (p != NULL) {
			cout << "学号" << '\t';
			cout << "姓名" << '\t';
			cout << "性别" << '\t';
			cout << "专业" << '\t';
			cout << "平均绩点" << endl;
			cout << p->pnumber << '\t';
			cout << p->pname << '\t';
			cout << p->pgender << '\t';
			cout << p->pmajor << '\t';
			cout << p->pgpa << endl;
		}
		else cout << "未找到该学号" << endl;
	}
	void cselect(student*cjbhead,student*xxbhead, string m) {
		student*p = cjbhead;
		student*q = xxbhead;
		cout << "学号" << '\t' << "姓名" << '\t' << "专业" << '\t' << "成绩" << endl;
		while (p != NULL) {
			if (p->pcourse1 == m) {
				while (q != NULL) {
					if (q->pnumber == p->pnumber) {
						cout << p->pnumber << '\t' << q->pname << '\t' << q->pmajor << '\t' << p->pscore1 << endl;
					}
					q = q->next;
				}
				q = xxbhead;
			}
			if (p->pcourse2 == m) {
				while (q != NULL) {
					if (q->pnumber == p->pnumber) {
						cout << p->pnumber << '\t' << q->pname << '\t' << q->pmajor << '\t' << p->pscore2 << endl;
					}
					q = q->next;
				}
				q = xxbhead;
			}
			p = p->next;
		}
	}
};

int main()
{
	student ms;
	student*zbhead, *xxbhead, *cjbhead;
	int n;
	cout << "是否要建立新表？建立新表请输入1，读取已有记录输入其他数字：";
	cin >> n;
	if(n==1){//新建表
		zbhead=ms.zbset();
		xxbhead=ms.xxbset(zbhead);
		cjbhead=ms.cjbset(zbhead);
		ms.xxbwrite(xxbhead);
		ms.cjbwrite(cjbhead);
		xxbhead = ms.xxbread();
		cjbhead = ms.cjbread();
	}
	else {//读取文件
		xxbhead = ms.xxbread();
		cjbhead = ms.cjbread();
	}
	n = 1;
	cout << "操作列表" << endl;
	cout << "1 增加记录" << endl;
	cout << "2 删除记录" << endl;
	cout << "3 排序" << endl;
	cout << "4 按学号查找学生信息" << endl;
	cout << "5 按课程查找学生信息" << endl;
	cout << "9 显示当前表格" << endl;
	cout << "0 结束使用" << endl;
	while (n != 0) {
		cout << "请选择需要使用的操作:";
		cin >> n;
		switch (n) {
		case 1: {
			student*newhead = ms.newset();
			ms.xxbwrite(ms.add(xxbhead, newhead));
			ms.cjbwrite(ms.add(cjbhead, newhead));
			cout << "添加完成" << endl;

		}break;
		case 2: {
			int m;
			cout << "请输入要删除的学号：";
			cin >> m;
			ms.dismiss(xxbhead, m);
			ms.dismiss(cjbhead, m);
			ms.xxbwrite(xxbhead);
			ms.cjbwrite(cjbhead);
		}break;
		case 3: {
			ms.arrange(xxbhead);
			ms.arrange(cjbhead);
			ms.xxbwrite(xxbhead);
			ms.cjbwrite(cjbhead);
		}break;
		case 4: {
			cout << "请输入要查找的学号：";
			int n;
			cin >> n;
			ms.xxbselect(xxbhead,n);
			ms.cjbselect(cjbhead,n);
		}break;
		case 5: {
			string m;
			cout << "请输入要查询的课程名：";
			cin >> m;
			ms.cselect(cjbhead, xxbhead, m);
		}break;
		case 9: {
			ms.xxbprint(xxbhead);
			ms.cjbprint(cjbhead);
		}; break;
		case 0: {
			cout << "欢迎下次使用" << endl;
		}; break;
		default:cout << "错误输入" << endl;
		}
		xxbhead = ms.xxbread();
		cjbhead = ms.cjbread();
	}
    return 0;
}

