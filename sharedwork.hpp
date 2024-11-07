class Core
{
public:
    int *deque;
    int N;
    int f;
    int r;
    int core_ID;
    Core(int core_id);
    void enqueue(int P_ID);
    void dequeueFront();
    int dequeueBack();
    int size();

private:
    void doubleSize();
    void halfSize();
    // double size is a responsive thing done within the object.
};

class System
{
private:
    Core **deques;
    Core *smallest;
    Core *greatest;
    int totalTasks;
    int numOfCores;
    void steal(Core *core);
    void findSmallestNotIncluding(int C_ID);
    void findGreatestNotIncluding(int C_ID);

public:
    System(int N);
    ~System();
    void spawn(int P_ID);
    void run(int C_ID);
    void sleep(int C_ID);
    void shutdown();
    void size(int C_ID);
    void capacity(int C_ID);
};
