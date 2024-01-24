#include<iostream>
using namespace std;
#include "workerManager.h"

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include "boss.h"

int main()
{
    // 测试代码
   /* Worker* worker = NULL;
    worker = new Employee(1, "张三", 1);
    worker->showinfo();
    delete worker;

    worker = new Manager(2, "李四", 2);
    worker->showinfo();
    delete worker;

    worker = new Boss(3, "王五", 3);
    worker->showinfo();
    delete worker;*/
    // 实例化管理对象
    WorkerManager wm;
    // 读取用户的选择
    int choice;

    while (true)
    {
        // 调用展示菜单的成员函数
        wm.Show_Menu();

        cout << "请输入你的选择" << endl;
        cin >> choice;  // 接受用户的选择

        switch (choice)
        {
        case 0: // 退出系统
            wm.exitSystem();
            break;
        case 1: // 添加职工
            wm.Add_Emp();
            break;
        case 2: // 显示职工
            wm.Show_Emp();
            break;
        case 3: // 删除职工
            wm.Del_Emp();
            break;
        case 4: // 修改职工
            wm.Mod_Emp();
            break;
        case 5: // 查找职工
            wm.Find_Emp();
            break;
        case 6: // 排序职工
            wm.Sort_Emp();
            break;
        case 7: // 清空文档
            break;
        default:
            system("cls");
            break;
        }
    }

    return 0;
}