#include "pch.h"
#include "CppUnitTest.h"
#include "C:\c\дзшка5\дзшка5\дзшка5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest1
{
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(testcravnenie1)
		{
			int arr[] = { 1, 2, 3, 4 };
			int result = cravnenie(arr, 4, 10);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(testcravnenie_all_znach)
		{
			int arr[] = { 15, 20, 25, 30 };
			int result = cravnenie(arr, 4, 10);
			Assert::AreEqual(4, result);
		}
		TEST_METHOD(testcravnenie_emptyarray)
		{
			int* arr = nullptr;
			int result = cravnenie(arr, 0, 5);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(testcravnenie_odinak_znach)
		{
			int arr[] = { 5, 5, 5, 5 };
			int result = cravnenie(arr, 4, 5);
			Assert::AreEqual(0, result); 
		}
		TEST_METHOD(testcravnenie_otr_znach)
		{
			int arr[] = { -10, -5, 0, 5, 10 };
			int result = cravnenie(arr, 5, 0);
			Assert::AreEqual(2, result);
		}
		TEST_METHOD(testcravnenie_otr_cravn)
		{
			int arr[] = { -10, -5, 0, 5, 10 };
			int result = cravnenie(arr, 5, -3);
			Assert::AreEqual(3, result);
		}
		TEST_METHOD(testcravnenie_odin_element)
		{
			int arr[] = { 100 };
			int result = cravnenie(arr, 1, 50);
			Assert::AreEqual(1, result);
		}
		TEST_METHOD(testcravnenie_t_menshe_vseh)
		{
			int arr[] = { 100, 200, 300, 400, 500 };
			int result = cravnenie(arr, 5, -1000);  
			Assert::AreEqual(5, result);
		}
		TEST_METHOD(testcravnenie_t_bolshe_vseh)
		{
			int arr[] = { 1, 2, 3, 4, 5 };
			int result = cravnenie(arr, 5, 1000);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(testcravnenie_negative_size)
		{
			int arr[] = { 1, 2, 3, 4, 5 };
			int result = cravnenie(arr, -3, 2);
			Assert::AreEqual(0, result);
		}
		TEST_METHOD(testcravnenie_nullptr_with_size)
		{
			int* arr = nullptr;
			int result = cravnenie(arr, 5, 10);
			Assert::AreEqual(0, result);
		}


		TEST_METHOD(testmincount_outputB)
		{
			int A[] = { 1, 2, 3 };
			int B[] = { 10, 20, 30 };

			try {
				mincount(A, B, 3, 5);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Функция mincount вызвала исключение");
			}
		}

		TEST_METHOD(testmincount_outputA)
		{
			int A[] = { 10, 20, 30 };
			int B[] = { 1, 2, 3 };

			try {
				mincount(A, B, 3, 5);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Функция mincount вызвала исключение");
			}
		}

		TEST_METHOD(testmincount_oba)
		{
			int A[] = { 10, 20, 30 };
			int B[] = { 15, 25, 35 };

			try {
				mincount(A, B, 3, 5);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Функция mincount вызвала исключение");
			}
		}
		TEST_METHOD(testmincount_empty)
		{
			try {
				mincount(nullptr, nullptr, 0, 5); 
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Программа сломалась на пустых массивах!");
			}
		}

		TEST_METHOD(testmincount_otr_znach)
		{
			int A[] = { -10, -20, -30 };
			int B[] = { -5, 0, 5 };

			try {
				mincount(A, B, 3, -2); 
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Сломалось на отрицательных числах!");
			}
		}

		TEST_METHOD(testmincount_larget)
		{
			int A[] = { 100, 200, 300 };
			int B[] = { 400, 500, 600 };

			try {
				mincount(A, B, 3, 1000);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Сломалось на большом t!");
			}
		}
		TEST_METHOD(testmincount_smallt)
		{
			int A[] = { -100, -50, 0 };
			int B[] = { 1, 2, 3 };

			try {
				mincount(A, B, 3, -1000);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Сломалось на маленьком t!");
			}
		}
		TEST_METHOD(testmincount_all)
		{
			int A[] = { 5, 5, 5, 5, 5 }; 
			int B[] = { 6, 6, 6, 6, 6 };  

			try {
				mincount(A, B, 5, 5);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Сломалось на граничном значении t!");
			}
		}
		TEST_METHOD(testmincount_oneznach)
		{
			int A[] = { 100 };
			int B[] = { 50 };

			try {
				mincount(A, B, 1, 75);
				Assert::IsTrue(true);
			}
			catch (...) {
				Assert::Fail(L"Сломалось на массиве с одним значением");
			}
		}
	};
}
