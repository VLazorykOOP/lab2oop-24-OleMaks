#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;

    cout << "Enter values of a, b, c, d: ";
    cin >> a >> b >> c >> d;

    // Обчислення зсувами
    int result = 0;

    // 33 * b -> (b << 5) + b
    result += (b << 5) + b;

    // d * 15 + 12 * a / 512
    // d * 15 -> (d << 3) + (d << 2) + (d << 1) + d
    // 12 * a -> (a << 3) + (a << 2)
    result += (((d << 3) + (d << 2) + (d << 1) + d) + ((a << 3) + (a << 2))) >> 9;

    // 65 * c -> (c << 6) + c
    result -= ((c << 6) + c);

    // d * 14 -> (d << 3) + (d << 2) + (d << 1)
    result += (d << 3) + (d << 2) + (d << 1);

    cout << "Result: " << result << endl;

    return 0;
}