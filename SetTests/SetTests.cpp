#include "pch.h"
#include "CppUnitTest.h"
#include "..\SetLib\Set.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SetTests
{

	TEST_CLASS(ConstructorsTests)
	{
	public:
		TEST_METHOD(TestDefault—onstructor)
		{
			Set<int> A;
			Set<double> B;
			Set<char> C;
			Assert::AreEqual(0, A.get_size());
			Assert::AreEqual(0, B.get_size());
			Assert::AreEqual(0, C.get_size());
		}
		TEST_METHOD(TestOneElementConstructor)
		{
			Set<int> A(100);
			Set<double> B(2.718);
			Set<char> C('A');
			Assert::AreEqual(1, A.get_size());
			Assert::IsTrue(A.contain(100));
			Assert::AreEqual(1, B.get_size());
			Assert::IsTrue(B.contain(2.718));
			Assert::AreEqual(1, C.get_size());
			Assert::IsTrue(C.contain('A'));
		}
		TEST_METHOD(TestArrayConstructor)
		{
			int a[] = { 5, 2, 2, 2, 5 };
			int b[] = { 1,2,3,4,5,4,3,2,1};
			Set<int> A(a, 5);
			Set<int> B(b, 9);
			Assert::AreEqual(2, A.get_size());
			Assert::IsTrue(A.contain(2));
			Assert::IsTrue(A.contain(5));
			Assert::AreEqual(5, B.get_size());
			Assert::IsTrue(B.contain(5));
		}
		TEST_METHOD(TestCopyConstructor)
		{
			int a[] = { 1, 2, 3, 4, 5 };
			Set<int> A(a, 5);
			Set<int> B(A);
			Assert::IsTrue(A == B);
		}
	};
	TEST_CLASS(AddRemoveTests)
	{
		TEST_METHOD(TestAddOneElement)
		{
			Set<int> A;
			A.add(1);
			Assert::IsTrue(A.contain(1));
			A.add(2);
			Assert::IsTrue(A.contain(2));
			A.add(2);
			Assert::AreEqual(2, A.get_size());
		}
		TEST_METHOD(TestAddArray)
		{
			int a[] = {1,2,3,4,5 };
			Set<int> A;
			A.add(a, 5);
			Assert::AreEqual(5, A.get_size());
			std::string hw[] = { "Hello","World","!" };
			Set<std::string> HW(hw, 3);
			Assert::AreEqual(3, HW.get_size());
			Assert::IsTrue(HW.contain("World"));
			Assert::IsTrue(HW.contain("!"));
		}
		TEST_METHOD(TestRemoveOneElement)
		{
			int a[] = { 1,2,3,4,5 };
			Set<int> A;
			A.add(a, 5);
			A.remove(5);
			Assert::AreEqual(4, A.get_size());
			Assert::IsFalse(A.contain(5));
			std::string hw[] = { "Hello","World","!" };
			Set<std::string> HW(hw, 3);
			HW.remove("World");
			Assert::AreEqual(2, HW.get_size());
			Assert::IsFalse(HW.contain("World"));
			Assert::ExpectException<std::runtime_error>([&HW] { HW.remove("World"); });
		}
		TEST_METHOD(TestRemoveAll)
		{
			int a[] = { 1,2,3,4,5 };
			Set<int> A;
			A.add(a, 5);
			A.remove_all();
			Assert::AreEqual(0, A.get_size());
			Assert::IsFalse(A.contain(3));
			std::string hw[] = { "Hello","World","!" };
			Set<std::string> HW(hw, 3);
			HW.remove_all();
			Assert::AreEqual(0, HW.get_size());
			Assert::IsFalse(HW.contain("!"));
		}
	};
	TEST_CLASS(OperationsTests)
	{
		TEST_METHOD(TestSetUnion)
		{
			Set<int> A;
			int a[] = { 1,2,3,4 };
			A.add(a, 4);
			Set<int> B;
			int b[] = { 5,6,3,4 };
			B.add(b, 4);
			Set<int> C = A.set_union(B);
			int d[] = {1,2,3,4,3,4,5,6};
			Set<int> D(d, 8);
			Assert::AreEqual(6, C.get_size());
			Assert::IsTrue(C == D);
		}
		TEST_METHOD(TestIntersection)
		{
			Set<int> A;
			int a[] = { 1,2,3,4};
			A.add(a, 4);
			Set<int> B;
			int b[] = { 5,6,3,4 };
			B.add(b, 4);
			Set<int> C = A.intersect(B);
			int d[] = { 3,4 };
			Set<int> D(d, 2);
			Assert::AreEqual(2, C.get_size());
			Assert::IsTrue(C == D);
		}
		TEST_METHOD(TestDifference)
		{
			Set<int> A;
			int a[] = { 1,2,3,4 };
			A.add(a, 4);
			Set<int> B;
			int b[] = { 5,6,3,4 };
			B.add(b, 4);
			Set<int> C = A.differ(B);
			int d[] = { 1,2 };
			Set<int> D(d, 2);
			Assert::AreEqual(2,C.get_size());
			Assert::IsTrue(C == D);
		}
		TEST_METHOD(TestSymDifference)
		{
			Set<int> A;
			int a[] = { 1,2,3,4 };
			A.add(a, 4);
			Set<int> B;
			int b[] = { 5,6,3,4 };
			B.add(b, 4);
			Set<int> C = A.sym_diff(B);
			int d[] = { 5,6,1,2 };
			Set<int> D(d, 4);
			Assert::AreEqual(4,C.get_size());
			Assert::IsTrue(C == D);
		}
		TEST_METHOD(TestCartesianProduct)
		{
			Set<int> A;
			int a[] = { 1,2 };
			A.add(a, 2);
			Set<char> B;
			char b[] = "ab";
			B.add(b, 2);
			Set<std::pair<int,char>> C = cartesian_product(A, B);
			std::pair<int, char> d[4] = { {1,'a'},{1,'b'} ,{2,'a'} ,{2,'b'} };
			Set<std::pair<int,char>> D(d, 4);
			Assert::AreEqual(4,C.get_size());
			Assert::IsTrue(C == D);
		}
	};
	TEST_CLASS(GeneralTests)
	{
		TEST_METHOD(TestPrintAll)
		{
			Set<int> A;
			std::ostringstream oss;
			A.print_all(oss);
			Assert::AreEqual(std::string("Empty set\n"), oss.str());
			int a[] = { 4,3,2,1 };
			A.add(a, 4);
			oss.str("");
			A.print_all(oss);
			Assert::AreEqual(std::string("Set: { 1 ; 2 ; 3 ; 4 }, size: 4\n"), oss.str());
		}
		TEST_METHOD(TestAssignmentOperator)
		{
			Set<int> A;
			int a[] = { 1,2,3,4 };
			A.add(a, 4);
			Set<int> B = A;
			Assert::IsTrue(A == B);
			A.remove(1);
			Assert::IsFalse(A == B);
		}
	};
}
