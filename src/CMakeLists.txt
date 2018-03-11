set(SOURCE_FILES
    activation_functions.h
    neural_net.h
    neuron.h
    synapse.h
    layer.h
    neural_net.cpp
    main.cpp
)

add_library(neuralnet_core STATIC ${SOURCE_FILES})
add_executable(neuralnet main.cpp)
target_link_libraries(neuralnet neuralnet_core)
