#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

constexpr int ITERATIONS = 1'000'000'000;

template <typename T>
void fx(T &a)
{
    for (int i = 0; i < ITERATIONS; i++)
        a.x++;
}

template <typename T>
void fy(T &a)
{
    int sum = 0;
    for (int i = 0; i < ITERATIONS; i++)
        sum += a.y;
}

class Sequential
{
    struct A
    {
        int x = 0;
        int y = 0;
    } a;

public:
    void run()
    {
        fx(a);
        fy(a);
    }
};

class ParallelFalseSharing
{
    struct A
    {
        int x = 0;
        int y = 0;
    } a;

public:
    void run()
    {
        std::thread tx(fx<A>, std::ref(a));
        std::thread ty(fy<A>, std::ref(a));
        tx.join();
        ty.join();
    }
};

class ParallelNoFalseSharing
{
    struct A
    {
        int x = 0;
        alignas(64) int y = 0;
    } a;

public:
    void run()
    {
        std::thread tx(fx<A>, std::ref(a));
        std::thread ty(fy<A>, std::ref(a));
        tx.join();
        ty.join();
    }
};

// Функция для измерения времени выполнения
double benchmark(auto &&func)
{
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Функция для вывода результатов
void printResults(double seqTime, double pfsTime, double pnfsTime)
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Operation                Sequential (ms)  Parallel FS (ms)  Parallel No-FS (ms)\n";
    std::cout << "---------------------------------------------------------------------------------\n";
    std::cout << "Execution Time           " 
              << std::setw(15) << seqTime 
              << std::setw(17) << pfsTime 
              << std::setw(20) << pnfsTime << "\n";
}

int main()
{
    Sequential seq;
    ParallelFalseSharing pfs;
    ParallelNoFalseSharing pnfs;

    double seqTime = benchmark([&]() { seq.run(); });
    double pfsTime = benchmark([&]() { pfs.run(); });
    double pnfsTime = benchmark([&]() { pnfs.run(); });

    printResults(seqTime, pfsTime, pnfsTime);

    return 0;
}
