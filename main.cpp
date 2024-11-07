#include "sharedwork.hpp"
#include <iostream>
#include <string>

int main();

int main()
{

    std::string cmd;
    System *CPU = nullptr;

    while (std::cin >> cmd)
    {
        if (cmd == "ON")
        {
            if (CPU != nullptr)
            {
                std::cout << "failure" << std::endl;
            }
            else
            {
                int N;
                std::cin >> N;
                CPU = new System(N);
            }
        }
        else if (cmd == "SPAWN")
        {
            int P_ID;
            std::cin >> P_ID;
            CPU->spawn(P_ID);
        }
        else if (cmd == "RUN")
        {
            int C_ID;
            std::cin >> C_ID;
            CPU->run(C_ID);
        }
        else if (cmd == "SLEEP")
        {
            int C_ID;
            std::cin >> C_ID;
            CPU->sleep(C_ID);
        }
        else if (cmd == "SHUTDOWN")
        {
            CPU->shutdown();
        }
        else if (cmd == "SIZE")
        {
            int C_ID;
            std::cin >> C_ID;
            CPU->size(C_ID);
        }
        else if (cmd == "CAPACITY")
        {
            int C_ID;
            std::cin >> C_ID;
            CPU->capacity(C_ID);
        }
        else if (cmd == "EXIT")
        {
            delete CPU;
            break;
        }
    }
    return 0;
}