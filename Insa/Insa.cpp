// FileHandling.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//
// 2023년 1월 30일, Coded by E.B Kim
//
// 간략 RDB 구현
// 동적 메모리 할당
// 구조체와 포인터
// 이중 포인터 사용
//
// 라이선스 없음(무제한 라이선스)



#include "showinfo.h"


int main()
{
    short nRes = 0;

    // 읽어들일 버퍼
    EMPLOYEE* pem = NULL;
    BUSEO_CODE* pbu = NULL;
    JIKGUP_CODE* pji = NULL;

    size_t lSize = 0;   // 직원 정보 버퍼의 사이즈    // 구조체 사이즈는 아니다
    size_t buSize = 0;  // 부서 정보 버퍼의 사이즈
    size_t jiSize = 0;  // 직급 정보 버퍼의 사이즈

    int n = 0;
    s_res res = SUCCESS_RES;

    //
    // 처음 실행한 경우 employee.dat 파일이 없는경우 레코드 한개를 입력받고
    // 파일에 저장한 뒤 다음으로 진행한다.
    if (ExistFile(EMPLOYEE_FILE) == FILE_NOT_FOUND)
    {
        EMPLOYEE emp;
        res = InputRecord(&emp);
        if (res != SUCCESS_RES)
        {
            ErrorHandle(res);
            return 0;
        }

        res = WriteToFile(&emp, sizeof(EMPLOYEE), RW_EMPLOYEE);
        if (res != SUCCESS_RES)
        {
            ErrorHandle(res);
            return 0;
        }
    }


    //
    // 직원 정보 로딩
    nRes = GetFileSize(EMPLOYEE_FILE, &lSize);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        return 0;
    }

    pem = (EMPLOYEE*)malloc(lSize);
    if (pem == NULL)
    {
        ErrorHandle(MEM_ALLOC_FAIL);
        return 0;
    }


    // 직원 정보 로딩
    // pem 파일 사이즈만큼 할당을 받았다, 아직 데이터는 없다, pem==>쓰레기값
    memset(pem,    // pem은 직원 정보를 넣기 위한 버퍼이다.
           0,      // 0으로 pem을 초기화 하려고 한다.
           lSize); // pem버퍼의 사이즈이다.
        
    nRes = ReadFromFile(pem, lSize, RW_EMPLOYEE);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }


    // 부서 정보 메모리에 로딩
    nRes = GetFileSize(BUSEO_FILE, &buSize);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }

    pbu = (BUSEO_CODE*)malloc(buSize);
    if (pbu == NULL)
    {
        ErrorHandle(MEM_ALLOC_FAIL);
        goto ReleaseMem;
    }



    memset(pbu, 0, buSize);
    nRes = ReadFromFile(pbu, buSize, RW_BUSEO, NULL);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }


    // 직급정보 메모리에 로딩
    nRes = GetFileSize(JIKGUP_FILE, &jiSize);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }

    pji = (JIKGUP_CODE*)malloc(jiSize);
    if (pji == NULL)
    {
        ErrorHandle(MEM_ALLOC_FAIL);
        goto ReleaseMem;
    }


    memset(pji, 0, jiSize);
    nRes = ReadFromFile(pji, jiSize, RW_JIKGUP, NULL);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        goto ReleaseMem;
    }


    
    // 메뉴 핸들링
    while ( TRUE )
    {
        ShowMenu();

        n = _getch();   // msc에서만 가능, 키보드로부터 한 키만 입력받을수 있는 함수, ascii 코드값으로 받음
        system("cls");  // msc에서만 가능

        switch (n)
        {
        case '1': // 직원 정보 출력
            PrintRecord(RW_EMPLOYEE,    // 출력할 모드((직원), 부서, 직급)
                        pem,            // 직원정보 메모리(버퍼)
                        lSize,          // pem의 사이즈
                        pbu,            // 부서정보의 메모리(버퍼)
                        buSize,         // pbu의 사이즈
                        pji,            // 직급정보의 메모리(버퍼)
                        jiSize);        // pji의 사이즈
            break;

        case '2':   // 직원 정보 입력
        {
            EMPLOYEE emp;
            memset(&emp, 0, sizeof(EMPLOYEE));
            if (InputRecord(&emp, pem, lSize) == SUCCESS_RES)
            {
                res = AppendData((void**)&pem, &lSize, (void*)&emp, sizeof(EMPLOYEE));
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                res = WriteToFile(pem, lSize, RW_EMPLOYEE);
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                PrintRecord(RW_EMPLOYEE, pem, lSize, pbu, buSize, pji, jiSize);
            }
            break;
        }

        case '5':
            PrintRecord(RW_BUSEO, pem, lSize, pbu, buSize, pji, jiSize);
            break;

        case '6':
        {
            BUSEO_CODE buseo;
            if (InputBuseo(&buseo, pbu, buSize) == SUCCESS_RES)
            {
                res = AppendData((void**)&pbu, &buSize, (void*)&buseo, sizeof(BUSEO_CODE));
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                res = WriteToFile(pbu, buSize, RW_BUSEO);
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                PrintRecord(RW_BUSEO, pem, lSize, pbu, buSize, pji, jiSize);
            }

            break;
        }

        case '9':
            PrintRecord(RW_JIKGUP, pem, lSize, pbu, buSize, pji, jiSize);
            break;

        case '0':
        {
            JIKGUP_CODE jikgup;
            if (InputJikGup(&jikgup, pji, jiSize) == SUCCESS_RES)
            {
                res = AppendData((void**)&pji, &jiSize, (void*)&jikgup, sizeof(JIKGUP_CODE));
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                res = WriteToFile(pji, jiSize, RW_JIKGUP);
                if (res != SUCCESS_RES)
                {
                    ErrorHandle(res);
                    _getch();
                    break;
                }

                PrintRecord(RW_JIKGUP, pem, lSize, pbu, buSize, pji, jiSize);
            }
        }
        break;

        case 'x':
        case 'X':
            goto ReleaseMem;

        default:
            break;
        }
    }


ReleaseMem:

    if (pem != NULL)
    {
        free(pem);
        pem = NULL;
    }

    if (pbu != NULL)
    {
        free(pbu);
        pbu = NULL;
    }

    if (pji != NULL)
    {
        free(pji);
        pji = NULL;
    }


    // 고치고 다시 푸시

    //size_t lSize = 0;
    //nRes = GetFileSize(EMPLOYEE_FILE, &lSize);
    //if (nRes != SUCCESS_RES)
    //{
    //    ErrorHandle(nRes);
    //    return 0;
    //}

    //EMPLOYEE* pem = (EMPLOYEE*)malloc(lSize);
    //if (pem)
    //{
    //    memset(pem, 0, lSize);
    //    nRes = ReadFromFile(pem, lSize, RW_EMPLOYEE, OnFileHandleEvent);
    //    if (nRes != SUCCESS_RES)
    //    {
    //        ErrorHandle(nRes);
    //        return 0;
    //    }
    //}

    //for (size_t p = 0; p < (lSize/ sizeof(EMPLOYEE)); p++ )
    //{
    //    PrintRecord(&pem[p]);
    //}
    //
    //free(pem);
    //pem = NULL;


    // printf("sizeof(EMPLOYEE)= %zd\n", sizeof(EMPLOYEE));      

    /*JIKGUP_CODE jikgup;
    memset(&jikgup, 0, sizeof(JIKGUP_CODE));
    nRes = ReadFromFile(&jikgup, RW_JIKGUP, OnFileHandleEvent);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        return 0;
    }*/





    //nRes = InputJikGup(&jikgup);
    //if (!nRes)
    //    printf("직급 정보 입력 실패!\n");
    //
    //nRes = WriteToFile(&jikgup, RW_JIKGUP);
    //if (nRes != SUCCESS_RES )
    //{
    //    ErrorHandle(nRes);
    //    return 0;
    //}

    /*
    if (!InputRecord(&emp))
    {
        printf("데이터를 입력받을 수 없습니다.\n");
        return 0;
    }
    PrintRecord(&emp);
    nRes = WriteToFile(&emp);
    if (nRes != SUCCESS_RES)
    {
        ErrorHandle(nRes);
        return 0;
    }


    PrintTitle();
    nRes = ReadFromFile(&emp, OnFileHandleEvent);
    if ( nRes!= SUCCESS_RES )
    {
        ErrorHandle(nRes);
        return 0;
    }
    */

    /*   BUSEO_CODE code;
       memset(&code, 0, sizeof(BUSEO_CODE));
       nRes = ReadFromFile(&code, RW_BUSEO, OnFileHandleEvent);
       if (nRes != SUCCESS_RES)
       {
           ErrorHandle(nRes);
           return 0;
       }*/
       /*
       if (!InputBuseo(&code))
       {
           printf("데이터를 입력받을 수 없습니다.\n");
           return 0;
       }
       nRes = WriteToFile(&code, RW_BUSEO);
       if (nRes != SUCCESS_RES)
       {
           ErrorHandle(nRes);
           return 0;
       }
       */

       // PrintRecord(&emp);

    return 0;
}


// void OnFileHandleEvent(void* p, unsigned int nCode)
void OnFileHandleEvent(void* p, size_t size, unsigned int nCode)
{
    switch (nCode)
    {
    case FILE_ACR_EMPLOYEE:
    case FILE_ACR_BUSEO:
    case FILE_ACR_JIKGUP:    break;
    }
}