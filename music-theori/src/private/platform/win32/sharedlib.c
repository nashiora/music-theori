#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "theori/theori.h"

theori_platform_shared_library_handle THEORI_FUNC
theori_platform_load_shared_library_from_file(const char* fileName)
{
    HMODULE sharedLibrary = LoadLibraryA(fileName);
    if (sharedLibrary == NULL)
    {
        // GetLastError
        return NULL;
    }

    return (theori_platform_shared_library_handle)sharedLibrary;
}

theori_platform_entity_address THEORI_FUNC
theori_platform_get_entity_address(theori_platform_shared_library_handle sharedLibrary, const char* entityName)
{
    FARPROC entityAddress = GetProcAddress((HMODULE)sharedLibrary, entityName);
    if (entityAddress == NULL)
    {
        // GetLastError
        return NULL;
    }

    return (theori_platform_entity_address)entityAddress;
}

void THEORI_FUNC
theori_platform_unload_shared_library(theori_platform_shared_library_handle sharedLibrary)
{
    FreeLibrary((HMODULE)sharedLibrary);
}
