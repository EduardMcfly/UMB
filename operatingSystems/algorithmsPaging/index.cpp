#include <climits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function to find the index of the maximum value in a vector
int maxValueIndex(vector<int> &v)
{

    int max_val = INT_MIN;
    int max_idx;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] > max_val)
        {
            max_val = v[i];
            max_idx = i;
        }
    }
    return max_idx;
}

// function to find the index of the minimum value in a vector
int minValueIndex(vector<int> &v)
{

    int min_val = INT_MAX;
    int min_idx;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] < min_val)
        {
            min_val = v[i];
            min_idx = i;
        }
    }
    return min_idx;
}

// function to search for a given value in a vector
int search(vector<int> &v, int idx, int value)
{

    for (int i = idx; i < v.size(); i++)
    {
        if (v[i] == value)
        {
            return i;
        }
    }
    return INT_MAX;
}

// function to print the contents of a vector
void print(vector<int> &v)
{

    cout << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

// function to print the contents of the page table
void print(vector<int> &frames, int page)
{

    cout << setfill(' ') << setw(2) << page << " : ";
    for (int i = frames.size() - 1; i >= 0; --i)
    {
        if (frames[i] == INT_MAX)
        {
            cout << "* ";
        }
        else
        {
            cout << frames[i] << " ";
        }
    }
    cout << endl;
}

// function to print the results of a replacement algorithm
void print(int misses, int hits)
{

    cout << endl
         << "Page Faults: " << misses << ", Page Hits: " << hits;
    cout << endl
         << "Miss Ratio: " << ((double)misses / (hits + misses)) * 100 << "%";
    cout << ", Hit Ratio: " << ((double)hits / (hits + misses)) * 100 << "%" << endl
         << endl;
}

// Algorithm: First-In, First_Out
void FIFO(vector<int> &array, int num_frames)
{

    int misses = 0;
    int hits = 0;

    vector<int> frames(num_frames, INT_MAX);

    cout << endl;

    for (int i = 0; i < array.size(); i++)
    {
        int idx = search(frames, 0, array[i]);

        if (idx == INT_MAX)
        {
            frames.erase(frames.begin());
            frames.push_back(array[i]);
            misses++;
        }
        else
        {
            hits++;
        }
        print(frames, array[i]);
    }

    print(misses, hits);
    frames.clear();
}

// Algorithm: Least Recently Used
void LRU(vector<int> &array, int num_frames)
{

    int misses = 0;
    int hits = 0;

    vector<int> frames(num_frames, INT_MAX);

    cout << endl;

    for (int i = 0; i < array.size(); i++)
    {
        int idx = search(frames, 0, array[i]);

        if (idx == INT_MAX)
        {
            frames.erase(frames.begin());
            frames.push_back(array[i]);
            misses++;
        }
        else
        {
            int temp = frames[idx];
            frames.erase(frames.begin() + idx);
            frames.push_back(temp);
            hits++;
        }
        print(frames, array[i]);
    }

    print(misses, hits);
    frames.clear();
}

// Algorithm: Least Frequently Used
void LFU(vector<int> &array, int num_frames)
{

    int misses = 0;
    int hits = 0;

    vector<int> frames(num_frames, INT_MAX);
    vector<int> counts(num_frames, INT_MIN);

    cout << endl;

    for (int i = 0; i < array.size(); i++)
    {
        int idx = search(frames, 0, array[i]);

        if (idx == INT_MAX)
        {
            frames.erase(frames.begin() + minValueIndex(counts));
            counts.erase(counts.begin() + minValueIndex(counts));
            frames.push_back(array[i]);
            counts.push_back(0);
            misses++;
        }
        else
        {
            counts[idx] = counts[idx] + 1;
            hits++;
        }
        print(frames, array[i]);
    }

    print(misses, hits);
    frames.clear();
    counts.clear();
}

// Algorithm: Most Frequently Used
void MFU(vector<int> &array, int num_frames)
{
    int misses = 0;
    int hits = 0;

    vector<int> frames(num_frames, INT_MAX);
    vector<int> counts(num_frames, INT_MAX);

    cout << endl;

    for (int i = 0; i < array.size(); i++)
    {
        int idx = search(frames, 0, array[i]);

        if (idx == INT_MAX)
        {
            frames.erase(frames.begin() + maxValueIndex(counts));
            counts.erase(counts.begin() + maxValueIndex(counts));
            frames.push_back(array[i]);
            counts.push_back(0);
            misses++;
        }
        else
        {
            counts[idx] = counts[idx] + 1;
            hits++;
        }

        print(frames, array[i]);
    }

    print(misses, hits);
    frames.clear();
    counts.clear();
}

int main(void)
{

    int num_frames = 5;
    int option;
    int length = 13;
    int temp;

    vector<int> array;

    srand(time(NULL));
    array.push_back(6);
    array.push_back(0);
    array.push_back(2);
    array.push_back(1);
    array.push_back(0);
    array.push_back(4);
    array.push_back(3);
    array.push_back(0);
    array.push_back(2);
    array.push_back(3);
    array.push_back(0);
    array.push_back(3);
    array.push_back(2);

    cout << endl
         << "A random memory trace has been generated." << endl;
    print(array);

    cout << endl;
    cout << "First-In First-Out" << endl;
    FIFO(array, num_frames);

    cout << "Least Recently Used" << endl;
    LRU(array, num_frames);

    cout << "Least Frequently Used" << endl;
    LFU(array, num_frames);

    cout << "Most Frequently Used" << endl;
    MFU(array, num_frames);
    array.clear();
}