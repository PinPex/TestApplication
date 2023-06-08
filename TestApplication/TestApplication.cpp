#include <iostream>
#include "Engines.h"
#include "Test.h"
int main()
{
    /* An example of starting test with internal combustion engine */
    Test* test = new TestInternalCombustion();
    test->Start();
}