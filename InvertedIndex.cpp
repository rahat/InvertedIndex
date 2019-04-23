#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

struct location {
    int line_number;
    int position;
};

bool is_whitespace(const std::string &s) {
    return std::all_of(s.begin(), s.end(), isspace);
}

int main() {
    std::string line, word;
    std::ifstream input_file("Gettysburg Address.txt");
    std::map<std::string, std::vector<location>> word_map;

    int line_number = 0;
    int word_number = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            location loc{};
            std::vector<location> word_loc;
            line_number++;
            word_number = 0;
            std::stringstream ss(line);

            while (ss >> word) {
                word_number++;
                for (auto &c : word) {
                    word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
                    c = tolower(c);
                }

                if (!is_whitespace(word)) {
                    loc.line_number = line_number;
                    loc.position = word_number;
                    word_map[word].push_back(loc);
                }
            }
        }
    }

    for (auto &it : word_map) {
        auto vec = it.second;
        std::cout << it.first << " " << vec.size() << " [";
        for (size_t i = 0; i < vec.size(); i++) {
            std::cout << "(" << vec[i].line_number << "," << vec[i].position << ")";
            if (i != vec.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]";
        std::cout << std::endl;
    }
    input_file.close();
    return 0;
}