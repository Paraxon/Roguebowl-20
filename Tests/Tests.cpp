#include "CppUnitTest.h"
import Locator;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Locator<int>::set(42);
			Assert::AreEqual(42, Locator<int>::get());
		}
	};
}
