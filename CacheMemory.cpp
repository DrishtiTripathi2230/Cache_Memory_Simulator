#include <iostream>
#include <list>
#include <unordered_set>
#include <queue>
#include <string>
using namespace std;

class Cache{
private: 
    int capacity; //FIXED SIZE
    string policy; //LRO or FIFO
    //tracking
    int hits;
    int misses;

    //LRU
    list<int> LruList;
    unordered_set<int> LruSet;

    //FIFO
    queue<int> FifoQueue;
    unordered_set<int> FifoSet;

public:
    Cache(int capacity, string policy){
        this->capacity = capacity;
        this->policy = policy;
        hits = 0;
        misses = 0;
    }    
    
    void access(int address){
        //LRU
        if(policy == "LRU"){
            if(LruSet.find(address) != LruSet.end()){
                //HIT
                hits++;
                LruList.remove(address);
                LruList.push_front(address);
                cout << "HIT";
            }
            else{
                //MISS
                misses++;
                if(LruList.size() == capacity){
                    int leastUsed = LruList.back();
                    LruList.pop_back();
                    LruSet.erase(leastUsed);
                }
                LruList.push_front(address);
                LruSet.insert(address);
                cout << "MISS";
            }
            printCacheState();
            //FIFO
        }else if(policy == "FIFO"){
            //hit
            if(FifoSet.find(address) != FifoSet.end()){
                hits++;
                cout << "HIT";
            }else{
                //misses
                misses++;
                if(FifoQueue.size() == capacity){
                    int oldest = FifoQueue.front();
                    FifoQueue.pop();
                    FifoSet.erase(oldest);
                
                }
                FifoQueue.push(address);
                FifoSet.insert(address);
                cout << "MISS";
            }
            

            printCacheState();
        }

    }
    void printCacheState(){
        cout << " | Cache: [";
        if(policy == "LRU"){
            for(auto it = LruList.begin(); it != LruList.end(); it++){
                cout << *it;
                if(next(it) != LruList.end()) cout << ", ";
            }
        } else if(policy == "FIFO"){
            queue<int> temp = FifoQueue;
            while(!temp.empty()){
                cout << temp.front();
                temp.pop();
                if(!temp.empty()) cout << ", ";
            }
        }
        cout << "]";
    }
    void display(){
        int total = hits + misses;
        cout << "\n--- Cache Statistics ---" << endl;
        cout << "Total Accesses: " << total << endl;
        cout << "Hits: " << hits << endl;
        cout << "Misses: " << misses << endl;
        cout << "Hit Rate: " << (double)hits / total * 100 << "%" << endl;
        cout << "Miss Rate: " << (double)misses / total * 100 << "%" << endl;
    }
    
};
int main(){
    int capacity;
    string policy;

    cout << "Enter cache size: ";
    cin >> capacity;

    cout << "Choose policy (LRU/FIFO): ";
    cin >> policy;

    Cache cache(capacity, policy);

    // sample memory access sequence
    vector<int> accessSequence = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};

    cout << "\nMemory Access Sequence:" << endl;
    for (int address : accessSequence) {
        cout << "Accessing " << address << " -> ";
        cache.access(address);
        cout << "\n";
    }

    cache.display();
    return 0;
}