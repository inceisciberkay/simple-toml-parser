cmake_minimum_required(VERSION 3.0.0)
project(toml-parser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy;-header-filter=.; -checks='bugprone*,clang-analyzer*,cert*,cppcoreguidelines*,misc*,modernize*,performance*,portability*,readability*,hicpp*,llvm*-llvm-header-guard')
# find_program(IWYU_PATH NAMES include-what-you-use iwyu)
# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

include(CTest)
enable_testing()

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
file(GLOB src_files "${source_dir}/*.cpp")

add_executable(parse ${src_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)