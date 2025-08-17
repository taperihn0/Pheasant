#pragma once

extern Phs::Application* Phs::createApplication();

int main() 
{
	Phs::Application* app = Phs::createApplication();
	app->run();
	delete app;
}