#include "ordinary_statistics.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#define ARR_FOR_TEST_SIZE 20

void generate_rand_array(std::vector<int>& v) {
    v.clear();
    std::srand(std::time(nullptr));
    for (int i = 0; i != ARR_FOR_TEST_SIZE; ++i) {
        v.push_back(std::rand() % 1000);
    }
}

void print_vector(std::vector<int> v) {
    for (int i = 0; i != v.size(); ++i) {
        if (i == 0)
            std::cout << v[i];
        else
            std::cout << ' ' << v[i];
    }
}

int main() {
    std::vector<int> nums;
    generate_rand_array(nums);
    RBTree_with_statistics obj(nums);
    std::cout << "random sequence:\n";
    print_vector(nums);
    std::cout << "\nsorted sequence:\n";
    std::sort(nums.begin(), nums.end());
    print_vector(nums);
    std::cout << "\noutput of tree vertices in ascending order:\n";
    obj.print();
    for (int j = 0; j != 10; ++j) {
        double alpha = 1;
        while (std::ceil(alpha * nums.size()) == nums.size())
            alpha = static_cast<double>(std::rand() % 101) / 100.;
        std::cout << "\nalpha is " << alpha << std::endl;
        std::cout << "real result is "
                  << nums[std::ceil(alpha * nums.size())]
                  << "; my result is "
                  << obj[alpha]
                  << std::endl;
    }
}
