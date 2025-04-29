#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
using namespace std;

// Перевірка парності
bool checkParity(uint16_t data) {
    int count = 0;
    for (int i = 0; i < 16; ++i)
        if (data & (1 << i)) ++count;

    return (count % 2 == 0);
}

int main() {
    ifstream fin("output.enc", ios::binary);
    if (!fin) {
        cerr << "Couldnt open output.enc" << endl;
        return 1;
    }

    ofstream fout("decoded.txt");
    if (!fout) {
        cerr << "Couldnt open decoded.txt" << endl;
        return 1;
    }

    string result(128, ' ');

    for (int i = 0; i < 128; ++i) {
        unsigned char high = fin.get();
        unsigned char low = fin.get();
        if (fin.eof()) break;

        uint16_t data = (high << 8) | low;

        if (!checkParity(data)) {
            cerr << "Matching error in symbol #" << i << endl;
            continue;
        }

        unsigned char ascii = (data >> 7) & 0xFF;
        unsigned char pos = data & 0x7F;

        if (pos < 128)
            result[pos] = ascii;
    }

    fin.close();

    cout << "Decoded text:\n" << result << endl;
    fout << result;
    fout.close();

    return 0;
}