#pragma once

extern Phs::Application* Phs::createApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	Phs::Application* app = Phs::createApplication(argc, argv);
	app->run();
	delete app;
}