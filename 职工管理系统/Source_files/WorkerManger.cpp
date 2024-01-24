#include "workerManager.h"

WorkerManager::WorkerManager()
{
    // 1���ж��ļ��Ƿ���� --> �ļ���ʼ���Ĺ���
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // �Զ��ķ�ʽ��
    if (!ifs.is_open())
    {
        cout << "�ļ�������" << endl;
        // ��ʼ������
        // ��ʼ����¼����
        this->m_EmpNum = 0;
        // ��ʼ������ָ��
        this->m_EmpArray = NULL;
        // ��ʼ���ļ��Ƿ�Ϊ��
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // 2���ļ����ڣ�����Ϊ��
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        // �ļ�Ϊ��
        cout << "�ļ�Ϊ��!" << endl;
        // ��ʼ������
        // ��ʼ����¼����
        this->m_EmpNum = 0;
        // ��ʼ������ָ��
        this->m_EmpArray = NULL;
        // ��ʼ���ļ��Ƿ�Ϊ��
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // ��ͳ�ƺõ������������
    int num = this->get_EmpNum();
   /* cout << "ְ������Ϊ:" << num << endl;*/
    // ���õ�����������λ�� ���Ǳ����ļ����Ѿ����ڵ�������
    this->m_EmpNum = num;
    // ��Ϊ�����Ѿ������� ����������ָ�������ֱ�Ӹ��� ���ǿ��ٵ�����
    this->m_EmpArray = new Worker * [this->m_EmpNum];
    // ��Ϊ�Ѿ�����һ���Ŀռ��С�� ���Խ��������Ƕ�ȡ�ļ����ݴ�ŵ�����
    init_Emp(); 

    // ��������
    /*for (int i = 0; i < this->m_EmpNum; i++)
    {
        cout << "ְ����:   " << this->m_EmpArray[i]->m_ID
            << "  ְ������:  " << this->m_EmpArray[i]->m_Name
            << "  ���ű��:  " << this->m_EmpArray[i]->m_DeptID << endl;
    }*/
}

// չʾ�˵��ľ��廯
void WorkerManager::Show_Menu()
{
    cout << "************************************" << endl;
    cout << "******* ��ӭʹ��ְ������ϵͳ *******" << endl;
    cout << "********** 0.�˳�������� **********" << endl;
    cout << "********** 1.����Ա����Ϣ **********" << endl;
    cout << "********** 2.��ʾԱ����Ϣ **********" << endl;
    cout << "********** 3.ɾ����ְԱ�� **********" << endl;
    cout << "********** 4.�޸�ְ����Ϣ **********" << endl;
    cout << "********** 5.����ְ����Ϣ **********" << endl;
    cout << "********** 6.���ձ������ **********" << endl;
    cout << "********** 7.���������Ϣ **********" << endl;
    cout << "************************************" << endl;
}

void WorkerManager::exitSystem()
{
    cout << "��ӭ�´�ʹ��" << endl;
    system("pause");
    exit(0);
}

// �����Ա
void WorkerManager::Add_Emp()
{
    cout << "���������ְ������" << endl;
    int addNum = 0;// �����û����������
    cin >> addNum;

    if (addNum > 0)
    {
        // ���
        // ������ӵ��µĿռ��С
        int newSize = this->m_EmpNum + addNum; // �¿ռ����� = ԭ����¼������+��������

        // �����¿ռ�
        // ������һ������ָ�� ָ��һ�����ٵ�ָ������ �����д��ָ������Ϊ����ֻ�ܷ�һ���������� ��ô��ָ����ָ��ͬ���������;Ϳ��� ���Դ��ָ�뼴��
        Worker** newSpace = new Worker * [newSize];

        // ��ԭ���µĿռ����� �������µ����� �����ӿ�����ʱ���������� ԭ���ľ�Ū���µ���
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                // ������ԭ����λ����������������ԭ��λ��
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        // �����������
        for (int i = 0; i < addNum; i++)
        {
            int id;  // ְ�����
            string name; // ְ������
            int dSelect; // ����ѡ��

            cout << "������� " << i + 1 << " ����ְ�����:" << endl;
            cin >> id;

            cout << "������� " << i + 1 << " ����ְ��������" << endl;
            cin >> name;

            cout << "��ѡ���ְ���ĸ�λ:" << endl;
            cout << "1����ְͨ��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
            cin >> dSelect;

            // ��̬��ʽ
            Worker* worker = NULL; // ����һ������ָ�� Ȼ�����ָ����Ҫѡ������� ���������������Ӧ�Ĺ���
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
            // ������ְ��ְ�𱣴浽������
            newSpace[this->m_EmpNum + i] = worker;
        }
        // �ͷ�ԭ�пռ�
        delete[] this->m_EmpArray;

        // �����¿ռ�ָ��
        this->m_EmpArray = newSpace;

        // �����µ�ְ������
        this->m_EmpNum = newSize;
        
        // ����ְ����Ϊ�ձ�־
        this->m_FileIsEmpty = false;

        // ��ʾ��ӳɹ�
        cout << "�ɹ����" << addNum << "����ְ��!" << endl;

        // �������ݵ��ļ���
        this->save();

        // ����������������ص��ϼ�Ŀ¼
        system("pause");
        system("cls");
    }
    else
    {
        cout << "������������" << endl;
    }
}

// �����ļ�
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);  // ������ķ�ʽ���ļ� --- д�ļ�
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_ID << "  "
            << this->m_EmpArray[i]->m_Name << "  "
            << this->m_EmpArray[i]->m_DeptID << endl;
    }

    // �ر��ļ�
    ofs.close();
}

// ͳ������
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // ���ļ� ���Ҷ��ļ�

    int id;
    string name;
    int dId;

    // ������
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }
    return num;
}

// ��ʼ��Ա��
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // ���ļ�
    int id;
    string name;
    int dId;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        // ����һ����������ָ�� ����ָ���Ӧ����������������
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
        // ��ŵ������� ��0��ʼ���η��� ���������ȡ�ļ����ݵ������� Ȼ���ڴ�֮����Լ�������µ�������
        this->m_EmpArray[index] = worker;
        index++;
    }
}

// ��ʾְ��
void WorkerManager::Show_Emp()
{
    // ����ļ�Ϊ��
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��߼�¼Ϊ��!" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            // ���ö�̬���ó���ӿ�
            // �ø���������� ���಻ͬ ��ʾ��ͬ
            this->m_EmpArray[i]->showinfo();
        }
    }
    // ����
    system("pause");
    system("cls");
}

// ɾ��ְ��
void WorkerManager::Del_Emp()
{
    int id;
    cout << "������Ҫɾ����ְ���ı��" << endl;
    cin >> id;
    int index = IsExist(id);
    if (index != -1)
    {
        // ����
        for (int i = index; i < this->m_EmpNum - 1; i++)
        {
            // ����ǰ��
            this->m_EmpArray[i] = this->m_EmpArray[i + 1];
        }
        this->m_EmpNum--; // ���������м�¼��Ա����
        cout << "ɾ���ɹ�!" << endl;
        // ����ͬ�����ļ���
        this->save();
    }
    else
    {
        cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��!" << endl;
    }

    // ������� ����
    system("pause");
    system("cls");
}

// �ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã��������򷵻�-1
int WorkerManager::IsExist(int id)
{
    int index = -1; // ���費���� ������Ϊ�±��λ��
    for (int i = 0; i < this->m_EmpNum;i++)
    {
        // �ҵ�ְ��
        index = i;
        break;
    }
    return index;
}

void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
    }
    else
    {
        cout << "������Ҫ�޸ĵ�ְ���ı��" << endl;
        int id;
        cin >> id;

        int ret = this->IsExist(id);
        if (ret != -1)
        {
            // ����
            delete this->m_EmpArray[ret]; // �ͷŸ��±�λ�õ���������

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "�鵽: " << id << "��ְ��,��������ְ����:" << endl;
            cin >> newId;

            cout << "�������µ�����:" << endl;
            cin >> newName;

            cout << "�������λ:" << endl;
            cout << "1����ͨԱ��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
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

            // �������ݵ�������
            this->m_EmpArray[ret] = worker;

            cout << "�޸ĳɹ�!" << endl;

            // ���浽�ļ���
            this->save();
        }
        else
        {
            // ������
            cout << "�޸�ʧ��,δ�鵽����!" << endl;
        }
    }
    // �����������
    system("pause");
    system("cls");
}

void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ��" << endl;
    }
    else
    {
        cout << "��������ҵķ�ʽ:" << endl;
        cout << "1����ְ����Ų���" << endl;
        cout << "2����ְ����������" << endl;

        int select = 0;
        cin >> select;

        if (select == 1)
        {
            // ���ձ�Ų���
            int id;
            cout << "������Ҫ���ҵ�ְ���ı��:" << endl;
            cin >> id;

            int ret = IsExist(id);
            if (ret != -1)
            {
                // �ҵ�ְ��
                cout << "��ѯ�ɹ�!��ְ����Ϣ����:" << endl;
                this->m_EmpArray[ret]->showinfo();
            }
            else
            {
                cout << "��ѯʧ��,���޴���!" << endl;
            }
        }
        else if (select == 2)
        {
            // ������������
            string name;
            cout << "��������ҵ�����:" << endl;
            cin >> name;

            // �����ж��Ƿ�鵽�ı�־
            bool flag = false; // Ĭ��δ�ҵ�

            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "��ѯ�ɹ�,ְ�����Ϊ: " << this->m_EmpArray[i]->m_ID << "��ְ����Ϣ����:" << endl;

                    flag = true;

                    // ������ʾ��Ϣ�ӿ�
                    this->m_EmpArray[i]->showinfo();
                }
            }
            if (!flag)
            {
                cout << "��ѯʧ��,���޴��ˣ�" << endl;
            }
        }
        else
        {
            cout << "����ѡ������!" << endl;
        }
    }

    // �����������
    system("pause");
    system("cls");
}

// �������
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ��!" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "��ѡ������ʽ:" << endl;
        cout << "1����ְ���Ž�������" << endl;
        cout << "2����ְ���Ž��н���" << endl;

        int select = 0;
        cin >> select;
        // ���� �����õ���ѡ������
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int minOrmax = i; // ��ʼ������С ����Ϊѡ���������� ��������������
            for (int j = i + 1; j < this->m_EmpNum; i++)
            {
                if (select == 1)
                {
                    // ����
                    if (this->m_EmpArray[minOrmax]->m_ID > this->m_EmpArray[j]->m_ID)
                    {
                        minOrmax = j;
                    }
                }
                else
                {
                    // ����
                    if (this->m_EmpArray[minOrmax]->m_ID < this->m_EmpArray[j]->m_ID)
                    {
                        minOrmax = j;
                    }
                }
                // ��������
            }

            // �������� 
            if (i != minOrmax)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
                this->m_EmpArray[minOrmax] = temp;
            }
        }

        cout << "����ɹ�!�����Ľ��Ϊ:" << endl;
        this->save(); // �����Ľ�����浽�ļ���
        this->Show_Emp(); // չʾ����ְ��
    }
}

void WorkerManager::Clean_File()
{
    int select = 0;
    cout << "ȷ�����?" << endl;
    cout << "1��ȷ��" << endl;
    cout << "2��ȡ��" << endl;
    cin >> select;

    if (select == 1)
    {
        // ����ļ�
        ofstream ofs(FILENAME, ios::trunc); // ��ɾ���ļ����ٴ���
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            // ɾ�������е�ÿ��ְ������
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
                m_EmpArray[i] = NULL;
            }

            // ɾ��������ָ��
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true; 
        }

        cout << "��ճɹ�!" << endl;
    }

    // ����
    system("pause");
    system("cls");
}

WorkerManager::~WorkerManager()
{
    // ����ͷ������� Ҳ���������� Ȼ��Ѷ������ڴ��ͷŵ�
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}