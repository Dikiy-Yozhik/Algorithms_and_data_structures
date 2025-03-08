#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Heap {
private:
    std::vector<int> heap;

    void heapify(int i) {
        int l_child = 2 * i + 1;
        int r_child = 2 * i + 2;
        int root = i;

        if (l_child < heap.size() && heap[l_child] > heap[root]) {
            root = l_child;
        }
        if (r_child < heap.size() && heap[r_child] > heap[root]) {
            root = r_child;
        }

        if (root != i) {
            std::swap(heap[i], heap[root]);
            heapify(root);
        }
    }

public:
    void add_node(int var) {
        heap.push_back(var);
        int i = heap.size() - 1;

        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            std::swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }

    int get_max() {
        if (heap.empty()) {
            return -1; 
        }

        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapify(0);
        }
        
        return max; 
    }
};


int main() {
    Heap priority_queue;

    int n;
    std::cin >> n;
  
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "ExtractMax") {
            int max = priority_queue.get_max();
            if (max != -1) { 
                std::cout << max << std::endl;
            }
        } 
        else if (input.find("Insert") == 0) { 
            std::istringstream iss(input);
            std::string operation;
            int value;

            iss >> operation >> value;
            priority_queue.add_node(value);
        } 
        else {
            return 1;
        }
    }
    return 0;
}