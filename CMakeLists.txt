cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_STANDARD 17)

#Set the executable name
set(EXE_SERVER server)

#Set the executable name
set(EXE_CLIENT client)

project (socketTime)

#Bring the custom libraries
link_directories( lib )


#Bring the headers
include_directories(include)

#Bring the sources
file(GLOB SOURCES_SERVER "src/server/*.cpp")
file(GLOB SOURCES_CLIENT "src/client/*.cpp")

#Add opencv cmake .config path
#set (OpenCV_DIR opt/opencv/release)

SET(Boost_USE_STATIC_LIBS ON)
set(CMAKE_USE_PTHREADS_INIT true)
set(CMAKE_USE_PTHREADS_INIT ON)

find_package(Threads REQUIRED )
find_package(Boost COMPONENTS program_options log log_setup REQUIRED)
find_package(Threads)


#Build the executable
add_executable(${EXE_SERVER} ${SOURCES_SERVER})
add_executable(${EXE_CLIENT} ${SOURCES_CLIENT})

#Link the libraries 
target_link_libraries(${EXE_SERVER} Threads::Threads Boost::program_options Boost::log Boost::log_setup)
target_link_libraries(${EXE_CLIENT} Threads::Threads Boost::program_options Boost::log Boost::log_setup)


