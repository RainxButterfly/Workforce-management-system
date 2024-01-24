#include "workerManager.h"

WorkerManager::WorkerManager()
{
    // 1、判断文件是否存在 --> 文件初始化的功能
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 以读的方式打开
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        // 初始化属性
        // 初始化记录人数
        this->m_EmpNum = 0;
        // 初始化数组指针
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 2、文件存在，数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // 文件为空
        cout << "文件为空!" << endl;
        // 初始化属性
        // 初始化记录人数
        this->m_EmpNum = 0;
        // 初始化数组指针
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // 将统计好的人数载入进来
    int num = this->get_EmpNum();
   /* cout << "职工人数为:" << num << endl;*/
    // 让用到的人数数量位置 就是保存文件中已经存在的数量了
    this->m_EmpNum = num;
    // 因为数量已经保存了 所以让数组指针的数量直接更新 且是开辟到堆区
    this->m_EmpArray = new Worker * [this->m_EmpNum];
    // 因为已经有了一定的空间大小了 所以接下来就是读取文件数据存放到里面
    init_Emp(); 

    // 测试数据
    /*for (int i = 0; i < this->m_EmpNum; i++)
    {
        cout << "职工号:   " << this->m_EmpArray[i]->m_ID
            << "  职工姓名:  " << this->m_EmpArray[i]->m_Name
            << "  部门编号:  " << this->m_EmpArray[i]->m_DeptID << endl;
    }*/
}

// 展示菜单的具体化
void WorkerManager::Show_Menu()
{
    cout << "************************************" << endl;
    cout << "******* 欢迎使用职工管理系统 *******" << endl;
    cout << "********** 0.退出管理程序 **********" << endl;
    cout << "********** 1.增加员工信息 **********" << endl;
    cout << "********** 2.显示员工信息 **********" << endl;
    cout << "********** 3.删除离职员工 **********" << endl;
    cout << "********** 4.修改职工信息 **********" << endl;
    cout << "********** 5.查找职工信息 **********" << endl;
    cout << "********** 6.按照编号排序 **********" << endl;
    cout << "********** 7.清空所有信息 **********" << endl;
    cout << "************************************" << endl;
}

void WorkerManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}

// 添加人员
void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工数量" << endl;
    int addNum = 0;// 保护用户输入的数量
    cin >> addNum;

    if (addNum > 0)
    {
        // 添加
        // 计算添加的新的空间大小
        int newSize = this->m_EmpNum + addNum; // 新空间人数 = 原来记录的人数+新增人数

        // 开辟新空间
        // 创建的一个二级指针 指向一个开辟的指针数组 数组中存放指针是因为数组只能放一种数据类型 那么让指针来指向不同的数据类型就可以 所以存放指针即可
        Worker** newSpace = new Worker * [newSize];

        // 将原来下的空间数据 拷贝到新的下面 这样子可以随时扩大数组了 原来的就弄到新的了
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                // 旧数组原来的位置在新数组依旧是原来位置
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        // 批量添加数据
        for (int i = 0; i < addNum; i++)
        {
            int id;  // 职工编号
            string name; // 职工姓名
            int dSelect; // 部门选择

            cout << "请输入第 " << i + 1 << " 个新职工编号:" << endl;
            cin >> id;

            cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
            cin >> name;

            cout << "请选择该职工的岗位:" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            // 多态方式
            Worker* worker = NULL; // 创建一个父类指针 然后可以指向需要选择的子类 调用子类来完成相应的功能
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            // 将创建职工职责保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
        // 释放原有空间
        delete[] this->m_EmpArray;

        // 更新新空间指向
        this->m_EmpArray = newSpace;

        // 更新新的职工人数
        this->m_EmpNum = newSize;
        
        // 更新职工不为空标志
        this->m_FileIsEmpty = false;

        // 提示添加成功
        cout << "成功添加" << addNum << "名新职工!" << endl;

        // 保存数据到文件中
        this->save();

        // 按任意键后清屏，回到上级目录
        system("pause");
        system("cls");
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
}

// 保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);  // 以输出的方式打开文件 --- 写文件
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_ID << "  "
            << this->m_EmpArray[i]->m_Name << "  "
            << this->m_EmpArray[i]->m_DeptID << endl;
    }

    // 关闭文件
    ofs.close();
}

// 统计人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 打开文件 并且读文件

    int id;
    string name;
    int dId;

    // 计数器
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }
    return num;
}

// 初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 读文件
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        // 创建一个父类对象的指针 用来指向对应的子类来存入数组
        Worker* worker = NULL;
        if (dId == 1)
        {
            worker = new Employee(id, name, 1);
        }
        else if (dId == 2)
        {
            worker = new Manager(id, name, 2);
        }
        else
        {
            worker = new Boss(id, name, 3);
        }
        // 存放到数组中 从0开始依次放入 这样就算读取文件数据到数组中 然后在此之后可以继续存放新的数据了
        this->m_EmpArray[index] = worker;
        index++;
    }
}

// 显示职工
void WorkerManager::Show_Emp()
{
    // 如果文件为空
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空!" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            // 利用多态调用程序接口
            // 用父类调用子类 子类不同 显示不同
            this->m_EmpArray[i]->showinfo();
        }
    }
    // 清屏
    system("pause");
    system("cls");
}

// 删除职工
void WorkerManager::Del_Emp()
{
    int id;
    cout << "请输入要删除的职工的编号" << endl;
    cin >> id;
    int index = IsExist(id);
    if (index != -1)
    {
        // 存在
        for (int i = index; i < this->m_EmpNum - 1; i++)
        {
            // 数据前移
            this->m_EmpArray[i] = this->m_EmpArray[i + 1];
        }
        this->m_EmpNum--; // 更新数组中记录人员个数
        cout << "删除成功!" << endl;
        // 数据同步道文件中
        this->save();
    }
    else
    {
        cout << "删除失败，未找到该职工!" << endl;
    }

    // 按任意键 清屏
    system("pause");
    system("cls");
}

// 判断职工是否存在，如果存在返回职工所在数组中的位置，不存在则返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1; // 假设不存在 存在则为下标的位置
    for (int i = 0; i < this->m_EmpNum;i++)
    {
        // 找到职工
        index = i;
        break;
    }
    return index;
}

void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        cout << "请输入要修改的职工的编号" << endl;
        int id;
        cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1)
        {
            // 存在
            delete this->m_EmpArray[ret]; // 释放改下标位置的数据内容

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到: " << id << "号职工,请输入新职工号:" << endl;
            cin >> newId;

            cout << "请输入新的姓名:" << endl;
            cin >> newName;

            cout << "请输入岗位:" << endl;
            cout << "1、普通员工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            Worker* worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }

            // 更新数据到数组中
            this->m_EmpArray[ret] = worker;

            cout << "修改成功!" << endl;

            // 保存到文件中
            this->save();
        }
        else
        {
            // 不存在
            cout << "修改失败,未查到此人!" << endl;
        }
    }
    // 按任意键清屏
    system("pause");
    system("cls");
}

void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入查找的方式:" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按职工姓名查找" << endl;

        int select = 0;
        cin >> select;

        if (select == 1)
        {
            // 按照编号查找
            int id;
            cout << "请输入要查找的职工的编号:" << endl;
            cin >> id;

            int ret = IsExist(id);
            if (ret != -1)
            {
                // 找到职工
                cout << "查询成功!该职工信息如下:" << endl;
                this->m_EmpArray[ret]->showinfo();
            }
            else
            {
                cout << "查询失败,查无此人!" << endl;
            }
        }
        else if (select == 2)
        {
            // 按照姓名查找
            string name;
            cout << "请输入查找的姓名:" << endl;
            cin >> name;

            // 加入判断是否查到的标志
            bool flag = false; // 默认未找到

            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "查询成功,职工编号为: " << this->m_EmpArray[i]->m_ID << "号职工信息如下:" << endl;

                    flag = true;

                    // 调用显示信息接口
                    this->m_EmpArray[i]->showinfo();
                }
            }
            if (!flag)
            {
                cout << "查询失败,查无此人！" << endl;
            }
        }
        else
        {
            cout << "输入选项有误!" << endl;
        }
    }

    // 按任意键清屏
    system("pause");
    system("cls");
}

// 编号排序
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空!" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "请选择排序方式:" << endl;
        cout << "1、按职工号进行升序" << endl;
        cout << "2、按职工号进行降序" << endl;

        int select = 0;
        cin >> select;
        // 排序： 这里用的是选择排序
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int minOrmax = i; // 初始最大或最小 是因为选择降序还是升序 所以命名成这样
            for (int j = i + 1; j < this->m_EmpNum; i++)
            {
                if (select == 1)
                {
                    // 升序
                    if (this->m_EmpArray[minOrmax]->m_ID > this->m_EmpArray[j]->m_ID)
                    {
                        minOrmax = j;
                    }
                }
                else
                {
                    // 降序
                    if (this->m_EmpArray[minOrmax]->m_ID < this->m_EmpArray[j]->m_ID)
                    {
                        minOrmax = j;
                    }
                }
                // 交换数据
            }

            // 交换数据 
            if (i != minOrmax)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
                this->m_EmpArray[minOrmax] = temp;
            }
        }

        cout << "排序成功!排序后的结果为:" << endl;
        this->save(); // 排序后的结果保存到文件中
        this->Show_Emp(); // 展示所有职工
    }
}

void WorkerManager::Clean_File()
{
    int select = 0;
    cout << "确定清空?" << endl;
    cout << "1、确定" << endl;
    cout << "2、取消" << endl;
    cin >> select;

    if (select == 1)
    {
        // 清空文件
        ofstream ofs(FILENAME, ios::trunc); // 先删除文件后再创建
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            // 删除堆区中的每个职工对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                m_EmpArray[i] = NULL;
            }

            // 删除堆区的指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true; 
        }

        cout << "清空成功!" << endl;
    }

    // 清屏
    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager()
{
    // 这个释放是最后的 也就是用完了 然后把堆区的内存释放掉
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}