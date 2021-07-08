#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <FltUser.h>

using namespace std;

HANDLE g_hPort = INVALID_HANDLE_VALUE;

typedef enum _MINI_COMMAND {
    ENUM_PASS = 0,
    ENUM_BLOCK
}MIN_COMMAND;

typedef struct _COMAND_MESSAGE
{
    MIN_COMMAND Command;
} COMMAND_MESSAGE, * PCOMMAND_MESSAGE;

typedef struct _OperationInfo
{
    char time[32];
    short operation_type;
    wchar_t user[32];
    wchar_t process[32];
    wchar_t path[64];
} OperationInfo;

typedef struct _SCANNER_MESSAGE
{
    FILTER_MESSAGE_HEADER MessageHeader;

    OperationInfo info;

    OVERLAPPED Ovlp;
} SCANNER_MESSAGE, * PSCANNER_MESSAGE;

class CApp
{
public:
    CApp();
    virtual ~CApp();

    int Init();

    void Message_Send(COMMAND_MESSAGE data_send);
    void Message_Get(PSCANNER_MESSAGE data_get);

private:

    HINSTANCE m_hModule;

    bool LoadminifilterDll();
};
