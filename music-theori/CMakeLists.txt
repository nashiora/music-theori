cmake_minimum_required(VERSION 3.15)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(CMAKE_CXX_VISIBILITY_PRESET     hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# -------------------- theori --------------------
set(theori_src
    "./src/private/theori_log.c"
    "./src/private/theori_plugin.c"
)

if(WIN32)
    list(APPEND theori_src
        "./src/private/platform/win32/sharedlib.c"
    )
elseif(UNIX)
    list(APPEND theori_src
        "./src/private/platform/linux/sharedlib.c"
    )
endif()

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

add_library(theori ${theori_src})

set_target_properties(theori PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

option(EXCLUDE_DEPRECATED "Exclude deprecated parts of the library" FALSE)
if(EXCLUDE_DEPRECATED)
    set(NO_BUILD_DEPRECATED DEFINE_NO_DEPRECATED)
endif()

generate_export_header(theori
    BASE_NAME "THEORI"
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/theori/export.h
)

write_basic_package_version_file(
    TheoriConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

target_include_directories(theori PUBLIC
    "./src/public"
    ${CMAKE_BINARY_DIR}/include
)

install(TARGETS theori
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   Theori_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT          Theori_Runtime
            NAMELINK_COMPONENT Theori_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   Theori_Development
)
# -------------------- theori --------------------

# -------------------- theori-standalone --------------------
add_executable(theori_standalone
    "./src/private/theori_standalone.c"
)

target_include_directories(theori_standalone PRIVATE
    "./src/public"
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(theori_standalone
    theori
)
# -------------------- theori-standalone --------------------
