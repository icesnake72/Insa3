//
// 2023�� 1�� 30��, Coded by E.B Kim
//
// �ʰ��� �λ�������� �޴� �� ���� ���÷��� ���� �Լ���
//
// ���̼��� ����(������ ���̼���)



#include "showinfo.h"


void ShowMenu()
{
    system("cls");  // msc������ ����, ȭ�� Ŭ���� ���ִ� �Լ��Դϴ�.

    printf("1. ���� ���� ����\n");
    printf("2. ���� ���� �Է�\n");
    printf("3. ���� ���� ����(�̱���)\n");
    printf("4. ���� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("5. �μ� ���� ����\n");
    printf("6. �μ� ���� �Է�\n");
    printf("7. �μ� ���� ����(�̱���)\n");
    printf("8. �μ� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("9  ���� ���� ����\n");
    printf("0. ���� ���� �Է�\n");
    printf("a. ���� ���� ����(�̱���)\n");
    printf("b. ���� ���� ����(�̱���)\n");
    printf("============================\n");
    printf("x. ����\n");
    printf("============================\n");
    printf("���Ͻô� �޴��� �����ϼ���");
}


void ShowSubMenu()
{
    for (int i = 0; i < 50; i++) printf("=");

    printf("\n");
    printf("p. ���� �޴��� ���ư���\n");

    int n = 0;
    while (n = _getch())
    {
        if ('p' == n || 'P' == n)
            return;
    }
}


void PrintTitle(short mode)
{
    switch (mode)
    {
    case RW_EMPLOYEE:
        printf("���\t");
        printf("�̸�\t\t");
        printf("�μ��ڵ�\t");
        printf("�����ڵ�\n");
        for (int i = 0; i < 50; i++)
            printf("=");

        printf("\n");
        break;

    case RW_BUSEO:
        printf("�μ��ڵ�\t");
        printf("�μ���\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    case RW_JIKGUP:
        printf("�����ڵ�\t");
        printf("���޸�\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    default:
        ErrorHandle(INVALID_MODE);
    }
}

// pData ���ڵ� �Ѱ��Դϴ�.
// ���������� �Ѱ��� ���ڵ��̰�, �μ��� ������ ��ü ���ڵ带 ���� ȣ���
void PrintEmployeeRecord(void* pData, size_t empSize, BUSEO_CODE* pbu, size_t buSize, JIKGUP_CODE* pji, size_t jiSize)
{
    CHK_2PARAM_V(pData, empSize);
    CHK_2PARAM_V(pbu, buSize);
    CHK_2PARAM_V(pji, jiSize);

    char tmp[20] = { 0 };   // ���ڿ��� ������� �迭, �μ��̸� �Ǵ� �����̸��� ���⿡ ���� ����
    EMPLOYEE* emp = (EMPLOYEE*)pData;   // ����ü �Ѱ�, �ϳ��� ���ڵ�

    // (����) ? ���̸� ���� : �����̸� ����; ===> 3�� ������

    printf("%d\t", emp->num);       // ���
    printf("%s\t\t", emp->name);    // �̸��� �׳� ���
    GetBuseoName(emp->buseo, pbu, buSize, tmp, 20) == SUCCESS_RES ? printf("%s\t\t", tmp) : printf("%d\t\t", emp->buseo);
    memset(tmp, 0, 20);
    GetJikgupName(emp->jikgup, pji, jiSize, tmp, 20) == SUCCESS_RES ? printf("%s\n", tmp) : printf("%d\n", emp->jikgup);
}

void PrintBuseoRecord(BUSEO_CODE* pbu, size_t buSize)
{
    CHK_2PARAM_V(pbu, buSize);

    u_int nCount = (u_int)(buSize / sizeof(BUSEO_CODE));
    for (u_int i = 0; i < nCount; i++)
    {
        printf("%d\t", pbu[i].code);
        printf("%s\n", pbu[i].buseo_name);
    }
}

void PrintJikgupRecord(JIKGUP_CODE* pji, size_t jiSize)
{
    CHK_2PARAM_V(pji, jiSize);

    system("cls");
    PrintTitle(RW_JIKGUP);


    u_int nCount = (u_int)(jiSize / sizeof(JIKGUP_CODE));
    for (u_int i = 0; i < nCount; i++)
    {
        printf("%d\t", pji[i].code);
        printf("%s\n", pji[i].jikgup_name);
    }
}

// ��ü ���۸� ������ ��
void PrintRecord(short mode, void* pData, size_t empSize, BUSEO_CODE* pbu, size_t buSize, JIKGUP_CODE* pji, size_t jiSize)
{
    system("cls");
    PrintTitle(mode);

    u_int nCount = 0;
    EMPLOYEE* pemp = (EMPLOYEE*)pData;  // �޸� ī�Ǵ� �ƴϰ�, ������ �������ٰ� �׳� �����͸� �ѱ��!!!
    

    switch (mode)
    {
    case RW_EMPLOYEE:
        CHK_2PARAM_V(pData, empSize);

        nCount = (u_int)(empSize / sizeof(EMPLOYEE));   // ���ڵ���� ����
        for (u_int i = 0; i < nCount; i++)  // ���ڵ� ����ŭ �ݺ��ؼ� ����Ϸ��� ��
            PrintEmployeeRecord(&pemp[i], empSize, pbu, buSize, pji, jiSize);   // ���ڵ� �Ѱ��� ���� ȣ��
        break;


    case RW_BUSEO:
        CHK_2PARAM_V(pbu, buSize);
        PrintBuseoRecord(pbu, (size_t)buSize);
        break;



    case RW_JIKGUP:
        CHK_2PARAM_V(pji, jiSize);
        PrintJikgupRecord(pji, jiSize);
        break;

    }
    ShowSubMenu();
}

short InputRecord(EMPLOYEE* emp, EMPLOYEE* emps, size_t lSize)
{
    CHK_PARAM(emp);

    //
    // emps �� lSize�� ���� ��쿡�� �ڵ� �ߺ� üũ�� ���� �����Ƿ� 
    // CHK_2PARAM()�� ���� �ʴ´�.
    //


    printf("���� �����ͺ��̽� �Է� ���α׷��Դϴ�\n\n");

    //
    // �߿�!!!(������ ���ÿ�)
    // ���Ĵٵ� ��ǲ���κ��� ���۸� �ǵ�����.
    // �ѱ� ���� �޴��� ���������� scanf_s�� ���������� �������� �ʾ� �̸� �ذ��ϱ� ���� �����    
    //
    rewind(stdin);
    //


    int nRet = 0;

    //
    // res�� �⺻���� CODE_NOT_FOUND�� �س��� �����ؾ�
    // �ߺ� üũ�� ���� ������� res==CODE_NOT_FOUND �� �Ǿ�
    // do~while() ������ ���� ���� �� �ִ�.
    s_res res = CODE_NOT_FOUND;


    do
    {
        printf("����� �Է����ּ���\n");
        nRet = scanf_s("%hd", &emp->num);
        if (!nRet) return CANNOT_READ;

        if (emps && lSize)
            res = ExistCode(emp->num, RW_EMPLOYEE, (void*)emps, lSize);

        if (res == CODE_EXIST)
            printf("�̹� �����ϴ� �����ȣ�Դϴ�. �ٸ� ��ȣ�� �Է����ּ���\n");

    } while (res == CODE_EXIST);


    printf("���� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%29s", emp->name, (unsigned int)sizeof(emp->name));
    if (!nRet) return CANNOT_READ;

    printf("�μ� �ڵ带 �Է����ּ���\n");
    nRet = scanf_s("%hd", &emp->buseo);
    if (!nRet) return CANNOT_READ;

    printf("���� �ڵ带 �Է����ּ���\n");
    scanf_s("%hd", &emp->jikgup);
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}

short InputBuseo(BUSEO_CODE* code, BUSEO_CODE* pbu, size_t lSize)
{
    CHK_PARAM(code);

    //
    // pbu �� lSize�� ���� ��쿡�� �ڵ� �ߺ� üũ�� ���� �����Ƿ� 
    // CHK_2PARAM()�� ���� �ʴ´�.
    //

    printf("�μ� ���� ������ �Է����ּ���\n\n");

    //
    // �߿�!!!(������ ���ÿ�)
    // ���Ĵٵ� ��ǲ���κ��� ���۸� �ǵ�����.
    // �ѱ� ���� �޴��� ���������� scanf_s�� ���������� �������� �ʾ� �̸� �ذ��ϱ� ���� �����    
    //
    rewind(stdin);
    //

    int nRet = 0;

    //
    // res�� �⺻���� CODE_NOT_FOUND�� �س��� �����ؾ�
    // �ߺ� üũ�� ���� ������� res==CODE_NOT_FOUND �� �Ǿ�
    // do~while() ������ ���� ���� �� �ִ�.
    s_res res = CODE_NOT_FOUND;

    do
    {
        printf("�μ� �ڵ带 �Է����ּ���\n");
        nRet = scanf_s("%hd", &code->code);
        if (!nRet) return CANNOT_READ;

        res = ExistCode(code->code, RW_BUSEO, (void*)pbu, lSize);
        if (res == CODE_EXIST)
            printf("�Է��Ͻ� �ڵ�� �μ��ڵ忡 �̹� �����մϴ�.\n�ٸ� �ڵ��ȣ�� �Է����ּ���.");

    } while (res == CODE_EXIST);


    printf("�μ� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}

short InputJikGup(JIKGUP_CODE* code, JIKGUP_CODE* pji, size_t lSize)
{
    CHK_PARAM(code);

    //
    // pji �� lSize�� ���� ��쿡�� �ڵ� �ߺ� üũ�� ���� �����Ƿ� 
    // CHK_2PARAM()�� ���� �ʴ´�.
    //

    printf("���� ���� ������ �Է����ּ���\n\n");

    //
    // �߿�!!!(������ ���ÿ�)
    // ���Ĵٵ� ��ǲ���κ��� ���۸� �ǵ�����.
    // �ѱ� ���� �޴��� ���������� scanf_s�� ���������� �������� �ʾ� �̸� �ذ��ϱ� ���� �����    
    //
    rewind(stdin);
    //


    int nRet = 0;

    //
    // res�� �⺻���� CODE_NOT_FOUND�� �س��� �����ؾ�
    // �ߺ� üũ�� ���� ������� res==CODE_NOT_FOUND �� �Ǿ�
    // do~while() ������ ���� ���� �� �ִ�.
    s_res res = CODE_NOT_FOUND;

    do
    {
        printf("���� �ڵ带 �Է����ּ���\n");
        nRet = scanf_s("%hd", &code->code);
        if (!nRet) return CANNOT_READ;


        res = ExistCode(code->code, RW_JIKGUP, (void*)pji, lSize);
        if (res == CODE_EXIST)
            printf("�Է��Ͻ� �ڵ�� �����ڵ忡 �̹� �����մϴ�.\n�ٸ� �ڵ��ȣ�� �Է����ּ���.");

    } while (res == CODE_EXIST);



    printf("���� �̸��� �Է����ּ���(�ѱ� 14�� ����)\n");
    nRet = scanf_s("%19s", code->jikgup_name, (unsigned int)sizeof(code->jikgup_name));
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}


short GetBuseoName(short nCode, void* pData, size_t lSize, char* name, size_t bufSize) {
    CHK_2PARAM(pData, lSize);
    CHK_2PARAM(name, bufSize);

    // �Ķ���� ����
    // nCode�� �μ� �ڵ��Դϴ�. ( ���÷����� �μ��ڵ� )
    // pData�� �μ� �������� �޸�(����) �Դϴ�.
    // lSize�� pData�� ������ �Դϴ�.
    // name �� ��ȯ�� �μ����� ���ϴ�.
    // bufSize�� name�� ������ �Դϴ�.

    BUSEO_CODE* pbu = (BUSEO_CODE*)pData;
    u_int nCount = (u_int)(lSize / sizeof(BUSEO_CODE)); // �μ� ������ ���ڵ� ������ ���Ѵ�.
    for (u_int i = 0; i < nCount; i++)  // �μ������� ���ڵ� ������ŭ �ݺ�
    {
        if (nCode == pbu[i].code)
        {
            strcpy_s(name, bufSize, pbu[i].buseo_name);
            return SUCCESS_RES;
        }
    }

    return FAIL_RES;
}

short GetJikgupName(short nCode, void* pData, size_t lSize, char* name, size_t bufSize)
{
    CHK_2PARAM(pData, lSize);
    CHK_2PARAM(name, bufSize);

    JIKGUP_CODE* pji = (JIKGUP_CODE*)pData;
    u_int nCount = (u_int)(lSize / sizeof(JIKGUP_CODE));
    for (u_int i = 0; i < nCount; i++)
    {
        if (nCode == pji[i].code)
        {
            strcpy_s(name, bufSize, pji[i].jikgup_name);
            return SUCCESS_RES;
        }
    }

    return FAIL_RES;
}