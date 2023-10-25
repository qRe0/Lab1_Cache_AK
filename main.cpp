#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>

std::vector<int> randomCyclicPermutation(int length) {
    std::vector<int> result(length);
    std::vector<int> unusedIndexes;
    for (int i = 1; i < length; i++) {
        unusedIndexes.push_back(i);
    }
    int currentIndex = 0;
    for (int i = 0; i < length - 1; i++) {
        int r = rand() % unusedIndexes.size();
        int nextInd = unusedIndexes[r];
        unusedIndexes.erase(unusedIndexes.begin() + r);
        result[currentIndex] = nextInd;
        currentIndex = nextInd;
    }
    return result;
}

double benchmarkLatency(int sizeBytes, int iterations) {
    std::vector<int> array = randomCyclicPermutation(sizeBytes / 4);
    int pointer = 0;
    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        pointer = array[pointer];
    }
    clock_t end = clock();
    return static_cast<double>(end - start) / CLOCKS_PER_SEC / static_cast<double>(iterations);
}

int main() {
    // Открываем файл для записи
    std::ofstream out("data.txt");

    // Устанавливаем seed для генератора случайных чисел
    srand(static_cast<unsigned>(time(0)));

    for (double i = 5000.0; i <= 20000000.0; i *= 1.2) {
        std::cout << static_cast<int>(i) << " " << benchmarkLatency(static_cast<int>(i), 20000000) * 1000000000 << std::endl;
        out << static_cast<int>(i) << " " << benchmarkLatency(static_cast<int>(i), 20000000) * 1000000000 << std::endl;
    }

    std::cout << "All done\n";

    out.close();
    return 0;
}
