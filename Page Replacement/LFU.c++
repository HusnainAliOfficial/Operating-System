#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Page
{
    int page_Number;
    int frequency;
    int order;
};
int LFU(int pages[], int n, int capacity)
{
    Page page_Array[capacity];
    int page_faults = 0;
    int order = 0;

    for (int i = 0; i < n; i++)
    {
        if (order < capacity)
        {
            Page *current = find_if(page_Array, page_Array + order, [&](const Page &p)
                               { return p.page_Number == pages[i]; });

            if (current == page_Array + order)
            {
                page_faults++;
                Page new_Page = {pages[i], 1, order++};
                page_Array[order - 1] = new_Page;
            }
            else
            {
                current->frequency++;
            }
        }
        else
        {
            Page *current = find_if(page_Array, page_Array + order, [&](const Page &p)
                                    { return p.page_Number == pages[i]; });

            if (current == page_Array + order)
            {
                Page *lfu_Page = min_element(page_Array, page_Array + order,
                                            [](const Page &a, const Page &b)
                                            {
                                                return a.frequency < b.frequency;
                                            });

                int lfu_Index = lfu_Page - page_Array;
                *lfu_Page = {pages[i], 1, order++};
                page_faults++;
            }
            else
            {
                current->frequency++;
            }
        }
    }

    return page_faults;
}
int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 0, 9, 8, 7, 6, 5, 2, 3, 0, 3, 2, 9};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    cout << "Total Number Of Page Fault: " << LFU(pages, n, capacity) << endl;
    return 0;
}
