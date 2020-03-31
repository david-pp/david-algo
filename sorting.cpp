#include <iostream>
#include <vector>
#include <algorithm>

namespace david {
    template <typename ForwardIt, typename Compare>
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

    template <typename ForwardIt>
        bool is_sorted(ForwardIt first, ForwardIt end) {
            return david::is_sorted(first, end, std::less<>());
        }

    template <typename ForwardIt>
        void show(ForwardIt first, ForwardIt end) {
            for (ForwardIt it = first; it != end; it++) {
                std::cout << *it << ", ";
            }
            std::cout << std::endl;
        }

    template <typename ForwardIt, typename Compare>
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

    template <typename ForwardIt, typename Compare>
        void insertion_sort(ForwardIt first, ForwardIt end, Compare cmp) {
            for (auto i = first; i != end; i++) {

                // 依次向前交换，直到合适位置
                for (auto j = i; j != first && cmp(*j, *(j-1)); j--) {
                    std::swap(*j, *(j - 1));
                }
            }
        }

} // end namespace david

int main() {
    std::cout << "--- Sorting :" << std::endl;

    int a[] = {3, 2, 3, 1, 5, 4};

    std::vector<int> b = {5, 4, 3, 2, 1};
    //int a[] = {1, 2, 3, 4, 5};

    std::cout << david::is_sorted(a, a+5) << std::endl;
    std::cout << david::is_sorted(b.begin(), b.end(), std::greater<>()) << std::endl;

    //david::selection_sort(std::begin(a), std::end(a), std::less<>());
    david::insertion_sort(std::begin(a), std::end(a), std::less<>());
    david::show(std::begin(a), std::end(a));
}
