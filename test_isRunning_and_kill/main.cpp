#include <QCoreApplication>

#include <Windows.h>
#include <io.h>
#include <wtypes.h>
#include <winnt.h>
#include <shellapi.h>
#include <ShlObj.h>
#include <time.h>
#include <TlHelp32.h>

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool IsProcessRunning(wstring process_name) {
    bool bIsRunning = false;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);     //获得某一时刻系统的进程、堆（heap）、模块（module）或线程的快照信息
    if (hSnapshot == NULL) {
        cout << "CreateToolhelp32Snapshot Failed" << endl;
        return bIsRunning;
    }
    PROCESSENTRY32W processListStr;
    processListStr.dwSize = sizeof(PROCESSENTRY32W);
    bool return_value = Process32FirstW(hSnapshot, &processListStr);        //获得系统进程链表中第一个进程的信息
    while(return_value) {
        if (wcscmp(process_name.c_str(), processListStr.szExeFile) == 0) {          //比较进程名，如果此进程与传入的进程名相同，那么就找到了需要的进程信息
            bIsRunning = true;
            break;
        }
        return_value = Process32NextW(hSnapshot, &processListStr);          //获得系统进程链表中下一个进程的信息
    }
    CloseHandle(hSnapshot);
    
    return bIsRunning;
}

bool KillProcess(wstring process_name)
{
    bool result = false;
    
    string strProcess;
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pInfo;
    pInfo.dwSize = sizeof(pInfo);
    Process32First(hSnapShot, &pInfo);
    do {
        if (process_name == pInfo.szExeFile) {
            result = true;
            string cmd;
            char cmdData[128] = { 0 };
            sprintf_s(cmdData, "taskkill /F /PID %d /T", pInfo.th32ProcessID);
            cmd = cmdData;
            system(cmd.c_str());
        }
    } while (Process32Next(hSnapShot, &pInfo));
    
    return result;
}

bool KillProcessEx(wstring process_name) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnapShot, &pe)) {
        return false;
    }
    while (Process32Next(hSnapShot, &pe)) {
        if (process_name == pe.szExeFile) {
            DWORD dwProcessID = pe.th32ProcessID;
            HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
            ::TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    wstring process_name = QString("LJTools_Java.exe").toStdWString();
    if (IsProcessRunning(process_name)) {
        cout << "is running" << endl;
        //if (KillProcess(QString("VNote.exe").toStdWString())) {
        if (KillProcessEx(process_name)) {
            cout << "kill process success" << endl;
        }
        else {
            cout << "kill process failed" << endl;
        }
    }
    else {
        cout << "not running" << endl;
    }
    
    return a.exec();
}
