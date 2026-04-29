#include "pch.h"
#include "CppUnitTest.h"
#include "C:\c++\dzshkacplus3\main.cpp"
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest4)
	{
	public:

        TEST_METHOD(test_bubble)
        {
            vector<int> arr = { 5, 2, 9, 1 };
            vector<int> result = bubble_sort(arr);

            vector<int> expected = { 1, 2, 5, 9 };

            Assert::IsTrue(result == expected);
        }


        TEST_METHOD(test_merge)
        {
            vector<int> arr = { 5, 2, 9, 1 };
            merge_sort(arr);

            vector<int> expected = { 1, 2, 5, 9 };

            Assert::IsTrue(arr == expected);
        }


        TEST_METHOD(test_quick)
        {
            vector<int> arr = { 5, 2, 9, 1 };
            quick_sort(arr, 0, arr.size() - 1);

            vector<int> expected = { 1, 2, 5, 9 };

            Assert::IsTrue(arr == expected);
        }


        TEST_METHOD(test_empty_arr)
        {
            vector<int> arr = {};
            merge_sort(arr);

            vector<int> expected = {};

            Assert::IsTrue(arr == expected);
        }


        TEST_METHOD(test_one_element)
        {
            vector<int> arr = { 10 };
            quick_sort(arr, 0, arr.size() - 1);

            vector<int> expected = { 10 };

            Assert::IsTrue(arr == expected);
        }


        TEST_METHOD(test_identich)
        {
            vector<int> arr = { 3, 3, 3, 3 };
            vector<int> result = bubble_sort(arr);

            vector<int> expected = { 3, 3, 3, 3 };

            Assert::IsTrue(result == expected);
        }
		
	};
}
