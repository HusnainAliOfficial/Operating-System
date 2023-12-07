#include <iostream>
#include <map>
#include <climits>
using namespace std;
int LRU(int pages[], int n, int capacity)
{
    map<int, int> indexes;
    int pageOrder[capacity];
    int orderSize = 0;
    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        if (orderSize < capacity)
        {
            if (indexes.find(pages[i]) == indexes.end())
            {
                page_faults++;
                indexes[pages[i]] = orderSize;
                pageOrder[orderSize++] = pages[i];
            }
            else
            {
                indexes[pages[i]] = orderSize - 1;
            }
        }
        else
        {
            if (indexes.find(pages[i]) == indexes.end())
            {
                int lru = INT_MAX, val;
                for (int j = 0; j < orderSize; j++)
                {
                    if (indexes[pageOrder[j]] < lru)
                    {
                        lru = indexes[pageOrder[j]];
                        val = pageOrder[j];
                    }
                }
                indexes.erase(val);
                indexes[pages[i]] = orderSize - 1;
                pageOrder[orderSize - 1] = pages[i];
                page_faults++;
            }
            else
            {
                indexes[pages[i]] = orderSize - 1;
            }
        }
    }

    return page_faults;
}
int main()
{
    int pages[] ={7, 0, 1, 2, 0, 3, 0, 4, 0, 9, 8, 7, 6, 5,2, 3, 0, 3, 2, 9};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    cout << "Total Number Of Page Fault :" << LRU(pages, n, capacity)<<endl;
    return 0;
}
