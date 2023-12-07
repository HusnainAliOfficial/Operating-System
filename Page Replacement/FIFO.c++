#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int FIFO(int pages[], int n, int capacity)
{
    queue<int> indexes;
    int page_faults = 0;
    int setArray[capacity];
    int setSize = 0;

    for (int i = 0; i < n; i++)
    {
        if (setSize < capacity)
        {
            if (find(setArray, setArray + setSize, pages[i]) == setArray + setSize)
            {
                setArray[setSize++] = pages[i];
                page_faults++;
                indexes.push(pages[i]);
            }
        }
        else
        {

            if (find(setArray, setArray + setSize, pages[i]) == setArray + setSize)
            {
                int val = indexes.front();
                indexes.pop();
                auto it = find(setArray, setArray + setSize, val);
                if (it != setArray + setSize)
                {
                    copy(it + 1, setArray + setSize, it);
                    setSize--;
                }
                setArray[setSize++] = pages[i];
                indexes.push(pages[i]);
                page_faults++;
            }
        }
    }
    return page_faults;
}

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 0, 9, 8, 7, 6, 5,
                   2, 3, 0, 3, 2, 9};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 4;
    cout <<"Total Number Of Page Fault :"<< FIFO(pages, n, capacity) << endl;
    return 0;
}
