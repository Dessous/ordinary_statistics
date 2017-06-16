set(TESTS_SOURCES
            tests.cpp)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(TEST test_staticstics)
add_executable(${TEST} ${TESTS_SOURCES})
target_link_libraries(${TEST} rb_tree ${Boost_LIBRARIES})

add_test(${TEST} ${TEST})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)