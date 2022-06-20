#include <Mingine.h>

class Editor : public Mingine::Application {
public:
	Editor() {

	}

	~Editor() {

	}
};

Mingine::Application* Mingine::CreateApplication() {
	return new Editor();
}
