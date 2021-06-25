
MACRO(make_lib name)
    #Bring the sources
    FILE(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/lib/${name}/*.cpp)

    #Generate library
    ADD_LIBRARY(${name} SHARED ${SOURCES})
    #ADD_LIBRARY(${name} STATIC ${SOURCES})

    #Add other libraries used to build the main library
    #TARGET_LINK_LIBRARIES(${name} PRIVATE Threads::Threads Boost::log Boost::log_setup)
    TARGET_LINK_LIBRARIES(${name} ${Boost_LIBRARIES})

    #Set an installation path, type "sudo make install" to apply
    INSTALL(TARGETS ${name} DESTINATION /usr/lib)
ENDMACRO()

make_lib(myServer)
make_lib(myClient)



