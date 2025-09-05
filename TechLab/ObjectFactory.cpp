#include "ObjectFactory.h"
#include "Object.h"

FObjectFactory::~FObjectFactory()
{
    ReleaseAllObjects();
}

UObject* FObjectFactory::ConstructObject(UClass* ClassToConstruct)
{
    UObject* NewObject = ClassToConstruct->GetConstructor()();
    if (NewObject)
    {
        NewObject->InternalIndex = GUObjectArray.size();
        GUObjectArray.push_back(NewObject);
    }
    return NewObject;
}

void FObjectFactory::ReleaseObject(UObject* InObject)
{
    if (InObject && InObject->InternalIndex < GUObjectArray.size() && GUObjectArray[InObject->InternalIndex] == InObject)
    {
        size_t LastIndex = GUObjectArray.size() - 1;

        // Swap With Last Index Object
        if (InObject->InternalIndex != LastIndex)
        {
            std::swap(GUObjectArray[InObject->InternalIndex], GUObjectArray[LastIndex]);
            GUObjectArray[InObject->InternalIndex]->InternalIndex = InObject->InternalIndex;
        }

        GUObjectArray.pop_back();
        delete InObject;
    }
}

void FObjectFactory::TickObjects(float DeltaTimes)
{
    for (int i = 0; i < GUObjectArray.size(); ++i)
    {
        UObject* Object = GUObjectArray[i];
        if (Object)
        {
            if (Object->ShouldBeDestroyed())
            {
                ReleaseObject(Object);
                --i;
            }
            else { Object->Tick(DeltaTimes); }
        }
    }
}

void FObjectFactory::ReleaseAllObjects()
{
    for (UObject* Object : GUObjectArray)
    {
        if (Object)
        {
            delete Object;
        }
    }

    GUObjectArray.clear();
}
