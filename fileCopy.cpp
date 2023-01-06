#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

// Absolute location of directory to copy from
const std::string initial {"C:/Users/Asad Rizvi/Desktop/School/u/u"};
// File type of file to read from
const std::string initialType {".txt"};
// Eliminate part of string
const std::string elim{"C:/Users/Asad Rizvi/Desktop/School/u/u\\"};
// Absolute location of file to copy to 
const std::string final {"C:/Users/Asad Rizvi/Desktop/School/u/dictionary.txt"}; 
// Name of output file (excluding type)
const std::string outputFile{"dictionary"};

std::string getFilename(std::string file) {
    std::string fileTemp{file};
    auto search{fileTemp.find(elim)};
    if (search != std::string::npos) {fileTemp.erase(search, elim.size());}
    return fileTemp;
}

int main() {
    namespace folder = std::filesystem;
    std::ofstream dictionaryOutput(final, std::ios::trunc); 
    if (!dictionaryOutput.is_open()) {
        throw std::runtime_error("Failed to open 'dictionary' file.\n");
    }
    for(auto& p: folder::directory_iterator(initial)) {
        auto file = p.path();
        if (file.string().find(outputFile) == std::string::npos and !p.is_directory()) {
            //* Copy contents
            std::string fileName{getFilename(file.string())};
            std::cout << "Attempting to open: " << std::string(initial + "/" + fileName) << '\n';
            std::ifstream readFile(std::string(initial + "/" + fileName), std::ios::in);
            if (!readFile.is_open()) {
                throw std::runtime_error("Failed to open file for reading.\n");
            }
            std::string fileContents;
            std::getline(readFile, fileContents);
            auto filetypeIter = fileName.find(initialType);
            std::string word = fileName.erase(filetypeIter, initialType.size());
            dictionaryOutput << word << ": " << fileContents << '\n';
            readFile.close();
        } 
    }
    dictionaryOutput.close();
    return 0;
}