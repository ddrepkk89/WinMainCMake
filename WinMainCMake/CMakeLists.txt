﻿# CMakeList.txt: WinMainCMake 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 加入各种包
find_package(OpenMP REQUIRED)
# Onnx runtime
set(ONNXRUNTIME_ROOT_DIR "C:/Users/Administrator/source/repos/WinMainCMake/WinMainCMake/packages/onnxruntime-win-x64-gpu-1.19.2")
include_directories(${ONNXRUNTIME_ROOT_DIR}/include)
link_directories(${ONNXRUNTIME_ROOT_DIR}/lib)

# 将源代码添加到此项目的可执行文件。
add_executable (WinMainCMake "WinMainCMake.cpp" "WinMainCMake.h"  "targetver.h" "framework.h")

# 设置win32 接入点
set_target_properties(WinMainCMake PROPERTIES WIN32_EXECUTABLE TRUE)
# 链接包
target_link_libraries(WinMainCMake PRIVATE ${OPENMP_LIBS})
target_link_libraries(WinMainCMake PRIVATE onnxruntime)
set(DLL_SRC ${ONNXRUNTIME_ROOT_DIR}/bin/*.dll)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WinMainCMake PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
