
#include <mockcpp/Any.h>
#include <mockcpp/Stub.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/InvocationId.h>
#include <mockcpp/DefaultMatcher.h>
#include <mockcpp/StubsMatcher.h>
#include <mockcpp/ExpectsMatcher.h>
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/InvokedTimesMatcher.h>
#include <mockcpp/InvocationMockerSet.h>
#include <mockcpp/InvokedTimesRecorder.h>
#include <mockcpp/InvocationTimesMatcher.h>
#include <mockcpp/ChainableMockMethodCore.h>
#include <mockcpp/SimpleInvocationRecorder.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////
class ChainableMockMethodCoreImpl
{
public:
    std::string methodName;
    /////////////////////////////////////////////////////
    InvocationMockerSet mockers;
    InvocationMockerSet defaultMockers;
    InvocationMockerNamespace* invocationMockerNamespace;

	 /////////////////////////////////////////////////////
    ChainableMockMethodCoreImpl(const std::string& name, InvocationMockerNamespace* ns)
            : methodName(name), invocationMockerNamespace(ns) {}

    ~ChainableMockMethodCoreImpl();
   
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    std::string tellNoMatchedExpectation(const Invocation& inv);
    std::string toString() const;
    Any invoke(const Invocation& inv, SelfDescribe* &resultProvider);
    void reset();
    void verify();
};

/////////////////////////////////////////////////////////////
std::string ChainableMockMethodCoreImpl::toString() const
{
    return mockers.toString() + defaultMockers.toString();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::verify()
{
    mockers.verify();
}

/////////////////////////////////////////////////////////////
ChainableMockMethodCoreImpl::~ChainableMockMethodCoreImpl()
{
    reset();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::reset()
{
    mockers.reset();
    defaultMockers.reset();
}
 
/////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCoreImpl::
getInvocationMocker(const std::string& id) const
{
    return mockers.getInvocationMocker(id);
}

/////////////////////////////////////////////////////////////
std::string
ChainableMockMethodCoreImpl::
tellNoMatchedExpectation(const Invocation& inv)
{
    return std::string("Unexpected invocation") + "\n" 
       + "Invoked: " + methodName + inv.toString() 
       + ".caller(" + inv.getNameOfCaller() + ")\n" 
       + "Allowed: \n"
       + this->toString();
}

/////////////////////////////////////////////////////////////
Any
ChainableMockMethodCoreImpl::invoke(const Invocation& inv
                                   , SelfDescribe* &resultProvider)
{
    Any result = mockers.invoke(inv, resultProvider);
    if (!result.empty())
    {
      return result;
    }

    result = defaultMockers.invoke(inv, resultProvider);
    if (!result.empty())
    {
      return result;
    }

	 MOCKCPP_FAIL(tellNoMatchedExpectation(inv));
   
	 return getEmptyAny();
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::
ChainableMockMethodCore(const std::string& name, InvocationMockerNamespace* ns)
   : This(new ChainableMockMethodCoreImpl(name, ns))
{
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::~ChainableMockMethodCore()
{
    delete This;
}

//////////////////////////////////////////////////////////
std::string&
ChainableMockMethodCore::getName() const
{
   return This->methodName;
}

//////////////////////////////////////////////////////////
Any
ChainableMockMethodCore::invoke
             ( const std::string& nameOfCaller
             , const RefAny& p1
             , const RefAny& p2
             , const RefAny& p3
             , const RefAny& p4
             , const RefAny& p5
             , const RefAny& p6
             , const RefAny& p7
             , const RefAny& p8
             , const RefAny& p9
             , const RefAny& p10
             , const RefAny& p11
             , const RefAny& p12
             , SelfDescribe* &resultProvider)
{
    Invocation inv(nameOfCaller,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);
    return This->invoke(inv, resultProvider);
}

//////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCore::getInvocationMocker(const std::string& id)
{
    return This->getInvocationMocker(id);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::addInvocationMocker(InvocationMocker* mocker)
{
    This->mockers.addInvocationMocker(mocker);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::addDefaultInvocationMocker(InvocationMocker* mocker)
{
    This->defaultMockers.addInvocationMocker(mocker);
}

//////////////////////////////////////////////////////////
InvocationMockerNamespace* ChainableMockMethodCore::getNamespace() const
{
    return This->invocationMockerNamespace;
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::reset()
{
    This->reset();
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::verify()
{
    This->verify();
}

//////////////////////////////////////////////////////////

MOCKCPP_NS_END

