
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

// this tells the compiler how to output vectors via cout
ostream &operator<<(ostream &os, vector<int> &vec) {
    os << "[ ";
    for (int &el: vec)
        os << el << ", ";
    return os << "]";
}

bool isDone = false;
int winnerThread;
thread threads[4];
// a lock, which only one thread can hold at a time
mutex winnersLock;

void bogosorter(int number, vector<int> array) {
    while (!is_sorted(array.begin(), array.end()) && !isDone)
        random_shuffle(array.begin(), array.end());

    if (winnersLock.try_lock() && !isDone) {
        isDone = true;
        winnerThread = number;

        cout << "thread #" << winnerThread << " won!" << endl;
        cout << "Here's my array: " << array << endl;

        winnersLock.unlock();
    }
}

int main() {
    vector<int> myArray = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

    random_shuffle(myArray.begin(), myArray.end());

    threads[0] = thread(bogosorter, 1, myArray);
    threads[1] = thread(bogosorter, 2, myArray);
    threads[2] = thread(bogosorter, 3, myArray);
    threads[3] = thread(bogosorter, 4, myArray);

    for (thread &th: threads)
        th.join();

    return 0;
}
