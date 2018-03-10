set(SOURCE_FILES
    main.cpp
    neural_net.cpp
)

add_library(neuralnet_core STATIC ${SOURCE_FILES})
add_executable(neuralnet main.cpp)
target_link_libraries(neuralnet neuralnet_core)
