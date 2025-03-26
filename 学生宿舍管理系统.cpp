#include"iostream"
using namespace std;
#include<string>
#define MAX 1000
#include"fstream"

//菜单界面
void menu()
{
	cout << "1.宿舍信息录入" << endl;
	cout << "2.学生信息录入" << endl;
	cout << "3.浏览全部信息" << endl;
	cout << "4.查找信息功能" << endl;
	cout << "5.信息删除功能" << endl;
	cout << "6.信息修改功能" << endl;
	cout << "7.人数统计功能" << endl;
	cout << "0.退出系统功能" << endl;
	cout << "**************" << endl;
}

//创建宿舍结构体
struct dorm
{
	int dorm_num;//宿舍编号
	string dorm_type;//宿舍类型
	int bed_num;//床位数量
	int state;//入住状态
};

//宿舍录
struct dormbook
{
	struct dorm dormArray[MAX];
	int dorm_size;
};

//创建学生结构体
struct student
{
	string stu_id;//学号
	string stu_name;//姓名
	int stu_sex;//性别
	string stu_class;//学生班级
	int stu_dormid;//宿舍编号
};

struct studentbook
{
	student stuArray[MAX];
	int stu_size;
};

//判断宿舍是否存在
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

//1.宿舍信息录入
void adddorm(dormbook* dorm)
{
	if (dorm->dorm_size== MAX)
	{
		cout << "宿舍已满，无法添加" << endl;
		return;
	}
	else
	{
		//添加宿舍
		int num;
		cout << "请输入宿舍编号" << endl;
		cin >> num ;
		int ret = isExist_dorm(dorm, num);
		if (ret)//如果宿舍编号存在
		{
			cout << "宿舍编号已存在,请重新输入" << endl;
			return;
		}
		else//不存在即可输入
		{
			//输入宿舍编号
			dorm->dormArray[dorm->dorm_size].dorm_num = num;

			//输入宿舍类型
			string type;
			cout << "请输入宿舍类型" << endl;
			cin >> type;
			dorm->dormArray[dorm->dorm_size].dorm_type = type;

			//输入宿舍床位
			int n;
			cout << "请输入宿舍床位数" << endl;
			cin >> n;
			dorm->dormArray[dorm->dorm_size].bed_num = n;

			//输入状态
			int state;
			cout << "请输入已入住人数" << endl;
			cin >> state;
			dorm->dormArray[dorm->dorm_size].state = state;
			
			//文件输入
			ofstream ofs;
			ofs.open("text.txt", ios::app);

			ofs << "宿舍编号：" << dorm->dormArray[dorm->dorm_size].dorm_num << endl;
			ofs << "宿舍类型：" << dorm->dormArray[dorm->dorm_size].dorm_type << endl;
			ofs << "宿舍床位" << dorm->dormArray[dorm->dorm_size].bed_num << endl;
			ofs << "已入住" << dorm->dormArray[dorm->dorm_size].state<<"人" << endl;

			ofs.close();

			dorm->dorm_size++;
			cout << "信息录入成功" << endl;
			system("pause");
			system("cls");
			return;
		}


	}
}

//判断宿舍是否存在二号
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

//判断学生的学号是否存在
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

//2.学生信息录入
void studentinput(studentbook* stu, dormbook* dorm)
{
	//学号
	string num;
	cout << "请输入您的学号" << endl;
	cin >> num;
	int ret = isExistid(stu, num);
	if (ret)//学号已重复
	{
		cout << "学号已存在，无法输入" << endl;
		return;
	}
	else
	{
		int n;
		cout << "请输入宿舍编号" << endl;
		cin >> n;
		int r = isExist_dorm(dorm, n);
		//判断宿舍编号是否存在
		if (r)//如果宿舍编号存在
		{
			//姓名
			string name;
			cout << "请输入你的姓名" << endl;
			cin >> name;
			stu->stuArray[stu->stu_size].stu_name = name;

			//性别
			cout << "请输入性别：" << endl;
			cout << "1---男" << endl;
			cout << "2---女" << endl;
			int sex = 0;
			while (true) 
			{
				//如果输入为1或2则可以退出循环，因为输入的是正确值
				//如果输入有误，请重新输入
				cin >> sex;

				if (sex == 1 || sex == 2)
				{
					stu->stuArray[stu->stu_size].stu_sex = sex;
					break;

				}
				cout << "输入有误，请重新输入" << endl;
			}

			//班级
			string cla;
			cout << "请输入您的班级" << endl;
			cin >> cla;
			stu->stuArray[stu->stu_size].stu_class = cla;

			//可输入
			stu->stuArray[stu->stu_size].stu_id = num;

			//输入宿舍编号
			stu->stuArray[stu->stu_size].stu_dormid = n;

			//返回宿舍编号
			int result = isExist_dorm(dorm,stu, n);
			//入住人数增加
			dorm->dormArray[result].state++;

			ofstream ofs;
			ofs.open("text.txt", ios::app);

			ofs <<"学生姓名："<< stu->stuArray[stu->stu_size].stu_name << endl;
			ofs <<"学号："<< stu->stuArray[stu->stu_size].stu_id << endl;
			ofs << "班级："<< stu->stuArray[stu->stu_size].stu_class << endl;
			ofs <<"性别：" <<(stu->stuArray[stu->stu_size].stu_sex == 1?"男":"女") << endl;
			ofs << "宿舍编号：" << stu->stuArray[stu->stu_size].stu_dormid << endl;
			ofs << "宿舍" << result << "已入住" << dorm->dormArray[result].state << "人" << endl;

			ofs.close();

			stu->stu_size++;
			
			cout << "信息输入成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
		else//不存在不可输入
		{
			cout << "宿舍不存在，请重新操作" << endl;
			return;
		}
	}
}

//3.浏览功能
void show(dormbook* dorm, studentbook* s)
{

	for (int i = 0; i < dorm->dorm_size; i++)
	{
		cout << "宿舍编号:" << dorm->dormArray[i].dorm_num << "\t";
		cout << "宿舍类型:" << dorm->dormArray[i].dorm_type << "\t";
		cout << "床位数量:" << dorm->dormArray[i].bed_num << "\t";
		cout << "宿舍编号：" << dorm->dormArray[i].dorm_num << "已入住" << dorm->dormArray[i].state << "人" << endl;
		cout << "*******************************" << endl;
	}
	for (int i = 0; i < s->stu_size; i++)
	{
		cout << "学号：" << s->stuArray[i].stu_id << "\t";
		cout << "姓名：" << s->stuArray[i].stu_name << "\t";
		cout << "性别：" << (s->stuArray[i].stu_sex == 1 ? "男" : "女") << "\t";
		cout << "班级：" << s->stuArray[i].stu_class<< "\t";
		cout << "宿舍编号：" << s->stuArray[i].stu_dormid << endl;
	}
	system("pause");
	system("cls");
}


//判断宿舍是否存在
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

//判断学生的学号是否存在
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

//4.查找功能
void findinformation(studentbook* stu, dormbook* dorm)
{
	cout << "请问您将按宿舍编号查询还是按学号查询" << endl;
	cout << "1-按宿舍编号查询" << endl;
	cout << "0-按学号查询" << endl;
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
		cout << "请输入要查找的宿舍编号" << endl;
		int num;
		cin >> num;

		//判断宿舍编号是否存在
		int ret = isExist(dorm, num);
		if (ret != -1)
		{
			cout << "宿舍编号:" << dorm->dormArray[ret].dorm_num << "\t";
			cout << "宿舍类型:" << dorm->dormArray[ret].dorm_type << "\t";
			cout << "床位数量:" << dorm->dormArray[ret].bed_num << "\t";
			cout << "宿舍编号：" << dorm->dormArray[ret].dorm_num << "\t已入住" << dorm->dormArray[ret].state << "人" << endl;
			cout << "*******************************" << endl;

			for (int i = 0; i < stu->stu_size; i++)
			{	
				if (stu->stuArray[i].stu_dormid == num)
				{
					cout << "学号：" << stu->stuArray[i].stu_id << "\t";
					cout << "姓名：" << stu->stuArray[i].stu_name << "\t";
					cout << "性别：" << (stu->stuArray[i].stu_sex == 1 ? "男" : "女") << "\t";
					cout << "班级：" << stu->stuArray[i].stu_class << "\t";
					cout << "宿舍编号：" << stu->stuArray[i].stu_dormid << endl;
				}
			}
			system("pause");
			system("cls");
		}
		else
		{
			cout << "该宿舍不存在" << endl;
			return;
		}
	}
	else//按学号查询
	{
		cout << "请输入要查找的学号" << endl;
		string id;
		cin >> id;

		int r = isExist_id(stu, id);
		if (r != -1)//如果学号存在
		{
			cout << "学号：" << stu->stuArray[r].stu_id << "\t";
			cout << "姓名：" << stu->stuArray[r].stu_name << "\t";
			cout << "性别：" << (stu->stuArray[r].stu_sex == 1 ? "男" : "女") << "\t";
			cout << "班级：" << stu->stuArray[r].stu_class << "\t";
			cout << "宿舍编号：" << stu->stuArray[r].stu_dormid << endl;

			cout << "******************" << endl;

			for (int i = 0; i < dorm->dorm_size; i++)
			{
				if (dorm->dormArray[i].dorm_num == stu->stuArray[r].stu_dormid)
				{
					cout << "宿舍编号:" << dorm->dormArray[i].dorm_num << "\t";
					cout << "宿舍类型:" << dorm->dormArray[i].dorm_type << "\t";
					cout << "床位数量:" << dorm->dormArray[i].bed_num << "\t";
					cout << "宿舍编号：" << dorm->dormArray[i].dorm_num << "\t已入住" << dorm->dormArray[i].state << "人" << endl;
				}
			}
		}
		else//若学号不存在
		{
			cout << "学号不存在，请重新操作" << endl;
			return;
		}

		system("pause");
		system("cls");
	}
}

//5.删除功能
void deleteinformation(studentbook*stu, dormbook*dorm)
{
	cout << "请确认是否要进行删除操作" << endl;
	cout << "1-是" << endl;
	cout << "0-否" << endl;
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
		cout << "请问您将按宿舍编号查询还是按学号删除" << endl;
		cout << "1-按宿舍编号删除" << endl;
		cout << "0-按学号删除" << endl;
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
			cout << "请输入要删除的宿舍编号" << endl;
			int num;

			cin >> num;
			//判断宿舍编号是否存在
			int ret = isExist(dorm, num);
			if (ret != -1)
			{
				for (int i = ret; i < dorm->dorm_size; i++)
				{
					//数据前移
					dorm->dormArray[i] = dorm->dormArray[i + 1];
				}

				for (int i = 0; i < stu->stu_size; i++)
				{
					if (stu->stuArray[i].stu_dormid == dorm->dormArray[dorm->dorm_size].dorm_num)
					{
						stu->stuArray[i].stu_dormid = 0;
					
					}
				}

				dorm->dorm_size--;//更新宿舍数

				//更新文件中的信息
				ofstream ofs;
				ofs.open("text.txt", ios::trunc );

				for (int i = 0; i < dorm->dorm_size; i++)
				{
					ofs << "宿舍编号:" << dorm->dormArray[i].dorm_num << "\t";
					ofs << "宿舍类型:" << dorm->dormArray[i].dorm_type << "\t";
					ofs << "床位数量:" << dorm->dormArray[i].bed_num << "\t";
					ofs << "宿舍编号：" << dorm->dormArray[i].dorm_num << "\t已入住" << dorm->dormArray[i].state << "人" << endl;
					ofs << "*******************************" << endl;
				}

				for (int i = 0; i < stu->stu_size; i++)
				{
					ofs << "学号：" << stu->stuArray[i].stu_id << "\t";
					ofs << "姓名：" << stu->stuArray[i].stu_name << "\t";
					ofs << "性别：" << (stu->stuArray[i].stu_sex == 1 ? "男" : "女") << "\t";
					ofs << "班级：" << stu->stuArray[i].stu_class << "\t";
					ofs << "宿舍编号：" << stu->stuArray[i].stu_dormid << endl;
				}
				ofs.close();

				cout << "删除成功" << endl;
			}
			else
			{
				cout << "宿舍编号不存在" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "请输入要删除的学号" << endl;
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

				cout << "删除成功" << endl;

				system("pause");
				system("cls");
			}
			else
			{
				cout << "查无此人" << endl;
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

//6.修改功能
void modify(dormbook* dorm)
{
	cout << "请确认是否修改" << endl;
	cout << "1-是" << endl;
	cout << "0-否" << endl;

	int select;
	while (true)
	{
		cin >> select;
		if (select == 1 || select == 0)
		{
			break;
		}
	}
	
	if (select)//确认修改
	{
		cout << "请输入要修改的宿舍编号" << endl;
		int num;
		cin >> num;

		//判断宿舍编号是否存在
		int ret = isExist(dorm, num);
		if (ret != -1)
		{
			cout << "请输入修改后的的宿舍类型" << endl;
			string type;
			cin >> type;

			dorm->dormArray[ret].dorm_type = type;

			cout << "请输入修改后的床位" << endl;
			int bednum;
			cin >> bednum;

			dorm->dormArray[ret].bed_num = bednum;

			cout << "请输入修改后的入住人数" << endl;
			int state;
			cin >> state;

			dorm->dormArray[ret].state = state;
			cout << "修改成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		else
		{
			cout << "宿舍编号不存在" << endl;
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


//7.统计功能
void count(dormbook* dorm)
{
	for (int i = 0; i < dorm->dorm_size; i++)
	{
		cout <<  dorm->dormArray[i].dorm_num <<"号宿舍已入住" << dorm->dormArray[i].state << "人" << endl;
	}
}

int main() 
{
	//创建宿舍变量
	dormbook d;
	//创建学生变量
	studentbook stu;
	stu.stu_size = 0;
	d.dorm_size = 0;
	int order=0;

	while (true)
	{
		//调用菜单
		menu();

		cout << "请输入指令" << endl;
		cin >> order;

		switch (order)
		{
		case 1://宿舍信息录入
			adddorm(&d);
			break;
		case 2://学生信息录入
			studentinput(&stu, &d);
			break;
		case 3://浏览功能
			show(&d, &stu);
			break;
		case 4://查找功能
			findinformation(&stu, &d);
			break;
		case 5://删除功能
			deleteinformation(&stu, &d);
			break;
		case 6://修改功能
			modify(&d);
			break;
		case 7://统计功能
			count(&d);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "无对应操纵，请重新输入。" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
