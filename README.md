This code demonstrates a basic semaphore mechanism to control access to a shared resource among multiple threads, ensuring that only one thread can access the resource at a time.

Explanation
Semaphore Class:

signal(): Increments the semaphore counter and notifies one waiting thread.
wait(): Decrements the semaphore counter if it's greater than zero. If the counter is zero, the thread waits until it's signaled.
Example Usage:

Semaphore semaphore(1): Initializes the semaphore with one permit, allowing only one thread to access the shared resource at a time.
accessResource(int threadID): Function that simulates accessing a shared resource. It acquires the semaphore before entering the critical section and releases it afterward.
main(): Creates and starts multiple threads, each trying to access the shared resource. The threads are joined to ensure the main thread waits for their completion.
