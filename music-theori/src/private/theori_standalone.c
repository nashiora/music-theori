#include <assert.h>
#include <stdio.h>

#include "theori/theori.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Dynamic library file path expected\n");
        return 1;
    }

    theori_plugin* plugin = theori_plugin_load_from_file(argv[1]);
    if (!theori_plugin_is_loaded(plugin))
    {
        printf("Failed to load plugin from library file\n");
        return 1;
    }

    assert(plugin->handle);
    assert(plugin->initialize);

    plugin->initialize();

    printf("Hello, :theori!\n");
    return 0;
}
