#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
using namespace std;

// Додає біт парності
uint16_t addParityBit(uint16_t data) {
    int count = 0;
    for (int i = 0; i < 15; ++i)
        if (data & (1 << i)) ++count;

    if (count % 2 != 0)
        data |= (1 << 15); // Встановл. біта парності

    return data;
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Couldnt open input.txt" << endl;
        return 1;
    }

    string text;
    getline(fin, text, '\0');
    fin.close();

    text.resize(128, ' '); // Доповнення пробілами

    ofstream fout("output.enc", ios::binary);
    if (!fout) {
        cerr << "Couldnt open output.enc" << endl;
        return 1;
    }

    for (int i = 0; i < 128; ++i) {
        unsigned char ch = text[i];
        uint16_t data = 0;

        data |= (ch << 7);   // ASCII у бітах 7-14
        data |= (i & 0x7F);  // Позиція у бітах 0-6

        data = addParityBit(data); // біт парності

        // Запис у файл від старшого до молодшого
        fout.put(static_cast<char>((data >> 8) & 0xFF));
        fout.put(static_cast<char>(data & 0xFF));
    }

    fout.close();
    cout << "Encoding complete.File written in output.enc" << endl;
    return 0;
}
