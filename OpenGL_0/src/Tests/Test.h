#pragma once
#include <functional>
#include <vector>

namespace test {

	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}

	private:
	
	};
	

	class TestMenu : public Test
	{
	public:

		TestMenu(Test*& currentTestPointer);
		void OnImguiRender() override;

		// Registered test type as "key/Button Title" : <Test...>
		template <typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}