#pragma once

extern Application* createApplication();

int main() {
	auto app = createApplication();
	app->run();
	delete app;
}