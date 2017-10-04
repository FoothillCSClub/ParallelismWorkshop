
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

bool isDone = false;

void bogosorter(int number, vector<int> array) {
    while (!is_sorted(array.begin(), array.end()) && !isDone)
        random_shuffle(array.begin(), array.end());
    isDone = true;
}

int main() {
    vector<int> myArray = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

    random_shuffle(myArray.begin(), myArray.end());

    thread threads[4] = {
        thread(bogosorter, 1, myArray),
        thread(bogosorter, 2, myArray),
        thread(bogosorter, 3, myArray),
        thread(bogosorter, 4, myArray),
    };

    for (thread &th: threads)
        th.join();

    return 0;
}
