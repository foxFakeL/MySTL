include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

aux_source_directory(. DIR_SRCS)

# set(LIB_NAME "lib${PROJECT_NAME}")

add_library(SRC ${DIR_SRCS})