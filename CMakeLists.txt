cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the CUDA compiler path or name
set(CMAKE_CUDA_COMPILER "/usr/bin/nvcc")
set(CUDA_HOST_COMPILER /usr/bin/g++-10)
project(llama_infer CXX CUDA)
include(cmake/cuda.cmake)
add_definitions(-DARMA_ALLOW_FAKE_GCC)
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} --expt-relaxed-constexpr")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)


find_package(GTest REQUIRED)
find_package(glog REQUIRED)
find_package(Armadillo REQUIRED)

aux_source_directory(lpeng_llama_infer/source/tensor/ DIR_TENSOR)
aux_source_directory(lpeng_llama_infer/source/base/ DIR_BASE)
aux_source_directory(lpeng_llama_infer/source/op/ DIR_OP)
aux_source_directory(lpeng_llama_infer/source/model/ DIR_MODEL)
aux_source_directory(lpeng_llama_infer/source/op/kernels/cpu DIR_KERNEL_CPU)
aux_source_directory(lpeng_llama_infer/source/op/kernels/cuda DIR_KERNEL_CUDA)
aux_source_directory(lpeng_llama_infer/source/op/kernels/ DIR_KERNEL)
aux_source_directory(lpeng_llama_infer/source/sampler DIR_SAMPLE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(llama SHARED ${DIR_TENSOR} ${DIR_BASE} ${DIR_OP} ${DIR_KERNEL} ${DIR_MODEL} ${DIR_KERNEL_CPU} ${DIR_KERNEL_CUDA} ${DIR_KERNEL} ${DIR_SAMPLE})
target_link_libraries(llama sentencepiece glog::glog gtest gtest_main pthread cudart armadillo)
target_link_directories(llama PUBLIC ${CMAKE_CUDA_COMPILER_LIBRARY_ROOT}/lib64)

target_include_directories(llama PUBLIC ${glog_INCLUDE_DIR})
target_include_directories(llama PUBLIC ${PROJECT_SOURCE_DIR}/lpeng_llama_infer/include)
target_include_directories(llama PUBLIC ${Armadillo_INCLUDE_DIR})
target_include_directories(llama PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

set_target_properties(llama PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
add_subdirectory(demo)
