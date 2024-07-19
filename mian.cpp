#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int Nowthread = 1;

void print(int id, const std::string& message)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [id] { return Nowthread == id; });

    std::cout << message << std::endl;
    Nowthread++;
    cv.notify_all();
}

int main() 
{
    std::thread t1(print, 1, "スレッド1");
    std::thread t2(print, 2, "スレッド2");
    std::thread t3(print, 3, "スレッド3");

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
