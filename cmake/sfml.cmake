include(FetchContent)

set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

if (WIN32)
    set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
else()
    set(SFML_STATIC_LIBRARIES OFF CACHE BOOL "" FORCE)
endif()

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)
