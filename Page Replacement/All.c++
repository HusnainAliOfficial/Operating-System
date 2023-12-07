#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

void initializeFrames(list<int> &frames)
{
    frames.clear();
}

int pageFaultsFIFO(list<int> &frames, int capacity, int page)
{
    int pageFaults = 0;

    auto it = find(frames.begin(), frames.end(), page);
    if (it == frames.end())
    {
        if (frames.size() == capacity)
        {
            frames.pop_front();
        }
        frames.push_back(page);
        pageFaults++;
    }

    return pageFaults;
}

int findMinFrequencyPage(const list<int> &frames, const list<int> &reference, int *frequency)
{
    int minFreq = frequency[frames.front()];
    int minFreqPage = frames.front();

    for (int frame : frames)
    {
        if (frequency[frame] < minFreq)
        {
            minFreq = frequency[frame];
            minFreqPage = frame;
        }
    }

    return minFreqPage;
}

int pageFaultsLFU(list<int> &frames, int *frequency, int capacity, int page)
{
    int pageFaults = 0;

    auto it = find(frames.begin(), frames.end(), page);
    if (it == frames.end())
    {
        if (frames.size() == capacity)
        {
            int minFreqPage = findMinFrequencyPage(frames, frames, frequency);
            frames.remove(minFreqPage);
        }
        frames.push_back(page);
        pageFaults++;
    }

    frequency[page]++;
    return pageFaults;
}

int pageFaultsLRU(list<int> &frames, int capacity, int page)
{
    int pageFaults = 0;

    frames.remove(page);
    if (frames.size() == capacity)
    {
        frames.pop_front();
    }
    frames.push_back(page);
    pageFaults++;

    return pageFaults;
}

int simulatePageReplacement(list<int> &frames, int capacity, int *pageReference, int referenceSize, int algorithm)
{
    int pageFaults = 0;
    int *frequency = new int[referenceSize](); // Initialize frequency array to 0

    initializeFrames(frames);

    for (int i = 0; i < referenceSize; ++i)
    {
        switch (algorithm)
        {
        case 0:
            pageFaults += pageFaultsFIFO(frames, capacity, pageReference[i]);
            break;
        case 1:
            pageFaults += pageFaultsLFU(frames, frequency, capacity, pageReference[i]);
            break;
        case 2:
            pageFaults += pageFaultsLRU(frames, capacity, pageReference[i]);
            break;
        }

        cout << "Page frames after reference " << i + 1 << ": ";
        for (int frame : frames)
        {
            cout << frame << " ";
        }
        cout << endl;
    }

    delete[] frequency;
    return pageFaults;
}

int main()
{
    const int capacity = 4;
    const int referenceSize = 20;

    int page_Reference_1[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 4, 2, 3, 0, 3, 2};
    int page_Reference_2[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5, 3, 4, 1, 2, 5, 3, 4, 1, 2};
    int page_Reference_3[] = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    list<int> frames;
    int pageFaults;

    cout << "FIFO Algorithm - Scenario 1:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_1, referenceSize, 0);
    cout << "Total Page Faults: " << pageFaults << endl << endl;

    cout << "LFU Algorithm - Scenario 1:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_1, referenceSize, 1);
    cout << "Total Page Faults: " << pageFaults << endl << endl;

    cout << "LRU Algorithm - Scenario 1:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_1, referenceSize, 2);
    cout << "Total Page Faults: " << pageFaults << endl
         << endl;

    cout << "FIFO Algorithm - Scenario 2:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_2, referenceSize, 0);
    cout << "Total Page Faults: " << pageFaults << endl << endl;

    cout << "LFU Algorithm - Scenario 2:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_2, referenceSize, 1);
    cout << "Total Page Faults: " << pageFaults << endl<< endl;

    cout << "LRU Algorithm - Scenario 2:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_2, referenceSize, 2);
    cout << "Total Page Faults: " << pageFaults << endl  << endl;

    cout << "FIFO Algorithm - Scenario 3:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_3, referenceSize, 0);
    cout << "Total Page Faults: " << pageFaults << endl
         << endl;

    cout << "LFU Algorithm - Scenario 3:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_3, referenceSize, 1);
    cout << "Total Page Faults: " << pageFaults << endl
         << endl;

    cout << "LRU Algorithm - Scenario 3:" << endl;
    pageFaults = simulatePageReplacement(frames, capacity, page_Reference_3, referenceSize, 2);
    cout << "Total Page Faults: " << pageFaults << endl
         << endl;
    return 0;
}
