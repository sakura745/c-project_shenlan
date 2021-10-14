#include <iostream>
#include <cstdlib>
#include <chrono>

int main() {
    int Cnt = 0;
    std::cout << "Enter the number of equations you want to calculate: ";
    std::cin >> Cnt;
    int tmp = Cnt;//用来跳出循环，因为Cnt用到最后判断是否全对，而不能用来跳出循环。

    double maxScore = 0;
    std::cout << "Type in what full marks you want: ";
    std::cin >> maxScore;

    int i = 0;
    std::cout << "Select add and type 1, subtract and type 2, multiply and type 3, divide and type 4: ";
    std::cin >> i;

    int maxValue = 0;
    std::cout << "Please give the maximum range of calculation: ";
    std::cin >> maxValue;

    int correctCnt = 0;
    int wrongCnt = 0;
    double totalScore = 0;
    time_t minTime = INT32_MAX, totalTime;
    srand(time(nullptr));//srand和rand不能放到循环里，否则每次生成的随机数对会不变。

    while (tmp) {
        int a = rand() % maxValue + 1;
        int b = rand() % maxValue + 1;
        int res = 0;

        switch (i) {//四则运算的选择
            case 1:
                res = a + b;
                break;
            case 2:
                res = abs(a - b);
                break;
            case 3:
                res = a * b;
                break;
            case 4:
                res = a / b;
                break;
            default:
                std::cout << "Please enter the correct option!!!\n";
        }

        if (res > maxValue)//确保是res以内的四则运算
            continue;
        tmp--;

        std::cout << "\nGiven two numbers " << a << " and " << b << '\n';
        auto start = std::chrono::steady_clock::now();
        int input = 0;
        std::cout << "Please compute the result: ";
        std::cin >> input;
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time for this problem: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << "ms\n";
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        minTime = std::min(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), minTime);

        if (input == res) {
            correctCnt++;
            double sum = maxScore / Cnt;
            totalScore += sum;
        } else {
            std::cout << "Em! The correct answer is: " << a << " and " << b << " is " << res << std::endl;
            wrongCnt++;
        }
    }

    std::cout << "\nTHE FINAL TEST RESULT\n";
    if (correctCnt == Cnt) {
        std::cout << "Oops! You are fuckin genius! \n";
    } else if (correctCnt == 0) {
        std::cout << "Come on~ Please be serious!! \n";
    }
    std::cout << "Your total score is " << (int)totalScore << " and the full marks is " << maxScore << '\n'
              << "MinTime is " << minTime << "ms, " << "Average Time is " << totalTime / Cnt << "ms\n"
              << "There are " << Cnt << " questions\n"
              << "The correct number of question is " << correctCnt << '\n'
              << "The wrong number of question is " << wrongCnt << '\n';

    return 0;
}

