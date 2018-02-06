project(ZMQ)
find_package(cppzmq)
add_executable(MultiClient MultiClient.cpp)
target_link_libraries(MultiClient PUBLIC ${cppzmq_LIBRARY} pthread)

add_executable(WhatifSendTwice WhatifSendTwice.cpp)
target_link_libraries(WhatifSendTwice PUBLIC ${cppzmq_LIBRARY} pthread)

add_executable(MultiContext MultiContext.cpp)
target_link_libraries(MultiContext PUBLIC ${cppzmq_LIBRARY} pthread)