project(quickjs LANGUAGES C)


file(STRINGS VERSION version)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(quickjs_src quickjs.c libunicode.c libregexp.c cutils.c quickjs-libc.c)
set(quickjs_def CONFIG_VERSION="${version}" _GNU_SOURCE)

option(QUICKJS_BIGNUM "Compile BigNum support" ON)

if(QUICKJS_BIGNUM)
  list(APPEND quickjs_src libbf.c)
  list(APPEND quickjs_def CONFIG_BIGNUM)
endif()

add_library(quickjs ${quickjs_src})
target_compile_definitions(quickjs PRIVATE ${quickjs_def} )


if(UNIX)
  target_link_libraries(quickjs ${CMAKE_DL_LIBS} m )
endif()
