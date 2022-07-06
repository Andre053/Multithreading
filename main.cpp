/*


    This program is meant to demonstrate the power of threads when doing work

    Must use -pthread library and link std using -lstdc++

    TODO: Create a wrapper class to time the working functions

*/
#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>

using namespace std::chrono;

void workUnthreaded();
void workThreaded();
void fillRdmData(int data[], size_t size);
void fillData(int data[], size_t size);
void calcMean(int data[], size_t size);
void calcMode(int data[], size_t size);

int main() {
    workUnthreaded();

    workThreaded();
    return 0;
}

void workUnthreaded() {
    std::cout << "\n### Starting unthreaded work ###\n" << std::endl;
    auto startProg = steady_clock::now();

    size_t size = 50000;
    int data[50000];
    
    fillData(data, size);
    
    calcMean(data, size);
    
    calcMode(data, size);
    
    auto stopProg = steady_clock::now();
    auto durationProg = duration_cast<microseconds>(stopProg - startProg);
    
    std::cout << "The duration to complete all work was: " << durationProg.count() << std::endl;
}

void workThreaded() {
    std::cout << "\n### Starting threaded work ###\n" << std::endl;
    auto startProg = steady_clock::now();

    size_t size = 50000;
    int data[50000];
    
    fillData(data, size);
    std::thread first (calcMean, data, size);
    std::thread second (calcMode, data, size);

    first.join(); // pause until thread 1 is done
    second.join(); // pause until thread 2 is done
    
    auto stopProg = steady_clock::now();
    auto durationProg = duration_cast<microseconds>(stopProg - startProg);
    
    std::cout << "The duration to complete all threaded work was: " << durationProg.count() << std::endl;
}

void fillRdmData(int data[], size_t size) {
    for (int i = 0; i < size; i++)
        data[i] = rand() % 1000; // random number between 0 and 99
}

void fillData(int data[], size_t size) {

    auto start = steady_clock::now();
    fillRdmData(data, size);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    std::cout << "The duration to fill the array was: " << duration.count() << std::endl;
}

void calcMean(int data[], size_t size) {
    // calculate mean
    auto start = steady_clock::now();

    float mean;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }
    mean = sum / size;
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "The duration to calculate the mean was: " << duration.count() << std::endl;
    std::cout << "The mean of the data is: " << mean << std::endl;
}

void calcMode(int data[], size_t size) {
    auto start = steady_clock::now();
    std::unordered_map<int, int> numCounts = {};
    int mode = -1;
    int v;
    for (int i = 0; i < size; i++) {
        v = data[i];
        // add to dictionary
        if (numCounts.find(v) == numCounts.end()) {
            numCounts.insert(std::pair<int, int>(v, 0));
            if (mode == -1) mode = v;
        } else {
            numCounts[v] += 1;
            if (numCounts[v] >= numCounts[mode]) {
                mode = v;
            }
        }
    }
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "The duration to calculate the mode was: " << duration.count() << std::endl;
    std::cout << "The mode of the data is: " << mode << std::endl;

}