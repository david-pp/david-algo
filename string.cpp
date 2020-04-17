//
// Created by wangdawei on 2020/4/10.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//////////////////////////////////////////////////////////////

struct Item {
    std::string name;  // key
    int section;       // index
};

Item items[] = {
        {"Anderson", 2},
        {"Brown",    3},
        {"Davis",    3},
        {"Garcia",   4},
        {"Harris",   1},
        {"Jackson",  3},
        {"Johnson",  4},
        {"Jones",    3},
        {"Martin",   1},
        {"Martinez", 2},
        {"Miller",   2},
        {"Moore",    1},
        {"Robinson", 2},
        {"Smith",    4},
        {"Taylor",   3},
        {"Thomas",   4},
        {"Thompson", 4},
        {"White",    2},
        {"Williams", 3},
        {"Wilson",   4},
};

void print_items() {
    for (int i = 0; i < sizeof(items) / sizeof(Item); ++i) {
        std::cout << items[i].name << "\t" << items[i].section << std::endl;
    }
}

//
// Key-indexed counting
//
// time:  8N + 3R + 1 (小于NlgN)
// space:  N + R + 1
//
// N - 元素个数
// R - index范围（Radix）
void sort_by_index(Item *items, size_t n) {

    size_t R = 5; // index的范围：[0, R)

    std::vector<Item> aux(n);          // 辅助存储
    std::vector<int> count(R + 1, 0);  // 统计index频率: count[index]


    // 统计index频率 -> count[section + 1]
    for (size_t i = 0; i < n; i++) {
        count[items[i].section + 1]++;
    }

    // 频率转换成items的下标 -> 起始位置：count[section]
    for (size_t r = 0; r < R; r++) {
        count[r + 1] += count[r];
    }

    // 分配Item到合适的索引位置
    for (size_t i = 0; i < n; i++) {
        // 当前的Item根据index放入合适的aux位置，同时递增目前index的起始位置
        aux[count[items[i].section]++] = items[i];
    }

    // Copy Back
    for (size_t i = 0; i < n; i++) {
        items[i] = aux[i];
    }
}

//////////////////////////////////////////////////////////////


std::vector<std::string> licenses = {
        "4PGC938",
        "2IYE230",
        "3CIO720",
        "1ICK750",
        "1OHV845",
        "4JZY524",
        "1ICK750",
        "3CIO720",
        "1OHV845",
        "1OHV845",
        "2RLA629",
        "2RLA629",
        "3ATW723",
};

void print_lincenses() {
    for (auto &e : licenses) {
        std::cout << e << std::endl;
    }
}

void sort_by_lsd(std::vector<std::string> &a, int W) {
    int N = a.size();
    int R = 256;
    std::vector<std::string> aux(N);

    // 从右到左对每个字母进行key-indexed排序
    for (int d = W - 1; d >= 0; d--) {

        std::vector<int> count(R + 1, 0);

        // Compute frequency count
        for (size_t i = 0; i < N; i++) {
            count[a[i][d] + 1]++;
        }

        // Transform count to indices
        for (size_t r = 0; r < R; r++) {
            count[r + 1] += count[r];
        }

        // Distribute
        for (size_t i = 0; i < N; i++) {
            aux[count[a[i][d]]++] = a[i];
        }

        // Copy Back
        for (size_t i = 0; i < N; i++) {
            a[i] = aux[i];
        }
    }
}

//////////////////////////////////////////////////////////////

static std::vector<std::string> words = {
        "she",
        "sells",
        "seashells",
        "by",
        "the",
        "seashore",
        "the",
        "shells",
        "she",
        "sells",
        "are",
        "surely",
        "seashells",
};

void print_words() {
    for (auto &e : words) {
        std::cout << e << std::endl;
    }
}

void sort_by_insert(std::vector<std::string> &a, int lo, int hi, int d) {

    auto less = [](std::string &v, std::string &w, int d) -> bool {
        return v.substr(d) < w.substr(d);
    };
    for (int i = lo; i <= hi; i++) {
        for (int j = i; j > lo && less(a[j], a[j - 1], d); j--)
            std::swap(a[j], a[j - 1]);
    }
}

void sort_by_msd(std::vector<std::string> &a, int lo, int hi, int d) {

    static int M = 15; // cutoff by insert-sorting

    // 优化：小数组采用Insert排序
    if (hi <= lo + M) {
        sort_by_insert(a, lo, hi, d);
        return;
    }

    if (lo >= hi) return;

    int N = a.size();
    int R = 256; // Radix
    static std::vector<std::string> aux(N);
    std::vector<int> count(R + 2, 0);

    // Compute frequency count
    for (int i = lo; i <= hi; i++) {
        count[a[i][d] + 2]++;
    }

    // Transform counts to indices
    for (int r = 0; r < R + 1; r++) {
        count[r + 1] += count[r];
    }

    // Distribute
    for (int i = lo; i <= hi; i++) {
        aux[count[a[i][d] + 1]++] = a[i];
    }

    // Copy back.
    for (int i = lo; i <= hi; i++) {
        a[i] = aux[i - lo];
    }

    // Recursively sort for each character value
    for (int r = 0; r < R; r++) {
        sort_by_msd(a, lo + count[r], lo + count[r + 1] - 1, d + 1);
    }
}

//////////////////////////////////////////////////////////////


std::vector<std::string> urls = {
        "edu.princeton.cs",
        "com.apple",
        "edu.princeton.cs",
        "com.cnn",
        "com.google",
        "edu.uva.cs",
        "edu.princeton.cs",
        "edu.princeton.cs.www",
        "edu.uva.cs",
        "edu.uva.cs",
        "edu.uva.cs",
        "com.adobe",
        "edu.princeton.ee"
};


void sort_by_quick3(std::vector<std::string> &a, int lo, int hi, int d) {
    if (hi <= lo) return;

    int lt = lo;
    int gt = hi;
    int v = a[lo][d];
    int i = lo + 1;

    while (i <= gt) {
        int t = a[i][d];
        if (t < v) std::swap(a[lt++], a[i++]);
        else if (t > v) std::swap(a[i], a[gt--]);
        else i++;
    }

    sort_by_quick3(a, lo, lt - 1, d);
    if (v >= 0) sort_by_quick3(a, lt, gt, d + 1);
    sort_by_quick3(a, gt + 1, hi, d);
}

//////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
//    sort_by_index(items, sizeof(items) / sizeof(Item));
//    print_items();

//    sort_by_lsd(licenses, licenses[0].length());
//    print_lincenses();

//    sort_by_msd(words, 0, words.size() - 1, 0);
//    print_words();

    sort_by_quick3(urls, 0, urls.size() - 1, 0);
    for (auto &e : urls) {
        std::cout << e << std::endl;
    }
}