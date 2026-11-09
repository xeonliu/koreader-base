if(NOT MONOLIBTIC)
    set(CMAKE_PATCH_FILE ${CMAKE_BINARY_DIR}/k2pdfopt_exports.cmake)
    target_exports(k2pdfopt FILELIST_VAR CDECLS_FILES WRITE_TO_FILE ${CMAKE_PATCH_FILE} CDECLS koptcontext_cdecl)
    list(APPEND PATCH_CMD COMMAND ${ISED} "\$p" -e "\$s|.*|include(${CMAKE_PATCH_FILE})|" lib/CMakeLists.txt)
endif()

list(APPEND CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DBUILD_SHARED_LIBS=$<NOT:$<BOOL:${MONOLIBTIC}>>
    # Project options.
    -DANDROID=${ANDROID}
    -DLEPTONICA_PATCH=FALSE
)

if(PSP)
    # newlib already declares strlwr()/strupr() (differently typed): rename willuslib's (see the compat header).
    set(K2_COMPAT "-include ${BASE_DIR}/toolchain/psp/include/psp_k2pdfopt_compat.h")
    list(APPEND CMAKE_ARGS "-DCMAKE_C_FLAGS=${CFLAGS} ${K2_COMPAT}")
    # The C++ part (tesscapi.cpp) calls Tesseract's C++ API: it must see the same int32_t as Tesseract itself (name mangling).
    list(APPEND CMAKE_ARGS "-DCMAKE_CXX_FLAGS=${CXXFLAGS} ${K2_COMPAT} -U__INT32_TYPE__ -D__INT32_TYPE__=int -U__UINT32_TYPE__ -D__UINT32_TYPE__=unsigned")
endif()

list(APPEND BUILD_CMD COMMAND ninja)

list(APPEND INSTALL_CMD COMMAND ${CMAKE_COMMAND} --install .)

if(NOT MONOLIBTIC)
    append_shared_lib_install_commands(INSTALL_CMD k2pdfopt VERSION 2)
endif()

external_project(
    DOWNLOAD GIT 64aa9ccfcd55921c596458cb8a7197339d5f32c3
    https://github.com/koreader/libk2pdfopt.git
    PATCH_COMMAND ${PATCH_CMD}
    CMAKE_ARGS ${CMAKE_ARGS}
    SOURCE_SUBDIR lib
    BUILD_COMMAND ${BUILD_CMD}
    BUILD_DEPENDS ${CDECLS_FILES}
    INSTALL_COMMAND ${INSTALL_CMD}
)
