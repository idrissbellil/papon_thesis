
cmake_minimum_required(VERSION 2.8)

find_package(Boost 1.40.0 QUIET COMPONENTS regex filesystem)
find_package(PCL 1.7.1 REQUIRED HINTS "/home/jpapon/workspace/pcl_jpapon/build")
find_package(VTK REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(${VTK_INCLUDE_DIRS})
include (${VTK_USE_FILE})                   
include_directories(${Boost_INCLUDE_DIRS}) 

add_executable(playback example_playback.cpp CColor.cpp)  
target_link_libraries(playback pcl_common pcl_io pcl_visualization ${Boost_LIBRARIES} ${VTK_LIBRARIES})