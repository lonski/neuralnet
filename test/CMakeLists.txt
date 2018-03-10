set(SOURCE_FILES
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTESTING=1")
add_executable(neuralnet_test ${SOURCE_FILES})
target_link_libraries(neuralnet_test neuralnet_core)