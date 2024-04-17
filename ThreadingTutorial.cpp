#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <string>

using namespace std;

// как использовать condition_variable: 
// пример с двумя потоками, один ждет, пока другой не завершит работу

//std::mutex mtx;
//std::condition_variable cv;
//bool ready = false;

//void print_id(int id) {
//    std::unique_lock<std::mutex> lck(mtx);
//    while (!ready) cv.wait(lck);
//    std::cout << "thread " << id << '\n';
//}

//void go() {
//    std::unique_lock<std::mutex> lck(mtx);
//    ready = true;
//    cv.notify_all();
//}

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

// 1 --------------------------------------------------------------
// Класс, реализующий очередь для чтения и записи
// Позволяет нескольким потокам читать одновременно, но только одному писать
// При этом, если пишущий поток активен, то ни один читающий не может быть активен

///*Implementing a "Readers-Writers system with priority for writers" 
//involves managing access to a shared resource (like a database or a file) 
//in such a way that multiple readers can access the resource concurrently, 
//but writers have priority to ensure they don't experience long wait times.
//The goal is to prevent readers from starving writers and vice versa.
//*/
//class ReadersWritersQueue {
//private:
//    int readers_count = 0;
//    bool writer_active = false;
//    std::mutex mtx;
//    std::condition_variable cv;
//
//public:
//    // Function for reader threads
//    void read(int reader_id) {
//        std::unique_lock<std::mutex> lock(mtx);
//        cv.wait(lock, [this]() { return !writer_active; });  // Wait until there's no active writer
//        ++readers_count;
//        lock.unlock();
//
//        // Simulating reading (you would access shared resources here)
//        std::cout << "Reader " << reader_id << " is reading." << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate read operation
//
//        lock.lock();
//        --readers_count;
//        if (readers_count == 0) {
//            cv.notify_all();  // Notify waiting writers if this is the last reader
//        }
//        lock.unlock();
//    }
//
//    // Function for writer threads
//    void write(int writer_id) {
//        std::unique_lock<std::mutex> lock(mtx);
//        cv.wait(lock, [this]() { return readers_count == 0 && !writer_active; });  // Wait until no readers or other writers are active
//        writer_active = true;
//        lock.unlock();
//
//        // Simulating writing (you would modify shared resources here)
//        std::cout << "Writer " << writer_id << " is writing." << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate write operation
//
//        lock.lock();
//        writer_active = false;
//        cv.notify_all();  // Notify waiting readers and writers
//        lock.unlock();
//    }
//};
//
//int main() {
//    ReadersWritersQueue queue;
//    std::vector<std::thread> threads;
//
//    // Create several reader and writer threads
//    for (int i = 0; i < 5; ++i) {
//        threads.push_back(std::thread(&ReadersWritersQueue::read, &queue, i));
//        threads.push_back(std::thread(&ReadersWritersQueue::write, &queue, i));
//    }
//
//    // Wait for all threads to complete
//    for (auto& t : threads) {
//        t.join();
//    }
//
//    return 0;
//}


// 2 --------------------------------------------------------------
// два потока печатают числа от 1 до N, один - четные, другой - нечетные

//std::mutex mtx;
//std::condition_variable cv;
//bool isOddTurn = true;
//
//int N = 20;
//int currentNumber = 1; // Start from 1, the first odd number
//
//void PrintEven() {
//    while (true) {
//        std::unique_lock<std::mutex> lock(mtx);
//        cv.wait(lock, [] { return !isOddTurn; });
//          if (currentNumber > N) return; // Exit condition
//          cout << currentNumber << endl;
//          ++currentNumber;
//        isOddTurn = true;
//        cv.notify_all();
//    }
//}
//
//void PrintOdd() {
//    while (true) {
//        std::unique_lock<std::mutex> lock(mtx);
//        cv.wait(lock, [] { return isOddTurn; });
//          if (currentNumber > N) return; // Exit condition
//          cout << currentNumber << endl;
//          ++currentNumber;
//        isOddTurn = false;
//        cv.notify_all();
//    }
//}
//
//int main() {
//    std::thread oddThread(PrintOdd);
//    std::thread evenThread(PrintEven);
//
//    oddThread.join();
//    evenThread.join();
//
//    return 0;
//}


// 3 --------------------------------------------------------------
// официант и шеф-повар

//#include <mutex>
//#include <condition_variable>
//#include <iostream>
//
//class Restaurant {
//    enum class Status { idle, newOrder, ready };
//    Status orderStatus = Status::idle;
//    std::mutex order;
//    std::condition_variable orderBell;
//
//public:
//
//    void chef() {
//
//        std::unique_lock<std::mutex> ul(order);
//        orderBell.wait(ul, [=]() { return orderStatus == Status::newOrder; });
//        //приготовление блюд из заказа
//        orderStatus = Status::ready;
//        orderBell.notify_one();
//
//    }
//
//    void waiter() {
//        {
//            std::lock_guard<std::mutex> lg(order);
//            orderStatus = Status::newOrder;
//            orderBell.notify_one();
//        } // lg вне области видимости = order.unlock()
//
//        std::unique_lock<std::mutex> ul(order);
//        orderBell.wait(ul, [=]() { return orderStatus == Status::ready; });
//        orderStatus = Status::idle;
//        ul.unlock();
//        //приносят заказ
//    }
//
//};
//Замечание: lock guard в методе waiter вполне можно заменить на unique lock.
//
//И, наконец, класс Restaurant используется вот так :
//
//#include "Restaurant.h"
//#include <thread>
//
//int main() {
//    Restaurant restaurant;
//    std::thread chef(&Restaurant::chef, std::ref(restaurant));
//    std::thread waiter(&Restaurant::waiter, std::ref(restaurant));
//    chef.join();
//    waiter.join();
//    return 0;
//}


// 4 --------------------------------------------------------------


// 5 --------------------------------------------------------------





















