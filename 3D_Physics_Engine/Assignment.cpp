#include <iostream>
#include "VisualDebugger.h"

using namespace std;

int main()
{
	try
	{
		VisualDebugger::Init("Assignment", 800, 800);
	}
	catch (Exception exc)
	{
		cerr << exc.what() << endl;
		return 0;
	}

	VisualDebugger::Start();

	return 0;
}