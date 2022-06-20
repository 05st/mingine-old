#pragma once

#include "Application.h"

extern Mingine::Application* Mingine::CreateApplication();

int main() {
	Mingine::Application* a = Mingine::CreateApplication();
	a->Run();
	delete a;
}
