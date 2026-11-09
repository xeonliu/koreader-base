if(PSP)
    # PSP: no LibreSSL. pspdev ships wolfSSL (built with its OpenSSL compatibility layer): expose its headers as
    # <openssl/...> and its library as libssl/libcrypto. The OpenSSL function names that KOReader's FFI uses are
    # aliased to wolfSSL_* at link time (see utils/gen-psp-symtab.py --alias-prefix).
    # pkg-config files, so that projects using pkg_check_modules(openssl) find the stand-in.
    foreach(PC openssl libssl libcrypto)
        file(WRITE ${STAGING_DIR}/lib/pkgconfig/${PC}.pc
"prefix=${STAGING_DIR}
libdir=${STAGING_DIR}/lib
includedir=${STAGING_DIR}/include

Name: ${PC}
Description: wolfSSL (OpenSSL compatibility layer) standing in for LibreSSL on the PSP
Version: 3.0.0
Libs: -L${STAGING_DIR}/lib -lssl -lcrypto
Cflags: -I${STAGING_DIR}/include -include wolfssl/options.h
")
    endforeach()
    list(APPEND INSTALL_CMD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${STAGING_DIR}/include ${STAGING_DIR}/lib
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PSPDEV}/psp/include/wolfssl/openssl ${STAGING_DIR}/include/openssl
        COMMAND ${CMAKE_COMMAND} -E copy ${PSPDEV}/psp/lib/libwolfssl.a ${STAGING_DIR}/lib/libssl.a
        COMMAND ${CMAKE_COMMAND} -E copy ${PSPDEV}/psp/lib/libwolfssl.a ${STAGING_DIR}/lib/libcrypto.a
    )
    external_project(
        BUILD_COMMAND ${CMAKE_COMMAND} -E true
        INSTALL_COMMAND ${INSTALL_CMD}
    )
    return()
endif()

list(APPEND PATCH_FILES cmake_tweaks.patch)
if(ANDROID)
    list(APPEND PATCH_FILES android.patch)
endif()

list(APPEND CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DBUILD_SHARED_LIBS=$<NOT:$<BOOL:${MONOLIBTIC}>>
    # Project options.
    -DLIBRESSL_APPS=OFF
    -DLIBRESSL_TESTS=OFF
    -DENABLE_ASM=${WANT_SIMD}
)
if(GLIBC_VERSION_MAX AND GLIBC_VERSION_MAX VERSION_LESS "2.8")
    # Avoid pulling-in `__asprintf_chk@GLIBC_2.8` and `__vasprintf_chk@GLIBC_2.8`.
    list(APPEND CMAKE_ARGS -DHAVE_ASPRINTF=FALSE)
endif()

list(APPEND BUILD_CMD COMMAND ninja)

list(APPEND INSTALL_CMD COMMAND ${CMAKE_COMMAND} --install .)

if(NOT MONOLIBTIC)
    append_shared_lib_install_commands(INSTALL_CMD crypto VERSION 57)
    append_shared_lib_install_commands(INSTALL_CMD ssl VERSION 60)
endif()

external_project(
    DOWNLOAD URL ed2f4274ed8f2733ab257f0fe97aedaf
    https://github.com/libressl/portable/releases/download/v4.4.0/libressl-4.4.0.tar.gz
    https://cloudflare.cdn.openbsd.org/pub/OpenBSD/LibreSSL/libressl-4.4.0.tar.gz
    https://cdn.openbsd.org/pub/OpenBSD/LibreSSL/libressl-4.4.0.tar.gz
    PATCH_FILES ${PATCH_FILES}
    CMAKE_ARGS ${CMAKE_ARGS}
    BUILD_COMMAND ${BUILD_CMD}
    INSTALL_COMMAND ${INSTALL_CMD}
)
