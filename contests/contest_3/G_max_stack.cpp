#include <iostream>
#include <vector>
#include <string>

class Stack {
private:
    std::vector<int> stack; 
    int max; 

public:
    void push(int var){
        if (stack.empty()) {
            stack.push_back(var);
            max = var; 
        } else {
            if (var > max) {
                stack.push_back(2 * var + max);
                max = var;
            } else {
                stack.push_back(var);
            }
        }
    }

    int pop(){
        int var = stack.back();
        stack.pop_back();

        if (var > max) {
            int temp = var;
            var = max;
            max = stack.empty() ? 0 : temp - 2 * var; 
        }

        return var;
    }

    int get_max(){
        return max;
    }
};


int main() {
    Stack max_stack;
    
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "max") {
            std::cout << max_stack.get_max() << std::endl;
        } 
        else if (input == "pop") {
            max_stack.pop();
        } 
        else if (input.substr(0, 5) == "push ") {
            int val = std::stoi(input.substr(5));
            max_stack.push(val);
        } 
        else {
            std::cout << "Error\n";
        }
    }

    return 0;
}

