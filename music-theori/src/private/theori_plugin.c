#include "theori/theori.h"

theori_plugin* THEORI_FUNC
theori_plugin_load_from_file(const char* fileName)
{
    theori_plugin_handle pluginHandle = (theori_plugin_handle)theori_platform_load_shared_library_from_file(fileName);

    theori_plugin* resultPlugin = calloc(1, sizeof(theori_plugin));
    resultPlugin->handle = pluginHandle;

#define GET_FUNCTION(E, T, N) \
    resultPlugin->E = (T)theori_platform_get_entity_address(pluginHandle, N); \
    if (resultPlugin->E == NULL) { \
        theori_log("Failed to lookup function " N " in plugin file %s\n", fileName); \
        return NULL; \
    }

    GET_FUNCTION(initialize, theori_plugin_initialize_function, "theori_plugin_initialize");
#undef GET_FUNCTION

    return resultPlugin;
}

bool THEORI_FUNC
theori_plugin_is_loaded(theori_plugin* plugin)
{
    return plugin != NULL && plugin->handle != NULL;
}

void THEORI_FUNC
theori_plugin_unload(theori_plugin* plugin)
{
    theori_platform_unload_shared_library((theori_platform_shared_library_handle)plugin);
}
