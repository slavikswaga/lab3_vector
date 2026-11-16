cmake_minimum_required(VERSION 3.14)
project(lab3_vector VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(lab3_vector main.cpp)
target_compile_features(lab3_vector PRIVATE cxx_std_20)

enable_testing()

add_executable(vector_tests
    vector_tests.cpp
)
target_link_libraries(vector_tests PRIVATE gtest_main)
target_compile_features(vector_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(vector_tests)

set(CPACK_PACKAGE_NAME "lab3_vector")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_VENDOR "slavik")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "vvk160@tpu.ru")
set(CPACK_GENERATOR "DEB")

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(CPACK_PACKAGE_VERSION "0.1.0.$ENV{GITHUB_RUN_NUMBER}")
else()
    set(CPACK_PACKAGE_VERSION "0.1.0")
endif()

install(TARGETS vector_tests RUNTIME DESTINATION bin)

include(CPack)