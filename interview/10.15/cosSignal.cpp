#include <iostream>
#include <cmath>

const double PI = acos(-1.0);
const double RATE = 20e6;		// 采样率
const double FREQUENCE = 1e3;	// 频率
const double DURATION = 0.01;	// 持续时间

//使用熟悉的语言生成一个1kHz的余弦信号，信号长度为10ms，采样率为20MHz
void generate(double* signal, int count) {
    for (int i = 0; i < count; ++i) {
        double angle = 2 * PI * FREQUENCE * i / RATE;
        signal[i] = cos(angle);
    }
}

int main() {
    const int count = DURATION * RATE;
    //const int count = 100;
    double* signal = new double[count];
    generate(signal, count);
    for (int i = 0; i < count; ++i) std::cout << signal[i] << " ";
    delete[] signal;
    return 0;
}