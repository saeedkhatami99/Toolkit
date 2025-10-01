#define _CRT_SECURE_NO_WARNINGS  // for use of C functions, if you want use the safe versions of the functions.


#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <Windows.h>
#include <intrin.h>
#include "threadlib/threadlib.hpp"
#include "simplified_fn/simplified_fn.hpp"
#include "menu/menu.hpp"

using namespace std;

int main()
{
    thread_info thread_information = thread_lib::initialize_info();
    std::vector<std::thread> threads(thread_information.amount);
    
    thread_lib::print_info(thread_information);
    

    void (*sleep_s)(int) = &smpl::sleep_sec;

    // Resize console window
    smpl::resize_console(545, 600);

    // Start heartbeat thread for continuous security monitoring
    std::thread heartbeat_thread(smpl::heartbeat);
    heartbeat_thread.detach();

#ifdef _DEBUG

    thread_lib::run_workload(thread_information, threads.data(), true);
    (*sleep_s)(5);  // added for testing since there is almost 0 load and operations execute quickly
    MessageBoxA(0, "Finished.", "Multithreading operation finished", MB_OK);
    return 0;

#endif

    std::string log_test = "Testing popup log.";
    std::string log_f_test = "Testing file log.";

    thread_lib::run_workload(thread_information, threads.data(), false);

    (*sleep_s)(5);   // added for testing since there is almost 0 load and operations execute quickly

    if (smpl::is_debugger_present()) {
        MessageBoxA(0, "Debugger detected!", "Security Alert", MB_OK | MB_ICONWARNING);
        return 1;
    }

    MessageBoxA(0, "Finished.", "Multithreading operation finished", MB_OK);

    while (true) {
        menu::run_menu();
    }

    return 0;

}

