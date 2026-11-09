list(APPEND PATCH_FILES fix_visibility_check.patch)

list(APPEND CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    # Project options.
    -DZLIB_BUILD_TESTING=FALSE
)
if(MONOLIBTIC)
    list(APPEND CMAKE_ARGS -DBUILD_SHARED_LIBS=FALSE)
    if(PSP)
        # No shared objects on PSP: only build the static library, or both targets output libz.a.
        list(APPEND CMAKE_ARGS -DZLIB_BUILD_SHARED=OFF -DZLIB_BUILD_STATIC=ON)
    endif()
endif()

list(APPEND BUILD_CMD COMMAND ninja)

list(APPEND INSTALL_CMD COMMAND ${CMAKE_COMMAND} --install .)

if(NOT MONOLIBTIC)
    append_shared_lib_install_commands(INSTALL_CMD z VERSION 1)
endif()

external_project(
    DOWNLOAD URL ae8baba210d81247293bca36babcb429
    https://github.com/madler/zlib/releases/download/v1.4/zlib-1.4.tar.xz
    PATCH_FILES ${PATCH_FILES}
    CMAKE_ARGS ${CMAKE_ARGS}
    BUILD_COMMAND ${BUILD_CMD}
    INSTALL_COMMAND ${INSTALL_CMD}
)
