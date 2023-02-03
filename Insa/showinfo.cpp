//
// 2023년 1월 30일, Coded by E.B Kim
//
// 초간단 인사관리에서 메뉴 및 정보 디스플레이 관련 함수들
//
// 라이선스 없음(무제한 라이선스)



#include "showinfo.h"


void ShowMenu()
{
    system("cls");  // msc에서만 가능, 화면 클리어 해주는 함수입니다.

    printf("1. 직원 정보 보기\n");
    printf("2. 직원 정보 입력\n");
    printf("3. 직원 정보 수정(미구현)\n");
    printf("4. 직원 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("5. 부서 정보 보기\n");
    printf("6. 부서 정보 입력\n");
    printf("7. 부서 정보 수정(미구현)\n");
    printf("8. 부서 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("9  직급 정보 보기\n");
    printf("0. 직급 정보 입력\n");
    printf("a. 직급 정보 수정(미구현)\n");
    printf("b. 직급 정보 삭제(미구현)\n");
    printf("============================\n");
    printf("x. 종료\n");
    printf("============================\n");
    printf("원하시는 메뉴를 선택하세요");
}


void ShowSubMenu()
{
    for (int i = 0; i < 50; i++) printf("=");

    printf("\n");
    printf("p. 이전 메뉴로 돌아가기\n");

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
        printf("사번\t");
        printf("이름\t\t");
        printf("부서코드\t");
        printf("직급코드\n");
        for (int i = 0; i < 50; i++)
            printf("=");

        printf("\n");
        break;

    case RW_BUSEO:
        printf("부서코드\t");
        printf("부서명\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    case RW_JIKGUP:
        printf("직급코드\t");
        printf("직급명\n");
        for (int i = 0; i < 30; i++)
            printf("=");
        printf("\n");
        break;

    default:
        ErrorHandle(INVALID_MODE);
    }
}

// pData 레코드 한개입니다.
// 직원정보만 한개의 레코드이고, 부서와 직급은 전체 레코드를 갖고 호출됨
void PrintEmployeeRecord(void* pData, size_t empSize, BUSEO_CODE* pbu, size_t buSize, JIKGUP_CODE* pji, size_t jiSize)
{
    CHK_2PARAM_V(pData, empSize);
    CHK_2PARAM_V(pbu, buSize);
    CHK_2PARAM_V(pji, jiSize);

    char tmp[20] = { 0 };   // 문자열을 담기위한 배열, 부서이름 또는 직급이름을 여기에 넣을 예정
    EMPLOYEE* emp = (EMPLOYEE*)pData;   // 구조체 한개, 하나의 레코드

    // (조건) ? 참이면 수행 : 거짓이면 수행; ===> 3항 연산자

    printf("%d\t", emp->num);       // 사번
    printf("%s\t\t", emp->name);    // 이름은 그냥 출력
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

// 전체 버퍼를 가지고 옴
void PrintRecord(short mode, void* pData, size_t empSize, BUSEO_CODE* pbu, size_t buSize, JIKGUP_CODE* pji, size_t jiSize)
{
    system("cls");
    PrintTitle(mode);

    u_int nCount = 0;
    EMPLOYEE* pemp = (EMPLOYEE*)pData;  // 메모리 카피는 아니고, 포인터 변수에다가 그냥 포인터만 넘긴것!!!
    

    switch (mode)
    {
    case RW_EMPLOYEE:
        CHK_2PARAM_V(pData, empSize);

        nCount = (u_int)(empSize / sizeof(EMPLOYEE));   // 레코드수를 구함
        for (u_int i = 0; i < nCount; i++)  // 레코드 수만큼 반복해서 출력하려고 함
            PrintEmployeeRecord(&pemp[i], empSize, pbu, buSize, pji, jiSize);   // 레코드 한개씩 갖고 호출
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
    // emps 와 lSize가 없는 경우에는 코드 중복 체크를 하지 않으므로 
    // CHK_2PARAM()을 하지 않는다.
    //


    printf("직원 데이터베이스 입력 프로그램입니다\n\n");

    //
    // 중요!!!(지우지 마시요)
    // 스탠다드 인풋으로부터 버퍼를 되돌린다.
    // 한글 모드로 메뉴를 선택했을때 scanf_s가 정상적으로 동작하지 않아 이를 해결하기 위해 사용함    
    //
    rewind(stdin);
    //


    int nRet = 0;

    //
    // res의 기본값을 CODE_NOT_FOUND로 해놓고 진행해야
    // 중복 체크를 하지 않을경우 res==CODE_NOT_FOUND 가 되어
    // do~while() 루프를 빠져 나올 수 있다.
    s_res res = CODE_NOT_FOUND;


    do
    {
        printf("사번을 입력해주세요\n");
        nRet = scanf_s("%hd", &emp->num);
        if (!nRet) return CANNOT_READ;

        if (emps && lSize)
            res = ExistCode(emp->num, RW_EMPLOYEE, (void*)emps, lSize);

        if (res == CODE_EXIST)
            printf("이미 존재하는 사원번호입니다. 다른 번호를 입력해주세요\n");

    } while (res == CODE_EXIST);


    printf("직원 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%29s", emp->name, (unsigned int)sizeof(emp->name));
    if (!nRet) return CANNOT_READ;

    printf("부서 코드를 입력해주세요\n");
    nRet = scanf_s("%hd", &emp->buseo);
    if (!nRet) return CANNOT_READ;

    printf("직급 코드를 입력해주세요\n");
    scanf_s("%hd", &emp->jikgup);
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}

short InputBuseo(BUSEO_CODE* code, BUSEO_CODE* pbu, size_t lSize)
{
    CHK_PARAM(code);

    //
    // pbu 와 lSize가 없는 경우에는 코드 중복 체크를 하지 않으므로 
    // CHK_2PARAM()을 하지 않는다.
    //

    printf("부서 기초 정보를 입력해주세요\n\n");

    //
    // 중요!!!(지우지 마시요)
    // 스탠다드 인풋으로부터 버퍼를 되돌린다.
    // 한글 모드로 메뉴를 선택했을때 scanf_s가 정상적으로 동작하지 않아 이를 해결하기 위해 사용함    
    //
    rewind(stdin);
    //

    int nRet = 0;

    //
    // res의 기본값을 CODE_NOT_FOUND로 해놓고 진행해야
    // 중복 체크를 하지 않을경우 res==CODE_NOT_FOUND 가 되어
    // do~while() 루프를 빠져 나올 수 있다.
    s_res res = CODE_NOT_FOUND;

    do
    {
        printf("부서 코드를 입력해주세요\n");
        nRet = scanf_s("%hd", &code->code);
        if (!nRet) return CANNOT_READ;

        res = ExistCode(code->code, RW_BUSEO, (void*)pbu, lSize);
        if (res == CODE_EXIST)
            printf("입력하신 코드는 부서코드에 이미 존재합니다.\n다른 코드번호를 입력해주세요.");

    } while (res == CODE_EXIST);


    printf("부서 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->buseo_name, (unsigned int)sizeof(code->buseo_name));
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}

short InputJikGup(JIKGUP_CODE* code, JIKGUP_CODE* pji, size_t lSize)
{
    CHK_PARAM(code);

    //
    // pji 와 lSize가 없는 경우에는 코드 중복 체크를 하지 않으므로 
    // CHK_2PARAM()을 하지 않는다.
    //

    printf("직급 기초 정보를 입력해주세요\n\n");

    //
    // 중요!!!(지우지 마시요)
    // 스탠다드 인풋으로부터 버퍼를 되돌린다.
    // 한글 모드로 메뉴를 선택했을때 scanf_s가 정상적으로 동작하지 않아 이를 해결하기 위해 사용함    
    //
    rewind(stdin);
    //


    int nRet = 0;

    //
    // res의 기본값을 CODE_NOT_FOUND로 해놓고 진행해야
    // 중복 체크를 하지 않을경우 res==CODE_NOT_FOUND 가 되어
    // do~while() 루프를 빠져 나올 수 있다.
    s_res res = CODE_NOT_FOUND;

    do
    {
        printf("직급 코드를 입력해주세요\n");
        nRet = scanf_s("%hd", &code->code);
        if (!nRet) return CANNOT_READ;


        res = ExistCode(code->code, RW_JIKGUP, (void*)pji, lSize);
        if (res == CODE_EXIST)
            printf("입력하신 코드는 직급코드에 이미 존재합니다.\n다른 코드번호를 입력해주세요.");

    } while (res == CODE_EXIST);



    printf("직급 이름을 입력해주세요(한글 14자 제한)\n");
    nRet = scanf_s("%19s", code->jikgup_name, (unsigned int)sizeof(code->jikgup_name));
    if (!nRet) return CANNOT_READ;

    return SUCCESS_RES;
}


short GetBuseoName(short nCode, void* pData, size_t lSize, char* name, size_t bufSize) {
    CHK_2PARAM(pData, lSize);
    CHK_2PARAM(name, bufSize);

    // 파라미터 설명
    // nCode는 부서 코드입니다. ( 임플로이의 부서코드 )
    // pData는 부서 정보들의 메모리(버퍼) 입니다.
    // lSize는 pData의 사이즈 입니다.
    // name 은 반환할 부서명이 들어갑니다.
    // bufSize는 name의 사이즈 입니다.

    BUSEO_CODE* pbu = (BUSEO_CODE*)pData;
    u_int nCount = (u_int)(lSize / sizeof(BUSEO_CODE)); // 부서 정보의 레코드 갯수를 구한다.
    for (u_int i = 0; i < nCount; i++)  // 부서정보의 레코드 갯수만큼 반복
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