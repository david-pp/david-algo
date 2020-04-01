#include <iostream>
#include <vector>
#include <algorithm>

namespace david {
    template<typename ForwardIt, typename Compare>
    bool is_sorted(ForwardIt first, ForwardIt end, Compare cmp) {

        if (first != end) {
            ForwardIt next = first;
            while (++next != end) {
                if (!cmp(*first, *next))
                    return false;

                first = next;
            }
        }

        return true;
    }

    template<typename ForwardIt>
    bool is_sorted(ForwardIt first, ForwardIt end) {
        return david::is_sorted(first, end, std::less<>());
    }

    template<typename ForwardIt>
    void show(ForwardIt first, ForwardIt end) {
        for (ForwardIt it = first; it != end; it++) {
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
    }

    template<typename ForwardIt, typename Compare>
    void selection_sort(ForwardIt first, ForwardIt end, Compare cmp) {
        for (auto i = first; i != end; ++i) {

            // 找到后面最小的
            auto min = i;
            for (auto j = i; j != end; ++j) {
                if (cmp(*j, *min))
                    min = j;
            }

            // 和当前的进行交换
            std::swap(*i, *min);
        }
    }

    template<typename ForwardIt, typename Compare>
    void insertion_sort(ForwardIt first, ForwardIt end, Compare cmp) {
        for (auto i = first; i != end; i++) {

            // 依次向前交换，直到合适位置
            for (auto j = i; j != first && cmp(*j, *(j - 1)); j--) {
                std::swap(*j, *(j - 1));
            }
        }
    }

    template<typename ForwardIt, typename Compare>
    void shell_sort(ForwardIt first, ForwardIt end, Compare cmp) {
        int N = std::distance(first, end);
        int h = 1;
        while (h < N / 3) h = 3 * h + 1; // 1, 4, 13, 40, 121, 364, 1093, ...
        while (h >= 1) {

            // h-sort the array (insertion sort)
            for (ForwardIt i = first + h; i != end; i++) {
                // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]... .
                for (ForwardIt j = i; j >= (first + h) && cmp(*j, *(j - h)); j -= h)
                    std::swap(*j, *(j - h));
            }
            h = h / 3;
        }
    }


    static int aux[1000];

    void merge(int a[], int lo, int mid, int hi) {
        int i = lo;
        int j = mid + 1;

        // copy to aux
        for (int k = lo; k <= hi; k++)
            aux[k] = a[k];

        for (int k = lo; k <= hi; k++) {
            if (i > mid) a[k] = aux[j++];  // left已空
            else if (j > hi) a[k] = aux[i++];  // right已空
            else if (aux[j] < aux[i]) a[k] = aux[j++];  // 取最小的
            else a[k] = aux[i++];
        }
    }

    // top-down
    void merge_sort(int a[], int lo, int hi) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        merge_sort(a, lo, mid);
        merge_sort(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }

    // bottom-up
    void merge_sort2(int a[], int len) {
        int *aux = new int[len];

        for (int sz = 1; sz < len; sz = sz + sz) {
            for (int lo = 0; lo < len - sz; lo += sz + sz) {
                merge(a, lo, lo + sz - 1, std::min(lo + sz + sz - 1, len - 1));
            }
        }

        delete[] aux;
    }


    int partition(int a[], int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        int v = a[lo]; // pivot
        while (true) {
            while (a[++i] < v) if (i == hi) break; // scan right
            while (v < a[--j]) if (j == lo) break; // scan left
            if (i >= j) break;

            std::swap(a[i], a[j]);
        }

        std::swap(a[lo], j);
        return j;
    }

    void quick_sort(int a[], int lo, int hi) {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        quick_sort(a, lo, j - 1);
        quick_sort(a, j + 1, hi);
    }

} // end namespace david

int main() {
    std::cout << "--- Sorting :" << std::endl;

    int a[] = {3, 2, 3, 1, 5, 4};

    std::vector<int> b = {5, 4, 3, 2, 1};
    //int a[] = {1, 2, 3, 4, 5};

    std::cout << david::is_sorted(a, a + 5) << std::endl;
    std::cout << david::is_sorted(b.begin(), b.end(), std::greater<>()) << std::endl;

    //david::selection_sort(std::begin(a), std::end(a), std::less<>());
    //david::insertion_sort(std::begin(a), std::end(a), std::less<>());
    //david::shell_sort(std::begin(a), std::end(a), std::less<>());
    //david::merge_sort(a, 0, 5);
    //david::merge_sort2(a, 5);
    //david::quick_sort(a, 0, 5);
    std::sort(std::begin(a), std::end(a));
    david::show(std::begin(a), std::end(a));
}
