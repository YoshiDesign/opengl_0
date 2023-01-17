#pragma once
#include "Test.h"

namespace test {

	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImguiRender() override;
	private:
		float m_ClearColor[4];
	};

}