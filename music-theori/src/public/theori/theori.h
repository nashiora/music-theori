#ifndef THEORI_THEORI_H
#define THEORI_THEORI_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "theori/export.h"

#if defined(_WIN32)
# define THEORI_FUNC
#elif defined(__GNUC__)
# define THEORI_FUNC
#else
# define THEORI_FUNC
#endif

typedef void* theori_platform_shared_library_handle;
typedef void* theori_platform_entity_address;

typedef int theori_plugin_id;
typedef struct theori_plugin theori_plugin;

typedef void* theori_plugin_handle;
typedef void (*theori_plugin_initialize_function)(void);

struct theori_plugin
{
    theori_plugin_id id;
    theori_plugin_handle handle;
    theori_plugin_initialize_function initialize;
};

struct theori_state
{
    theori_plugin** plugins;
    size_t nPlugins;
};

THEORI_EXPORT void THEORI_FUNC
theori_log(const char* format, ...);

/// @brief Platform wrapper for loading shared libraries from a file name.
/// @param fileName The name of the shared library file to load.
/// @return An opaque handle to the loaded shared library.
THEORI_EXPORT theori_platform_shared_library_handle THEORI_FUNC
theori_platform_load_shared_library_from_file(const char* fileName);

/// @brief Gets the address of an exported function (or variable) from the specified shared library.
/// @param sharedLibrary The shared library instance handle that contains the function or variable.
/// @param entityName The name of the function or variable to get.
/// @return The address of the function or variable if it could be found, NULL otherwise.
THEORI_EXPORT theori_platform_entity_address THEORI_FUNC
theori_platform_get_entity_address(theori_platform_shared_library_handle sharedLibrary, const char* entityName);

/// @brief Unloads the specified shared library.
/// @param sharedLibrary The shared library to unload.
THEORI_EXPORT void THEORI_FUNC
theori_platform_unload_shared_library(theori_platform_shared_library_handle sharedLibrary);

/// @brief Loads a :theori plugin library from the given dynamic library file.
/// @param fileName The name of the plugin file to load. This should be a dynamic library.
/// @return Data associated with the loaded plugin. Call `bool theori_plugin_is_loaded(theori_plugin*)` to verify loading was successful.
THEORI_EXPORT theori_plugin* THEORI_FUNC
theori_plugin_load_from_file(const char* fileName);

/// @brief Returns true if the plugin was loaded successfully and contains valid function addresses, false otherwise.
/// @param plugin The plugin to check the status of.
/// @return True if the plugin was loaded successfully and contains valid function addresses, false otherwise.
THEORI_EXPORT bool THEORI_FUNC
theori_plugin_is_loaded(theori_plugin* plugin);

/// @brief Unload a plugin.
/// @param plugin The plugin to unload.
THEORI_EXPORT void THEORI_FUNC
theori_plugin_unload(theori_plugin* plugin);

#endif // THEORI_THEORI_H
