#include "application.h"
#include "entry.h"

class Testbed : public Application 
{
public:
	Testbed() = default;
	~Testbed() = default;
};

Application* createApplication() {
	return new Testbed;
}