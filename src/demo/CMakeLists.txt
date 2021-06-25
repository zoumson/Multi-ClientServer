function (make_exe name Custom_LIBS)

    #Bring the sources
    file(GLOB SOURCES_DEMO ${PROJECT_SOURCE_DIR}/src/demo/${name}/*.cpp)

    #Build the executable
    add_executable(${name} ${SOURCES_DEMO})

    #Link the libraries 
    #target_link_libraries(${name} ${Custom_LIBS} Threads::Threads Boost::program_options Boost::log Boost::log_setup)
    target_link_libraries(${name} ${Custom_LIBS} ${Boost_LIBRARIES})

endfunction()


make_exe(demoServer myServer )
make_exe(demoClient myClient )

