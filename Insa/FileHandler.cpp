//
// 2023�� 1�� 30��, Coded by E.B Kim
//
// ���� RDB ����
// ���� �޸� �Ҵ�
// ����ü�� ������
// ���� ������ ���
//
// ���̼��� ����(������ ���̼���)



#include "FileHandle.h"



void ErrorHandle(short errCode)
{
    switch (errCode)
    {
    case CANNOT_OPEN_FILE:
        printf("������ ���� ���߽��ϴ�.\n");
        break;

    case CANNOT_WRITE:
        printf("(���)��ü�� ������ �� �� �����ϴ�.\n");
        break;

    case CANNOT_READ:
        printf("(�Է�)��ü�κ��� ������ �о�� �� �����ϴ�.");
        break;

    case INVALID_MODE:
        printf("��� ��(Mode Value)�� ����ġ �ʽ��ϴ�.\n");
        break;

    case MEM_ALLOC_FAIL:
        printf("�ý������κ��� �޸��Ҵ��� ���� �� �����ϴ�.\n");
        break;

    case INVALID_PARAM:
        printf("���޵� �Ķ����(�Ű�����) ���� NULL�̰ų� �߸��� �����Դϴ�.");
        break;

    default:
        printf("������ �߻������� ���ǵ��� ���� �����Դϴ�.");
        break;
    }
}


s_res SetFileNameAndDataSize(int nCode, char* szFileName, unsigned short fileNameLen, size_t* lSize)
{
    CHK_2PARAM(szFileName, fileNameLen);
    CHK_PARAM(lSize);

    switch (nCode)
    {
    case RW_EMPLOYEE:
        strcpy_s(szFileName, FILE_NAME_LEN, EMPLOYEE_FILE);
        *lSize = sizeof(EMPLOYEE);
        break;

    case RW_BUSEO:
        strcpy_s(szFileName, FILE_NAME_LEN, BUSEO_FILE);
        *lSize = sizeof(BUSEO_CODE);
        break;

    case RW_JIKGUP:
        strcpy_s(szFileName, FILE_NAME_LEN, JIKGUP_FILE);
        *lSize = sizeof(JIKGUP_CODE);
        break;

    default:
        return INVALID_MODE;
    }

    return SUCCESS_RES;
}


// short WriteToFile(EMPLOYEE* emp)
s_res WriteToFile(void* pData, size_t lDataSize, int nCode)
{
    CHK_2PARAM(pData, lDataSize);

    size_t bufSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);
    s_res res = SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &bufSize);
    if (res != SUCCESS_RES)
        return res;

    FILE* fp = NULL;
    fopen_s(&fp, szFileName, "wb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    // printf("sizeof(EMPLOYEE)=%zd\n", sizeof(EMPLOYEE));
    // PrintRecord(emp);

    size_t nRet = 0;
    nRet = fwrite(pData, lDataSize, 1, fp);
    if (!nRet)
    {
        fclose(fp);
        fp = NULL;
        return CANNOT_WRITE;
    }

    // (nRet) ? printf("���Ͼ��� ����(%zd block(s))\n", nRet) : printf("���Ͼ��� ����\n");
    fclose(fp);
    fp = NULL;

    return SUCCESS_RES;
}



// short ReadFromFile(EMPLOYEE* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount)
s_res ReadFromFile(void* pData, size_t dataSize, int nCode, void (*ptrFileHandler)(void* p, size_t size, unsigned int nCode), unsigned short toReadCount)
{
    CHK_2PARAM(pData, dataSize);

    size_t buffSize = 0;
    char szFileName[FILE_NAME_LEN];
    memset(szFileName, 0, FILE_NAME_LEN);

    s_res res = SetFileNameAndDataSize(nCode, szFileName, FILE_NAME_LEN, &buffSize);
    if (res != SUCCESS_RES)
        return res;

    unsigned int readDataCode = 0;
    switch (nCode)
    {
    case RW_EMPLOYEE: readDataCode = FILE_ACR_EMPLOYEE; break;
    case RW_BUSEO:  readDataCode = FILE_ACR_BUSEO; break;
    case RW_JIKGUP: readDataCode = FILE_ACR_JIKGUP;
    }


    FILE* fp = NULL;
    fopen_s(&fp, szFileName, "rb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    // char* p = (char *)pData;
    size_t readedCount = dataSize / buffSize;
    // do {
    size_t nRet = fread_s(pData, dataSize, buffSize, readedCount, fp);
    if (!nRet)
    {
        fclose(fp);
        fp = NULL;
        return CANNOT_READ;
    }

    if (ptrFileHandler)
        ptrFileHandler(pData, dataSize, readDataCode);

    //         readedCount++;
            // p += buffSize;

        // } while (!feof(fp) && readedCount < toReadCount);
    fclose(fp);
    fp = NULL;

    return SUCCESS_RES;
}

s_res GetFileSize(const char* filename, size_t* size)
{
    FILE* fp = NULL;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL)
    {
        return CANNOT_OPEN_FILE;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fclose(fp);
        fp = NULL;
        return CANNOT_SEEK;
    }

    *size = ftell(fp);
    fclose(fp);
    fp = NULL;

    return SUCCESS_RES;
}



s_res AppendData(void** ppData, size_t* lSizeData, void* pAppend, size_t lAppendSize)
{
    CHK_2PARAM(ppData, *lSizeData);
    CHK_2PARAM(pAppend, lAppendSize);


    size_t lNewSize = *lSizeData + lAppendSize;
    char* pNewData = (char*)malloc(lNewSize);
    if (pNewData == NULL)
        return MEM_ALLOC_FAIL;

    memcpy(pNewData, *ppData, *lSizeData);
    memcpy(pNewData + *lSizeData, pAppend, lAppendSize);

    free(*ppData);
    *ppData = NULL;

    *ppData = pNewData;
    *lSizeData = lNewSize;

    return SUCCESS_RES;
}


// filename : ���ϸ�
s_res ExistFile(const char* filename)
{
    CHK_PARAM(filename);

    FILE* fp = NULL;
    fopen_s(&fp, filename, "r");
    if (fp == NULL)
        return FILE_NOT_FOUND;

    fclose(fp);
    fp = NULL;

    return FILE_EXIST;
}

s_res ExistCode(short code, short nMode, void* pData, size_t lSizeData)
{
    CHK_2PARAM(pData, lSizeData);

    u_int nCount = 0;
    switch (nMode)
    {
    case RW_EMPLOYEE:
    {
        EMPLOYEE* pem = (EMPLOYEE*)pData;
        nCount = (u_int)(lSizeData / sizeof(EMPLOYEE));
        for (u_int i = 0; i < nCount; i++)
        {
            if (code == pem[i].num)
                return CODE_EXIST;
        }
        break;
    }
    case RW_BUSEO:
    {
        BUSEO_CODE* pbu = (BUSEO_CODE*)pData;
        nCount = (u_int)(lSizeData / sizeof(BUSEO_CODE));
        for (u_int i = 0; i < nCount; i++)
        {
            if (code == pbu[i].code)
                return CODE_EXIST;
        }
        break;
    }
    case RW_JIKGUP:
    {
        JIKGUP_CODE* pji = (JIKGUP_CODE*)pData;;
        nCount = (u_int)(lSizeData / sizeof(JIKGUP_CODE));
        for (u_int i = 0; i < nCount; i++)
        {
            if (code == pji[i].code)
                return CODE_EXIST;
        }
        break;
    }

    }

    return CODE_NOT_FOUND;
}


