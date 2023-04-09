#include <iostream>
#include <list>
#include <map>
// Firstly create a file in nano editor with the name memory_manager.cpp
//  nano memory_manager.cpp
// Command to create an executable
// g++ memory_manager.cpp -o memory_manager
// Run the command to create an executable of name memory_manger
// To run the executable type this command
//  ./memory_manager

// Jacob Sober memory management

using namespace std;

class MemoryManager
{
    int memorySize;
    int allocatedMemory;
    int numProcesses;
    int numWastedBlocks;
    int numFragments;
    list<int> freeList;
    map<int, int> processMap;

public:
    MemoryManager(int memorySize)
    {
        this->memorySize = memorySize;
        allocatedMemory = 0;
        numProcesses = 0;
        numWastedBlocks = 0;
        numFragments = 0;
        freeList.push_back(0);
    }

    bool allocateMemory(int processId, int processSize)
    {
        
        if (processSize > (memorySize - allocatedMemory))
        {
            ++numWastedBlocks;
            return false;
        }

        list<int>::iterator it = freeList.begin();
        while (it != freeList.end())
        {
            int startIndex = *it;
            int endIndex = startIndex + processSize - 1;
            if (endIndex >= memorySize)
            {
                break;
                // return false;
            }
            bool isFree = true;
            // for (int i = startIndex; i <= endIndex; i++)
            // {
            //     if (processMap.count(i) > 0)
            //     {
            //         isFree = false;
            //         break;
            //     }
            // }
            if (isFree)
            {
                it = freeList.erase(it);
                for (int i = startIndex; i <= endIndex; i++)
                {
                    processMap[i] = processId;
                }
                allocatedMemory += processSize;
                numProcesses++;
                // cout<<"Allocated memory function initiated"<<endl;
                return true;
            }
            else
            {
                ++it;
            }
        }

        
        return false;
    }

    void deallocateMemory(int processId)
    {
        list<int> blocksToFree;
        for (auto it = processMap.begin(); it != processMap.end(); ++it)
        {
            if (it->second == processId)
            {
                blocksToFree.push_back(it->first);
            }
        }
        for (auto block : blocksToFree)
        {
            processMap.erase(block);
            freeList.push_back(block);
        }
        numProcesses--;
        allocatedMemory -= blocksToFree.size();
    }

    void runSimulation(int numTimeUnits)
    {
        for (int i = 0; i < numTimeUnits; i++)
        {
            numFragments = freeList.size();
            cout << "Time Unit " << i << ":" << endl;
            cout << "No. of Processes: " << numProcesses << endl;
            cout << "No. of Wasted Blocks: " << numWastedBlocks << endl;
            cout << "No. of Fragments: " << numFragments << endl;
            cout << "Allocated Memory: " << allocatedMemory << "/" << memorySize << endl;
        }
    }
};

int main()
{
    MemoryManager memoryManager(100);
    memoryManager.allocateMemory(1, 20);
    memoryManager.runSimulation(1);
    memoryManager.deallocateMemory(1);
    memoryManager.runSimulation(1);
    memoryManager.allocateMemory(2, 30);
    memoryManager.runSimulation(1);
    memoryManager.deallocateMemory(2);
    memoryManager.runSimulation(1);
    memoryManager.allocateMemory(3, 10);
    memoryManager.runSimulation(1);
    memoryManager.allocateMemory(4, 20);
    memoryManager.runSimulation(1);
    memoryManager.allocateMemory(5, 60);
    memoryManager.runSimulation(1);
    // memoryManager.allocateMemory(6, 40);
    // memoryManager.runSimulation(1);
    return 0;
}
