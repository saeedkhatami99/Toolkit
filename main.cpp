#define _CRT_SECURE_NO_WARNINGS 


#include <iostream>
#include <thread>
#include <Windows.h>
#include <intrin.h>
#include "threadlib.hpp"
#include "simplified_fn.hpp"
#include "logs.hpp"




using namespace std;

int main()
{
    thread_info thread_information = thread_lib::initialize_info();
    thread* threads = new thread[thread_information.amount];
    
    thread_lib::print_info(thread_information);
    
    void (*sleep_s)(int) = &smpl::sleep_sec;

    HWND console = GetConsoleWindow();
    RECT console_rect;
    GetWindowRect(console, &console_rect);

    MoveWindow(console, console_rect.left, console_rect.top, 545, 600, TRUE);

#ifdef _DEBUG

    thread_lib::run_workload(thread_information, threads, true);
    (*sleep_s)(5); 
    MessageBox(0, "Finished.", "Multithreading operation finished", MB_OK);
    return 0;

#endif

    char log_test[32];
    strcpy(log_test, "Testing popup log.");
    char log_f_test[32] = "Testing file log.";

    thread_lib::run_workload(thread_information, threads, false);

    logs::popup(log_test, DEFAULT_LOG); 
    logs::lsavef(log_f_test, DEFAULT_LOG);

    (*sleep_s)(5);  

    MessageBox(0, "Finished.", "Multithreading operation finished", MB_OK);

    return 0;

}

