#include <iostream>
#include <memory>
#include <string>
#include <cstring>
#include <vector>

template<typename T>
class Tries {
public:
    static const int R = 256; // Radix
    struct Node {
        Node() {
            nil = true;
            val = T();
            std::memset(next, 0, sizeof(next));
        }

        bool nil;
        T val;
        Node *next[R];
    };

    Tries() {
//        root_ = new Node;
    }

    T get(const std::string &key) {
        Node *x = get(root_, key, 0);
        if (!x) return T();
        return x->val;
    }

    void put(const std::string &key, T val) {
        put(root_, key, val, 0);
    }

    int size() {
        return size(root_);
    }

    // 显示树状结构
    void dump() {
        dumpnode(root_, '#', 0);
    }

    std::vector<std::string> keys() {
        return keysWithPrefix("");
    }

    std::vector<std::string> keysWithPrefix(const std::string &pre) {
        std::vector<std::string> keys;
        collect(get(root_, pre, 0), pre, keys);
        return keys;
    }

    std::vector<std::string> keysThatMatch(const std::string &pat) {
        std::vector<std::string> keys;
        collect_match(root_, "", pat, keys);
        return keys;
    }

    std::string longestPrefixOf(const std::string &s) {
        int length = search(root_, s, 0, 0);
        return s.substr(0, length);
    }

    int search(Node *x, const std::string &s, int d, int length) {
        if (!x) return length;
        if (!x->nil) length = d;
        if (d == s.length()) return length;
        char c = s.at(d);
        return search(x->next[c], s, d + 1, length);
    }

private:
    Node *get(Node *x, const std::string &key, int d) {
        if (!x) return nullptr;
        if (d == key.length()) return x;

        char c = key.at(d);
        return get(x->next[c], key, d + 1);
    }

    // key[d]放在x节点的下面
    Node *put(Node *&x, const std::string &key, T val, int d) {

        if (!x) x = new Node;

        if (d == key.length()) {
            x->val = val;
            x->nil = false;
            return x;
        }

        char c = key.at(d);
        x->next[c] = put(x->next[c], key, val, d + 1);
        return x;
    }

    int size(Node *x) {
        if (!x) return 0;
        int cnt = 0;
        if (!x->nil) cnt++;

        for (char c = 0; c < R; c++) {
            cnt += size(x->next[c]);
        }

        return cnt;
    }

    void dumpnode(Node *x, char ch, int d) {
        if (!x) return;

        if (d > 0) {
            std::cout << std::string(d, ' ');
        }

        std::cout << ch << ": " << x->val << std::endl;

        for (int c = 0; c < R; c++) {
            Node *node = x->next[c];
            if (node) {
                dumpnode(node, c, d + 1);
            }
        }
    }

    void collect(Node *x, const std::string &pre, std::vector<std::string> &keys) {
        if (!x) return;

        if (!x->nil) {
            keys.push_back(pre);
        }

        for (int c = 0; c < R; c++) {
            collect(x->next[c], pre + char(c), keys);
        }
    }

    void collect_match(Node *x,
                       const std::string &pre,
                       const std::string &pat,
                       std::vector<std::string> &keys) {
        int d = pre.length();
        if (!x) return;
        if (d == pat.length() && !x->nil) {
            keys.push_back(pre);
        }

        if (d == pat.length()) return;

        char next = pat.at(d);
        for (int c = 0; c < R; c++) {
            if (next == '.' || next == c) {
                collect_match(x->next[c], pre + char(c), pat, keys);
            }
        }
    }

    Node *root_ = nullptr;
};

void test() {
    std::cout << "------------------------" << std::endl;
    Tries<int> tries;
    tries.put("she", 0);
    tries.put("sells", 1);
    tries.put("sea", 2);
    tries.put("shells", 3);
    tries.put("by", 4);
    tries.put("the", 5);
    tries.put("see", 6);
    tries.put("shore", 7);
    tries.dump();

    std::cout << "------------------------" << std::endl;
    std::cout << tries.get("shore") << std::endl;

    std::cout << "------------------------" << std::endl;
    for (auto &v : tries.keysWithPrefix("se")) {
        std::cout << "key : " << v << std::endl;
    }

    std::cout << "------------------------" << std::endl;
    for (auto &v : tries.keysThatMatch("s.")) {
        std::cout << "key : " << v << std::endl;
    }

    std::cout << "------------------------" << std::endl;
    std::cout << tries.longestPrefixOf("shelters") << std::endl;
}

int main(int argc, char *argv[]) {
    test();
}