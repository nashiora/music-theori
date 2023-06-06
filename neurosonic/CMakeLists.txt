cmake_minimum_required(VERSION 3.15)

include(GenerateExportHeader)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

#include(../music-theori)

set(CMAKE_CXX_VISIBILITY_PRESET     hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# -------------------- theori --------------------
set(neurosonic_src
    "./src/private/nsc_plugin.c"
)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

add_library(neurosonic ${neurosonic_src})

set_target_properties(neurosonic PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

option(EXCLUDE_DEPRECATED "Exclude deprecated parts of the library" FALSE)
if(EXCLUDE_DEPRECATED)
    set(NO_BUILD_DEPRECATED DEFINE_NO_DEPRECATED)
endif()

generate_export_header(neurosonic
    BASE_NAME "NSC"
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/nsc/export.h
)

write_basic_package_version_file(
    TheoriConfigVersion.cmake
    VERSION 1.0.0
    COMPATIBILITY SameMajorVersion
)

target_include_directories(neurosonic PUBLIC
    "./src/public"
    ${CMAKE_BINARY_DIR}/include
)

install(TARGETS neurosonic
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT   NSC_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT          NSC_Runtime
            NAMELINK_COMPONENT NSC_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT   NSC_Development
)
# -------------------- theori --------------------

# -------------------- neurosonic-standalone --------------------
add_executable(neurosonic_standalone
    "./src/private/nsc_standalone.c"
)

target_include_directories(neurosonic_standalone PRIVATE
    "./src/public"
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(neurosonic_standalone
    theori
    neurosonic
)
# -------------------- neurosonic-standalone --------------------
