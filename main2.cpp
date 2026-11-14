#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

// Длина UTF-8 последовательности по первому байту.
static size_t utf8Length(unsigned char lead) {
    if (lead < 0x80)
        return 1;
    if (lead < 0xE0)
        return 2;
    if (lead < 0xF0)
        return 3;
    return 4;
}

// Число букв в слове: латинские буквы и русские (А-я, Ё, ё) в UTF-8.
// Знаки препинания и прочие символы не считаются.
static size_t countLetters(const string &word) {
    size_t letters = 0;
    for (size_t i = 0; i < word.size();) {
        const auto lead = static_cast<unsigned char>(word[i]);
        if (lead < 0x80) {
            if (isalpha(lead))
                ++letters;
            i += 1;
            continue;
        }

        const size_t len = utf8Length(lead);
        if (len == 2 && i + 1 < word.size()) {
            const unsigned codePoint = ((lead & 0x1F) << 6) | (word[i + 1] & 0x3F);
            const bool cyrillicLetter = codePoint == 0x401 || codePoint == 0x451 ||
                                        (codePoint >= 0x410 && codePoint <= 0x44F);
            if (cyrillicLetter)
                ++letters;
        }
        i += len;
    }
    return letters;
}

// Слово — последовательность символов, разделённых пробельными символами.
static size_t countShortWords(ifstream &file) {
    size_t count = 0;
    string line;
    while (getline(file, line)) {
        istringstream words(line);
        string word;
        while (words >> word) {
            const size_t letters = countLetters(word);
            if (letters >= 1 && letters <= 4)
                ++count;
        }
    }
    return count;
}

int main() {
    try {
        cout << "Введите имя файла: ";
        string filename;
        getline(cin, filename);

        ifstream file(filename);
        if (!file.is_open())
            throw runtime_error("не удалось открыть файл: " + filename);

        cout << "Слов, состоящих не более чем из четырёх букв: " << countShortWords(file) << endl;
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}
