#ifndef LAB_1_SPELLCHECKER_H
#define LAB_1_SPELLCHECKER_H
#include "RadixTree.h"
#include "../stream-dir/core/TextFileReader.h"

#include <memory>

class SpellChecker {
private:
  std::unique_ptr<RadixTree> radix_tree;

  void init_radix_tree(std::string path) {
    TextFileReader reader(path);

    while (!reader.is_eof()) {
      radix_tree->insert(reader.read_word());
    }

    radix_tree.get()->debug_print();
  }

  std::string to_lower_case(const std::string& word) const {
    std::string lower_word = word;
    std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return lower_word;
  }

  std::string to_upper_case(const std::string& word) const {
    std::string upper_word = word;
    std::transform(upper_word.begin(), upper_word.end(), upper_word.begin(),
                   [](unsigned char c){ return std::toupper(c); });

    return upper_word;
  }

  std::string capitalize(const std::string& word) const {
    std::string result = word;
    result[0] = static_cast<char>(std::toupper(result[0]));

    for (size_t i = 1; i < result.size(); ++i) {
      result[i] = static_cast<char>(std::tolower(result[i]));
    }

    return result;
  }

public:
  explicit SpellChecker(const std::string& path_to_vocabulary = "D:/Programming/Prog_Cpp/lab-assignment-3d-term/lab-1/src/resources/vocabulary.txt") : radix_tree(std::make_unique<RadixTree>()) {
    init_radix_tree(path_to_vocabulary);
  }

  bool search(const std::string &word) {
    if (word == to_lower_case(word) || word == to_upper_case(word) || word == capitalize(word)) {
      return radix_tree->search(to_lower_case(word));
    }

    return false;
  }

  void insert(const std::string& word) {
    radix_tree->insert(to_lower_case(word));
  }

  std::vector<std::string> auto_complete(const std::string& word) const {
    std::vector<std::string> result = radix_tree->auto_complete(to_lower_case(word));

    if (word == to_lower_case(word)) {
      return result;
    }
    if (word == to_upper_case(word)) {
      for (auto& w: result) {
        w = to_upper_case(w);
      }
      return result;
    }
    if (word == capitalize(word)) {
      for (auto& w: result) {
        w[0] = static_cast<char>(std::toupper(w[0]));
      }
      return result;
    }
    return result;
  }
};

#endif // LAB_1_SPELLCHECKER_H
