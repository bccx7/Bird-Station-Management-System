#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include<math.h>
#define openday "2025-05-18"//��ҵ

typedef struct User {
	char ID[20];//�˺�
	char password[20];//����
	char name[20];//����
	double money;//���
	int vip;//��Ա�ȼ�
	int times;//��ȡ������
}USE;//�û���Ϣ
typedef struct Package{
	int type=0;//1Ϊ��ȡ��2Ϊ��ȡ��3Ϊ�Ѽĳ�,4Ϊ�������,5Ϊδ�ĳ�6Ϊ��ȡ7Ϊ��ʧ
	int number=0;//����
	char ID[20];//�����û�ID
	int position[4];//����λ��,a[0]��ʾ����ABC,ֵ�ֱ�Ϊ0 1 2����[1]��ʾi������,a[2]��ʾj������
	//����Ϊ�ļ�ʱ��Ҫ��д����Ϣ
	double volume = 0;//���
	double weight = 0;//����
	char place[150];//�ʼ�Ŀ�ĵ�
	char company[20];
	char time1[50];//����ȡ��ʱ��
	char time2[50];//���ʱ��
	char time3[50];//�ļ�ʱ��
}PAC;//�����Ϣ
typedef struct Node1 {
	USE users;
	struct Node1* next;
}Node1;//�û�����
typedef struct Node2 {
	PAC packages;
	struct Node2* next;
}Node2;//�������
Node1* ptr1 = NULL;
Node1* head1 = NULL;
Node2* ptr2 = NULL;
Node2* head2 = NULL;
Node1* USER = NULL;//��ǰ�û�
int first = 0;//�Ƿ��һ��ʹ��
int pro = 0;//��¥����
int usercount = 0;//�û�����
int paccount = 0;//�������
char power = '0';//Ȩ�޿���
char USEID[40] = { "\0" };//�û����ʶ��
float nowmoney = 0;//��ǰ���
char nowday[50];//��ǰ����
char date[50];//�ϴδ��ļ�������
int a[4][4] = { 0 };//����a��b��c��Ϣ
int b[4][4] = { 0 };
int c[4][4] = { 0 };

void LoginInterface();//��¼����
void StaffMenu();//����Ա�˵�
void UserMenu();//�û��˵�
void PickUp_Package();//ȡ��
void Send_Package();//�ļ�
void InformationService();//��Ϣ����
void Notice();//֪ͨ
void Bill();//�˵�
void Wallet();//Ǯ��
void UserManagement();//�û�����
void OutboundManagement();//�������
void EnterboundManagement();//������
void DataStatistic();//����ͳ��
void WarehouseSituation();//�ֿ����
void lose();//��ʧ
void PackageSendingManagement();//�ļ�����
void View_AllUsers();//�鿴�����û�
void Modify_User();//�޸��û���Ϣ
void Find_User();//�����û�
void Delete_User();//ɾ���û�
void undealoutmessage();//δ����ĳ�������
void Modify_Package();//�޸Ŀ����Ϣ
void Find_Package();//���ҿ��
void BatchInput();//�������
void BatchDelete();//����ɾ��
void EmptyPage1();//��ҳ��1
void EmptyPage2();//��ҳ��2
void EmptyPage3();//��ҳ��3
void EmptyPage4();//��ҳ��4
void InboundStatistic();//���ͳ��
void OutboundStatistic();//����ͳ��
void PackageSendingStatistic();//�ļ�ͳ��
void FinanceStatistic();//����ͳ��
void SelectPackage_toOutbound();//ѡ���ݳ���
void PendingInformation();//�ļ���������Ϣ
void SelectPackage_toSendOut();//ѡ���ݼļ�
void Recharge();//��ֵ

void UserLogin();//�û���¼
void Add_User();//����û�
void StaffLogin();//����Ա��¼
void ReadFromFile1();//��ȡ�û���Ϣ
void ReadFromFile2();//��ȡ�����Ϣ
void ReadFromFile3();//��ȡ�����Ϣ
void SetSTAPassword();//���ù���Ա����
void wcharTochar(const wchar_t* wchar, char* chr, int length);//���ַ�תխ�ַ�
void charTowchar(const char* chr, wchar_t* wchar, int size);//խ�ַ�ת���ַ�
void WriteUserToFile();//д���û���Ϣ
void WritePacToFile();//д������Ϣ
void WriteMoneyToFile();//д�������Ϣ
void release1(Node1* head1);//�ͷ��û�����
void release2(Node2* head2);//�ͷſ������
void ProService();//��¥����
void ModifyPassword();//�޸�����

int Find_User_ByID(char* user);//����ID�����û�
int Find_Pac_ByNumber(char* pac);//���ݵ��Ų��ҿ��
void stapassward();//���ù���Ա����
void View_AllPackages();//�鿴���п��
int autoputin(int a[4][4], Node2* k);//�Զ����
void autoputout(Node2* k);//�Զ�����
int ifblank(char* a);//�ж��Ƿ�Ϊ��
int ifnonumber(char* a);//�ж��Ƿ�Ϊ����
int ifnonumber2(char* a);//�ж��Ƿ�Ϊ����
void getCurrentTimeAsString(char* buffer, size_t bufferSize);//��ȡ��ǰʱ��
void putimage1(int a1, int b, int a[4][4], int x, int y);//������
void getCurrentDate(char* dateStr);//��ȡ��ǰ����
int istoday(Node2* p);//�ж��Ƿ�Ϊ����
int istoday2(Node2* p);//�ж��Ƿ�Ϊ����
int ismonth(Node2* p);//�ж��Ƿ�Ϊ����
int ismonth2(Node2* p);//	�ж��Ƿ�Ϊ����
int isthreemonth();//�ж��Ƿ�Ϊ������
int getnumber();//��ȡ��ݵ���
int getmoney(Node2* p);//��ȡ��ݷ���
int calculateDateDifference(char* date1, char* date2);//�������ڲ�
void linear_regression(float x[], float y[], int n, float* slope, float* intercept);//���Իع�
void CountPackagesLast7Days1(float num[7], float day[7]);//ͳ�ƽ�7���������
void CountPackagesLast7Days2(float num[7], float day[7]);//ͳ�ƽ�7���������
void CountPackagesLast7Days3(float num[7], float day[7]);//ͳ�ƽ�7��ļ�����
void CountPackagesLast7Days4(float num[7], float day[7]);//ͳ�ƽ�7������
void DrawLineChart(float num[7], float day[7], int x, int y, int width, int height);//������ͼ

void WarehouseWriteA(int a[4][4]);//д�����A
void WarehouseWriteB(int b[4][4]);//д�����B
void WarehouseWriteC(int c[4][4]);//д�����C
void WarehouseReadA(int a[4][4]);//��ȡ����A
void WarehouseReadB(int b[4][4]);//��ȡ����B
void WarehouseReadC(int c[4][4]);//��ȡ����C
int main()
{
	getCurrentDate(nowday);
	ReadFromFile3();
	nowmoney += 50* calculateDateDifference(nowday, date);
	WriteMoneyToFile();
	initgraph(1366, 768, EX_NOCLOSE);
	HWND hwnd;// ���ô��ھ���������洰����Ϣ
	hwnd = GetHWnd();// ��ȡ���ھ��
	SetWindowText(hwnd, L"������վ����ϵͳ1.0");
	ReadFromFile1();
	ReadFromFile2();
	LoginInterface();
	system("pause");
	return 0;
}

void LoginInterface() 
{
	cleardevice();
	IMAGE img;
	loadimage(&img,_T( "./image/1.png"), 1366, 768);
	putimage(0, 0, &img);
	//������¼�����
	MOUSEMSG msg;// ������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������	
	while (1)
	{ // ��ѭ�� ѭ�����������Ϣ
		while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
		{
			msg = GetMouseMsg();// ��ȡ�����Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 561 && msg.x <= 783 && msg.y >= 341 && msg.y <= 425) {

				UserLogin();
				UserMenu();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 561 && msg.x <= 783 && msg.y >= 499 && msg.y <= 594) {

				StaffLogin();
				StaffMenu();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 616 && msg.x <= 771 && msg.y >= 690 && msg.y <= 710) {
				WriteUserToFile();
				WritePacToFile();
				WriteMoneyToFile();
				release1(head1);
				release2(head2);
				closegraph();
				goto label;
			}
		}
	}
label:return;
}//

  void StaffMenu()
  {
	 pro = 0;
	 cleardevice();
	IMAGE img;
	loadimage(&img, _T("./image/2.png"), 1366, 768);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, L"����");
	wchar_t qw[50];
	charTowchar(nowday, qw, 50);
	outtextxy(1161, 63, qw);
	//������¼�����
	MOUSEMSG msg;// ������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������	
	while (1)
	{ // ��ѭ�� ѭ�����������Ϣ
		while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
		{
			msg = GetMouseMsg();// ��ȡ�����Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 181 && msg.y <= 286) {

				UserManagement();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 356 && msg.y <= 452) {

				WarehouseSituation();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 524 && msg.y <= 623) {

				DataStatistic();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 754 && msg.x <= 979 && msg.y >= 181 && msg.y <= 286) {

				EnterboundManagement();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 754 && msg.x <= 979 && msg.y >= 530 && msg.y <= 624) {

				PackageSendingManagement();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 754 && msg.x <= 979 && msg.y >= 356 && msg.y <= 452) {

				OutboundManagement();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 47 && msg.x <= 137 && msg.y >= 712 && msg.y <= 745) {

				stapassward();

			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

				LoginInterface();
				goto label;
			}
		}
	}
label:return;

}

    void UserManagement() {
	cleardevice();
	IMAGE img;
	loadimage(&img, _T("./image/3.png"), 1366, 768);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, L"����");
	wchar_t qw[50];
	charTowchar(nowday, qw, 50);
	outtextxy(1161, 63, qw);
	//������¼�����
	MOUSEMSG msg;// ������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������	
	while (1)
	{ // ��ѭ�� ѭ�����������Ϣ
		while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
		{
			msg = GetMouseMsg();// ��ȡ�����Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 532 && msg.x <= 760 && msg.y >= 170 && msg.y <= 262) {

				View_AllUsers();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 227 && msg.x <= 449 && msg.y >= 380 && msg.y <= 469) {

				Add_User();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 331 && msg.x <= 568 && msg.y >= 610 && msg.y <= 704) {

				Modify_User();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 741 && msg.x <= 968 && msg.y >= 608 && msg.y <= 700) {

				Find_User();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 840 && msg.x <= 1065 && msg.y >= 376 && msg.y <= 479) {

				Delete_User();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

				StaffMenu();
				goto label;
			}
		}
	}
label:return;


}
           void Add_User() {
	HWND hwnd;
	hwnd = GetHWnd();
	ptr1 = head1;
	if (usercount) {
		for (int i = 1; i < usercount; i++) {
			ptr1 = ptr1->next;
		}
	}
	while (1) {
		Node1* new_user = (Node1*)malloc(sizeof(Node1));

		if (new_user == NULL) {
			printf("�ڴ濪��ʧ�ܣ�");
			exit(1);
		}
		wchar_t TempID[40];
		wchar_t TempPassword[40];
		wchar_t TempName[40];
		int i;
		wchar_t title[20];
		_stprintf_s(title, _T("����¼��� %d λ�û�"), usercount + 1);
		i = InputBox(TempID, 5, _T("�����롾�˺š�(������ҪС��5�ַ�)"), title, NULL, 0, 0, false);
		if (i == true) {
			wcharTochar(TempID, new_user->users.ID, 20);
			if (strlen(new_user->users.ID) == 0) {
				MessageBox(hwnd, _T("�˺Ų���Ϊ�գ�"), _T("����"), MB_OK);
				continue;
			}
			if (Find_User_ByID(new_user->users.ID)) {
				MessageBox(hwnd, _T("���û��Ѵ��ڣ�"), _T("����"), MB_OK);
				continue;
			}
            if (ifblank(new_user->users.ID)) {
				MessageBox(hwnd, _T("�˺Ų��ܰ����ո�"), _T("����"), MB_OK);
				continue;
			}
			wchar_t reminder[20];
			_stprintf_s(reminder, _T("������%s�û��ġ�������"), TempID);
			InputBox(TempName, 40, reminder, title, NULL, 0, 0, true);
			wcharTochar(TempName, new_user->users.name, 20);
			if (strlen(new_user->users.name) == 0) {
				MessageBox(hwnd, _T("��������Ϊ�գ�"), _T("����"), MB_OK);
				continue;
			}
			if (ifblank(new_user->users.name)) {
				MessageBox(hwnd, _T("�������ܰ����ո�"), _T("����"), MB_OK);
				continue;
			}
			wcharTochar(TempID, new_user->users.ID, 20);
			wcharTochar(_T("123456"), new_user->users.password, 20);
			if (isthreemonth()) {
				new_user->users.money = 100;
				nowmoney -= 100;
				WriteMoneyToFile();
			}
			else {
				new_user->users.money = 10;
				nowmoney -= 10;
				WriteMoneyToFile();
			}
			new_user->users.times = 0;
			new_user->users.vip = 0;
			if (usercount == 0) {
				head1 = new_user;
				new_user->next = NULL;
				ptr1 = new_user;
			}
			else {
				ptr1->next = new_user;
				ptr1 = new_user;
				ptr1->next = NULL;
			}
			usercount++;
		}
		else if (i == false) {
			WriteUserToFile();//д���ļ�
			UserManagement();
			goto labelInputInformation;
		}
	}

labelInputInformation:
	return;


}
		   void View_AllUsers() {
			   EmptyPage1();
			   ReadFromFile1();
			   settextstyle(40, 0, L"����");
			   setbkcolor(RGB(255, 255, 255));
			   settextcolor(RGB(0, 0, 0));
			   settextstyle(18, 0, L"����");
			   outtextxy(100, 140, L"�˺�    ����  ����     ��Ա�ȼ�   ���     ��ȡ������");
			   setbkmode(TRANSPARENT);
			   settextcolor(WHITE);
			   settextstyle(20, 0, L"����");
			   wchar_t qw[50];
			   charTowchar(nowday, qw, 50);
			   outtextxy(1161, 63, qw);
			   settextcolor(BLACK);
			   wchar_t s[256];
			   char s1[128];
			   Node1* p = head1;
			   for (int i = 1; p != NULL; i++) {
				   
				   sprintf(s1, "%s       %s    %s       %d         %.2lf       %d", p->users.ID, p->users.name, p->users.password, p->users.vip, p->users.money, p->users.times);
				   
				   charTowchar(s1, s, 256);
				   outtextxy(100, 150 + i * 35, s);
				   p = p->next;
			   }

			   MOUSEMSG msg;// ������������������Ϣ
			   FlushMouseMsgBuffer();// ��������Ϣ������
			   while (1)
			   { // ��ѭ�� ѭ�����������Ϣ
				   while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
				   {
					   msg = GetMouseMsg();// ��ȡ�����Ϣ
					   if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
						   UserManagement();
						   return;
					   }
				   }
			   }
		   }
		   void Modify_User() {
			  
	HWND hwnd;
	hwnd = GetHWnd();
	wchar_t Temppassaccount[20];
	char Temaccount[10];
ModifyTabel1:
	Node1* ptr = head1;
	if (ptr == NULL) {
		MessageBox(hwnd, L"�û���ϢΪ�գ���������û�", _T("�޸���Ϣ"), MB_OK);
		UserManagement();
		return;
	}
	int i = 0;
	i=InputBox(Temppassaccount, 20, _T("�������˺�"), _T("�޸��û���Ϣ"), NULL, 0, 0, false);
	if (i == 0) {
		UserManagement();
		return;
	}
	wcharTochar(Temppassaccount, Temaccount, 20);
	while (1) {
		if (strcmp(Temaccount,ptr->users.ID )==0) {
			break;
		}
		else if (ptr->next == NULL){
			MessageBox(hwnd, L"δ�ҵ��˺ţ�����������˺��Ƿ���ȷ", _T("�޸��û���Ϣ"), MB_OK);
			goto ModifyTabel1;
		}
		ptr = ptr->next;
	}
	USE p= ptr->users;
	wchar_t type[10];
	char Temtype[10];
	wchar_t title[100];
switchusermodify:
	_stprintf(title, _T("��ѡ����Ҫ�޸ĵ���Ϣ���������Ӧ����\n1:����\n2:����\n3:��Ա�ȼ�\n4;���\n5:��ȡ������"));
	i = InputBox(type, 20, title, _T("�޸Ŀ����Ϣ"), NULL, 0, 0, true);
	if (i == 0) {
		UserManagement();
		return;
	}
	wcharTochar(type, Temtype,10);
	int int_type = atoi(Temtype);
	wchar_t storeage[40];
	char storeAGE[20];
	switch(int_type) {
        case 1:
			i=InputBox(storeage, 40, _T("�������µġ��û�����"), _T("�޸��û���Ϣ"), NULL, 0, 0, true);
			if (i == 0) {
				UserManagement();
				return;
			}
			wcharTochar(storeage, storeAGE,40);
			if (strlen(storeAGE) == 0) {
				MessageBox(hwnd, _T("�û�������Ϊ�գ�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifblank(storeAGE)) {
				MessageBox(hwnd, _T("�û������ܰ����ո�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			strcpy(ptr->users.name, storeAGE);
			MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
			break;
		case 2:
			i = InputBox(storeage, 40, _T("�������µġ����롿"), _T("�޸��û���Ϣ"), NULL, 0, 0, true);
			if (i == 0) {
				UserManagement();
				return;
			}
			wcharTochar(storeage, storeAGE, 40);
			if (strlen(storeAGE) == 0) {
				MessageBox(hwnd, _T("���벻��Ϊ�գ�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifblank(storeAGE)) {
				MessageBox(hwnd, _T("���벻�ܰ����ո�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			strcpy(ptr->users.password, storeAGE);
			MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
			break;
		case 3:
			i = InputBox(storeage, 40, _T("�������µġ���Ա�ȼ���"), _T("�޸��û���Ϣ"), NULL, 0, 0, true);
			if (i == 0) {
				UserManagement();
				return;
			}
			wcharTochar(storeage, storeAGE, 40);
			if (strlen(storeAGE) == 0) {
				MessageBox(hwnd, _T("��Ա�ȼ�����Ϊ�գ�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifnonumber2(storeAGE)) {
				MessageBox(hwnd, _T("��Ա�ȼ�ֻ��Ϊ����"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifblank(storeAGE)) {
				MessageBox(hwnd, _T("��Ա�ȼ����ܰ����ո�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			ptr->users.vip = atoi(storeAGE);
			MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
			break;
		case 4:
			i = InputBox(storeage, 40, _T("�������µġ���"), _T("�޸��û���Ϣ"), NULL, 0, 0, true);
			if (i == 0) {
				UserManagement();
				return;
			}
			wcharTochar(storeage, storeAGE, 40);
			if (strlen(storeAGE) == 0) {
				MessageBox(hwnd, _T("����Ϊ�գ�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifnonumber(storeAGE)) {
				MessageBox(hwnd, _T("���ֻ��Ϊ����"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifblank(storeAGE)) {
				MessageBox(hwnd, _T("���ܰ����ո�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
            ptr->users.money = atof(storeAGE);
			MessageBox(hwnd, L"�޸ĳɹ�",L" ", MB_OK);
			break;
		case 5:
			i = InputBox(storeage, 40, _T("�������µġ���ȡ��������"), _T("�޸��û���Ϣ"), NULL, 0, 0, true);
			if (i == 0) {
				UserManagement();
				return;
			}
			wcharTochar(storeage, storeAGE, 40);
			if (strlen(storeAGE) == 0) {
				MessageBox(hwnd, _T("��ȡ����������Ϊ�գ�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			if (ifnonumber2(storeAGE)) {
                MessageBox(hwnd, _T("��ȡ������ֻ��Ϊ����"), _T("����"), MB_OK);
                goto switchusermodify;
			}
			if (ifblank(storeAGE)) {
				MessageBox(hwnd, _T("��ȡ���������ܰ����ո�"), _T("����"), MB_OK);
				goto switchusermodify;
			}
			ptr->users.times = atoi(storeAGE);
			MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
			break;
		default:
			MessageBox(hwnd, L"��������ȷ��ѡ��", L" ", MB_OK);
			goto switchusermodify;
			break;
	}WriteUserToFile();//д���ļ�
	UserManagement();
	
	return;
}
		   void Find_User() {
	HWND hwnd;
	hwnd = GetHWnd();
	int  _bool = 0;
	while (1) {
		Node1* ptrTemp = head1;
		if (ptrTemp == NULL) {
			MessageBox(hwnd, L"�û���ϢΪ�գ���������û�", _T("�޸���Ϣ"), MB_OK);
			UserManagement();
			return;
		}
	labelFindStart:	
			wchar_t _TempID[40];
			char ID[100];
			int i;
			i = InputBox(_TempID, 40, _T("��������Ӧ�û����˺�"), _T("�����û���Ϣ"), NULL, 0, 0, false);
			wcharTochar(_TempID, ID, 40);
			if (strlen(ID) == 0) {
				MessageBox(hwnd, _T("�˺Ų���Ϊ�գ�"), _T("����"), MB_OK);
				goto labelFindStart;
			}if (ifblank(ID)) {
				MessageBox(hwnd, _T("�˺Ų��ܰ����ո�"), _T("����"), MB_OK);
				goto labelFindStart;
			}
		if (i == true) 
		{
				while (ptrTemp != NULL) {
					if (strcmp(ID, ptrTemp->users.ID) == 0) {
						_bool = 1;
						wchar_t title[40], content[500];
						wchar_t TempName[20];
						wchar_t TempID[40];
						charTowchar(ptrTemp->users.name, TempName, 20);
						charTowchar(ptrTemp->users.ID, TempID, 40);
						_stprintf_s(title, _T("���ҵ��˺�Ϊ��%s�����û�"), TempID);
						_stprintf_s(content, _T("����:%s\n�˺�:%s\n���:%lf\nVIP LV:%d"), TempName,TempID, ptrTemp->users.money,  ptrTemp->users.vip);
						MessageBox(hwnd, content, title, MB_OK);
					}
					ptrTemp = ptrTemp->next;
				}
				if (_bool == 0) {
					MessageBox(hwnd, _T("�����˺��Ƿ�������ȷ"), _T("δ�ҵ����û�"), MB_OK | MB_ICONWARNING);
				}
				_bool = 0;
			}
		else  {
			WriteUserToFile();//д���ļ�
			goto labelFind;
		}
	}
labelFind:
	UserManagement();
}
		   void Delete_User() {
	HWND hwnd;
	hwnd = GetHWnd();
	Node1* tempuser = NULL;
	wchar_t TempDelete[40];
	char Delete[40];
	int _bool = 0;
	labelDeleteStart:	
			Node1* _delete = head1;
			if (head1== NULL) {
				MessageBox(hwnd, L"�û���ϢΪ�գ���������û�", _T("�޸���Ϣ"), MB_OK);
				UserManagement();
				return;
			}
			Node1* deleteTemp = head1;
			int i;
			i = InputBox(TempDelete, 40, _T("��������Ӧ�û����˺�"), _T("ɾ���û���Ϣ"), NULL, 0, 0, false);
			wcharTochar(TempDelete, Delete, 40);
			if (strlen(Delete) == 0) {
				MessageBox(hwnd, _T("�˺Ų���Ϊ�գ�"), _T("����"), MB_OK);
				goto labelDeleteStart;
			}if (ifblank(Delete)) {
				MessageBox(hwnd, _T("�˺Ų��ܰ����ո�"), _T("����"), MB_OK);
				goto labelDeleteStart;
			}
			if (i == true) 
			{
				int tempcount = 0;
				while (_delete != NULL) {
					tempcount++;
					if (strcmp(_delete->users.ID, Delete) == 0) {
						_bool = 1;
						wchar_t s[50];
						wchar_t TempID[50];
						wchar_t TempName[50];
						int n;
						charTowchar(_delete->users.ID, TempID, 50);
						charTowchar(_delete->users.name, TempName, 50);
						_stprintf_s(s, _T("�ҵ��ʺ�Ϊ%s��%s�û�"), TempID, TempName);
						n = MessageBox(hwnd, _T("ȷ��Ҫɾ�����û�������Ϣ��"), s, MB_OKCANCEL | MB_ICONWARNING);
						if (n == 1) {
							if (tempcount > 1 && tempcount != usercount) 
							{
								tempuser = _delete->next;
								free(_delete);
								deleteTemp->next = tempuser;
								usercount--;
							}
							else if (tempcount == 1) 
							{
								head1 = head1->next;
								free(_delete);
								usercount--;
							}
							else if (tempcount == usercount) 
							{
								deleteTemp->next = NULL;
								free(_delete);
								usercount--;
							}
							MessageBox(hwnd, _T("�ɹ�ɾ��"), _T(" "), MB_OKCANCEL | MB_ICONWARNING);
							_bool = 0;
							goto labelDeleteStart;
						}
						else 
						{
							//ȡ��ɾ��
							//��ִ���κ�ָ��
						}
					}
					_delete = _delete->next;
					if (tempcount >= 2) 
					{
						deleteTemp = deleteTemp->next;
					}
				}
				if (_bool == 0) 
				{
					MessageBox(hwnd, _T("�����Ƿ���ȷ�����˺�"), _T("δ�ҵ���Ӧ�û�"), MB_OK | MB_ICONWARNING);

				}
				_bool = 0;
			}
			else if (i == false) 
			{   WriteUserToFile();
				goto labelDelete;
			}
labelDelete:
UserManagement();
}
	   
    void OutboundManagement() {
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("./image/6.png"), 1366, 768);
		putimage(0, 0, &img);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[50];
		charTowchar(nowday, qw, 50);
		outtextxy(1161, 63, qw);
		//������¼�����
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������	
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 465 && msg.x <= 755 && msg.y >= 300 && msg.y <= 400) {
					SelectPackage_toOutbound();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 465 && msg.x <= 755 && msg.y >= 479 && msg.y <= 578) {

					undealoutmessage();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

					StaffMenu();
					goto label;
				}
			}
		}
	label:return;
	   }
	       void undealoutmessage() {
		ReadFromFile2();
		cleardevice();
		setbkcolor(WHITE);
		setbkmode(TRANSPARENT);
		cleardevice();
		IMAGE img1;
		loadimage(&img1, _T("./image/01.png"));
		putimage(0, 0, &img1);

		IMAGE img2;
		loadimage(&img2, _T("./image/03.png"));
		putimage(1209, 682, &img2);

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[50];
		charTowchar(nowday, qw, 50);
		outtextxy(1161, 63, qw);
		
		setbkcolor(RGB(255, 255, 255));
		settextcolor(RGB(0, 0, 0));
		settextstyle(18, 0, L"����");
		outtextxy(60, 170, L"���� �����û�ID ����λ��");
		outtextxy(700, 170, L"���� �����û�ID ����λ��");
		outtextxy(60, 140, L"��������:");
		outtextxy(700, 140, L"��ȡ�Ŀ��:");
		Node2* ptrTemp = head2;
		int i = 0,j=0;
		while (ptrTemp != NULL) {
			if (ptrTemp->packages.type == 4|| ptrTemp->packages.type == 6) {
				wchar_t s[256];
				char s1[128];
				sprintf(s1, "%d   %s   %c%d%d", ptrTemp->packages.number, ptrTemp->packages.ID, 'A'+ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2]);
				charTowchar(s1, s, 256);
				if (!(ptrTemp->packages.type == 6)) { outtextxy(60, 200 + i * 35, s);i++; }
				else { outtextxy(700, 200 + j * 35, s); j++; }
				
			}
			
			ptrTemp = ptrTemp->next;
		}

		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					OutboundManagement();
					goto label;
				}
			}
		}
	label:return;
	}
	       void SelectPackage_toOutbound() {
		HWND hwnd;
		hwnd = GetHWnd();
		int  _bool = 0;
		WarehouseReadA(a);
		WarehouseReadB(b);
		WarehouseReadC(c);
		while (1) {
			Node2* ptrTemp = head2;
		labelDeleteStart:
			wchar_t _TempID[40];
			char ID[100];
			int i;
			i = InputBox(_TempID, 40, _T("��������Ӧ��ݵĵ���"), _T("��ݳ���"), NULL, 0, 0, false);
			
			if (i == true)
			{
				wcharTochar(_TempID, ID, 40);
				if (strlen(ID) == 0) {
					MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
					goto labelDeleteStart;
				}
				if (ifnonumber2(ID)) {
					MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
					goto labelDeleteStart;
				}
				if (ifblank(ID)) {
					MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
					goto labelDeleteStart;
				}
				while (ptrTemp != NULL) {

					if ((atoi(ID) == ptrTemp->packages.number) && ((ptrTemp->packages.type == 1)|| (ptrTemp->packages.type == 4))) {
						_bool = 1;
						
						autoputout(ptrTemp);
						getCurrentTimeAsString(ptrTemp->packages.time3, sizeof(ptrTemp->packages.time3));
						MessageBox(hwnd, _T("����ɹ�"), _T("�������"), MB_OK);
					}
					ptrTemp = ptrTemp->next;
				}
				if (_bool == 0) {
					MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("δ�ҵ��˻���"), MB_OK | MB_ICONWARNING);
				}
				_bool = 0;
			}
			else {
				WritePacToFile();//д���ļ�
				WarehouseWriteA(a);
				WarehouseWriteB(b);
				WarehouseWriteC(c);
				goto labelout;
			}
		}
	labelout:
		OutboundManagement();

	}

    void EnterboundManagement() {
			 cleardevice();
			 IMAGE img;
			 loadimage(&img, _T("./image/5.png"), 1366, 768);
			 putimage(0, 0, &img);
			 setbkmode(TRANSPARENT);
			 settextcolor(WHITE);
			 settextstyle(20, 0, L"����");
			 wchar_t qw[50];
			 charTowchar(nowday, qw, 50);
			 outtextxy(1161, 63, qw);
			 //������¼�����
			 MOUSEMSG msg;// ������������������Ϣ
			 FlushMouseMsgBuffer();// ��������Ϣ������	
			 while (1)
			 { // ��ѭ�� ѭ�����������Ϣ
				 while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
				 {
					 msg = GetMouseMsg();// ��ȡ�����Ϣ

					 if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 248 && msg.x <= 478 && msg.y >= 441 && msg.y <= 538) {

						 Modify_Package();
						 goto label;
					 }
					 else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 759 && msg.x <= 991 && msg.y >= 441 && msg.y <= 538) {

						 Find_Package();
						 goto label;
					 }
					 else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 248 && msg.x <= 478 && msg.y >= 600 && msg.y <= 700) {

						 BatchInput();
						 goto label;
					 }
					 else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 759 && msg.x <= 991 && msg.y >= 600 && msg.y <= 700) {

						 BatchDelete();
						 goto label;
					 }
					 else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 499 && msg.x <= 730 && msg.y >= 276 && msg.y <= 375) {

						 View_AllPackages();
						 goto label;
					 }
					 else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

						 StaffMenu();
						 goto label;
					 }
				 }
			 }
		 label:return;


		 }

		  void Modify_Package() {
			  
			 HWND hwnd;
			 hwnd = GetHWnd();
			 wchar_t Temppassaccount[20];
			 char Temaccount[10];
		 ModifyTabel2:
			 Node2* ptr = head2;
			 if (ptr == NULL) {
				 MessageBox(hwnd, L"�����ϢΪ�գ�������ӿ��", _T("�޸Ŀ����Ϣ"), MB_OK);
				 UserManagement();
				 return;
			 }
			 int i = 0;
			 i = InputBox(Temppassaccount, 20, _T("�����롾���š�"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
			 if (i == 0) {
				 EnterboundManagement();
				 return;
			 }
			 wcharTochar(Temppassaccount, Temaccount, 20);
			 
			 if (strlen(Temaccount) == 0) {
				 MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
				 goto ModifyTabel2;
			 if (ifnonumber2(Temaccount) == 1) {
				 MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
				 goto ModifyTabel2;
			 }
			 }if (ifblank(Temaccount)) {
				 MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
				 goto ModifyTabel2;
			 }
			 while (1) {
				 if (ptr->packages.number==atoi(Temaccount)) {
					 break;
				 }
				 else if (ptr->next == NULL) {
					 MessageBox(hwnd, L"δ�ҵ���ݣ���������ĵ����Ƿ���ȷ", _T("�޸Ŀ����Ϣ"), MB_OK);
					 goto ModifyTabel2;
				 }
				 ptr = ptr->next;
			 }
			 PAC p = ptr->packages;
			 wchar_t type[10];
			 char Temtype[10];
			 wchar_t title[100];
switchpacmodify:
			 _stprintf(title, _T("��ѡ����Ҫ�޸ĵ���Ϣ���������Ӧ����\n1:�����û�ID\n2:����λ��\n3;���\n4:����\n5:��ݹ�˾\n6:����ȡ��ʱ��\n7:�ļ�Ŀ�ĵ�"));
			 i = InputBox(type, 20, title, _T("�޸��û���Ϣ"), NULL, 0, 0, false);
			 if (i == 0) {
				 EnterboundManagement();
				 return;
			 }
			 wcharTochar(type, Temtype, 10);
			 int int_type = atof(Temtype);
			 wchar_t storeage[40];
			 char storeAGE[20];
			 switch (int_type) {
			 case 1:
				 i = InputBox(storeage, 40, _T("�������µġ������û�ID��"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("�����û�ID����Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("�����û�ID���ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 strcpy(ptr->packages.ID, storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
				 break;
			 case 2:
				 if(ptr->packages.type==3|| ptr->packages.type == 5){
					 MessageBox(hwnd, _T("�޷��޸Ļ���λ��"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 i = InputBox(storeage, 40, _T("�������µġ�����λ�á���A12"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (!(strlen(storeAGE) == 3)) {
					 MessageBox(hwnd, _T("��ʽ����"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 if (storeAGE[0] == 'A' || storeAGE[0] == 'a')
					 storeAGE[0] = '0';
				 if (storeAGE[0] == 'B' || storeAGE[0] == 'b')
					 storeAGE[0] = '1';
				 if (storeAGE[0] == 'C' || storeAGE[0] == 'c')
					 storeAGE[0] = '2';
				 if (ifnonumber2(storeAGE) == 1) {
					 MessageBox(hwnd, _T("��ʽ����"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 if (storeAGE[0] > '2' || storeAGE[0] < '0') {
					 MessageBox(hwnd, _T("��ʽ����"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 if (storeAGE[1] > '3' || storeAGE[1] < '0') {
					 MessageBox(hwnd, _T("��ʽ����"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 if (storeAGE[2] > '3' || storeAGE[2] < '0') {
					 MessageBox(hwnd, _T("��ʽ����"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 if (storeAGE[0] == '0') {
					 WarehouseReadA(a);
					 if (a[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] != 0) {
						 MessageBox(hwnd, _T("�û���λ�����п�ݣ�������ѡ��"), _T("����"), MB_OK);
						 goto ModifyTabel2;
					 }
					 a[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] = ptr->packages.number;
					 WarehouseWriteA(a);
				 }
				 else if (storeAGE[0] == '1') {
					 WarehouseReadB(b);
					 if (b[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] != 0) {
						 MessageBox(hwnd, _T("�û���λ�����п�ݣ�������ѡ��"), _T("����"), MB_OK);
						 goto ModifyTabel2;
					 }
					 b[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] = ptr->packages.number;
					 WarehouseWriteB(b);
				 }
				 else if (storeAGE[0] == '2') {
					 WarehouseReadC(c);
					 if (c[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] != 0) {
						 MessageBox(hwnd, _T("�û���λ�����п�ݣ�������ѡ��"), _T("����"), MB_OK);
						 goto ModifyTabel2;
					 }
					 c[(int)(storeAGE[1] - '0')][(int)(storeAGE[2] - '0')] = ptr->packages.number;
					 WarehouseWriteC(c);
				 }
				 if (ptr->packages.position[0] == 0) {
					 WarehouseReadA(a);
					 a[ptr->packages.position[1]][ptr->packages.position[2]] = 0;
                     WarehouseWriteA(a);
				 }
				 else if (ptr->packages.position[0] == 1) {
					 WarehouseReadB(b);
					 b[ptr->packages.position[1]][ptr->packages.position[2]] = 0;
                     WarehouseWriteB(b);
				 }
				 else if (ptr->packages.position[0] == 2) {
					 WarehouseReadC(c);
					 c[ptr->packages.position[1]][ptr->packages.position[2]] = 0;
                     WarehouseWriteC(c);
				 }
				 ptr->packages.position[0] = (int)(storeAGE[0] - '0');
				 ptr->packages.position[1] = (int)(storeAGE[1] - '0');
				 ptr->packages.position[2] = (int)(storeAGE[2] - '0');
				 MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
				 break;
			 case 3:
				 i = InputBox(storeage, 40, _T("�������µġ������"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("�������Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("������ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 ptr->packages.volume = atof(storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", L" ", MB_OK);
				 break;
			 case 4:
				 i = InputBox(storeage, 40, _T("�������µġ�������"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("��������Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("�������ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 ptr->packages.weight = atoi(storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", _T(""), MB_OK);
				 break;
			 case 5:
				 if(!(ptr->packages.type == 3 || ptr->packages.type == 5)) {
					 MessageBox(hwnd, _T("�޷��޸Ŀ�ݹ�˾"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 i = InputBox(storeage, 40, _T("�������µġ���ݹ�˾��"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("��ݹ�˾����Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("��ݹ�˾���ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 strcpy(ptr->packages.company, storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", L" ", MB_OK);
				 break;
			 case 6:
				 if (!(ptr->packages.type == 3 || ptr->packages.type == 5)) {
					 MessageBox(hwnd, _T("�޷��޸�����ȡ��ʱ��"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 i = InputBox(storeage, 40, _T("�������µġ�����ȡ��ʱ�䡿"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("����ȡ��ʱ�䲻��Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("����ȡ��ʱ�䲻�ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 strcpy(ptr->packages.time1, storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", L" ", MB_OK);
				 break;
			 case 7:
				 if (!(ptr->packages.type == 3 || ptr->packages.type == 5)) {
					 MessageBox(hwnd, _T("�޷��޸ļļ�Ŀ�ĵ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 i = InputBox(storeage, 40, _T("�������µġ��ļ�Ŀ�ĵء�"), _T("�޸Ŀ����Ϣ"), NULL, 0, 0, false);
				 if (i == 0) {
					 UserManagement();
					 return;
				 }
				 wcharTochar(storeage, storeAGE, 40);
				 if (strlen(storeAGE) == 0) {
					 MessageBox(hwnd, _T("�ļ�Ŀ�ĵز���Ϊ�գ�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }if (ifblank(storeAGE)) {
					 MessageBox(hwnd, _T("�ļ�Ŀ�ĵز��ܰ����ո�"), _T("����"), MB_OK);
					 goto switchpacmodify;
				 }
				 strcpy(ptr->packages.place, storeAGE);
				 MessageBox(hwnd, L"�޸ĳɹ�", L" ", MB_OK);
				 break;
			 default:
				 MessageBox(hwnd,L"��������ȷ��ѡ��",L" ",MB_OK);
				 goto switchpacmodify;
				 break;
			 }
			 WritePacToFile();//д���ļ�
			 EnterboundManagement();
			 return;
		 }
		  void Find_Package() {
			 HWND hwnd;
			 hwnd = GetHWnd();
			 int  _bool = 0;
			 if (head2 == NULL) {
				 MessageBox(hwnd, L"�����ϢΪ�գ�������ӿ��", _T("��ѯ�����Ϣ"), MB_OK);
				 UserManagement();
				 return;
			 }
			 while (1) {
				 Node2* ptrTemp = head2;
			 labelDeleteStart2:
				 wchar_t _TempNumber[40] = { 0 };
				 char Number[20] = { 0 };
				 int i;
				 i = InputBox(_TempNumber, 40, _T("��������Ӧ��ݵĵ���"), _T("���ҿ����Ϣ"), NULL, 0, 0, false);
				 if(i==0) {
					 EnterboundManagement();
					 return;
				 }
				 wcharTochar(_TempNumber, Number, 40);
				 if (strlen(Number) == 0) {
					 MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 if (ifnonumber2(Number)) {
					 MessageBox(hwnd, _T("����ֻ�ܰ�������"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 if (ifblank(Number)) {
					 MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 if (i == true)
				 {
					 while (ptrTemp != NULL) {
						 if (ptrTemp->packages.number == atoi(Number)) {
							 _bool = 1;
							 wchar_t title[40], content[500];
							 wchar_t TempID[20], TempPlace[20], TempCompany[20], TempTime1[50], TempTime2[50], TempTime3[50];
							 charTowchar(ptrTemp->packages.ID, TempID, 20);
							 charTowchar(ptrTemp->packages.place, TempPlace, 20);
							 charTowchar(ptrTemp->packages.company, TempCompany, 20);
							 charTowchar(ptrTemp->packages.time1, TempTime1, 50);
							 charTowchar(ptrTemp->packages.time2, TempTime2, 50);
							 charTowchar(ptrTemp->packages.time3, TempTime3, 50);
							 wchar_t TempType[10];
							 char Type[20];
							 if (ptrTemp->packages.type == 1){
								 strcpy(Type, "��ȡ");
								 charTowchar(Type, TempType, 10);
							 }
							 if (ptrTemp->packages.type == 2) {
                                 strcpy(Type, "��ȡ");
								 charTowchar(Type,TempType, 10);
							 }
							 if (ptrTemp->packages.type == 3) {
                                 strcpy(Type, "�ĳ�");
                                 charTowchar(Type, TempType, 10);
							 }
							 if (ptrTemp->packages.type == 4) {
								 strcpy(Type, "�������");
								 charTowchar(Type, TempType, 10);

							 } if (ptrTemp->packages.type == 5) {
								 strcpy(Type, "δ�ĳ�");
								 charTowchar(Type, TempType, 10);
							 }
							 if (ptrTemp->packages.type == 6) {
								 strcpy(Type, "��ȡ");
								 charTowchar(Type, TempType, 10);
							 }
							 if (ptrTemp->packages.type == 7) {
								 strcpy(Type, "��ʧ");
								 charTowchar(Type, TempType, 10);
							 } wchar_t wNumber[20]; // Adjust size as needed
                               charTowchar(Number, wNumber, 20); // Convert char* to wchar_t*

                               _stprintf(title, _T("���ҵ�����Ϊ��%s���Ŀ��"), wNumber);
							 
							 if(ptrTemp->packages.type == 1|| ptrTemp->packages.type == 4 || ptrTemp->packages.type == 6){
							 _stprintf(content, _T("�����û�ID:%s\n״̬:%s\n����λ��:%c%d%d\n���ʱ��:%s\n���:%.2lf\n����:%.2lf\n��ݹ�˾:%s\n�ĳ�ʱ��:%s\n�ļ�Ŀ�ĵ�:%s\nԤԼ����ȡ��ʱ��:%s"), TempID, TempType, 'A' + ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2],TempTime2, ptrTemp->packages.volume, ptrTemp->packages.weight, TempCompany, TempTime3, TempPlace,TempTime1);

							 }
							 else {
								 _stprintf(content, _T("�����û�ID:%s\n״̬:%s\n���ʱ��:%s\n���:%.2lf\n����:%.2lf\n��ݹ�˾:%s\n�ĳ�ʱ��:%s\n�ļ�Ŀ�ĵ�:%s\nԤԼ����ȡ��ʱ��:%s"), TempID, TempType, TempTime2, ptrTemp->packages.volume, ptrTemp->packages.weight, TempCompany, TempTime3, TempPlace, TempTime1);
							 }
							 MessageBox(hwnd, content, title, MB_OK);
							 break;
						 }
						 ptrTemp = ptrTemp->next;
					 }
					 if (_bool == 0) {
						 MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("δ�ҵ��ÿ��"), MB_OK | MB_ICONWARNING);
					 }
					 _bool = 0;
				 }
				 else {
					 WritePacToFile();//д���ļ�
					 goto labelFind;
				 }
			 }
		 labelFind:
			 EnterboundManagement();
		 }
	      void BatchInput() {
	HWND hwnd;
	hwnd = GetHWnd();
	ptr2 = head2;
	if (paccount) {
		for (int i = 1; i < paccount; i++) {
			ptr2 = ptr2->next;
		}
	}
	WarehouseReadA(a);
	WarehouseReadB(b);
	WarehouseReadC(c);
	while (1) {
		Node2* new_package = (Node2*)malloc(sizeof(Node2));
		if (new_package == NULL) {
			printf("�ڴ濪��ʧ�ܣ�");
			exit(1);
		}
		wchar_t TempID[40], TempNumber[40], TempVolume[20], TempWeight[20];
		char Number[20], Volume[10], Weight[10];
		int i;
		wchar_t title[20];
		_stprintf_s(title, _T("����¼��� %d �����"), paccount + 1);
		i = InputBox(TempNumber, 5, _T("�����롾���š�(С�ڵ���5λ����)"), title, NULL, 0, 0, false);
		if (i == true) {
			wcharTochar(TempNumber, Number, 10);
			if (strlen(Number) == 0) {
				MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			if (ifnonumber2(Number)) {
				MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
				continue;
			}
			if (Find_Pac_ByNumber(Number)) {
				MessageBox(hwnd, _T("�ÿ���Ѵ��ڣ�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			if (ifblank(Number)) {
				MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			wchar_t reminder[50];
			_stprintf_s(reminder, _T("������%s��ݵġ������û�ID��"), TempNumber);
			InputBox(TempID, 40, reminder, title, NULL, 0, 0, true);
			wcharTochar(TempID, new_package->packages.ID, 20);
			if (strlen(new_package->packages.ID) == 0) {
				MessageBox(hwnd, _T("�����û�ID����Ϊ�գ�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}if (ifblank(new_package->packages.ID)) {
				MessageBox(hwnd, _T("�����û�ID���ܰ����ո�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			_stprintf_s(reminder, _T("������%s��ݵġ����������λ���������ף�"), TempNumber);
			InputBox(TempVolume, 20, reminder, title, NULL, 0, 0, true);
			wcharTochar(TempVolume, Volume, 20);
			if (strlen(Volume) == 0) {
				MessageBox(hwnd, _T("�������Ϊ�գ�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			if (ifnonumber(Volume)) {
				MessageBox(hwnd, _T("���ֻ��Ϊ����"), _T("����"), MB_OK);
				continue;
			}
			if (ifblank(Volume)) {
				MessageBox(hwnd, _T("������ܰ����ո�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			_stprintf_s(reminder, _T("������%s��ݵġ�����������λ��ǧ�ˣ�"), TempNumber);
			InputBox(TempWeight, 20, reminder, title, NULL, 0, 0, true);
			wcharTochar(TempWeight, Weight, 20);
			if (strlen(Weight) == 0) {
				MessageBox(hwnd, _T("��������Ϊ�գ�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			if (ifnonumber(Weight)) {
				MessageBox(hwnd, _T("���ֻ��Ϊ����"), _T("����"), MB_OK);
				continue;
			}
			if (ifblank(Weight)) {
				MessageBox(hwnd, _T("�������ܰ����ո�"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}
			if (atof(Volume) < 0 || atof(Weight) < 0) {
				MessageBox(hwnd, _T("�������������Ϊ������"), _T("����"), MB_OK);
				free(new_package);
				continue;
			}

            getCurrentTimeAsString(new_package->packages.time2,sizeof(new_package->packages.time2));
			new_package->packages.type = 1;
			new_package->packages.number = atoi(Number);
			new_package->packages.volume = atof(Volume);
			new_package->packages.weight = atof(Weight);
			new_package->packages.position[3] = -1;
			char t[20] = { "NONE" };
			strcpy(new_package->packages.company, t);
			strcpy(new_package->packages.place, t);
			strcpy(new_package->packages.time1, t);
			strcpy(new_package->packages.time3, t);
			if (new_package->packages.volume < 20)
			{  
				if (autoputin(a, new_package)==0)				{
					MessageBox(hwnd, _T("�ֿ�A����"), _T("����"), MB_OK);
					if (autoputin(b, new_package) == 0)
					{
						MessageBox(hwnd, _T("�ֿ�B����"), _T("����"), MB_OK);
						if (autoputin(c, new_package) == 0)
						{
							MessageBox(hwnd, _T("���вֿ�����"), _T("����"), MB_OK);
							free(new_package);
							continue;
						}
						else{
							new_package->packages.position[0] = 2;
							MessageBox(hwnd, _T("����ֿ�C"), _T("��ʾ"), MB_OK);
						}
					}
					else
					{
						new_package->packages.position[0] = 1;
						MessageBox(hwnd, _T("����ֿ�B"), _T("��ʾ"), MB_OK);
					}
				}
				else 
					{ 
						new_package->packages.position[0] = 0;
					  MessageBox(hwnd, _T("����ֿ�A"), _T("��ʾ"), MB_OK);
					}
			}
			
			else if (new_package->packages.volume >= 20 && new_package->packages.volume <= 60) {
				
				if (autoputin(b, new_package) == 0) {
					MessageBox(hwnd, _T("�ֿ�B����"), _T("����"), MB_OK);
					if (autoputin(c, new_package) == 0)
					{
						MessageBox(hwnd, _T("���вֿ�����"), _T("����"), MB_OK);
						free(new_package);
						continue;
					}
					else {
						new_package->packages.position[0] = 2;
						MessageBox(hwnd, _T("����ֿ�C"), _T("��ʾ"), MB_OK);
					}
				}
				else {
					new_package->packages.position[0] = 1;
					MessageBox(hwnd, _T("����ֿ�B"), _T("��ʾ"), MB_OK);
				}
			}
			else if (new_package->packages.volume > 60) {
				
				 int as=autoputin(c, new_package);
				 if (as == 0)
				 {
					 MessageBox(hwnd, _T("���вֿ�����"), _T("����"), MB_OK);
					 free(new_package);
					 continue;
				 }
				 else {
					 new_package->packages.position[0] = 2;
					 MessageBox(hwnd, _T("����ֿ�C"), _T("��ʾ"), MB_OK);
				 }
			}

			if (paccount == 0) {
				head2 = new_package;
				new_package->next = NULL;
				ptr2 = new_package;
			}
			else {
				ptr2->next = new_package;
				ptr2 = new_package;
				ptr2->next = NULL;
			}
			paccount++;
		}
		else if (i == false) {
			WritePacToFile();//д���ļ�
			WarehouseWriteA(a);
			WarehouseWriteB(b);
			WarehouseWriteC(c);
			EnterboundManagement();
			goto labelInputInformation;
		}
	}

labelInputInformation:
	return;

}
          void BatchDelete() {
			 HWND hwnd;
			 hwnd = GetHWnd();
			 if (head2 == NULL) {
				 MessageBox(hwnd, L"�����ϢΪ�գ�������ӿ��", _T("�޸Ŀ����Ϣ"), MB_OK);
				 UserManagement();
				 return;
			 }
			 Node2* temppac = NULL;
			 wchar_t TempDelete[40];
			 char Delete[40];
			 int _bool = 0;
labelDeleteStart2:
			 Node2* _delete = head2;
			 Node2* deleteTemp = head2;
			 int i;
			 i = InputBox(TempDelete, 40, _T("��������Ӧ��ݵĵ���"), _T("ɾ�������Ϣ"), NULL, 0, 0, false);
			 if (i == true)
			 {
				 wcharTochar(TempDelete, Delete, 40);
				 if (strlen(Delete) == 0) {
					 MessageBox(hwnd, _T("�˺Ų���Ϊ�գ�"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 if (ifnonumber2(Delete)) {
					 MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 if (ifblank(Delete)) {
					 MessageBox(hwnd, _T("�˺Ų��ܰ����ո�"), _T("����"), MB_OK);
					 goto labelDeleteStart2;
				 }
				 int tempcount = 0;
				 while (_delete != NULL) {
					 tempcount++;
					 if (_delete->packages.number == atoi(Delete)) {
						 _bool = 1;
						 wchar_t s[50];
						 int n;
						
						 _stprintf_s(s, _T("�ҵ�����Ϊ��%s���"), TempDelete);
						 n = MessageBox(hwnd, _T("ȷ��Ҫɾ���ÿ��������Ϣ��"), s, MB_OKCANCEL | MB_ICONWARNING);
						 if (n == 1) {
							 WarehouseReadA(a);
							 WarehouseReadB(b);
							 WarehouseReadC(c);
							 autoputout(_delete);
							 WarehouseWriteA(a);
							 WarehouseWriteB(b);
							 WarehouseWriteC(c);
							 if (tempcount > 1 && tempcount != paccount)
							 {
								 temppac = _delete->next;
								 free(_delete);
								 deleteTemp->next = temppac;
								 paccount--;
							 }
							 else if (tempcount == 1)
							 {
								 head2 = head2->next;
								 free(_delete);
								 paccount--;
							 }
							 else if (tempcount == paccount)
							 {
								 deleteTemp->next = NULL;
								 free(_delete);
								 paccount--;
							 }
							 MessageBox(hwnd, _T("�ɹ�ɾ��"), _T(" "), MB_OKCANCEL | MB_ICONWARNING);
							 _bool = 0;
							 goto labelDeleteStart2;
						 }
						 else
						 {
							 //ȡ��ɾ��
							 //��ִ���κ�ָ��
						 }
					 }
					 _delete = _delete->next;
					 if (tempcount >= 2)
					 {
						 deleteTemp = deleteTemp->next;
					 }
				 }
				 if (_bool == 0)
				 {
					 MessageBox(hwnd, _T("�����Ƿ���ȷ���뵥��"), _T("δ�ҵ���Ӧ���"), MB_OK | MB_ICONWARNING);
				 }
				 _bool = 0;
			 }
			 else if (i == false)
			 {
				 WritePacToFile();
				 goto labelDelete2;
			 }
labelDelete2:
			 EnterboundManagement();
			 return;
		 }
		  void View_AllPackages() {
			 EmptyPage1();
			 ReadFromFile2();
			 setbkcolor(RGB(255, 255, 255));
			 settextcolor(RGB(0, 0, 0));
			 settextstyle(18, 0, L"����");
			 outtextxy(700, 140, L"��ʧ�Ŀ�ݵ���:");
			 outtextxy(6, 140, L"����     ״̬  ��    ��    ʱ    ��   �����û�ID ����λ��   ���   ����");
			 outtextxy(700, 180, L"����     ״̬  ��    ��    ʱ    ��   �����û�ID ����λ��   ���   ����");
			 setbkmode(TRANSPARENT);
			 settextcolor(WHITE);
			 settextstyle(20, 0, L"����");
			 wchar_t qw[50];
			 charTowchar(nowday, qw, 50);
			 outtextxy(1161, 63, qw);
			 setlinecolor(BLACK);
			 line(690, 140, 690, 740);
			 settextcolor(BLACK);
			 Node2* p = head2;
			 int i = 1; int j = 1;
			 wchar_t s[256];
			 wchar_t s3[256];
			 char s1[128];
			 char s2[128];
			 char TYPE[10];
			 char lla[10]="δ�ڿ���";
			 while (p != NULL) {
				 switch (p->packages.type) {
				 case 1:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 2:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 3:
					 strcpy(TYPE, "�Ѽĳ�");
					 break;
				 case 4:
					 strcpy(TYPE, "�������");
					 break;
				 case 5:
					 strcpy(TYPE, "���ĳ�");
					 break;
				 case 6:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 7:
					 strcpy(TYPE, "��ʧ");
					 break;

				 }
				if(p->packages.type==1|| p->packages.type == 4 || p->packages.type == 6)
				 {
				 sprintf(s1, "%d       %s %s  %s       %c%d%d       %.2lf  %.2lf", p->packages.number, TYPE, p->packages.time2, p->packages.ID, 'A' + p->packages.position[0], p->packages.position[1], p->packages.position[2], p->packages.volume, p->packages.weight);
				 charTowchar(s1, s, 256);
				 if (i <= 24)
					 outtextxy(6, 140 + i * 25, s);
				 if (i > 24)
					 outtextxy(700, 180 + i * 25 - 24 * 25, s);
				 i++;
				 }
				 else if ( p->packages.type == 7) 
				 {
					 sprintf(s2, "%d ", p->packages.number); 
					 charTowchar(s2, s3, 256);
					 outtextxy(780+ j * 60, 140, s3); j++;
				 }

				 else if (p->packages.type == 2)
				 {
					 sprintf(s1, "%d       %s %s  %s       %s  %.2lf  %.2lf", p->packages.number, TYPE, p->packages.time2, p->packages.ID, lla, p->packages.volume, p->packages.weight);
					 charTowchar(s1, s, 256);
					 if (i <= 24)
						 outtextxy(6, 140 + i * 25, s);
					 if (i > 24)
						 outtextxy(700, 180 + i * 25 - 24 * 25, s);
					 i++;
				 }
				 
				 p = p->next;
			 }
			 MOUSEMSG msg;// ������������������Ϣ
			 FlushMouseMsgBuffer();// ��������Ϣ������
			 while (1)
			 { // ��ѭ�� ѭ�����������Ϣ
				 while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
				 {
					 msg = GetMouseMsg();// ��ȡ�����Ϣ
					 if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
						 EnterboundManagement();
						 return;
					 }
				 }
			 }

		 }

    void DataStatistic() {
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("./image/8.png"), 1366, 768);
		putimage(0, 0, &img);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[50];
		charTowchar(nowday, qw, 50);
		outtextxy(1161, 63, qw);
		//������¼�����
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������	
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 251 && msg.x <= 477 && msg.y >= 316 && msg.y <= 417) {

					InboundStatistic();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 763 && msg.x <= 992 && msg.y >= 316 && msg.y <= 417) {

					OutboundStatistic();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 254 && msg.x <= 477 && msg.y >= 484 && msg.y <= 580) {

					PackageSendingStatistic();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 763 && msg.x <= 992 && msg.y >= 481 && msg.y <= 581) {

					FinanceStatistic();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

					StaffMenu();
					goto label;
				}
			}
		}


	label:return;

	}
	      void InboundStatistic() 
         { 
		   EmptyPage3(); 
		   ReadFromFile2();
		   setbkcolor(RGB(255, 255, 255));
		   settextcolor(RGB(0, 0, 0));
		   settextstyle(18, 0, L"����");
		   char lv[10] = { 0 };
		   char d[10] = { 0 };
		   char m[10] = { 0 };
		   int dday = 0;
		   int allnum = 0;
		   int mon = 0;
		   Node2* p = head2;
		   while (p != NULL) {
			   if ((p->packages.type == 1 || p->packages.type == 4|| p->packages.type == 2 || p->packages.type == 7)&&(istoday(p)==1)) {
				    dday++;
			   }
			   if ((p->packages.type == 1 || p->packages.type == 4 || p->packages.type == 2 || p->packages.type == 7) &&(ismonth(p)==1) ) {
				   mon++;
			   }
			   if ((p->packages.type == 1 || p->packages.type == 4 || p->packages.type == 2|| p->packages.type == 7) ) {
				  allnum++;
			   }
			   p = p->next;
		   }
		  
		   _itoa(allnum, lv, 10);
		   wchar_t lv1[10];
		   charTowchar(lv, lv1, 10);
		   outtextxy(835, 144, lv1);

		   _itoa(mon, m, 10);
		   wchar_t m1[10];
		   charTowchar(m, m1, 10);
		   outtextxy(835, 164, m1);

		   _itoa(dday, d, 10);
		   wchar_t d1[10];
		   charTowchar(d, d1, 10);
		   outtextxy(120, 164, d1);

		   outtextxy(750, 144, L"�ۼ����:");
		   outtextxy(35, 164, L"�������:");
		   outtextxy(750, 164, L"�������:");
		   outtextxy(30, 184, L"����     ״̬  ��    ��    ʱ    ��   �����û�ID ����λ��   ���   ����");
		   int i = 1;
		   wchar_t s[256];
		   char s1[128];
		   char TYPE[10];
		   char lla[10] = "δ�ڿ���";
		   p = head2;
		   while (p != NULL) 
		   {
			   switch (p->packages.type) {
			   case 1:
				   strcpy(TYPE, "��ȡ");
				   break;
			   case 2:
				   strcpy(TYPE, "��ȡ");
				   break;
			   case 3:
				   strcpy(TYPE, "�Ѽĳ�");
				   break;
			   case 4:
				   strcpy(TYPE, "�������");
				   break;
			   case 5:
				   strcpy(TYPE, "���ĳ�");
				   break;
			   case 6:
				   strcpy(TYPE, "��ȡ");
				   break;
			   case 7:
				   strcpy(TYPE, "��ʧ");
				   break;
			   }
			   
				   if (p->packages.type == 1 || p->packages.type == 4|| p->packages.type == 6) {
					   sprintf(s1, "%d       %s %s       %s         %c%d%d       %.2lf  %.2lf", p->packages.number, TYPE, p->packages.time2, p->packages.ID, 'A' + p->packages.position[0], p->packages.position[1], p->packages.position[2], p->packages.volume, p->packages.weight);
					   charTowchar(s1, s, 256);
					   outtextxy(35, 184 + i * 25, s);
					   i++;
					  
				   }
				   else if (p->packages.type == 2|| p->packages.type == 7) {
					   sprintf(s1, "%d       %s %s       %s         %s  %.2lf  %.2lf", p->packages.number, TYPE, p->packages.time2, p->packages.ID, lla, p->packages.volume, p->packages.weight);
					   charTowchar(s1, s, 256);
					   outtextxy(35, 184 + i * 25, s);
					   i++;
					   
				   }
			   
			   p = p->next;

		   }
		   float num[7],day[7];
		   CountPackagesLast7Days1(num, day);
		   DrawLineChart(num, day, 750, 200, 450, 450);
		   
		   MOUSEMSG msg;// ������������������Ϣ
		   FlushMouseMsgBuffer();// ��������Ϣ������
		   while (1)
		   { // ��ѭ�� ѭ�����������Ϣ
			   while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			   {
				   msg = GetMouseMsg();// ��ȡ�����Ϣ
				   if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					   DataStatistic();
					   goto label;
				   }
			   }
		   }
	       label:return;
	   }
	      void OutboundStatistic() {
		   EmptyPage3(); 
		   ReadFromFile2();
		   setbkcolor(RGB(255, 255, 255));
		   settextcolor(RGB(0, 0, 0));
		   settextstyle(18, 0, L"����");
		   char lv[10] = { 0 };
		   char d[10] = { 0 };
		   char m[10] = { 0 };
		   int dday = 0;
		   int allnum = 0;
		   int mon = 0;
		   Node2* p = head2;
		   while (p != NULL) {
			   if ((p->packages.type == 2) && (istoday(p) == 1)) {
				   dday++;
			   }
			   if ((p->packages.type == 2) && (ismonth(p) == 1)) {
				   mon++;
			   }
			   if (p->packages.type == 2) {
				   allnum++;
			   }
			   p = p->next;
		   }

		   _itoa(allnum, lv, 10);
		   wchar_t lv1[5];
		   charTowchar(lv, lv1, 5);
		   outtextxy(835, 144, lv1);

		   _itoa(mon, m, 10);
		   wchar_t m1[5];
		   charTowchar(m, m1, 5);
		   outtextxy(835, 164, m1);

		   _itoa(dday, d, 10);
		   wchar_t d1[5];
		   charTowchar(d, d1, 5);
		   outtextxy(120, 164, d1);

		   outtextxy(750, 144, L"�ۼƳ���:");
		   outtextxy(35, 164, L"���ճ���:");
		   outtextxy(750, 164, L"���³���:");
		   outtextxy(30, 184, L"����     ״̬        ����ʱ��         �����û�ID  ���   ����");
		   int i = 1;
		   wchar_t s[256];
		   char s1[128];
		   char TYPE[10];
		   p = head2;
		   while (p != NULL)
		   {
			   strcpy(TYPE, "��ȡ");
			  
				   if (p->packages.type == 2) {
					   sprintf(s1, "%d       %s %s       %s         %.2lf  %.2lf", p->packages.number, TYPE, p->packages.time3, p->packages.ID, p->packages.volume, p->packages.weight);
					   charTowchar(s1, s, 256);
					   outtextxy(35, 184 + i * 25, s);
					   i++;

				   }
			   
			   p = p->next;

		   }
		   float num[7], day[7];
		   CountPackagesLast7Days2(num, day);
		   DrawLineChart(num, day, 750, 200, 450, 450);
		   MOUSEMSG msg;// ������������������Ϣ
		   FlushMouseMsgBuffer();// ��������Ϣ������
		   while (1)
		   { // ��ѭ�� ѭ�����������Ϣ
			   while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			   {
				   msg = GetMouseMsg();// ��ȡ�����Ϣ
				   if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					   DataStatistic();
					   goto label;
				   }
			   }
		   }
	       label:return;
	   }
	      void PackageSendingStatistic() { 
		   EmptyPage3(); 
		   ReadFromFile2();
		   setbkcolor(RGB(255, 255, 255));
		   settextcolor(RGB(0, 0, 0));
		   settextstyle(18, 0, L"����");
		   char lv[10] = { 0 };
		   char d[10] = { 0 };
		   char m[10] = { 0 };
		   int dday = 0;
		   int allnum = 0;
		   int mon = 0;
		   Node2* p = head2;
		   while (p != NULL) {
			   if ((p->packages.type == 3) && (istoday2(p) == 1)) {
				   dday++;
			   }
			   if ((p->packages.type == 3) && (ismonth2(p) == 1)) {
				   mon++;
			   }
			   if ((p->packages.type == 3 )) {
				   allnum++;
			   }
			   p = p->next;
		   }

		   _itoa(allnum, lv, 10);
		   wchar_t lv1[10];
		   charTowchar(lv, lv1, 10);
		   outtextxy(835, 144, lv1);

		   _itoa(mon, m, 10);
		   wchar_t m1[10];
		   charTowchar(m, m1, 10);
		   outtextxy(835, 164, m1);

		   sprintf(d, "%d", dday);
		   wchar_t d1[10];
		   charTowchar(d, d1, 10);
		   outtextxy(120, 164, d1);

		   outtextxy(750, 144, L"�ۼƼļ�:");
		   outtextxy(5, 164, L"���ռļ�:");
		   outtextxy(750, 164, L"���¼ļ�:");
		   outtextxy(5, 184, L"����    ״̬    �����û�ID   ���   ����  �ĳ�ʱ��	  ��ݹ�˾	  �ʼ�Ŀ�ĵ�  ԤԼʱ��");
		   int i = 1;
		   wchar_t s[256];
		   char s1[128];
		   char TYPE[10];
		   p = head2;
		   while (p != NULL)
		   {
			   switch (p->packages.type) {
			   case 1:
				   strcpy(TYPE, "��ȡ");
				   break;
			   case 2:
				   strcpy(TYPE, "��ȡ");
				   break;
			   case 3:
				   strcpy(TYPE, "�Ѽĳ�");
				   break;
			   case 4:
				   strcpy(TYPE, "�������");
				   break;
			   case 5:
				   strcpy(TYPE, "���ĳ�");
				   break;

			   }
			  if(p->packages.type==3|| p->packages.type == 5)
			  {
				  
			   
				  
				   sprintf(s1, "%d  %s %s   %.2lf  %.2lf  %s  %s  %s  %s", p->packages.number, TYPE,p->packages.ID, p->packages.volume, p->packages.weight, p->packages.time3, p->packages.company, p->packages.place,p->packages.time1);
				   charTowchar(s1, s, 256);
				   outtextxy(5, 184 + i * 25, s);
				   	
				   i++;
			   
			   }
			   p = p->next;
		   }

		   float num[7], day[7];
		   CountPackagesLast7Days3(num, day);
		   DrawLineChart(num, day, 850, 200, 450, 450);
		   MOUSEMSG msg;// ������������������Ϣ
		   FlushMouseMsgBuffer();// ��������Ϣ������
		   while (1)
		   { // ��ѭ�� ѭ�����������Ϣ
			   while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			   {
				   msg = GetMouseMsg();// ��ȡ�����Ϣ
				   if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					   DataStatistic();
					   goto label;
				   }
			   }
		   }
	   label:return;
	   }
	      void FinanceStatistic() {
			 EmptyPage3();
			 ReadFromFile2();
			 setbkcolor(RGB(255, 255, 255));
			 settextcolor(RGB(0, 0, 0));
			 settextstyle(18, 0, L"����");
			 char lv[100] = { 0 };
			 char d[100] = { 0 };
			 char m[100] = { 0 };
			 int dday = 0;
			 int allnum = 0;
			 int mon = 0;
			 Node2* p = head2;
			 while (p != NULL) {
				 if ((p->packages.type == 2 || p->packages.type == 3 ) && (istoday2(p) == 1)) {
					 dday+=p->packages.position[3];
				 }
				 if ((p->packages.type == 2 || p->packages.type == 3) && (ismonth2(p) == 1)) {
					 mon+= p->packages.position[3];
				 }
				 p = p->next;
			 }
			 allnum = round(nowmoney);
			 _itoa(allnum, lv, 10);
			 wchar_t lv1[50];
			 charTowchar(lv, lv1, 50);
			 outtextxy(835, 144, lv1);

			 _itoa(mon, m, 10);
			 wchar_t m1[50];
			 charTowchar(m, m1, 50);
			 outtextxy(835, 164, m1);

			 _itoa(dday, d, 10);
			 wchar_t d1[50];
			 charTowchar(d, d1, 50);
			 outtextxy(120, 164, d1);

			 outtextxy(750, 144, L"���ʽ�:");
			 outtextxy(35, 164, L"���ս���:");
			 outtextxy(750, 164, L"���½���:");
			 outtextxy(30, 184, L"����     ״̬     �ĳ�ʱ��/����ʱ��     ����");
			 int i = 1;
			 wchar_t s[256];
			 char s1[128];
			 char TYPE[10];
			 p = head2;
			 while (p != NULL)
			 {
				 switch (p->packages.type) {
				 case 1:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 2:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 3:
					 strcpy(TYPE, "�Ѽĳ�");
					 break;
				 case 4:
					 strcpy(TYPE, "�������");
					 break;
				 case 5:
					 strcpy(TYPE, "���ĳ�");
					 break;
				 case 6:
					 strcpy(TYPE, "��ȡ");
					 break;
				 case 7:
					 strcpy(TYPE, "��ʧ");
					 break;
				 }
				 
					 if (p->packages.type == 3 || p->packages.type == 2) {
						 sprintf(s1, "%d       %s %s       %d", p->packages.number, TYPE, p->packages.time3, p->packages.position[3]);
						 charTowchar(s1, s, 256);
						 outtextxy(35, 184 + i * 25, s);
						 i++;
					 }
				 
				 p = p->next;

			 }
			 float num[7], day[7];
			 CountPackagesLast7Days4(num, day);
			 
			 DrawLineChart(num, day, 750, 200, 550, 455);

			 MOUSEMSG msg;// ������������������Ϣ
			 FlushMouseMsgBuffer();// ��������Ϣ������
			 while (1)
			 { // ��ѭ�� ѭ�����������Ϣ
				 while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
				 {
					 msg = GetMouseMsg();// ��ȡ�����Ϣ
					 if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
						 DataStatistic();
						 goto label;
					 }
				 }
			 }
		 label:return;
		 }
    void WarehouseSituation() {
		cleardevice();
		WarehouseReadA(a);
		WarehouseReadB(b);
		WarehouseReadC(c);
		IMAGE img;
		loadimage(&img, _T("./image/4.png"), 1366, 768);
		putimage(0, 0, &img);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[50];
		charTowchar(nowday, qw, 50);
		outtextxy(1161, 63, qw);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int m = j * 75;
				int n = i * 84;
				if (a[i][j] != 0)
					putimage1(87 + n, 593 - m, a, i, j);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int m = j * 75;
				int n = i * 84;
				if (b[i][j] != 0)
					putimage1(526 + n, 593 - m, b, i, j);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int m = j * 75;
				int n = i * 84;
				if (c[i][j] != 0)
					putimage1(960 + n, 593 - m, c, i, j);
			}
		}

		//������¼�����
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������	
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					StaffMenu();
					goto label;
				}
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1150 && msg.x <= 1322 && msg.y >= 177 && msg.y <= 222) {
					lose();
					goto label;
				}

			}
		}
	label:
		return;
	   }
	      void lose(){
		WarehouseReadA(a);
		WarehouseReadB(b);
		WarehouseReadC(c);

		HWND hwnd;
		hwnd = GetHWnd();
		int  _bool = 0;
		if (head2 == NULL) {
			MessageBox(hwnd, L"�����ϢΪ�գ�������ӿ��", _T("��ݶ�ʧ�Ǽ�"), MB_OK);
			UserManagement();
			return;
		}
		while (1) {
			Node2* ptrTemp = head2;
		labelDeleteStart2:
			wchar_t _TempNumber[40] = { 0 };
			char Number[20] = { 0 };
			int i;
			i = InputBox(_TempNumber, 40, _T("��������Ӧ��ݵĵ���"), _T("��ݶ�ʧ�Ǽ�"), NULL, 0, 0, false);
			if (i == 0) {
				WarehouseSituation();
				return;
			}
			wcharTochar(_TempNumber, Number, 40);
			if (strlen(Number) == 0) {
				MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
				goto labelDeleteStart2;
			}
			if (ifnonumber2(Number)) {
				MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
				goto labelDeleteStart2;
			}
			if (ifblank(Number)) {
				MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
				goto labelDeleteStart2;
			}
			if (i == true)
			{
				while (ptrTemp != NULL) {
					if (ptrTemp->packages.number == atoi(Number)) {
						_bool = 1;
						ptrTemp->packages.type = 7;
						
						if (ptrTemp->packages.position[0] == 0) {
							a[ptrTemp->packages.position[1]][ptrTemp->packages.position[2]] = 0;
						}
						else if (ptrTemp->packages.position[0] == 1) {
							b[ptrTemp->packages.position[1]][ptrTemp->packages.position[2]] = 0;
						}
						else if (ptrTemp->packages.position[0] == 2) {
							c[ptrTemp->packages.position[1]][ptrTemp->packages.position[2]] = 0;
						}
						ptrTemp->packages.position[0] = -1;
						ptrTemp->packages.position[1] = -1;
						ptrTemp->packages.position[2] = -1;
						MessageBox(hwnd, L"�Ǽǳɹ�", L"��ݶ�ʧ�Ǽ�", MB_OK); WritePacToFile(); WarehouseWriteA(a); WarehouseWriteB(b); WarehouseWriteC(c);//д���ļ�
						break;
					}
					ptrTemp = ptrTemp->next;
				}
				if (_bool == 0) {
					MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("δ�ҵ��ÿ��"), MB_OK | MB_ICONWARNING);
				}
				_bool = 0;
			}
			else {
				
				goto labelFind;
			}
		}
	labelFind:
		WarehouseSituation();

	}


    void PackageSendingManagement() {
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("./image/7.png"), 1366, 768);
		putimage(0, 0, &img);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[50];
		charTowchar(nowday, qw, 50);
		outtextxy(1161, 63, qw);
		//������¼�����
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������	
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 144 && msg.x <= 436 && msg.y >= 324 && msg.y <= 426) {

					SelectPackage_toSendOut();
					goto label;
				}
				
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 810 && msg.x <= 1108 && msg.y >= 324 && msg.y <= 426) {

					PendingInformation();
					goto label;
				}
				
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

					StaffMenu();
					goto label;
				}
			}
		}
	label:return;


	   }
	      void PendingInformation() {
			 ReadFromFile2();
			 cleardevice();
			 setbkcolor(WHITE);
			 setbkmode(TRANSPARENT);
			 cleardevice();
			 IMAGE img1;
			 loadimage(&img1, _T("./image/01.png"));
			 putimage(0, 0, &img1);

			 IMAGE img2;
			 loadimage(&img2, _T("./image/03.png"));
			 putimage(1209, 682, &img2);

			 setbkmode(TRANSPARENT);
			 settextcolor(WHITE);
			 settextstyle(20, 0, L"����");
			 wchar_t qw[50];
			 charTowchar(nowday, qw, 50);
			 outtextxy(1161, 63, qw);
			
			 setbkcolor(RGB(255, 255, 255));
			 settextcolor(RGB(0, 0, 0));
			 settextstyle(18, 0, L"����");
			 outtextxy(60, 170, L"����   �����û�ID   Ŀ�ĵ�      ��ݹ�˾   ԤԼʱ��");
			 outtextxy(60, 140, L"�ļ�����:");
			 Node2* ptrTemp = head2;
			 int i = 0;
			 while (ptrTemp != NULL) {
				 if (ptrTemp->packages.type == 5) {
					 wchar_t s[256];
					 char s1[128];
					 sprintf(s1, "%d   %s   %s   %s    %s", ptrTemp->packages.number, ptrTemp->packages.ID, ptrTemp->packages.place,  ptrTemp->packages.company, ptrTemp->packages.time1);
					 charTowchar(s1, s, 256);
					 outtextxy(60, 200 + i * 35, s);
					 i++;
				 }
				 ptrTemp = ptrTemp->next;
			 }

			 MOUSEMSG msg;// ������������������Ϣ
			 FlushMouseMsgBuffer();// ��������Ϣ������
			 while (1)
			 { // ��ѭ�� ѭ�����������Ϣ
				 while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
				 {
					 msg = GetMouseMsg();// ��ȡ�����Ϣ
					 if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
						 PackageSendingManagement();
						 goto label;
					 }
				 }
			 }
		 label:return;
	}
	      void SelectPackage_toSendOut(){
			 ReadFromFile2();
			 HWND hwnd;
			 hwnd = GetHWnd();
			 int  _bool = 0;
			 WarehouseReadA(a);
			 WarehouseReadB(b);
			 WarehouseReadC(c);
			 while (1) {
				 Node2* ptrTemp = head2;
			 labelDeleteStart:
				 wchar_t _TempID[40];
				 char ID[100];
				 int i;
				 i = InputBox(_TempID, 40, _T("��������Ӧ��ݵĵ���"), _T("�ļ�"), NULL, 0, 0, false);
				 if (i == true)
				 {

					 wcharTochar(_TempID, ID, 40);
					 if (strlen(ID) == 0) {
						 MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
						 goto labelDeleteStart;
					 }
					 if (ifnonumber2(ID)) {
						 MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
						 goto labelDeleteStart;
					 }
					 if (ifblank(ID)) {
						 MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
						 goto labelDeleteStart;
					 }
					 while (ptrTemp != NULL) {

						 if ((atoi(ID) == ptrTemp->packages.number) && (ptrTemp->packages.type == 5)) {
							 _bool = 1;
							 getCurrentTimeAsString(ptrTemp->packages.time3, sizeof(ptrTemp->packages.time3));
							 ptrTemp->packages.type = 3;

							 MessageBox(hwnd, _T("�ļ��ɹ�"), _T("�ļ�"), MB_OK);
						 }
						 ptrTemp = ptrTemp->next;
					 }
					 if (_bool == 0) {
						 MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("δ�ҵ��˿��"), MB_OK | MB_ICONWARNING);
					 }
					 _bool = 0;
				 }
				 else {
					 WritePacToFile();//д���ļ�
					 WarehouseWriteA(a);
					 WarehouseWriteB(b);
					 WarehouseWriteC(c);
					 goto labelout;
				 }
			 }
		 labelout:
			 PackageSendingManagement();

	  }
	void stapassward() {
		   FILE* fp;

		   fp = fopen("accountStaffs.txt", "r");
		   HWND hwnd;
		   hwnd = GetHWnd();
		   char staffID[20];
		   char staffpassword[20];
		   fscanf(fp, "%s %s", staffID, staffpassword);
		   wchar_t a[20];
		   char b[20];
		   InputBox(a, 20, _T("����������"), _T("�޸�����"), NULL, 0, 0, true);
		   wcharTochar(a, b, 20);
		   if (strlen(b) == 0) {
               MessageBox(hwnd, _T("���벻��Ϊ��"), _T("����"), MB_OK);
			   return;
		   }
		   if (ifblank(b)) {
               MessageBox(hwnd, _T("���벻�ܰ����ո�"), _T("����"), MB_OK);
               return;
		   }
		   MessageBox(hwnd, _T("�޸ĳɹ�"), _T("�޸�����"), MB_OK);
		   fclose(fp);
		   fp = fopen("accountStaffs.txt", "w");
		   fputs(staffID, fp);
		   fputs("\n", fp);
		   fputs(b, fp);
		   fputs("\n", fp);
		   fclose(fp);
		   
	   }


  void UserMenu()
{
	 cleardevice();
	IMAGE img;
	loadimage(&img, _T("./image/10.png"), 1366, 768);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(20, 0, L"����");
	wchar_t qw[20];
	charTowchar(USER->users.name, qw, 20);
	char lv[10] = { 0 };
	_itoa(USER->users.vip, lv, 10);
	wchar_t lv1[10];
	charTowchar(lv, lv1, 10);
	outtextxy(1233, 63, lv1);
	outtextxy(930, 97,qw);
	wchar_t qw1[50];
	charTowchar(nowday, qw1, 50);
	outtextxy(1160, 97, qw1);
	if (pro == 1)
	{
		IMAGE img;
		loadimage(&img, _T("./image/112.png"));
		putimage(762, 695, &img);
	}
	else {
		IMAGE img2;
		loadimage(&img2, _T("./image/111.png"));
		putimage(762, 695, &img2);
	}
	//������¼�����
	MOUSEMSG msg;// ������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������	
	while (1)
	{ // ��ѭ�� ѭ�����������Ϣ
		while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
		{
			msg = GetMouseMsg();// ��ȡ�����Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 181 && msg.y <= 286) {

				PickUp_Package();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 356 && msg.y <= 452) {

				InformationService();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 250 && msg.x <= 474 && msg.y >= 524 && msg.y <= 623) {

				Wallet();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >=754 && msg.x <= 979 && msg.y >= 181 && msg.y <= 286) {

				Send_Package();
			}
            else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 754 && msg.x <= 979 && msg.y >= 530 && msg.y <= 624) {

				Bill();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 754 && msg.x <= 979 && msg.y >= 356 && msg.y <= 452) {

				Notice();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

				LoginInterface();
				goto label;
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 752 && msg.x <= 790 && msg.y >= 690 && msg.y <= 722) {

				ProService();
				
			}
			else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 50 && msg.x <= 113 && msg.y >= 712 && msg.y <= 740) {
				ModifyPassword();
			}

		}
	}
    label:return;

}

      void PickUp_Package()
  {
	 ReadFromFile1();
	  ReadFromFile2();
	  ReadFromFile3();
	  HWND hwnd; Node1* p;
	  hwnd = GetHWnd();
	  int  _bool = 0;
	  while (1) {
		  Node2* ptrTemp = head2;
	  labelDeleteStart:
		  wchar_t _TempID[40];
		  char ID[100];
		  int i;
		  i = InputBox(_TempID, 40, _T("�������ݵ���"), _T("ȡ��"), NULL, 0, 0, false);
		  if (i == true)
		  {
			  wcharTochar(_TempID, ID, 40);
			  if (ifnonumber(ID)) {
				  MessageBox(hwnd, _T("���Ų���Ϊ�գ�"), _T("����"), MB_OK);
				  goto labelDeleteStart;
			  }
			  if (ifnonumber2(ID)) {
				  MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
				  goto labelDeleteStart;
			  }
			  if (ifblank(ID)) {
				  MessageBox(hwnd, _T("���Ų��ܰ����ո�"), _T("����"), MB_OK);
				  goto labelDeleteStart;
			  }
			  while (ptrTemp != NULL) {
				  if (atoi(ID) == ptrTemp->packages.number && ((ptrTemp->packages.type == 1) || (ptrTemp->packages.type == 4))) {
					  if (pro != 0 && USER->users.vip <= 3) {
						  MessageBox(hwnd, _T("����2Ԫ"), _T("ȡ��"), MB_OK);
						  if (USER->users.money < 2) {
							  MessageBox(hwnd, _T("����,���ֵ"), _T("����"), MB_OK);
							  goto  labelFind;
						  }
						  
						  p = head1;
						  while (p != NULL) {
							  if (strcmp(p->users.ID, USER->users.ID) == 0) { 
								  p->users.money -= 2;
								  p->users.times = p->users.times + 1;
								  p->users.vip = p->users.times / 10;
								  break; 
							  }
							  p = p->next;
						  }
						  USER = p;
						  nowmoney += 2;
						  ptrTemp->packages.position[3] = 2;
						  
						  WriteUserToFile();
					  }
					  else {
						  MessageBox(hwnd, _T("����1Ԫ"), _T("ȡ��"), MB_OK);
						  if (USER->users.money < 1) {
							  MessageBox(hwnd, _T("����,���ֵ"), _T("����"), MB_OK);
							  goto  labelFind;
						  }
						 
						  p = head1;
						  while (p != NULL) {
							  if (strcmp(p->users.ID, USER->users.ID) == 0) {
								  p->users.money -= 1;
								  p->users.times = p->users.times + 1;
								  p->users.vip = p->users.times / 10;
								  break;
							  }
							  p = p->next;
						  }
						  USER = p;
						  nowmoney += 1;
						  ptrTemp->packages.position[3] = 1;
						  
						  WriteUserToFile();
					  }
					  _bool = 1;
					  if (strcmp(ptrTemp->packages.ID, USER->users.ID) == 0) ptrTemp->packages.type = 4;
					  else  ptrTemp->packages.type = 6;
					  WritePacToFile();
					  MessageBox(hwnd, L"��֪ͨ����Ա����", L"ȡ��", MB_OK);
					  
					  goto labelDeleteStart;
				  }
				  ptrTemp = ptrTemp->next;
			  }
			  if (_bool == 0) {
				  MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("����δ�ҵ��˿��"), MB_OK | MB_ICONWARNING);
			  }
			  _bool = 0;
		  }
		  else {

			  goto labelFind;
		  }
	  }
  labelFind:
	  WriteMoneyToFile();
	  WriteUserToFile();
	  UserMenu();
	  return;

  }
	  void Send_Package()
	  {
		  ReadFromFile2();
		  ReadFromFile1();
		  ReadFromFile3();
		  HWND hwnd;
		  hwnd = GetHWnd();
		  Node2* tmp = head2;
		  if (head2 == NULL) {
			  tmp = head2;
		  }
		  else {
			  while (tmp->next != NULL) {
				  tmp = tmp->next;
			  }
		  }
		  Node1* ptr = head1;
		  while (ptr != NULL) {
			  if (strcmp(ptr->users.ID, USER->users.ID) == 0) { 
				  USER->users.money = ptr->users.money;
				  break; 
			  }
			  ptr = ptr->next;
		  }
		  if (USER->users.money < 50) {
			  MessageBox(hwnd, _T("���㣬������Ҫ50Ԫ"), _T("����"), MB_OK);
			  goto label5;
		  }
		  int i;
		  wchar_t TempPlace1[100];
		  wchar_t TempPlace2[100];
		  wchar_t TempPlace3[100];
		  char Place1[50];
		  char Place2[50];
		  char Place3[50];
		  char Volume[20];
		  char Weight[20];
		  wchar_t TempVolume[40];
		  wchar_t TempWeight[40];
		  wchar_t TempPlace[150];
		  wchar_t TempCompany[40];
		  wchar_t TempTime[50];
		  wchar_t s[100];
		  i = InputBox(TempVolume, 40, L"�������������λ���������ף�", _T("�ļ�"), NULL, 0, 0, false);

		  if (i == true) {
			  wcharTochar(TempVolume, Volume, 40);
			  if (strlen(Volume) == 0) {
				  MessageBox(hwnd, _T("�������Ϊ�գ�"), _T("����"), MB_OK);
				  goto label5;

			  }
			  if (ifnonumber2(Volume)) {
				  MessageBox(hwnd, _T("���ֻ��Ϊ����"), _T("����"), MB_OK);
				  goto label5;
			  }
			  if (ifblank(Volume)) {
				  MessageBox(hwnd, _T("������ܰ����ո�"), _T("����"), MB_OK);
				  goto label5;
			  }
			  i = InputBox(TempWeight, 40, L"��������������λ��ǧ�ˣ�", _T("�ļ�"), NULL, 0, 0, false);
			  if (i == true) {
				  wcharTochar(TempWeight, Weight, 40);
				  if (strlen(Weight) == 0) {
					  MessageBox(hwnd, _T("��������Ϊ�գ�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (ifnonumber(Weight)) {
					  MessageBox(hwnd, _T("����ֻ��Ϊ����"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (ifblank(Weight)) {
					  MessageBox(hwnd, _T("�������ܰ����ո�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  i = InputBox(TempPlace1, 100, L"������Ŀ�ĵ�ʡ", _T("�ļ�"), NULL, 0, 0, false);
				  if (i == 0) {
					  goto label5;
				  }
				  wcharTochar(TempPlace1, Place1, 50);
				  if (strlen(Place1) == 0) {
					  MessageBox(hwnd, _T("Ŀ�ĵ�ʡ����Ϊ�գ�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (ifblank(Place1)) {
					  MessageBox(hwnd, _T("Ŀ�ĵ�ʡ���ܰ����ո�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  i = InputBox(TempPlace2, 100, L"������Ŀ�ĵ���", _T("�ļ�"), NULL, 0, 0, false);
				  if (i == 0) {
					  goto label5;
				  }
				  wcharTochar(TempPlace2, Place2, 50);
				  if (strlen(Place2) == 0) {
					  MessageBox(hwnd, _T("Ŀ�ĵ��в���Ϊ�գ�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (ifblank(Place2)) {
					  MessageBox(hwnd, _T("Ŀ�ĵ��в��ܰ����ո�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  i = InputBox(TempPlace3, 100, L"����������ַ(������ʡ��)", _T("�ļ�"), NULL, 0, 0, false);
				  if (i == 0) {
					  goto label5;
				  }
				  wcharTochar(TempPlace3, Place3, 50);
				  if (strlen(Place3) == 0) {
					  MessageBox(hwnd, _T("�����ַ����Ϊ�գ�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (ifblank(Place3)) {
					  MessageBox(hwnd, _T("�����ַ���ܰ����ո�"), _T("����"), MB_OK);
					  goto label5;
				  }
				  if (i == true) {
					  char company[12];
					  wchar_t Company[6];
					  _stprintf(s, L"��ѡ���ݹ�˾�������Ӧ���֣�\n1:Բͨ���\n2:��ͨ���\n3:�°���\n4:˳����");
					  i = InputBox(Company, 6, s, _T("�ļ�"), NULL, 0, 0, true);
					  wcharTochar(Company, company, 6);
					  switch (atoi(company)) {
					  case 1:
						  _stprintf(TempCompany, L"Բͨ���");;
						  break;
					  case 2:
						  _stprintf(TempCompany, L"��ͨ���");
						  break;
					  case 3:
						  _stprintf(TempCompany, L"�°���");
						  break;
					  case 4:
						  _stprintf(TempCompany, L"˳����");
						  break;
					  default:
						  MessageBox(hwnd, _T("��������ȷ����"), _T("�ļ�"), MB_OK);
						  goto label5;
					  }
					  if (i == true) {
						  if (pro == 1) {
							  wchar_t time[6];
							  char Time[3];
							  _stprintf(s, L"��ѡ������ȡ��ʱ�䣨�����Ӧ���֣�\n1:����8��00-11��00\n2:����12��00-14��00\n3:����14��00-16��00\n4:����18��00-20��00");
							  i = InputBox(time, 50, s, _T("�ļ�"), NULL, 0, 0, true);
							  if (i == true) {
								  Node2* p = (Node2*)malloc(sizeof(Node2));
								  if (p == NULL) {
									  MessageBox(hwnd, _T("�ڴ����ʧ��"), _T("����"), MB_OK);
									  goto label5;
								  }
								  if (head2 == NULL) {
									  head2 = p;
								  }
								  else {
									  tmp->next = p;
								  }
								  p->next = NULL;
								  wcharTochar(time, Time, 6);
								  switch (atoi(Time)) {
								  case 1:
									  wcharTochar(L"8:00-11:00", p->packages.time1, 50);
									  break;
								  case 2:
									  wcharTochar(L"12��00-14��00", p->packages.time1, 50);
									  break;
								  case 3:
									  wcharTochar(L"14��00-16��00", p->packages.time1, 50);
									  break;
								  case 4:
									  wcharTochar(L"18��00-20��00", p->packages.time1, 50);
									  break;
								  default:
									  MessageBox(hwnd, _T("��������ȷ����"), _T("�ļ�"), MB_OK);
									  goto label5;
								  }
								  strcpy(p->packages.place, Place1);
								  strcat(p->packages.place, Place2);
								  strcat(p->packages.place, Place3);
								  wcharTochar(TempCompany, p->packages.company, 50);
								  p->packages.volume = atof(Volume);
								  p->packages.weight = atof(Weight);
								  strcpy(p->packages.ID, USER->users.ID);
								  p->packages.number = getnumber();
								  p->packages.type = 5;
								  strcpy(p->packages.time2, "NONE");
								  strcpy(p->packages.time3, "NONE");
								  ptr2 = p;
								  //�Ƿ�ʡ��
								  if (strcmp(Place1, "����") == 0 || strcmp(Place1, "����ʡ") == 0) {
									  p->packages.position[0] = 0;
								  }
								  else {
									  p->packages.position[0] = 1;
								  }
								  p->packages.position[1] = USER->users.times / 10;
								  p->packages.position[2] = pro;
								  p->packages.position[3] = getmoney(p);
								  char mm[20];
								  wchar_t mmm[20];
								  _itoa(p->packages.position[3], mm, 10);
								  strcat(mm, "Ԫ");
								  charTowchar(mm, mmm, 20);
								  MessageBox(hwnd, mmm, _T("����"), MB_OK);
								  Node1*p1= head1;
								  while (p1 != NULL) {
									  if (strcmp(p1->users.ID, USER->users.ID) == 0) {
										  p1->users.money -= p->packages.position[3];
										  p1->users.times = p1->users.times + 1;
										  p1->users.vip = p1->users.times / 10;
										  break;
									  }
									  p1 = p1->next;
								  }
								  USER = p1;
								  
								  nowmoney += p->packages.position[3];
								  
								  tmp = p;

								  paccount++;

								  MessageBox(hwnd, _T("¼��ɹ�"), _T("�ļ�"), MB_OK);
							  }
						  }
						  else if (pro == 0) {

							  Node2* p = (Node2*)malloc(sizeof(Node2));
							  if (p == NULL) {
								  MessageBox(hwnd, _T("�ڴ����ʧ��"), _T("����"), MB_OK);
								  goto label5;
							  }
							  if (head2 == NULL) {
								  head2 = p;
							  }
							  else {
								  tmp->next = p;
							  }
							  p->next = NULL;
							  strcpy(p->packages.place, Place1);
							  strcat(p->packages.place, Place2);
							  strcat(p->packages.place, Place3);
							  wcharTochar(TempCompany, p->packages.company, 40);
							  char volume[20], weight[20];
							  wcharTochar(TempVolume, volume, 40);
							  wcharTochar(TempWeight, weight, 40);
							  p->packages.volume = atof(volume);
							  p->packages.weight = atof(weight);
							  strcpy(p->packages.ID, USER->users.ID);
							  p->packages.number = getnumber();
							  p->packages.type = 5;
							  strcpy(p->packages.time2, "NONE");
							  strcpy(p->packages.time1, "NONE");
							  strcpy(p->packages.time3, "NONE");
							  ptr2 = p;
							  //�Ƿ�ʡ��
							  if (strcmp(Place1, "����") == 0 || strcmp(Place1, "����ʡ") == 0) {
								  p->packages.position[0] = 0;
							  }
							  else {
								  p->packages.position[0] = 1;
							  }
							  p->packages.position[1] = USER->users.times / 10;
							  p->packages.position[2] = pro;
							  p->packages.position[3] = getmoney(p);
							  char mm[20];
							  wchar_t mmm[20];
							  _itoa(p->packages.position[3], mm, 10);
							  strcat(mm, "Ԫ");
							  charTowchar(mm, mmm, 20);
							  MessageBox(hwnd, mmm, _T("����"), MB_OK);
							  Node1* p1 = head1;
							  while (p1 != NULL) {
								  if (strcmp(p1->users.ID, USER->users.ID) == 0) {
									  p1->users.money -= p->packages.position[3];
									  p1->users.times = p1->users.times + 1;
									  p1->users.vip = p1->users.times / 10;
									  break;
								  }
								  p1 = p1->next;
							  }
							  USER = p1;
							  nowmoney += p->packages.position[3];
							  tmp = p;
							  paccount++;
							  MessageBox(hwnd, _T("¼��ɹ�"), _T("�ļ�"), MB_OK);
						  }

					  }
				  }
			  }
		  }
	  label5:
		  WritePacToFile();
		  WriteUserToFile();
		  WriteMoneyToFile();
		  UserMenu();
		  return;
	  }
	  void InformationService()
	{
		ReadFromFile2();
		HWND hwnd;
		hwnd = GetHWnd();
		int  _bool = 0;
		while (1) {
			Node2* ptrTemp = head2;
		labelDeleteStart:
			wchar_t _TempNumber[40] = { 0 };
			char Number[20] = { 0 };
			int i;
			i = InputBox(_TempNumber, 40, _T("��������Ӧ��ݵĵ���"), _T("���ҿ����Ϣ"), NULL, 0, 0, false);
			if (i == true)
			{
				wcharTochar(_TempNumber, Number, 40);
				if (ifnonumber2(Number)) {
					MessageBox(hwnd, _T("����ֻ�ܰ�������"), _T("����"), MB_OK);
					goto labelDeleteStart;
				}
				while (ptrTemp != NULL) {
					if (ptrTemp->packages.number == atoi(Number) && strcmp(ptrTemp->packages.ID, USER->users.ID) == 0) {
						_bool = 1;
						wchar_t title[100], content[500];
						wchar_t TempID[20], TempPlace[20], TempCompany[20], TempTime1[50],TempTime2[50],TempTime3[50];
						charTowchar(ptrTemp->packages.ID, TempID, 20);
						charTowchar(ptrTemp->packages.place, TempPlace, 20);
						charTowchar(ptrTemp->packages.company, TempCompany, 20);
						charTowchar(ptrTemp->packages.time1, TempTime1, 50);
						charTowchar(ptrTemp->packages.time2, TempTime2, 50);
						charTowchar(ptrTemp->packages.time3, TempTime3, 50);
						wchar_t TempType[10];

						char Type[10];//1Ϊ��ȡ��2Ϊ��ȡ��3Ϊ�Ѽĳ�,4�������,5Ϊδ�ĳ�
						if (ptrTemp->packages.type == 1) {
							strcpy(Type, "��ȡ");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 2) {
							strcpy(Type, "��ȡ");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 3) {
							strcpy(Type, "�Ѽĳ�");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 4) {
							strcpy(Type, "�������");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 5) {
							strcpy(Type, "δ�ĳ�");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 6) {
							strcpy(Type, "��ȡ");
							charTowchar(Type, TempType, 10);
						}
						else if (ptrTemp->packages.type == 7) {
							strcpy(Type, "��ʧ");
							charTowchar(Type, TempType, 10);
						}

						if (ptrTemp->packages.type == 1){
							_stprintf(title, _T("���ҵ�����Ϊ��%d���Ŀ��"), atoi(Number));
							_stprintf(content, _T("״̬:%s\n����λ��:%c%d%d\n���ʱ��:%s\n���:%.2lf\n����:%.2lf"), TempType, 'A' + ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2],TempTime2, ptrTemp->packages.volume, ptrTemp->packages.weight);
							MessageBox(hwnd, content, title, MB_OK);
							break;
						}
						if (ptrTemp->packages.type == 2|| ptrTemp->packages.type == 7) {
							_stprintf(title, _T("���ҵ�����Ϊ��%d���Ŀ��"), atoi(Number));
							_stprintf(content, _T("״̬:%s\n���ʱ��:%s\n���:%.2lf\n����:%.2lf"), TempType,TempTime2,ptrTemp->packages.volume, ptrTemp->packages.weight);
							MessageBox(hwnd, content, title, MB_OK);
							break;
						}
						if (ptrTemp->packages.type == 3) {
							_stprintf(title, _T("���ҵ�����Ϊ��%d���Ŀ��"), atoi(Number));
							_stprintf(content, _T("״̬:%s\n���:%.2lf\n����:%.2lf\n����ȡ��ʱ��:%s\n��ݹ�˾:%s\n�ļ�Ŀ�ĵ�:%s\n�ĳ�ʱ��:%s"), TempType, ptrTemp->packages.volume, ptrTemp->packages.weight,TempTime1,TempCompany,TempPlace,TempTime3);
							MessageBox(hwnd, content, title, MB_OK);
							break;
						}
						if (ptrTemp->packages.type == 4|| ptrTemp->packages.type == 6) {
							_stprintf(title, _T("���ҵ�����Ϊ��%d���Ŀ��"), atoi(Number));
							_stprintf(content, _T("״̬:%s\n����λ��:%c%d%d\n���ʱ��:%s\n���:%.2lf\n����:%.2lf"), TempType, 'A' + ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2], TempTime2, ptrTemp->packages.volume, ptrTemp->packages.weight);
							MessageBox(hwnd, content, title, MB_OK);
							break;
						}
						if (ptrTemp->packages.type == 5) {
							_stprintf(title, _T("���ҵ�����Ϊ��%d���Ŀ��"), atoi(Number));
							_stprintf(content, _T("״̬:%s\n���:%.2lf\n����:%.2lf\n����ȡ��ʱ��:%s\n��ݹ�˾:%s\n�ļ�Ŀ�ĵ�:%s"), TempType, ptrTemp->packages.volume, ptrTemp->packages.weight, TempTime1, TempCompany, TempPlace);
							MessageBox(hwnd, content, title, MB_OK);
							break;
						}
						
					}
					ptrTemp = ptrTemp->next;
				}
				if (_bool == 0) {
					MessageBox(hwnd, _T("���鵥���Ƿ�������ȷ"), _T("δ�ҵ��ÿ��"), MB_OK | MB_ICONWARNING);
				}
				_bool = 0;
			}
			else {
				goto labelFind;
			}
		}
	labelFind:
		UserMenu();
	}
	  void Notice()
	{
		ReadFromFile2();
		EmptyPage4();

		setbkcolor(RGB(255, 255, 255));
		settextcolor(RGB(0, 0, 0));
		settextstyle(18, 0, L"����");
		outtextxy(60, 170, L"����    ���� ����λ��  ���ʱ��");
		outtextxy(60, 140, L"���¿����������վ�ֿ��뼰ʱȡ��:");
		outtextxy(900, 140, L"���¿���ѳɹ��ĳ�:");
		outtextxy(550, 170, L"����  ����λ��  ���ʱ��");
		outtextxy(550, 140, L"���¿�ݱ�������ȡ��:");
		outtextxy(550, 440, L"���¿�ݶ�ʧ:");
		outtextxy(900, 170, L"����   ���� �ʼ�Ŀ�ĵ� ��ݹ�˾  �ĳ�ʱ��");
		wchar_t qw1[50];
		charTowchar(nowday, qw1, 50);
		settextcolor(WHITE);
		outtextxy(1160, 97, qw1);
		Node2* ptrTemp = head2;
		
		settextcolor(RGB(0, 0, 0));
		int i = 0, j = 0,x=1;
		while (ptrTemp != NULL) {
			if ((ptrTemp->packages.type == 1) && (strcmp(ptrTemp->packages.ID, USER->users.ID) == 0)) {
				wchar_t s[256];
				char s1[128];
				sprintf(s1, "%d       %s    %c%d%d       %s", ptrTemp->packages.number, USER->users.name, 'A' + ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2],ptrTemp->packages.time2);
				charTowchar(s1, s, 256);
				outtextxy(60, 200 + i * 35, s);
				i++;
			}
			else if ((ptrTemp->packages.type == 3) && (strcmp(ptrTemp->packages.ID, USER->users.ID) == 0)) {
				wchar_t s2[256];
				char s3[128];
				sprintf(s3, "%d       %s  %s  %s  %s", ptrTemp->packages.number, USER->users.name, ptrTemp->packages.place, ptrTemp->packages.company,ptrTemp->packages.time3);
				charTowchar(s3, s2, 256);
				outtextxy(900, 200 + j * 35, s2);
				j++;
			}
			else if ((ptrTemp->packages.type == 6) && (strcmp(ptrTemp->packages.ID, USER->users.ID) == 0)) {
				wchar_t s5[256];
				char s6[128];
				sprintf(s6, "%d    %c%d%d       %s", ptrTemp->packages.number,  'A' + ptrTemp->packages.position[0], ptrTemp->packages.position[1], ptrTemp->packages.position[2], ptrTemp->packages.time2);
				charTowchar(s6, s5, 256);
				outtextxy(550, 200 + j * 35, s5);
				j++;
			}
			else if ((ptrTemp->packages.type == 7) && (strcmp(ptrTemp->packages.ID, USER->users.ID) == 0)) {
				wchar_t s7[256];
				char s8[128];
				sprintf(s8, "%d    δ�ڿ���   %s", ptrTemp->packages.number, ptrTemp->packages.time2);
				charTowchar(s8, s7, 256);
				outtextxy(550, 440+ x * 35, s7);
				x++;
			}
			ptrTemp = ptrTemp->next;
		}
		
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					UserMenu();
					goto label;
				}
			}
		}
	label:return;
	}
      void Bill()
{
		  ReadFromFile1();
		  ReadFromFile2();
		EmptyPage4();
		settextstyle(18, 0, L"����");
		wchar_t qw1[50];
		charTowchar(nowday, qw1, 50);
		settextcolor(WHITE);
		outtextxy(1160, 97, qw1);
		setbkcolor(RGB(255, 255, 255));
		settextcolor(RGB(0, 0, 0));
		settextstyle(18, 0, L"����");
		outtextxy(900, 144, L"�ۼ�����:");
		outtextxy(30, 184, L"����     ״̬  �ĳ�ʱ��/����ʱ��   Ŀ�ĵ�     ��ݹ�˾   Ԥ Լ ʱ ��   ����");
		Node2* p;
		p = head2;
		int i = 1;
		int allcost = 0;
		char s1[200];
		wchar_t s[200];
		char TYPE[20];
		while (p != NULL)
		{
			switch (p->packages.type) {
			case 1:
				strcpy(TYPE, "��ȡ");
				break;
			case 2:
				strcpy(TYPE, "��ȡ");
				break;
			case 3:
				strcpy(TYPE, "�Ѽĳ�");
				break;
			case 4:
				strcpy(TYPE, "�������");
				break;
			case 5:
				strcpy(TYPE, "���ĳ�");
				break;

			}
			if ((p->packages.type == 3 || p->packages.type == 5|| p->packages.type == 2|| p->packages.type == 4)&&(strcmp(p->packages.ID,USER->users.ID)==0)) {
				allcost += p->packages.position[3];
				sprintf(s1, "%d       %s %s    %s      %s    %s  %d", p->packages.number, TYPE, p->packages.time3,p->packages.place, p->packages.company,p->packages.time1, p->packages.position[3]);
				charTowchar(s1, s, 256);
				outtextxy(35, 184 + i * 25, s);
				i++;

			}
			p = p->next;

		}
		char allc[30];
		_itoa(allcost, allc, 10);
		wchar_t allc1[30];
		charTowchar(allc, allc1, 30);
		outtextxy(985, 144, allc1);
		char ci[20];
		_itoa(USER->users.times, ci,10);
		wchar_t ci1[20];
		charTowchar(ci, ci1,20);
		outtextxy(900, 164, L"���Ѵ���:");
		outtextxy(985, 164, ci1);
		char vipnext[100];
		sprintf(vipnext, "�������� %d ������ΪVIP lv: %d", (USER->users.times + 10 - USER->users.times % 10) - USER->users.times, USER->users.vip + 1);
	    wchar_t vip1[100];
		charTowchar(vipnext, vip1, 100);
		outtextxy(900, 184, vip1);
		



		 MOUSEMSG msg;// ������������������Ϣ
		  FlushMouseMsgBuffer();// ��������Ϣ������
		  while (1)
		  { // ��ѭ�� ѭ�����������Ϣ
			  while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			  {
				  msg = GetMouseMsg();// ��ȡ�����Ϣ
				  if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
					  UserMenu();
					  goto label;
				  }
			  }
		  }
	  label:return;
}
      void Wallet()
{
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("./image/11.png"), 1366, 768);
		putimage(0, 0, &img);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(20, 0, L"����");
		wchar_t qw[20];
		charTowchar(USER->users.name, qw, 20);
		char lv[10] = { 0 };
		_itoa(USER->users.vip, lv, 10);
		wchar_t lv1[10];
		charTowchar(lv, lv1, 10);
		outtextxy(1233, 63, lv1);
		outtextxy(930, 97, qw);
		wchar_t qw1[50];
		charTowchar(nowday, qw1, 50);
		outtextxy(1160, 97, qw1);
		//������¼�����
		MOUSEMSG msg;// ������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ������	
		char m1[100];
		wchar_t m[200];
		sprintf(m1, "%.2f", USER->users.money);
		strcat(m1, "$");
		charTowchar(m1, m, 200);
		settextstyle(60, 0, L"����");
		setbkcolor(RGB(255, 255, 255));
		settextcolor(RGB(0, 0, 0));
		outtextxy(495, 220, m);
		while (1)
		{ // ��ѭ�� ѭ�����������Ϣ
			while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
			{
				msg = GetMouseMsg();// ��ȡ�����Ϣ
				if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 524 && msg.x <= 755 && msg.y >= 400 && msg.y <= 500) {
					Recharge();
				

				}
				
				else if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {

					UserMenu();
					goto label;
				}
			}
		}
	label:return;

}
	  void Recharge() {
		  ReadFromFile1();
		wchar_t s[20];
		int i;
		i=InputBox(s, 20, L"��������", L"��ֵ", NULL, 0, 0, false);
		if (i == 0) {
			return;
		}
		char s1[100];
		wcharTochar(s, s1, 200);
		Node1* p;
		p = head1;
		while (p != NULL) {
			if (strcmp(p->users.ID, USER->users.ID) == 0) { p->users.money += atof(s1); break; }
			p = p->next;
		}
		if (p == NULL) {
			HWND hnd;
			hnd = GetHWnd();
			MessageBox(hnd, L"�Ҳ��������û���Ϣ", L"����", MB_OK);
			return;
		}
		float m = p->users.money;
		sprintf(s1, "%.2f", m);
		strcat(s1, "$");
		charTowchar(s1, s, 200);
		cleardevice();
		IMAGE img;
		loadimage(&img, _T("./image/11.png"), 1366, 768);
		putimage(0, 0, &img);
		outtextxy(495, 220, s);
		WriteUserToFile();
	   }
	  void ProService() {

		  HWND hnd;
		  hnd = GetHWnd();
		  if (first == 0) {
			  wchar_t s[50];
			  _stprintf(s, L"�ĳ���������30%%��ȡ����������1Ԫ\nvip 3���ϵ��û��÷������");
			  MessageBox(hnd, s, L"��¥����", MB_OK | MB_ICONASTERISK);
			  first = 1;
		  }
		  if (pro == 0)
		  {
			  pro = 1;
			  IMAGE img;
			  loadimage(&img, _T("./image/112.png"));
			  putimage(762, 695, &img);
		  }
		  else {
			  pro = 0;
			  IMAGE img2;
			  loadimage(&img2, _T("./image/111.png"));
			  putimage(762, 695, &img2);
		  }
	  }
	  void ModifyPassword() {
		wchar_t s[20];
		InputBox(s, 20, L"������������", L"�޸�����", NULL, 0, 0, false);
		char s1[20];
		wcharTochar(s, s1, 20);
		HWND hwnd;
        hwnd = GetHWnd();
		if (strlen(s1) == 0) {
            MessageBox(hwnd, L"���벻��Ϊ��", L"����", MB_OK);
            return;
		}
		if (ifblank(s1)) {
            MessageBox(hwnd, L"���벻�ܰ����ո�", L"����", MB_OK);
            return;
		}
		strcpy(USER->users.password, s1);
		WriteUserToFile();
		HWND hnd;
		hnd = GetHWnd();
		MessageBox(hnd, L"�޸ĳɹ�", L" ", MB_OK);
	}

void EmptyPage1(){
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	IMAGE img1;
	loadimage(&img1, _T("./image/01.png"));
	putimage(0, 0, &img1);

	IMAGE img2;
	loadimage(&img2, _T("./image/03.png"));
	putimage(1209, 682, &img2);
	setbkmode(TRANSPARENT);
	return;
}
void EmptyPage2(){
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	IMAGE img1;
	loadimage(&img1, _T("./image/01.png"));
	putimage(0, 0, &img1);

	IMAGE img2;
	loadimage(&img2, _T("./image/03.png"));
	putimage(1209, 682, &img2);
	MOUSEMSG msg;// ������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������
	while (1)
	{ // ��ѭ�� ѭ�����������Ϣ
		while (MouseHit())// ���������Ϣ ���������Ϣ��ʱ��ִ�� �ɼ�������������Ϣ
		{
			msg = GetMouseMsg();// ��ȡ�����Ϣ
			if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 1221 && msg.x <= 1366 && msg.y >= 684 && msg.y <= 748) {
				EnterboundManagement();
				goto label;
			}
		}
	}
label:return;
}
void EmptyPage3() {
	setbkcolor(WHITE);
	setbkmode(TRANSPARENT);
	cleardevice();
	IMAGE img1;
	loadimage(&img1, _T("./image/01.png"));
	putimage(0, 0, &img1);

	IMAGE img2;
	loadimage(&img2, _T("./image/03.png"));
	putimage(1209, 682, &img2);

	}
void EmptyPage4() {
		  setbkcolor(WHITE);
		  setbkmode(TRANSPARENT);
		  cleardevice();
		  IMAGE img1;
		  loadimage(&img1, _T("./image/02.png"));
		  putimage(0, 0, &img1);

		  IMAGE img2;
		  loadimage(&img2, _T("./image/03.png"));
		  putimage(1209, 682, &img2);
		  setbkmode(TRANSPARENT);
		  settextcolor(WHITE);
		  settextstyle(20, 0, L"����");
		  wchar_t qw[20];
		  charTowchar(USER->users.name, qw, 20);
		  char lv[10] = { 0 };
		  _itoa(USER->users.vip, lv, 10);
		  wchar_t lv1[5];
		  charTowchar(lv, lv1, 5);
		  outtextxy(1233, 63, lv1);
		  outtextxy(930, 97, qw);
	  }


void UserLogin() {//�û���¼
	ReadFromFile1();
	ReadFromFile2();
	ReadFromFile3();
	int _bool = 0;
	pro = 0;
	HWND hwnd;
    hwnd = GetHWnd();
	wchar_t Tempaccount[40];
	wchar_t Temppassword[40];
	char account[20];
	char password[20];
	char InputAccount[20];
	char InputPassword[20];
	int i;
labelaccount:
	Node1* ptrTemp = head1;
	i = InputBox(Tempaccount, 20, _T("�������˺�"), _T("�û���¼"), NULL, 0, 0, false);
	wcharTochar(Tempaccount, account, 20);
	if (strlen(account) == 0) {
		MessageBox(hwnd, L"�˺Ų���Ϊ��", _T("����"), MB_OK);
        goto labelaccount;
	}
	if (ifblank(account)) {
		MessageBox(hwnd, L"�˺Ų��ܰ����ո�", _T("����"), MB_OK);
        goto labelaccount;
	}
	if (i == true) {
		InputBox(Temppassword, 20, _T("����������"), _T("�û���¼"), NULL, 0, 0, true);
		wcharTochar(Temppassword, password, 20);
		if (strlen(password) == 0) {
			MessageBox(hwnd, L"���벻��Ϊ��", _T("����"), MB_OK);
            goto labelaccount;
		}
        if (ifblank(password)) {
			MessageBox(hwnd, L"���벻�ܰ����ո�", _T("����"), MB_OK);
            goto labelaccount;
		}
		while (ptrTemp != NULL) {
			if (strcmp(account, ptrTemp->users.ID) == 0) {
				if (strcmp(password, ptrTemp->users.password) == 0) {
					_bool = 1;
					break;
				}
			}
			ptrTemp = ptrTemp->next;
		}
		if (_bool == 1) {
			_bool = 0;
            strcat(USEID, ptrTemp->users.ID);
			USER = ptrTemp;
			power = 'U';
			UserMenu();
			goto labelUserLogin;
		}
		else if (_bool == 0) {
			hwnd = GetHWnd();
			MessageBox(hwnd, L"�ټ����������˺Ż������Ƿ���ȷ\n��ȷ������Ա�Ѿ�¼�������Ϣ", _T("�˺Ż���������"), MB_OK | MB_ICONHAND);
			goto labelaccount;
		}
	}
	else if (i == false) {
		LoginInterface();
	}

labelUserLogin:
	return;
}
void StaffLogin() {//����Ա��¼
	ReadFromFile1();
	ReadFromFile2();
	ReadFromFile3();
	HWND hwnd;
	hwnd = GetHWnd();
	FILE* fp;
	int _bool = 0;
labelSTA:	fp = fopen("accountStaffs.txt", "r");
	if (fp == NULL) {
		int i;
		i = MessageBox(hwnd, L"������Ҫ����һ���µ��˻���", _T("����û�����κ��˻�"), MB_OKCANCEL | MB_ICONEXCLAMATION);
		if (i == true) {
			SetSTAPassword();
			goto labelSTA;
		}
		else {
			LoginInterface();
			return;
		}
	}
	wchar_t STAid[40];
	wchar_t STApassword[40];
	char account[20];
	char password[20];
	int i;
	char staffID[20];
	char staffpassword[20];
	fscanf(fp, "%s %s", staffID, staffpassword);
labelaccount:
	i = InputBox(STAid, 40, L"�������˺�", L"����Ա��¼", NULL, 0, 0, false);
	wcharTochar(STAid, account, 20);
	if (strlen(account) == 0) {
        MessageBox(hwnd, L"�˺Ų���Ϊ��", L"����", MB_OK);
        goto labelaccount;
	}
    if (ifblank(account)) {
        MessageBox(hwnd, L"�˺Ų��ܰ����ո�", L"����", MB_OK);
        goto labelaccount;
	}
	if (i == true) {
		InputBox(STApassword, 40, L"����������", L"����Ա��¼", NULL, 0, 0, true);
		wcharTochar(STApassword, password, 20);
        if (strlen(password) == 0) {
            MessageBox(hwnd, L"���벻��Ϊ��", L"����", MB_OK);
            goto labelaccount;
		}
        if (ifblank(password)) {
            MessageBox(hwnd, L"���벻�ܰ����ո�", L"����", MB_OK);
            goto labelaccount;
		}
		if (strcmp(account, staffID) == 0) {
			if (strcmp(password, staffpassword) == 0) {
				//strcat(STAID,staffID);
				_bool = 1;
			}
		}
		if (_bool == 1) {
			_bool = 0;
			power = 'S';
			StaffMenu();
			goto labelStaffLogin;
		}
		else if (_bool == 0) {
			hwnd = GetHWnd();
			MessageBox(hwnd, L"�����������˺Ż������Ƿ���ȷ", _T("�˺Ż���������"), MB_ICONHAND);
			goto labelaccount;
		}
	}
	else if (i == false) {
		LoginInterface();
	}

labelStaffLogin:
	return;
}
void SetSTAPassword() {//��������Ա�˻�
	HWND hwnd;
	char InputAccount[20], InputPassword[20];
	hwnd = GetHWnd();
	MessageBox(hwnd, _T("����Ϊ������һ�����õġ�����Ա���˻�"), _T("�����˻�"), MB_OK);
	wchar_t Temppassaccount[20];
labelStart:	
	InputBox(Temppassaccount, 20, _T("�������˺�"), _T("����������Ա�˻���"), NULL, 0, 0, true);
	wcharTochar(Temppassaccount, InputAccount, 20);
    if (strlen(InputAccount) == 0) {
		MessageBox(hwnd, _T("�˺Ų���Ϊ��"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
    if (ifblank(InputAccount)) {
		MessageBox(hwnd, _T("�˺Ų��ܰ����ո�"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
	wchar_t Temppassword_one[20], Temppassword_two[20];
	char temp_one[20], temp_two[20];
	InputBox(Temppassword_one, 20, _T("����������"), _T("����������Ա�˻���"), NULL, 0, 0, true);
	wcharTochar(Temppassword_one, temp_one, 20);
	if (strlen(temp_one) == 0) {
		MessageBox(hwnd, _T("���벻��Ϊ��"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
	if (ifblank(temp_one)) {
		MessageBox(hwnd, _T("���벻�ܰ����ո�"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
	InputBox(Temppassword_two, 20, _T("��ȷ������"), _T("����������Ա�˻���"), NULL, 0, 0, true);
	if (strlen(temp_two) == 0) {
		MessageBox(hwnd, _T("���벻��Ϊ��"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
	if (ifblank(temp_two)) {
		MessageBox(hwnd, _T("���벻�ܰ����ո�"), _T("����"), MB_OK | MB_ICONHAND);
		goto labelStart;
	}
	wcharTochar(Temppassword_two, temp_two, 20);
	if (strcmp(temp_one, temp_two) != 0) {
		MessageBox(hwnd, _T("������������벻һ�£�����������"), _T(""), MB_OK | MB_ICONEXCLAMATION);
		goto labelStart;
	}
	FILE* fp;
	fp = fopen("accountStaffs.txt", "w");
	fputs(InputAccount, fp);
	fputs("\n", fp);
	wcharTochar(Temppassword_two, InputPassword, 20);
	fputs(InputPassword, fp);
	fputs("\n", fp);
	fclose(fp);
	MessageBox(hwnd, _T("���ڣ�������ʹ������˻���¼������ˡ��ˣ�"), _T("�����ɹ�"), MB_OK);
	return;
}

void wcharTochar(const wchar_t* wchar, char* chr, int length) {//��wcharת��Ϊchar
	WideCharToMultiByte(CP_ACP, 0, wchar, -1, chr, length, NULL, NULL);
}
void charTowchar(const char* chr, wchar_t* wchar, int size) {//��charת��Ϊwchar
	MultiByteToWideChar(CP_ACP, 0, chr, strlen(chr) + 1, wchar, size / sizeof(wchar[0]));
}
void ReadFromFile1() {//���ļ���ȡ��Ϣ
	FILE* fpTest;//��ʼ���ļ�����ֹ��һ��ʹ��ϵͳʱ�����ļ�ʧ�ܡ�
	fpTest = fopen("UsersInformation.txt", "a+");
	fclose(fpTest);
	
	FILE* fp;
	int countTemp = 0, count = 0;

	fp = fopen("UsersInformation.txt", "r");
	fscanf(fp, "Number of users : %d", &usercount);
	if (usercount == 0 || usercount == -1) {
		usercount = 0;
		return;
	}
	Node1* temp = NULL;
	Node1* ptr = NULL;
	while (1) {
		Node1* temp = (Node1*)malloc(sizeof(Node1));
		if (temp == NULL) {
			exit(1);
		}
		
		fscanf(fp, "%s %s %s %d %lf %d",temp->users.ID, temp->users.name, temp->users.password,&temp->users.vip,&temp->users.money,&temp->users.times);
      
		count++;
		if (countTemp == 0) {
			head1 = temp;
			temp->next = NULL;
			ptr = temp;
			countTemp = 1;
		}
		else {
			ptr->next = temp;
			ptr = temp;
			ptr->next = NULL;
		}
		if (count == usercount) {
			break;
		}
	}
	fclose(fp);

    return;
}
void ReadFromFile2() {
	FILE* fpTest;//��ʼ���ļ�����ֹ��һ��ʹ��ϵͳʱ�����ļ�ʧ�ܡ�
	fpTest = fopen("PackagesInformation.txt", "a+");
	fclose(fpTest);
	FILE* fp;
	int countTemp = 0, count = 0;

	fp = fopen("PackagesInformation.txt", "r");
	fscanf(fp, "Number of packages : %d", &paccount);
	if (paccount == 0 || paccount == -1) {
		paccount = 0;
		return;
	}
	Node2* tmp = NULL;
	Node2* p = NULL;
	while (1) {
		Node2* tmp = (Node2*)malloc(sizeof(Node2));
		if (tmp == NULL) {
			exit(1);
		}
		fscanf(fp, "%d %d %s %d %d %d %d %s %lf %lf %s %s %s %s\n", &tmp->packages.number, &tmp->packages.type, tmp->packages.ID, &tmp->packages.position[0], &tmp->packages.position[1], &tmp->packages.position[2], &tmp->packages.position[3], tmp->packages.time2,&tmp->packages.volume, &tmp->packages.weight, tmp->packages.time3, tmp->packages.place, tmp->packages.company,tmp->packages.time1);
		count++;
		if (countTemp == 0) {
			head2 = tmp;
			tmp->next = NULL;
			p = tmp;
			countTemp = 1;
		}
		else {
			p->next = tmp;
			p = tmp;
			p->next = NULL;
		}
		if (count == paccount) {
			break;
		}
	}
	fclose(fp);
	return;
}
void ReadFromFile3() {//���ļ���ȡ��Ϣ
	FILE* fpTest;//��ʼ���ļ�����ֹ��һ��ʹ��ϵͳʱ�����ļ�ʧ�ܡ�
	fpTest = fopen("MoneyInformation.txt", "a+");
	fclose(fpTest);
	FILE* fp;
	int countTemp = 0, count = 0;
	fp = fopen("MoneyInformation.txt", "r");
	fscanf(fp, "%f %s", &nowmoney,date);
	if (nowmoney == 0 || nowmoney == -1) {
		nowmoney = 0;
		
	}
	if (strlen(date) == 0) {
		strcpy(date, nowday);
	}
	fclose(fp);
	return;
}
void release1(Node1* head1) {
    while (head1 != NULL) {
        Node1* temp = head1;
        head1 = head1->next;
        free(temp);
    }
}
void release2(Node2* head2) {
	while (head2 != NULL) {
		Node2* temp = head2;
		head2 = head2->next;
		free(temp);
	}
}
void WriteUserToFile() {//���û���Ϣд���ļ�
	FILE* fp;
	Node1* temp = head1;
	fp = fopen("UsersInformation.txt", "w");
	fprintf(fp, "Number of users : %d\n", usercount);
	while (temp != NULL) { 
		fprintf(fp, "%s %s %s %d %lf %d\n", temp->users.ID, temp->users.name, temp->users.password, temp->users.vip, temp->users.money, temp->users.times);
		temp = temp->next;  
	}
	fclose(fp);
}
void WritePacToFile() {//�������Ϣд���ļ�
	FILE* fp;
	Node2* temp = head2;
	fp = fopen("PackagesInformation.txt", "w");
	fprintf(fp, "Number of packages : %d\n", paccount);
	while (temp != NULL) {
		fprintf(fp, "%d %d %s %d %d %d %d %s %lf %lf %s %s %s %s\n",  temp->packages.number,temp->packages.type,temp->packages.ID, temp->packages.position[0], temp->packages.position[1], temp->packages.position[2], temp->packages.position[3], temp->packages.time2,temp->packages.volume, temp->packages.weight, temp->packages.time3, temp->packages.place, temp->packages.company, temp->packages.time1);
		temp = temp->next;
	}
	fclose(fp);
}
void WriteMoneyToFile() {//����ˮ��Ϣд���ļ�
	FILE* fp;
	strcpy(date, nowday);
	fp = fopen("MoneyInformation.txt", "w");
	fprintf(fp, "%f %s", nowmoney,date);
	fclose(fp);
}

void putimage1(int a1, int b, int a[4][4], int x, int y) {
	IMAGE img;
	loadimage(&img, _T("./image/999.png"), 67, 37);
	putimage(a1, b, &img);
	setbkmode(TRANSPARENT);
	char ab[20];
	wchar_t ac[20];

	_itoa(a[x][y], ab, 10);
	charTowchar(ab, ac, 20);
	settextcolor(WHITE);
	settextstyle(20, 11, L"����");
	outtextxy(a1 + 7, b + 10, ac);
}
int Find_User_ByID(char* user) {

	Node1* p = head1;
	while (p != NULL) {
		if (strcmp(user, p->users.ID) == 0) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}
int Find_Pac_ByNumber(char* pac) {

	Node2* p = head2;
	while (p != NULL) {
		if (p->packages.number == atoi(pac)){
			return 1;
		}
		p = p->next;
	}
	return 0;
}
int autoputin(int a[4][4], Node2* k) {
	int i, j, flag = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
		{
			if (a[i][j] == 0) {
                a[i][j] = k->packages.number; // ȷ�� `k` ��ָ�� `Node2` ���͵�ָ��
				flag = 1;

				k->packages.position[1] = i;
				k->packages.position[2] = j;
				return flag;
			}
		}
	}
	return flag;

}
void autoputout(Node2* k) {
	k->packages.type = 2;
	if (k->packages.position[0] == 0) {
		a[k->packages.position[1]][k->packages.position[2]] = 0;
	}
	else if (k->packages.position[0] == 1) {
		b[k->packages.position[1]][k->packages.position[2]] = 0;
	}
	else if (k->packages.position[0] == 2) {
		c[k->packages.position[1]][k->packages.position[2]] = 0;
	}
	k->packages.position[0] = -1;
	k->packages.position[1] = -1;
	k->packages.position[2] = -1;
}
int ifblank(char *a) {
	int n = strlen(a);
    for (int i = 0; i < n; i++) {
        if (a[i] == ' ') {
            return 1;
        }
    }
	return 0;
}
int ifnonumber(char* a) {
    int n = strlen(a);
	int count = 0;
	for (int i = 0; i < n; i++) {
		if ((a[i] <= '9'&&a[i]>='0')||a[i]=='.') {
			if (a[i] == '.') {
				count++;
			}
		}
		else {
			return 1;
		}
		if (count > 1) {
			return 1;
		}
	}
	return 0;
}
int ifnonumber2(char* a) {
	int n = strlen(a);
	for (int i = 0; i < n; i++) {
		if (a[i] <= '9' && a[i] >= '0') {

		}
		else {
			return 1;
		}
	}
	return 0;
}
void getCurrentTimeAsString(char* buffer, size_t bufferSize) {
	time_t t = time(NULL); // ��ȡ��ǰʱ��
	struct tm* tm_info = localtime(&t); // ת��Ϊ����ʱ��

	// ��ʽ��ʱ��Ϊ�ַ��������� "YYYY-MM-DD HH:MM:SS"
	strftime(buffer, bufferSize, "%Y-%m-%d-%H:%M:%S", tm_info);
}
void getCurrentDate(char* dateStr) {
	time_t t = time(NULL); // ��ȡ��ǰʱ��
	struct tm tm = *localtime(&t); // ת��Ϊ����ʱ��ṹ
	sprintf(dateStr, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday); // ��ʽ��Ϊ�ַ���
}
int istoday(Node2* p) {
	char dday[20] = { 0 };
	int flag = 0;
	for (int u = 0; u < 20; u++) {
		if (p->packages.time2[u] == '-') flag++;
		if (flag < 3)
			dday[u] = p->packages.time2[u];
		else

			break;
	}
	int i=strcmp(dday, nowday);
	if (i == 0) i = 1;
	else i = 0;
	return i;

}
int istoday2(Node2* p) {
	char dday[20] = { 0 };
	int flag = 0;
	for (int u = 0; u < 20; u++) {
		if (p->packages.time3[u] == '-') flag++;
		if (flag < 3)
			dday[u] = p->packages.time3[u];
		else

			break;
	}
	int i = strcmp(dday, nowday);
	if (i == 0) i = 1;
	else i = 0;
	return i;

}
int ismonth(Node2* p) {
	char a[20] = { 0 };
	char b[20] = { 0 };
	a[0] = p->packages.time2[5];
	a[1] = p->packages.time2[6];
	b[0] = nowday[5];
	b[1] = nowday[6];
	int i = strcmp(a, b);
	if (i == 0) i = 1;
	else i = 0;
	return i;

}
int ismonth2(Node2* p) {
	char a[20] = { 0 };
	char b[20] = { 0 };
	a[0] = p->packages.time3[5];
	a[1] = p->packages.time3[6];
	b[0] = nowday[5];
	b[1] = nowday[6];
	int i = strcmp(a, b);
	if (i == 0) i = 1;
	else i = 0;
	return i;

}
int isthreemonth() {
	char three[50] = openday;
	if (strcmp(three, nowday) >= 0) return 1;
	else return 0;
}
int getnumber() {
	Node2* p = head2;
	for (int i = 1; i < 100000; i++) {
		int flag = 0;
		p = head2;
		while (p != NULL) {
			if (p->packages.number == i) {
				flag = 1;
				break;
			}
			p = p->next;
		}
		if (flag == 0)return i;
	}
	return -1;
}
int getmoney(Node2* p) {
	double temp1;//������շ�
	double temp2;//�������շ�
	double temp3;//��������
	int paobi = 0;//�ױ�ϵ��

	//���ݿ�ݹ�˾��ȷ���ױ�ϵ��
	char str1[20] = "Բͨ���";
	char str2[20] = "��ͨ���";
	char str3[20] = "�°���";
	char str4[20] = "˳����";
	if (strcmp(p->packages.company, str1) == 0 || strcmp(p->packages.company, str2) == 0) {
		paobi = 8000;
	}
	else if (strcmp(p->packages.company, str3) == 0) {
		paobi = 6000;
	}
	else if (strcmp(p->packages.company, str4) == 0) {
		paobi = 12000;
	}
	// ��� paobi �Ƿ���ȷ��ʼ��
	if (paobi == 0) {
		printf("δ֪��ݹ�˾���޷��������\n");
		return -1;
	}

	//temp3ȡֵ
	temp1 = p->packages.volume / paobi;
	temp2 = p->packages.weight * 3.44;
	if (temp1 >= temp2) {
		temp3 = temp1;
	}
	else { temp3 = temp2; }

	//����ʡ��ʡ���շ�
	if (p->packages.position[0] == 0) {}
	else { temp3 *= 1.3; }

	//�����Ƿ����ŷ����շ�
	if (p->packages.position[2] == 0) {}
	else { temp3 *= 1.3; }

	//����vip�ȼ��շ�
	temp3 = temp3 * (1.00 - p->packages.position[1] / 100);

	//��temp3��������
	return (int)round(temp3);
}
int calculateDateDifference(char* date1, char* date2) {
	struct tm tm1 = { 0 }, tm2 = { 0 };
	time_t time1, time2;
	// ���ַ�������ת��Ϊ struct tm
	sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
	sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
	// ������ݺ��·�
	tm1.tm_year -= 1900;
	tm1.tm_mon -= 1;
	tm2.tm_year -= 1900;
	tm2.tm_mon -= 1;
	// ת��Ϊʱ���
	time1 = mktime(&tm1);
	time2 = mktime(&tm2);
	// ����������
	double difference = difftime(time2, time1) / (60 * 60 * 24);
	return (int)difference;
}
void linear_regression(float x[], float y[], int n, float* slope, float* intercept) {
	float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

	for (int i = 0; i < n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2 += x[i] * x[i];
	}

	*slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
	*intercept = (sum_y - *slope * sum_x) / n;
}
void CountPackagesLast7Days1(float num[7], float day[7]) {
    // Initialize arrays
    for (int i = 0; i < 7; i++) {
        num[i] = 0;
        day[i] = 0;
    }

    // Get current date
    char currentDate[50];
    getCurrentDate(currentDate);

    // Iterate over the last 7 days
    for (int i = 0; i < 7; i++) {
        // Calculate the date for the day `i` days ago
        struct tm tm = {0};
        sscanf(currentDate, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_mday -= i;
        mktime(&tm); // Normalize the date

        // Format the date as MM.DD
        char formattedDate[10];
        sprintf(formattedDate, "%02d.%02d", tm.tm_mon + 1, tm.tm_mday);
        day[6 - i] = atof(formattedDate); // Store in reverse order

        // Count packages for this date
        Node2* current = head2;
        while (current != NULL) {
			
			if (!(current->packages.type==3|| current->packages.type == 5))
		    {
				char pacdate[20];
				int year, month, day, hour, minute, second;
				sscanf(current->packages.time2, "%d-%d-%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				sprintf(pacdate, "%02d.%02d",month,day);
				
				
				if (strcmp(pacdate,formattedDate) == 0) num[6 - i] += 1;
            
		    }

            current = current->next;
        }
    }
}
void CountPackagesLast7Days2(float num[7], float day[7]) {
	// Initialize arrays
	for (int i = 0; i < 7; i++) {
		num[i] = 0;
		day[i] = 0;
	}

	// Get current date
	char currentDate[50];
	getCurrentDate(currentDate);

	// Iterate over the last 7 days
	for (int i = 0; i < 7; i++) {
		// Calculate the date for the day `i` days ago
		struct tm tm = { 0 };
		sscanf(currentDate, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;
		tm.tm_mday -= i;
		mktime(&tm); // Normalize the date

		// Format the date as MM.DD
		char formattedDate[10];
		sprintf(formattedDate, "%02d.%02d", tm.tm_mon + 1, tm.tm_mday);
		day[6 - i] = atof(formattedDate); // Store in reverse order

		// Count packages for this date
		Node2* current = head2;
		while (current != NULL) {

			if (current->packages.type == 2)
			{
				char pacdate[20];
				int year, month, day, hour, minute, second;
				sscanf(current->packages.time3, "%d-%d-%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				sprintf(pacdate, "%02d.%02d", month, day);


				if (strcmp(pacdate, formattedDate) == 0) num[6 - i] += 1;

			}

			current = current->next;
		}
	}
}
void CountPackagesLast7Days3(float num[7], float day[7]) {
	// Initialize arrays
	for (int i = 0; i < 7; i++) {
		num[i] = 0;
		day[i] = 0;
	}

	// Get current date
	char currentDate[50];
	getCurrentDate(currentDate);

	// Iterate over the last 7 days
	for (int i = 0; i < 7; i++) {
		// Calculate the date for the day `i` days ago
		struct tm tm = { 0 };
		sscanf(currentDate, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;
		tm.tm_mday -= i;
		mktime(&tm); // Normalize the date

		// Format the date as MM.DD
		char formattedDate[10];
		sprintf(formattedDate, "%02d.%02d", tm.tm_mon + 1, tm.tm_mday);
		day[6 - i] = atof(formattedDate); // Store in reverse order

		// Count packages for this date
		Node2* current = head2;
		while (current != NULL) {

			if (current->packages.type == 3)
			{
				char pacdate[20];
				int year, month, day, hour, minute, second;
				sscanf(current->packages.time3, "%d-%d-%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				sprintf(pacdate, "%02d.%02d", month, day);


				if (strcmp(pacdate, formattedDate) == 0) num[6 - i] += 1;

			}

			current = current->next;
		}
	}
}
void CountPackagesLast7Days4(float num[7], float day[7]) {
	// Initialize arrays
	for (int i = 0; i < 7; i++) {
		num[i] = 0;
		day[i] = 0;
	}

	// Get current date
	char currentDate[50];
	getCurrentDate(currentDate);

	// Iterate over the last 7 days
	for (int i = 0; i < 7; i++) {
		// Calculate the date for the day `i` days ago
		struct tm tm = { 0 };
		sscanf(currentDate, "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;
		tm.tm_mday -= i;
		mktime(&tm); // Normalize the date

		// Format the date as MM.DD
		char formattedDate[10];
		sprintf(formattedDate, "%02d.%02d", tm.tm_mon + 1, tm.tm_mday);
		day[6 - i] = atof(formattedDate); // Store in reverse order

		// Count packages for this date
		Node2* current = head2;
		while (current != NULL) {

			if (current->packages.type == 3|| current->packages.type == 2)
			{
				char pacdate[20];
				int year, month, day, hour, minute, second;
				sscanf(current->packages.time3, "%d-%d-%d-%d:%d:%d", &year, &month, &day, &hour, &minute, &second);
				sprintf(pacdate, "%02d.%02d", month, day);


				if (strcmp(pacdate, formattedDate) == 0) num[6 - i] += current->packages.position[3];

			}

			current = current->next;
		}
	}
}
void DrawLineChart(float num[7], float day[7], int x, int y, int width, int height) {
    // Clear the specified region
    setfillcolor(WHITE);
    solidrectangle(x, y, x + width, y + height);

    // Draw axes
    setlinecolor(BLACK);
    line(x, y + height, x + width, y + height); // X-axis
    line(x, y, x, y + height);                 // Y-axis

    // Find the max values for scaling
    float maxNum = num[0];
    float maxDay = day[0];
    for (int i = 1; i < 7; i++) {
        if (num[i] > maxNum) maxNum = num[i];
        if (day[i] > maxDay) maxDay = day[i];
    }

    // Draw labels and grid lines
    settextcolor(BLACK);
    for (int i = 0; i <= 7; i++) {
        int xPos = x + (i * width / 7);
        int yPos = y + height - (i * height / 7);

        // X-axis labels
        if (i < 7) {
            char label[100];
			wchar_t label_w[100];
            sprintf(label, "%.2f", day[i]);
			charTowchar(label, label_w, 100);
            outtextxy(xPos - 10, y + height + 5, label_w);
        }

        // Y-axis labels
        char label[100];
        sprintf(label, "%.1f", maxNum * i / 7);
		wchar_t label_w[100];
		charTowchar(label, label_w, 100);
        outtextxy(x - 30, yPos - 5, label_w);

        // Grid lines
        setlinecolor(LIGHTGRAY);
        line(x, yPos, x + width, yPos); // Horizontal grid
        line(xPos, y, xPos, y + height); // Vertical grid
    }

    // Draw the line chart
    setlinecolor(BLUE);
    for (int i = 0; i < 6; i++) {
        int x1 = x + (i * width / 7);
        int y1 = y + height - (num[i] / maxNum * height);
        int x2 = x + ((i + 1) * width / 7);
        int y2 = y + height - (num[i + 1] / maxNum * height);
        line(x1, y1, x2, y2);
    }
	float slope = 0, intercept = 0;
	linear_regression(day, num, 7, &slope, &intercept);

	// �������ֱ��
	setlinecolor(RED);
	int xStart = x;
	int yStart = y + height - (slope * day[0] + intercept) / maxNum * height;
	int xEnd = x + width;
	int yEnd = y + height - (slope * day[6] + intercept) / maxNum * height;
	line(xStart, yStart, xEnd, yEnd);
}

void WarehouseWriteA(int a[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseA.txt", "w");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fprintf(fp, "%d ", a[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}
void WarehouseWriteB(int b[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseB.txt", "w");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fprintf(fp, "%d ", b[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}
void WarehouseWriteC(int c[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseC.txt", "w");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fprintf(fp, "%d ", c[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}
void WarehouseReadA(int a[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseA.txt", "r");
	if (fp == NULL)  return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fscanf(fp, "%d", &a[i][j]) != 1) {
				fclose(fp);  return;
			}
		}
	}
	fclose(fp);
}
void WarehouseReadB(int b[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseB.txt", "r");
	if (fp == NULL)  return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fscanf(fp, "%d", &b[i][j]) != 1) {
				fclose(fp);  return;
			}
		}
	}
	fclose(fp);
}
void WarehouseReadC(int c[4][4]) {
	FILE* fp;
	fp = fopen("WarehouseC.txt", "r");
	if (fp == NULL)  return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fscanf(fp, "%d", &c[i][j]) != 1) {
				fclose(fp);  return;
			}
		}
	}
}