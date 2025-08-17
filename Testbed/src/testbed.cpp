#include "pheasant.h"

class Testbed : public Phs::Application 
{
public:
	Testbed() = default;
	~Testbed() = default;
};

Phs::Application* Phs::createApplication()
{
	return new Testbed;
}