#ifndef LAB_1_RADIXTREE_H
#define LAB_1_RADIXTREE_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

struct RadixTrieNode {
    std::string prefix;
    std::vector<std::unique_ptr<RadixTrieNode>> children;
    bool is_end;

    explicit RadixTrieNode(std::string pref = "", const bool is_end = false)
        : prefix(std::move(pref)), is_end(is_end) {}
};

class RadixTree {
private:
    std::unique_ptr<RadixTrieNode> root;

    void insert_recursive(RadixTrieNode* node, const std::string& word, std::size_t pos) {
        std::size_t common_prefix_len = 0;

        while (pos + common_prefix_len < word.length() &&
               common_prefix_len < node->prefix.length() &&
               word[pos + common_prefix_len] == node->prefix[common_prefix_len]) {
            ++common_prefix_len;
        }

        if (common_prefix_len < node->prefix.length()) {
            auto new_child = std::make_unique<RadixTrieNode>(
                node->prefix.substr(common_prefix_len),
                node->is_end
            );
            new_child->children = std::move(node->children);

            node->prefix = node->prefix.substr(0, common_prefix_len);
            node->is_end = false;
            node->children.clear();
            node->children.push_back(std::move(new_child));
        }

        if (pos + common_prefix_len < word.length()) {
            std::size_t next_pos = pos + common_prefix_len;
            char next_char = word[next_pos];

            for (auto& child : node->children) {
                if (!child->prefix.empty() && child->prefix[0] == next_char) {
                    insert_recursive(child.get(), word, next_pos);
                    return;
                }
            }

            node->children.push_back(
                std::make_unique<RadixTrieNode>(word.substr(next_pos), true)
            );
        } else {
            node->is_end = true;
        }
    }

    bool search_recursive(const RadixTrieNode* node, const std::string& word, std::size_t pos) const {
        std::size_t common_prefix_len = 0;

        while (pos + common_prefix_len < word.length() &&
               common_prefix_len < node->prefix.length() &&
               word[pos + common_prefix_len] == node->prefix[common_prefix_len]) {
            ++common_prefix_len;
        }

        if (common_prefix_len < node->prefix.length()) {
            return false;
        }

        if (pos + common_prefix_len < word.length()) {
            std::size_t next_pos = pos + common_prefix_len;
            char next_char = word[next_pos];

            for (const auto& child : node->children) {
                if (!child->prefix.empty() && child->prefix[0] == next_char) {
                    return search_recursive(child.get(), word, next_pos);
                }
            }
            return false;
        }

        return node->is_end;
    }

    void collect_words(const RadixTrieNode* node, const std::string& current_word, std::vector<std::string>& results) const {
        if (node->is_end) {
            results.push_back(current_word);
        }

        for (const auto& child : node->children) {
            collect_words(child.get(), current_word + child->prefix, results);
        }
    }

    void print_node(const RadixTrieNode* node, std::size_t depth) const {
        for (std::size_t i = 0; i < depth; ++i) {
            std::cout << "  ";
        }

        std::cout << "- \"" << node->prefix << "\"";
        if (node->is_end) {
            std::cout << " [END]";
        }
        std::cout << "\n";

        for (const auto& child : node->children) {
            print_node(child.get(), depth + 1);
        }
    }

public:
    RadixTree() : root(std::make_unique<RadixTrieNode>()) {}

    void insert(const std::string& word) {
        if (word.empty()) return;
        insert_recursive(root.get(), word, 0);
    }

    bool search(const std::string& word) const {
        if (word.empty()) return false;
        return search_recursive(root.get(), word, 0);
    }

    std::vector<std::string> auto_complete(const std::string& prefix) const {
        std::vector<std::string> results;
        if (prefix.empty()) {
            return results;
        }
        
        const RadixTrieNode* current_node = root.get();
        std::string current_prefix = "";
        std::string prefix_remaining = prefix;

        while (!prefix_remaining.empty()) {
            bool found_child = false;
            for (const auto& child : current_node->children) {

                if (child->prefix[0] != prefix_remaining[0]) {
                    continue;
                }
                
                int common_len = 0;
                while (common_len < child->prefix.length() && common_len < prefix_remaining.length() &&
                       child->prefix[common_len] == prefix_remaining[common_len]) {
                    common_len++;
                       }
                
                if (common_len < prefix_remaining.length() && common_len < child->prefix.length()) {
                    return {};
                }

                if (common_len == prefix_remaining.length() && common_len < child->prefix.length()) {
                    current_prefix += child->prefix;
                    prefix_remaining.clear();
                    current_node = child.get();
                    found_child = true;
                    break;
                }

                current_prefix += child->prefix;
                prefix_remaining = prefix_remaining.substr(common_len);
                current_node = child.get();
                found_child = true;
                break;
            }

            if (!found_child) {
                return {};
            }
        }

        collect_words(current_node, current_prefix, results);

        return results;
    }

    void debug_print() const {
        if (!root) {
            std::cout << "<empty tree>\n";
            return;
        }
        std::cout << "RadixTree structure:\n";
        print_node(root.get(), 0);
    }
};

#endif // LAB_1_RADIXTREE_H
