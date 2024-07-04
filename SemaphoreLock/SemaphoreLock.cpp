#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {
public:
    Semaphore(int count = 0) : count(count) {}

    void signal() {
        unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    void wait() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        count--;
    }

private:
    mutex mtx;
    condition_variable cv;
    int count;
};


Semaphore semaphore(1); // Initialize the semaphore with 1 permit
int sharedResource = 0;

void accessResource(int threadID) {
    semaphore.wait(); // Acquire the semaphore

    // Critical section (accessing shared resource)
    cout << "Thread " << threadID << " is accessing the shared resource." << endl;
    sharedResource++;
    cout << "Shared resource value: " << sharedResource << endl;

    this_thread::sleep_for(chrono::seconds(1)); // Simulate some work

    cout << "Thread " << threadID << " is releasing the shared resource." endl;
    semaphore.signal(); // Release the semaphore
}

int main() {
    const int numThreads = 5;
    vector<thread> threads;

    // Create multiple threads to access the shared resource
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(thread(accessResource, i + 1));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
