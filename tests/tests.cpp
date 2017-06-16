#include "ordinary_statistics.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>


#define BOOST_TEST_MAIN

#define BOOST_TEST_MODULE main_test

#include <boost/test/unit_test.hpp>

void generate_rand_array(std::vector<int>& v, size_t test_size = 20) {
    v.clear();
    std::srand(std::time(nullptr));
    for (int i = 0; i != test_size; ++i) {
        v.push_back(std::rand() % 1000);
    }
}

BOOST_AUTO_TEST_SUITE(RB_tree_test)

    BOOST_AUTO_TEST_CASE(testTreeSize) {
        RBTree_with_statistics tree;
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        BOOST_CHECK_EQUAL(tree.size(), 3);
        tree.insert(3);
        BOOST_CHECK_EQUAL(tree.size(), 4);

    }

    BOOST_AUTO_TEST_CASE(testVecInitSize) {
        std::vector<int> elems = {1, 2, 3};
        RBTree_with_statistics tree(elems);
        BOOST_CHECK_EQUAL(tree.size(), 3);

    }

    BOOST_AUTO_TEST_CASE(testInsertFind) {
        RBTree_with_statistics tree;
        tree.insert(1);
        tree.insert(2);
        tree.insert(3);

        BOOST_CHECK(tree.find(1));
        BOOST_CHECK(tree.find(2));
        BOOST_CHECK(tree.find(3));
        BOOST_CHECK(!tree.find(4));
    }


     BOOST_AUTO_TEST_CASE(testInsertFindVecInit) {
        std::vector<int> elems = {1, 2, 3};
        RBTree_with_statistics tree(elems);

        BOOST_CHECK(tree.find(1));
        BOOST_CHECK(tree.find(2));
        BOOST_CHECK(tree.find(3));
        BOOST_CHECK(!tree.find(4));
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(STATISTICS_TEST)

    BOOST_AUTO_TEST_CASE(statistic_on_deterministic_array) {
        std::vector<int> data_vec = {2, 5, 4, 11, 4, 11, 23, 1};
        
        //    sorted data     1  2  4  4  5  11  11  23
        //    params:         correct result:
        //          k = 0     . 1
        //          k = 0.25  ...... 4      
        //          k = 0.5   ............ 5          
        //          k = 0.86  ....................... 23

        RBTree_with_statistics tree(data_vec);
        BOOST_CHECK_EQUAL(tree[0], 1);
        BOOST_CHECK_EQUAL(tree[0.25] , 4);
        BOOST_CHECK_EQUAL(tree[0.5]  , 5);
        BOOST_CHECK_EQUAL(tree[0.86] , 23);
    }

    BOOST_AUTO_TEST_CASE(invalid_k_throw) {
        std::vector<int> data_vec = {2, 5, 4, 11, 4, 11, 23, 1};
        RBTree_with_statistics tree(data_vec);
        BOOST_CHECK_THROW(tree[-1]   , std::invalid_argument);
        BOOST_CHECK_THROW(tree[1]    , std::invalid_argument);
        BOOST_CHECK_THROW(tree[1.2]  , std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(random_array) {
        std::vector<int> nums;
        generate_rand_array(nums);
        RBTree_with_statistics obj(nums);
        std::sort(nums.begin(),
                  nums.end());

        for (int j = 0; j != 10; ++j) {
            double alpha = 1;
            while (std::ceil(alpha * nums.size()) == nums.size())
                alpha = static_cast<double>(std::rand() % 101) / 100.;
            BOOST_CHECK_EQUAL(nums[std::ceil(alpha * nums.size())], obj[alpha]);
        }
    }

BOOST_AUTO_TEST_SUITE_END()

