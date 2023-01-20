#include "pch.h"
#include "CppUnitTest.h"
#include "../utils.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PruebasUnitarias
{
	TEST_CLASS(PruebasUnitarias)
	{
	public:
		
		TEST_METHOD(TestUtils)
		{
			Assert::IsFalse(Validaciones::cedula_valida("1726744295"));
			Assert::IsTrue(Validaciones::cedula_valida("1726744293"));
            
			Assert::AreEqual(Validaciones::trim("  abc  ").c_str(), "abc");
		}
	};
}
