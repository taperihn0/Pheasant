#include "pheasant.h"

class Testbed : public Phs::Application 
{
public:
	Testbed() = default;
	Testbed(int argc, char** argv);
	~Testbed() = default;
};

Testbed::Testbed(int argc, char** argv)
	: Phs::Application(argc, argv)
{}

Phs::Application* Phs::createApplication(int argc, char** argv)
{
	return new Testbed(argc, argv);
}