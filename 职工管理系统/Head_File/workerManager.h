#pragma once  // ��ֻ֤����һ��
#include<iostream>
using namespace std;
#include<string>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
    // ���캯��
    WorkerManager();

    // չʾ�˵�
    void Show_Menu();

    // �˳�����
    void exitSystem();

    // ��¼ְ������
    int m_EmpNum;

    // ְ������ָ��
    Worker** m_EmpArray;

    // ���ְ��
    void Add_Emp();

    // �������ݵ��ļ�
    void save();

    // �ж��ļ��Ƿ�Ϊ�� ��־
    bool m_FileIsEmpty;

    // ͳ���ļ�������
    int get_EmpNum();

    // ��ʼ��Ա��
    void init_Emp();

    // ��ʾְ��
    void Show_Emp();

    // ɾ��ְ��
    void Del_Emp();

    // �ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã��������򷵻�-1
    int IsExist(int id);

    // �޸�ְ��
    void Mod_Emp();

    // ��ѯְ��
    void Find_Emp();

    // �������
    void Sort_Emp();

    void Clean_File();

    // ��������
    ~WorkerManager();
};