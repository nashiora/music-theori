#include "dlfcn.h"

#include "theori/theori.h"

theori_platform_shared_library_handle
theori_platform_load_shared_library_from_file(const char* fileName)
{
    void* sharedLibrary = dlopen(fileName, RTLD_NOW);
    if (sharedLibrary == NULL)
    {
        theori_log("An error occured while loading a shared library: %s\n", dlerror());
        return NULL;
    }

    return (theori_platform_shared_library_handle)sharedLibrary;
}

theori_platform_entity_address
theori_platform_get_entity_address(theori_platform_shared_library_handle sharedLibrary, const char* entityName)
{
    void* entityAddress = dlsym((void*)sharedLibrary, entityName);
    if (entityAddress == NULL)
    {
        theori_log("An error occured while getting an entity addression from shared library: %s\n", dlerror());
        return NULL;
    }

    return entityAddress;
}

void THEORI_FUNC
theori_platform_unload_shared_library(theori_platform_shared_library_handle sharedLibrary)
{
    (void)dlclose((void*)sharedLibrary);
}
