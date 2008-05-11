
#include <TestFailureMatcher.h>
#include <Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////////
TestFailureMatcher::TestFailureMatcher(const std::string& m, const std::string& s)
	: msg(m), str(s)
{}

//////////////////////////////////////////////////////////////////////
bool TestFailureMatcher::matches(const Invocation& inv) const
{
    return true;
}

//////////////////////////////////////////////////////////////////////
void TestFailureMatcher::increaseInvoked(const Invocation& inv) 
{
    MOCKCPP_FAIL(msg);
}

//////////////////////////////////////////////////////////////////////
std::string TestFailureMatcher::toString(void) const
{
    return str;
}

//////////////////////////////////////////////////////////////////////
void TestFailureMatcher::verify(void)
{
}

MOCKCPP_NS_END


