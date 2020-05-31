include(FetchContent)

FetchContent_Declare(
    googletest

    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.10.0
)

FetchContent_GetProperties(googletest)

if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

    add_subdirectory(
        ${googletest_SOURCE_DIR}
        ${googletest_BINARY_DIR}
    )

    if (MSVC)
        foreach(trgt_ gtest gtest_main gmock gmock_main)
            target_compile_definitions(
                ${trgt_}

                PRIVATE
                    "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
            )
        endforeach()
    endif()
endif()
