list(APPEND PATCH_FILES
    # Make sure turbo use our SSL library.
    fix_ssl_load.patch
    # Make sure turbo find its libtffi_wrap library.
    fix_tffi_wrap_load.patch
    # Drop unused code.
    no_web_api.patch
    no_websocket_api.patch
    no_httpserver_api.patch
    no_tcpserver_api.patch
    no_signal_handler_api.patch
    no_linux_only_apis.patch
    # Only declare the cdefs we need and use our `ffi.posix_h` module.
    fix_cdefs.patch
    # No child processes on some platforms (the PSP): don't require io.popen for platform detection.
    no_popen_platform.patch
)

# Drop unused stuff, including the 7 years-old copy of a CA bundle that turbo doesn't actually use..
list(APPEND PATCH_CMD COMMAND rm
    turbo/ca-certificates.crt
    turbo/crypto_linux.lua
    turbo/epoll_ffi.lua
    turbo/fs.lua
    turbo/httpserver.lua
    turbo/inotify.lua
    turbo/mustache.lua
    turbo/signal.lua
    turbo/syscall.lua
    turbo/tcpserver.lua
    turbo/thread.lua
    turbo/web.lua
    turbo/websocket.lua
)
# Some of the LUA files are executables for no good reason.
list(APPEND PATCH_CMD COMMAND sh -c "chmod a-x turbo/*.lua")

if(PSP)
    # TLS comes from wolfSSL's OpenSSL compatibility layer (headers/libs installed in staging by the libressl stand-in).
    list(APPEND CMAKE_ARGS
        -DOPENSSL_ROOT_DIR=${STAGING_DIR}
        -DOPENSSL_INCLUDE_DIR=${STAGING_DIR}/include
        -DOPENSSL_SSL_LIBRARY=${STAGING_DIR}/lib/libssl.a
        -DOPENSSL_CRYPTO_LIBRARY=${STAGING_DIR}/lib/libcrypto.a
        "-DCMAKE_C_FLAGS=${CFLAGS} -include wolfssl/options.h -U__INT32_TYPE__ -D__INT32_TYPE__=int -U__UINT32_TYPE__ -D__UINT32_TYPE__=unsigned"
    )
endif()

list(APPEND CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DBUILD_SHARED_LIBS=$<NOT:$<BOOL:${MONOLIBTIC}>>
)

list(APPEND BUILD_CMD COMMAND ninja)

if(MONOLIBTIC)
    append_install_commands(INSTALL_CMD libtffi_wrap.a DESTINATION ${STAGING_DIR}/lib)
else()
    append_binary_install_command(INSTALL_CMD libtffi_wrap${LIB_EXT} DESTINATION libs)
endif()
append_install_commands(INSTALL_CMD ${SOURCE_DIR}/turbo.lua DESTINATION common)
append_tree_install_commands(INSTALL_CMD ${SOURCE_DIR}/turbo common/turbo)

external_project(
    DOWNLOAD GIT v2.1.5
    https://github.com/kernelsauce/turbo
    PATCH_OVERLAY overlay
    PATCH_FILES ${PATCH_FILES}
    PATCH_COMMAND ${PATCH_CMD}
    CMAKE_ARGS ${CMAKE_ARGS}
    BUILD_COMMAND ${BUILD_CMD}
    INSTALL_COMMAND ${INSTALL_CMD}
)
