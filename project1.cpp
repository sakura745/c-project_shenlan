#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>

int main() {
    int Cnt = 0;
    std::cout << "Enter the number of equations you want to calculate: ";
    std::cin >> Cnt;
    int tmp = Cnt;//用来跳出循环，因为Cnt用到最后判断是否全对，而不能用来跳出循环。

    double maxScore = 0;
    std::cout << "Type in what full marks you want: ";
    std::cin >> maxScore;

    int maxValue = 0;
    std::cout << "Please give the maximum range of calculation: ";
    std::cin >> maxValue;

    std::string str;
    std::cout << "Select mode esay and type \'easy\', hard and type \'hard\': ";
    std::cin >> str;

    std::cout << "Keep two decimal places!\n";

    int correctCnt = 0;
    int wrongCnt = 0;
    double totalScore = 0;
    time_t minTime = INT32_MAX, totalTime;
    srand(time(nullptr));//srand和rand不能放到循环里，否则每次生成的随机数对会不变。

    while (tmp) {
        double a = static_cast<double>(rand()) / static_cast<double>(RAND_MAX / maxValue);
        double b = static_cast<double>(rand()) / static_cast<double>(RAND_MAX / maxValue);
        double res = 0;

        std::string s;
        if (str == "easy") {
            int p = rand() % 2 + 1;
            if (p == 1) {
                s = " + ";
                res = a + b;
            } else {
                s = " - ";
                res = a - b;
            }
        } else if (str == "hard") {
            int p = rand() % 4 + 1;
            if (p == 1) {
                s = " + ";
                res = a + b;
            } else if (p == 2) {
                s = " - ";
                res = a - b;
            } else if (p == 3) {
                s = " * ";
                res = a * b;
            } else {
                s = " / ";
                res = a / b;
            }
        } else {
            std::cout << "Please enter the correct option!!!\n";
            break;
        }


        if (res > maxValue)//确保是res以内的四则运算
            continue;
        tmp--;

        std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed)
                  << "\nGiven two numbers " << a << s << b << '\n';
        auto start = std::chrono::steady_clock::now();
        double input = 0;
        std::cout << "Please compute the result: ";
        std::cin >> input;
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time for this problem: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << "ms\n";
        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        minTime = std::min(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), minTime);

        if ((double)std::abs(input - res) < 0.01) {//由于是浮点数，因此不可能输入到和底层写的精度一样。设置一个精度，注意绝对值也有类型！！！
            correctCnt++;
            double sum = maxScore / Cnt;
            totalScore += sum;
        } else {
            std::cout << "Em! The correct answer is: " << a << s << b << " = " << res << std::endl;
            wrongCnt++;
        }
    }

    std::cout << "\nTHE FINAL TEST RESULT\n";
    if (correctCnt == Cnt) {
        std::cout << "Oops! You are fuckin genius! \n";
    } else if (correctCnt == 0) {
        std::cout << "Come on~ Please be serious!! \n";
    }
    std::cout << "Your total score is " << (int)totalScore << " and the full marks is " << (int)maxScore << '\n'
              << "MinTime is " << minTime << "ms, " << "Average Time is " << totalTime / Cnt << "ms\n"
              << "There are " << Cnt << " questions\n"
              << "The correct number of question is " << correctCnt << '\n'
              << "The wrong number of question is " << wrongCnt << '\n';

    return 0;
}

