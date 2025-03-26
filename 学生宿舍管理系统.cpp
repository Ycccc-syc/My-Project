#include"iostream"
using namespace std;
#include<string>
#define MAX 1000
#include"fstream"

//�˵�����
void menu()
{
	cout << "1.������Ϣ¼��" << endl;
	cout << "2.ѧ����Ϣ¼��" << endl;
	cout << "3.���ȫ����Ϣ" << endl;
	cout << "4.������Ϣ����" << endl;
	cout << "5.��Ϣɾ������" << endl;
	cout << "6.��Ϣ�޸Ĺ���" << endl;
	cout << "7.����ͳ�ƹ���" << endl;
	cout << "0.�˳�ϵͳ����" << endl;
	cout << "**************" << endl;
}

//��������ṹ��
struct dorm
{
	int dorm_num;//������
	string dorm_type;//��������
	int bed_num;//��λ����
	int state;//��ס״̬
};

//����¼
struct dormbook
{
	struct dorm dormArray[MAX];
	int dorm_size;
};

//����ѧ���ṹ��
struct student
{
	string stu_id;//ѧ��
	string stu_name;//����
	int stu_sex;//�Ա�
	string stu_class;//ѧ���༶
	int stu_dormid;//������
};

struct studentbook
{
	student stuArray[MAX];
	int stu_size;
};

//�ж������Ƿ����
int isExist_dorm(dormbook* dorm, int num)
{
	for (int i = 0; i < dorm->dorm_size; i++)
	{
		if (dorm->dormArray[i].dorm_num == num)
		{
			return 1;
		}
	}
	return 0;
}

//1.������Ϣ¼��
void adddorm(dormbook* dorm)
{
	if (dorm->dorm_size== MAX)
	{
		cout << "�����������޷����" << endl;
		return;
	}
	else
	{
		//�������
		int num;
		cout << "������������" << endl;
		cin >> num ;
		int ret = isExist_dorm(dorm, num);
		if (ret)//��������Ŵ���
		{
			cout << "�������Ѵ���,����������" << endl;
			return;
		}
		else//�����ڼ�������
		{
			//����������
			dorm->dormArray[dorm->dorm_size].dorm_num = num;

			//������������
			string type;
			cout << "��������������" << endl;
			cin >> type;
			dorm->dormArray[dorm->dorm_size].dorm_type = type;

			//�������ᴲλ
			int n;
			cout << "���������ᴲλ��" << endl;
			cin >> n;
			dorm->dormArray[dorm->dorm_size].bed_num = n;

			//����״̬
			int state;
			cout << "����������ס����" << endl;
			cin >> state;
			dorm->dormArray[dorm->dorm_size].state = state;
			
			//�ļ�����
			ofstream ofs;
			ofs.open("text.txt", ios::app);

			ofs << "�����ţ�" << dorm->dormArray[dorm->dorm_size].dorm_num << endl;
			ofs << "�������ͣ�" << dorm->dormArray[dorm->dorm_size].dorm_type << endl;
			ofs << "���ᴲλ" << dorm->dormArray[dorm->dorm_size].bed_num << endl;
			ofs << "����ס" << dorm->dormArray[dorm->dorm_size].state<<"��" << endl;

			ofs.close();

			dorm->dorm_size++;
			cout << "��Ϣ¼��ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

//�ж������Ƿ���ڶ���
int isExist_dorm(dormbook* dorm, studentbook* stu, int num)
{
	for (int i = 0; i < dorm->dorm_size; i++)
	{
		if (dorm->dormArray[i].dorm_num == num)
		{
			return i;
		}
	}
	return 0;
}

//�ж�ѧ����ѧ���Ƿ����
int isExistid(studentbook* stu,string num)
{
	for (int i = 0; i < stu->stu_size; i++)
	{
		if (stu->stuArray[i].stu_id == num)
		{
			return 1;
		}
	}
	return 0;
}

//2.ѧ����Ϣ¼��
void studentinput(studentbook* stu, dormbook* dorm)
{
	//ѧ��
	string num;
	cout << "����������ѧ��" << endl;
	cin >> num;
	int ret = isExistid(stu, num);
	if (ret)//ѧ�����ظ�
	{
		cout << "ѧ���Ѵ��ڣ��޷�����" << endl;
		return;
	}
	else
	{
		int n;
		cout << "������������" << endl;
		cin >> n;
		int r = isExist_dorm(dorm, n);
		//�ж��������Ƿ����
		if (r)//��������Ŵ���
		{
			//����
			string name;
			cout << "�������������" << endl;
			cin >> name;
			stu->stuArray[stu->stu_size].stu_name = name;

			//�Ա�
			cout << "�������Ա�" << endl;
			cout << "1---��" << endl;
			cout << "2---Ů" << endl;
			int sex = 0;
			while (true) 
			{
				//�������Ϊ1��2������˳�ѭ������Ϊ���������ȷֵ
				//���������������������
				cin >> sex;

				if (sex == 1 || sex == 2)
				{
					stu->stuArray[stu->stu_size].stu_sex = sex;
					break;

				}
				cout << "������������������" << endl;
			}

			//�༶
			string cla;
			cout << "���������İ༶" << endl;
			cin >> cla;
			stu->stuArray[stu->stu_size].stu_class = cla;

			//������
			stu->stuArray[stu->stu_size].stu_id = num;

			//����������
			stu->stuArray[stu->stu_size].stu_dormid = n;

			//����������
			int result = isExist_dorm(dorm,stu, n);
			//��ס��������
			dorm->dormArray[result].state++;

			ofstream ofs;
			ofs.open("text.txt", ios::app);

			ofs <<"ѧ��������"<< stu->stuArray[stu->stu_size].stu_name << endl;
			ofs <<"ѧ�ţ�"<< stu->stuArray[stu->stu_size].stu_id << endl;
			ofs << "�༶��"<< stu->stuArray[stu->stu_size].stu_class << endl;
			ofs <<"�Ա�" <<(stu->stuArray[stu->stu_size].stu_sex == 1?"��":"Ů") << endl;
			ofs << "�����ţ�" << stu->stuArray[stu->stu_size].stu_dormid << endl;
			ofs << "����" << result << "����ס" << dorm->dormArray[result].state << "��" << endl;

			ofs.close();

			stu->stu_size++;
			
			cout << "��Ϣ����ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
		else//�����ڲ�������
		{
			cout << "���᲻���ڣ������²���" << endl;
			return;
		}
	}
}

//3.�������
void show(dormbook* dorm, studentbook* s)
{

	for (int i = 0; i < dorm->dorm_size; i++)
	{
		cout << "������:" << dorm->dormArray[i].dorm_num << "\t";
		cout << "��������:" << dorm->dormArray[i].dorm_type << "\t";
		cout << "��λ����:" << dorm->dormArray[i].bed_num << "\t";
		cout << "�����ţ�" << dorm->dormArray[i].dorm_num << "����ס" << dorm->dormArray[i].state << "��" << endl;
		cout << "*******************************" << endl;
	}
	for (int i = 0; i < s->stu_size; i++)
	{
		cout << "ѧ�ţ�" << s->stuArray[i].stu_id << "\t";
		cout << "������" << s->stuArray[i].stu_name << "\t";
		cout << "�Ա�" << (s->stuArray[i].stu_sex == 1 ? "��" : "Ů") << "\t";
		cout << "�༶��" << s->stuArray[i].stu_class<< "\t";
		cout << "�����ţ�" << s->stuArray[i].stu_dormid << endl;
	}
	system("pause");
	system("cls");
}


//�ж������Ƿ����
int isExist(dormbook* dorm, int num)
{
	for (int i = 0; i < dorm->dorm_size; i++)
	{
		if (dorm->dormArray[i].dorm_num == num)
		{
			return i;
		}
	}
	return -1;
}

//�ж�ѧ����ѧ���Ƿ����
int isExist_id(studentbook* stu, string num)
{
	for (int i = 0; i < stu->stu_size; i++)
	{
		if (stu->stuArray[i].stu_id == num)
		{
			return i;
		}
	}
	return -1;
}

//4.���ҹ���
void findinformation(studentbook* stu, dormbook* dorm)
{
	cout << "���������������Ų�ѯ���ǰ�ѧ�Ų�ѯ" << endl;
	cout << "1-�������Ų�ѯ" << endl;
	cout << "0-��ѧ�Ų�ѯ" << endl;
	int selet;
	while (true)
	{
		cin >> selet;
		if (selet == 1 || selet == 0)
		{
			break;

		}
	}

	if (selet)
	{
		cout << "������Ҫ���ҵ�������" << endl;
		int num;
		cin >> num;

		//�ж��������Ƿ����
		int ret = isExist(dorm, num);
		if (ret != -1)
		{
			cout << "������:" << dorm->dormArray[ret].dorm_num << "\t";
			cout << "��������:" << dorm->dormArray[ret].dorm_type << "\t";
			cout << "��λ����:" << dorm->dormArray[ret].bed_num << "\t";
			cout << "�����ţ�" << dorm->dormArray[ret].dorm_num << "\t����ס" << dorm->dormArray[ret].state << "��" << endl;
			cout << "*******************************" << endl;

			for (int i = 0; i < stu->stu_size; i++)
			{	
				if (stu->stuArray[i].stu_dormid == num)
				{
					cout << "ѧ�ţ�" << stu->stuArray[i].stu_id << "\t";
					cout << "������" << stu->stuArray[i].stu_name << "\t";
					cout << "�Ա�" << (stu->stuArray[i].stu_sex == 1 ? "��" : "Ů") << "\t";
					cout << "�༶��" << stu->stuArray[i].stu_class << "\t";
					cout << "�����ţ�" << stu->stuArray[i].stu_dormid << endl;
				}
			}
			system("pause");
			system("cls");
		}
		else
		{
			cout << "�����᲻����" << endl;
			return;
		}
	}
	else//��ѧ�Ų�ѯ
	{
		cout << "������Ҫ���ҵ�ѧ��" << endl;
		string id;
		cin >> id;

		int r = isExist_id(stu, id);
		if (r != -1)//���ѧ�Ŵ���
		{
			cout << "ѧ�ţ�" << stu->stuArray[r].stu_id << "\t";
			cout << "������" << stu->stuArray[r].stu_name << "\t";
			cout << "�Ա�" << (stu->stuArray[r].stu_sex == 1 ? "��" : "Ů") << "\t";
			cout << "�༶��" << stu->stuArray[r].stu_class << "\t";
			cout << "�����ţ�" << stu->stuArray[r].stu_dormid << endl;

			cout << "******************" << endl;

			for (int i = 0; i < dorm->dorm_size; i++)
			{
				if (dorm->dormArray[i].dorm_num == stu->stuArray[r].stu_dormid)
				{
					cout << "������:" << dorm->dormArray[i].dorm_num << "\t";
					cout << "��������:" << dorm->dormArray[i].dorm_type << "\t";
					cout << "��λ����:" << dorm->dormArray[i].bed_num << "\t";
					cout << "�����ţ�" << dorm->dormArray[i].dorm_num << "\t����ס" << dorm->dormArray[i].state << "��" << endl;
				}
			}
		}
		else//��ѧ�Ų�����
		{
			cout << "ѧ�Ų����ڣ������²���" << endl;
			return;
		}

		system("pause");
		system("cls");
	}
}

//5.ɾ������
void deleteinformation(studentbook*stu, dormbook*dorm)
{
	cout << "��ȷ���Ƿ�Ҫ����ɾ������" << endl;
	cout << "1-��" << endl;
	cout << "0-��" << endl;
	int decide;
	while (true)
	{
		cin >> decide;
		if (decide == 1 || decide == 0)
		{
			break;
		}

	}
	
	if (decide)
	{
		cout << "���������������Ų�ѯ���ǰ�ѧ��ɾ��" << endl;
		cout << "1-��������ɾ��" << endl;
		cout << "0-��ѧ��ɾ��" << endl;
		int selet;

		while (true)
		{
			cin >> selet;
			if (selet == 1 || selet == 0)
			{
				break;
			}
		}
		

		if (selet)
		{
			cout << "������Ҫɾ����������" << endl;
			int num;

			cin >> num;
			//�ж��������Ƿ����
			int ret = isExist(dorm, num);
			if (ret != -1)
			{
				for (int i = ret; i < dorm->dorm_size; i++)
				{
					//����ǰ��
					dorm->dormArray[i] = dorm->dormArray[i + 1];
				}

				for (int i = 0; i < stu->stu_size; i++)
				{
					if (stu->stuArray[i].stu_dormid == dorm->dormArray[dorm->dorm_size].dorm_num)
					{
						stu->stuArray[i].stu_dormid = 0;
					
					}
				}

				dorm->dorm_size--;//����������

				//�����ļ��е���Ϣ
				ofstream ofs;
				ofs.open("text.txt", ios::trunc );

				for (int i = 0; i < dorm->dorm_size; i++)
				{
					ofs << "������:" << dorm->dormArray[i].dorm_num << "\t";
					ofs << "��������:" << dorm->dormArray[i].dorm_type << "\t";
					ofs << "��λ����:" << dorm->dormArray[i].bed_num << "\t";
					ofs << "�����ţ�" << dorm->dormArray[i].dorm_num << "\t����ס" << dorm->dormArray[i].state << "��" << endl;
					ofs << "*******************************" << endl;
				}

				for (int i = 0; i < stu->stu_size; i++)
				{
					ofs << "ѧ�ţ�" << stu->stuArray[i].stu_id << "\t";
					ofs << "������" << stu->stuArray[i].stu_name << "\t";
					ofs << "�Ա�" << (stu->stuArray[i].stu_sex == 1 ? "��" : "Ů") << "\t";
					ofs << "�༶��" << stu->stuArray[i].stu_class << "\t";
					ofs << "�����ţ�" << stu->stuArray[i].stu_dormid << endl;
				}
				ofs.close();

				cout << "ɾ���ɹ�" << endl;
			}
			else
			{
				cout << "�����Ų�����" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "������Ҫɾ����ѧ��" << endl;
			string id;
			cin >> id;

			int r = isExist_id(stu, id);

			if (r != -1)
			{
				for (int i = r; i < stu->stu_size; i++)
				{
					stu->stuArray[i] = stu->stuArray[i + 1];
				}
				

				for (int i = 0; i < dorm->dorm_size; i++)
				{
					if (dorm->dormArray[i].dorm_num == stu->stuArray[stu->stu_size].stu_dormid)
					{
						dorm->dormArray[i].state--;
					}
				}

				stu->stu_size--;

				cout << "ɾ���ɹ�" << endl;

				system("pause");
				system("cls");
			}
			else
			{
				cout << "���޴���" << endl;
				return;
			}
		}
	}
	else
	{
		system("pause");
		system("cls");
	}

}

//6.�޸Ĺ���
void modify(dormbook* dorm)
{
	cout << "��ȷ���Ƿ��޸�" << endl;
	cout << "1-��" << endl;
	cout << "0-��" << endl;

	int select;
	while (true)
	{
		cin >> select;
		if (select == 1 || select == 0)
		{
			break;
		}
	}
	
	if (select)//ȷ���޸�
	{
		cout << "������Ҫ�޸ĵ�������" << endl;
		int num;
		cin >> num;

		//�ж��������Ƿ����
		int ret = isExist(dorm, num);
		if (ret != -1)
		{
			cout << "�������޸ĺ�ĵ���������" << endl;
			string type;
			cin >> type;

			dorm->dormArray[ret].dorm_type = type;

			cout << "�������޸ĺ�Ĵ�λ" << endl;
			int bednum;
			cin >> bednum;

			dorm->dormArray[ret].bed_num = bednum;

			cout << "�������޸ĺ����ס����" << endl;
			int state;
			cin >> state;

			dorm->dormArray[ret].state = state;
			cout << "�޸ĳɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "�����Ų�����" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else
	{
		system("pause");
		system("cls");
		return;
	}

}


//7.ͳ�ƹ���
void count(dormbook* dorm)
{
	for (int i = 0; i < dorm->dorm_size; i++)
	{
		cout <<  dorm->dormArray[i].dorm_num <<"����������ס" << dorm->dormArray[i].state << "��" << endl;
	}
}

int main() 
{
	//�����������
	dormbook d;
	//����ѧ������
	studentbook stu;
	stu.stu_size = 0;
	d.dorm_size = 0;
	int order=0;

	while (true)
	{
		//���ò˵�
		menu();

		cout << "������ָ��" << endl;
		cin >> order;

		switch (order)
		{
		case 1://������Ϣ¼��
			adddorm(&d);
			break;
		case 2://ѧ����Ϣ¼��
			studentinput(&stu, &d);
			break;
		case 3://�������
			show(&d, &stu);
			break;
		case 4://���ҹ���
			findinformation(&stu, &d);
			break;
		case 5://ɾ������
			deleteinformation(&stu, &d);
			break;
		case 6://�޸Ĺ���
			modify(&d);
			break;
		case 7://ͳ�ƹ���
			count(&d);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�޶�Ӧ���ݣ����������롣" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
