#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;
/*
predict() that takes a frame vector, index, and page array. It returns the  predicted page.
*/
int predictPage(int page[], vector<int>& frames, int pageNumber, int pageIndex)
{
    int result = -1, farthestPage = pageIndex;
    for (int i = 0; i < frames.size(); i++)
    {
        int j;
        for (j = pageIndex; j < pageNumber; j++)
        {
            if (frames[i] == page[j])
            {
                if (j > farthestPage)
                {
                    farthestPage = j;
                    result = i;
                }
                break;
            }
        }

        if (j == pageNumber)
            return i;
    }

    if (result == -1)
        return 0;
    else
        return result;
}


/*
boolSearch() that takes a frame vector, and a key that has to be searched in the frame. It return true if the key is found else it returns false
*/
bool searchPage(int key, vector<int>& frames)
{
    for (int i = 0; i < frames.size(); i++)
    {
        // if the frame is found, return true
        if (frames[i] == key)
            return true;
    }

    return false;
}

/*
find() that takes a page array, frame number, and page number. It finds and prints the page hits and page misses.
*/
void findOPT(int page[], int pageNumber, int frameNumber, int step, int fault)
{
    vector<int> frames;
    int hit = 0;
    for (int i = 0; i < pageNumber; i++)
    {
        if (searchPage(page[i], frames))
        {
            // if found, increment the hit counter
            hit++;
            continue;
            
        }

        if (frames.size() < frameNumber) {
            frames.push_back(page[i]);

            // if found, increment the fault and step counter
            fault++;
            step++;
            std::cout << "Step " << step << ": Page fault(" << fault << ") - Page Table: {";
            for (int i = 0; i < frames.size(); i++)
            {
                std::cout << frames[i];

                if (i != (frames.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            std::cout << "}, Frames: [";
            for (int i = 0; i < frames.size(); i++)
            {
                std::cout << frames[i];

                if (i != (frames.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            cout << "], Faults: " << fault << std::endl;
        }
        else
        {
            // if found, increment the fault and step counter
            fault++;
            step++;
            std::cout << "Step " << step << ": Page fault(" << fault  << ") - Page Table: {";
            for (int i = 0; i < frames.size(); i++)
            {
                std::cout << frames[i];

                if (i != (frames.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            std::cout << "}, Frames: [";
            for (int i = 0; i < frames.size(); i++)
            {
                std::cout << frames[i];

                if (i != (frames.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            cout << "], Faults: " << fault << std::endl;

            int j = predictPage(page, frames, pageNumber, i + 1);
            frames[j] = page[i];

        }
        
    }

    // printing the number of faults.
    std::cout << "Total Page Faults: " << pageNumber - hit << endl << endl;
}

void findLRU(std::vector<int> page_reference_string, int size, std::vector<int> pages, int hits, int faults, int step) {
    for (int ref_page : page_reference_string) {
        // if a ref_page already exists in pages list, remove it and append it at the end
        auto it = std::find(pages.begin(), pages.end(), ref_page);
        if (it != pages.end()) {
            pages.erase(it);
            pages.push_back(ref_page);
            // incrementing the page hits
            hits++;
        }
        // if ref_page is not in the pages list
        else {
            // incrementing the page faults
            faults++;
            // check length of the pages list. If length of pages list
            // is less than memory size, append ref_page into pages list
            if (pages.size() < size) {
                pages.push_back(ref_page);
            }
            // if length of pages list is greater than or equal to memory size,
            // remove first page of pages list and append new page to pages
            else {
                pages.erase(pages.begin());
                pages.push_back(ref_page);
            }
            
            step++;
            std::cout << "Step " << step << ": Page fault(" << faults << ") - Page Table: {";
            for (int i = 0; i < pages.size(); i++)
            {
                std::cout << pages[i];

                if (i != (pages.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            std::cout << "}, Frames: [";
            for (int i = 0; i < pages.size(); i++)
            {
                std::cout << pages[i];

                if (i != (pages.size() - 1))
                {
                    std::cout << ", ";
                }
            }
            std::cout << "], Faults: " << faults << std::endl;
        }
    }
    // printing the number of page faults
    std::cout << "Total number of Page Faults: " << faults << std::endl << std::endl;
}

void findFIFO(int pages[], int capacity, int n, queue<int> pageQueue, unordered_set<int> pageSet, int fault, int step){
    for (int i = 0; i < n; i++) {
        if (pageSet.size() < capacity) {
            if (pageSet.find(pages[i]) == pageSet.end()) {
                pageSet.insert(pages[i]);

                // if found, increment the fault and step counter
                fault++;
                step++;
                std::cout << "Step " << step << ": Page fault(" << fault << ") - Page Table: {";
                for (int i = 0; i < sizeof(pages)/sizeof(pages[0]); i++)
                {
                    std::cout << pages[i];

                    if (i != (sizeof(pages) / sizeof(pages[0]) - 1))
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << "}, Frames: [";
                for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); i++)
                {
                    std::cout << pages[i];

                    if (i != (sizeof(pages) / sizeof(pages[0]) - 1))
                    {
                        std::cout << ", ";
                    }
                } 
                std::cout<< "], Faults: " << fault << std::endl;
                pageQueue.push(pages[i]);
            }
        }
        else {
            if (pageSet.find(pages[i]) == pageSet.end()) {
                int val = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(val);
                pageSet.insert(pages[i]);
                pageQueue.push(pages[i]);

                // if found, increment the fault and step counter
                fault++;
                step++;
                std::cout << "Step " << step << ": Page fault(" << fault << ") - Page Table: {";
                for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); i++)
                {
                    std::cout << pages[i];

                    if (i != (sizeof(pages) / sizeof(pages[0]) - 1))
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << "}, Frames: [";
                for (int i = 0; i < sizeof(pages) / sizeof(pages[0]); i++)
                {
                    std::cout << pages[i];

                    if (i != (sizeof(pages) / sizeof(pages[0]) - 1))
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << "], Faults: " << fault << std::endl;
            }
        }
    }

    cout << "Total Page Faults: " << fault << endl;
}

int main() {
    // memory's capacity to hold pages
    int size = 3;

    std::vector<int> page_reference_string = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };

    // creating a list to store the current pages in memory
    std::vector<int> pages;

    // page faults
    int faults = 0;

    // page hits
    int hits = 0;

    //keeps track of steps
    int step = 0;

    std::cout << "For LRU Algroithm:" << std::endl;
    // iterating the reference string
    findLRU(page_reference_string, size, pages, hits, faults, step);

    std::cout << "For Optimal Algorithm:" << endl;
    int page[] = { 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5 };
    int pageNumber = sizeof(page) / sizeof(page[0]);
    findOPT(page, pageNumber, size, step, faults);

    std::cout << "For Optimal Algorithm:" << endl;
    queue<int> pageQueue;
    unordered_set<int> pageSet;
    findFIFO(page, size, pageNumber, pageQueue, pageSet, faults, step);
    return 0;
}
