#ifndef LAB_1_SPELLHEPLER_H
#define LAB_1_SPELLHEPLER_H
#include "Trie.h"

#include <memory>

class SpellHelper {
private:
  std::unique_ptr<Trie> trie;

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
  SpellHelper() {
    trie = std::make_unique<Trie>();
  }

  void insert(const std::string& word) const {
    trie->insert(to_lower_case(word));
  }

  std::vector<std::string> search(const std::string& word) const {
    std::vector<std::string> result;
    if (word != to_lower_case(word) && word != to_upper_case(word) && word != capitalize(word)) {
      return result;
    }

    result = trie->auto_complete(to_lower_case(word));

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

#endif // LAB_1_SPELLHEPLER_H
