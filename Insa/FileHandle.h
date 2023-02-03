#pragma once

#include <stdio.h>
#include <vcruntime_string.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <malloc.h> 


typedef struct {
    short num;      // »ç¹ø
    char name[30];  // ÀÌ¸§
    short buseo;    // ºÎ¼­
    short jikgup;   // Á÷±Þ
} EMPLOYEE;

typedef struct {
    short code;
    char buseo_name[20];
}BUSEO_CODE;

typedef struct {
    short code;
    char jikgup_name[20];
}JIKGUP_CODE;

#define SUCCESS_RES         1
#define FAIL_RES            0


#define CANNOT_OPEN_FILE     0  
#define CANNOT_WRITE        -1
#define CANNOT_READ         -2
#define INVALID_MODE        -3
#define CANNOT_SEEK         -4
#define MEM_ALLOC_FAIL      -5
#define INVALID_PARAM       -500

#define FILE_EXIST          1
#define FILE_NOT_FOUND      -1

#define CODE_EXIST          1
#define CODE_NOT_FOUND     -1


#define FILE_ACR_EMPLOYEE  0
#define FILE_ACR_BUSEO   1
#define FILE_ACR_JIKGUP  2


#define RW_EMPLOYEE    1
#define RW_BUSEO     2
#define RW_JIKGUP    3


#define EMPLOYEE_FILE     "c:\\EMPLOYEE.dat"
#define BUSEO_FILE      "c:\\buseo.dat"
#define JIKGUP_FILE     "c:\\jikgup.dat"

#define FILE_NAME_LEN   512

#define MAX_RECORDS     10
#define MAX_EMP_BUFFER  (sizeof() * MAX_RECORDS)

#define CHK_PARAM(x)    if(x==NULL)return INVALID_PARAM
#define CHK_2PARAM(x,y) if(x==NULL||y==0)return INVALID_PARAM

#define CHK_PARAM_V(x)    if(x==NULL)return
#define CHK_2PARAM_V(x,y) if(x==NULL||y==0)return

typedef unsigned int    u_int;
typedef short           s_res;


void OnFileHandleEvent(void* p, size_t size, unsigned int nCode);

s_res SetFileNameAndDataSize(int nCode, char* szFileName, unsigned short fileNameLen, size_t* lSize);

// short WriteToFile(EMPLOYEE* emp);
s_res WriteToFile(void* pData, size_t lDataSize, int nCode);

// short ReadFromFile(EMPLOYEE* emp, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount=10);
//short ReadFromFile(void* pData, int nCode, void (*ptrFileHandler)(void* p, unsigned int nCode), unsigned short toReadCount = 10);
s_res ReadFromFile(void* pData, size_t dataSize, int nCode, void (*ptrFileHandler)(void* p, size_t size, unsigned int nCode) = NULL, unsigned short toReadCount = 10);

s_res GetFileSize(const char* filename, size_t* size);

s_res AppendData(void** ppData, size_t* lSizeData, void* pAppend, size_t lAppendSize);

s_res ExistFile(const char* filename);

void ErrorHandle(short errCode);




