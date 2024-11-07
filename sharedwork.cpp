#include <iostream>
#include "sharedwork.hpp"

System::System(int N)
{
    this->deques = new Core *[N];
    this->numOfCores = N;
    for (int i = 0; i < N; ++i)
    {
        this->deques[i] = new Core(i);
    }
    this->smallest = this->deques[0];
    this->greatest = this->deques[N - 1];
    this->totalTasks = 0;
    std::cout << "success" << std::endl;
}

Core::Core(int core_id)
{
    this->N = 5;
    this->deque = new int[5];
    this->f = 0;
    this->r = 0;
    this->core_ID = core_id;
}

int Core::dequeueBack()
{
    r = (r - 1 + N) % N;
    int stolenTask = this->deque[r];
    this->deque[r] = 0;
    if (this->N > 3 && this->size() == (this->N - 1) / 4)
    {
        this->halfSize();
    }
    return stolenTask;
}

void Core::enqueue(int P_ID)
{
    // if (size() == N - 1)
    //     std::cout << "SIZE SOOMEHOW MAXZED";
    this->deque[r] = P_ID;
    r = (r + 1) % this->N;
    if (this->size() == this->N - 1)
    {
        this->doubleSize();
    }
}
void Core::dequeueFront()
{
    if (size() == 0)
        return;
    this->deque[f] = 0;
    f = (f + 1) % this->N;
    if (this->N > 3 && this->size() == (this->N - 1) / 4)
    {
        this->halfSize();
    }
}

int Core::size()
{
    return (this->N - this->f + this->r) % this->N;
}

void Core::doubleSize()
{
    int *newDeque = new int[((this->N - 1) * 2) + 1];
    int j = 0;
    for (int i = this->f; j < this->size(); i = (i + 1) % N)
    {
        newDeque[j++] = this->deque[i];
    }
    delete[] this->deque;
    this->r = j;
    this->f = 0;
    this->deque = newDeque;
    this->N = ((this->N - 1) * 2) + 1;
}

void Core::halfSize()
{
    int *newDeque = new int[((this->N - 1) / 2) + 1];
    int j = 0;
    for (int i = this->f; j < this->size(); i = (i + 1) % N)
    {
        newDeque[j++] = this->deque[i];
    }
    delete[] this->deque;

    this->deque = newDeque;
    this->r = j;
    this->f = 0;
    this->N = ((this->N - 1) / 2) + 1;
}

void System::spawn(int P_ID)
{
    if (P_ID <= 0)
    {
        std::cout << "failure" << std::endl;
        return;
    }
    this->findSmallestNotIncluding(numOfCores);
    this->smallest->enqueue(P_ID);
    this->totalTasks++;
    std::cout << "core " << this->smallest->core_ID << " assigned task " << P_ID << std::endl;
    this->findGreatestNotIncluding(numOfCores);
    this->findSmallestNotIncluding(numOfCores);
    // print();
}

void System::run(int C_ID)
{
    if (C_ID < 0 || C_ID >= numOfCores)
    {
        std::cout << "failure" << std::endl;
        return;
    }
    Core *core = this->deques[C_ID];
    this->findGreatestNotIncluding(C_ID);
    this->findSmallestNotIncluding(numOfCores);
    // there is a case where greatets and smalest are equal: lets see what happens.
    if (core->size() == 0)
    {
        this->steal(core);
        // only if we put the core to sleep will we have this condition.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::cout << "core " << core->core_ID << " has no tasks to run" << std::endl;
    }

    else
    {
        std::cout << "core " << C_ID << " is running task " << core->deque[core->f] << std::endl;
        this->totalTasks--;
        core->dequeueFront();
        if (core->size() == 0)
        {
            // this->findGreatestNotIncluding(C_ID);
            this->steal(core);
        }
    }
    findSmallestNotIncluding(numOfCores);
    findGreatestNotIncluding(numOfCores);
}

void System::steal(Core *core)
{
    if (totalTasks == 0 || this->greatest->size() < 1)
        return;

    int stolenTask = this->greatest->dequeueBack();
    core->enqueue(stolenTask);
}

void System::sleep(int C_ID)
{
    if (C_ID < 0 || C_ID >= numOfCores)
    {
        std::cout << "failure" << std::endl;
        return;
    }
    Core *core = this->deques[C_ID];
    if (core->size() == 0)
    {
        std::cout << "core " << core->core_ID << " has no tasks to assign" << std::endl;
        return;
    }
    this->findSmallestNotIncluding(C_ID);
    while (core->size() > 0)
    {
        int dequeuedBackVal = core->dequeueBack();
        this->smallest->enqueue(dequeuedBackVal);
        std::cout << "task " << dequeuedBackVal << " assigned to core " << this->smallest->core_ID << " ";
        this->findSmallestNotIncluding(C_ID);
    }
    std::cout << std::endl;
    this->findSmallestNotIncluding(numOfCores);
    this->findGreatestNotIncluding(numOfCores);
}

void System::shutdown()
{
    if (this->totalTasks == 0)
    {
        std::cout << "no tasks to remove" << std::endl;
        return;
    }
    for (int i = 0; i < this->numOfCores; ++i)
    {
        while (deques[i]->size() > 0)
        {
            int val = this->deques[i]->deque[this->deques[i]->f];
            this->deques[i]->dequeueFront();
            std::cout << "deleting task " << val << " from core " << this->deques[i]->core_ID << " ";
        }
    }
    std::cout << std::endl;
    this->totalTasks = 0;
    this->smallest = this->deques[0];
    this->greatest = this->deques[this->numOfCores - 1];
}
void System::size(int C_ID)
{
    if (C_ID < 0 || C_ID >= numOfCores)
    {
        std::cout << "failure" << std::endl;
        return;
    }

    std::cout << "size is " << this->deques[C_ID]->size() << std::endl;
}

void System::capacity(int C_ID)
{
    if (C_ID < 0 || C_ID >= numOfCores)
    {
        std::cout << "failure" << std::endl;
        return;
    }

    std::cout << "capacity is " << (this->deques[C_ID]->N) - 1 << std::endl;
}

System::~System()
{
    if (this->deques != nullptr)
    {
        for (int i = 0; i < this->numOfCores; ++i)
        {
            if (this->deques[i] != nullptr)
            {
                delete[] this->deques[i]->deque;
                this->deques[i]->deque = nullptr;
                delete this->deques[i];
                this->deques[i] = nullptr;
            }
        }
        delete[] this->deques;
        this->deques = nullptr;
    }
}
// delete the deque array in Core class, delete the Core object,

void System::findSmallestNotIncluding(int C_ID)
{
    Core *core = nullptr;
    for (int i = 0; i < this->numOfCores; ++i)
    {
        if (i != C_ID)
        {
            if (core == nullptr || this->deques[i]->size() < core->size())
            {
                core = this->deques[i];
            }
        }
    }
    this->smallest = core;
}

void System::findGreatestNotIncluding(int C_ID)
{
    Core *core = nullptr;
    for (int i = this->numOfCores - 1; i >= 0; i--)
    {
        if (i != C_ID)
        {
            if (core == nullptr || this->deques[i]->size() > core->size())
            {
                core = this->deques[i];
            }
        }
    }
    this->greatest = core;
}