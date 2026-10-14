cmake_minimum_required(VERSION 3.14)
project(DroneMeshSimulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# For thread sanitizer in debug mode, or we can just append it:
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
# The prompt says: "note in the README that ThreadSanitizer is recommended for this concurrency-heavy pass."

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

add_library(simulator_lib
    src/domain/Coordinate.cpp
    src/domain/Dispatcher.cpp
    src/domain/Drone.cpp
    src/domain/Mission.cpp
    src/domain/PriorityMission.cpp
    src/domain/QuadCopter.cpp
    src/concurrency/ThreadPool.cpp
    src/engine/EventScheduler.cpp
    src/engine/Simulation.cpp
    src/events/FaultEvent.cpp
    src/events/DispatchEvent.cpp
)
target_include_directories(simulator_lib PUBLIC include)
target_link_libraries(simulator_lib PRIVATE Threads::Threads)

enable_testing()

add_executable(test_event_queue tests/test_event_queue.cpp)
target_link_libraries(test_event_queue PRIVATE simulator_lib gtest_main Threads::Threads)
add_test(NAME test_event_queue COMMAND test_event_queue)

add_executable(test_thread_pool tests/test_thread_pool.cpp)
target_link_libraries(test_thread_pool PRIVATE simulator_lib gtest_main Threads::Threads)
add_test(NAME test_thread_pool COMMAND test_thread_pool)

add_executable(test_dispatcher tests/test_dispatcher.cpp)
target_link_libraries(test_dispatcher PRIVATE simulator_lib gtest_main Threads::Threads)
add_test(NAME test_dispatcher COMMAND test_dispatcher)
