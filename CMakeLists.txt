cmake_minimum_required(VERSION 3.7)
project(OnlineTetris)

set(CMAKE_CXX_STANDARD 14)



include_directories(Commons)
include_directories(Commons/Room)
include_directories(OnlineTetris)
include_directories(Server/Messenger)
include_directories(Server/Room)
include_directories(Server/Server)

add_executable(OnlineTetris
        Commons/Room/TIGameRoom.h
        Commons/Room/TIRoom.cpp
        Commons/Room/TIRoom.h
        Commons/Room/TIWaitingRoom.h
        Commons/DefineInfo.h
        Commons/ITObjectContainer.h
        Commons/Logger.h
        Commons/Property.h
        Commons/structs.h
        Commons/TAtomic.cpp
        Commons/TAtomic.h
        Commons/TMessage.h
        Commons/TObject.h
        Commons/TObjectContainer.h
        Commons/TObjectContainerFactory.h
        Commons/TSocket.cpp
        Commons/TSocket.h
        Commons/TMessageThread.cpp
        Commons/TMessageThread.h
        Commons/TSwitchingMessage.cpp
        Commons/TSwitchingMessage.h
        Commons/TType.h
        Commons/TUser.cpp
        Commons/TUser.h
        Commons/TypeTraits.h
        Commons/Uncopyable.h
        Commons/Validator.cpp
        Commons/Validator.h
        Server/Messenger/Messenger.h
        Server/Messenger/TUserMessenger.cpp
        Server/Messenger/TUserMessenger.h
        Server/Room/TGameRoom.cpp
        Server/Room/TGameRoom.h
        Server/Room/TWaitingRoom.cpp
        Server/Room/TWaitingRoom.h
        Server/Server/TServerManager.cpp
        Server/Server/TServerManager.h
        Server/Server/TServerSocket.cpp
        Server/Server/TServerSocket.h
        Server/Server/TServerUser.cpp
        Server/Server/TServerUser.h
        Server/Server/TSocketImpl.cpp
        Server/Server/TSocketImpl.h
        Server/main.cpp
        ReadMe.txt Commons/Room/TIWaitingRoom.cpp Commons/Room/TIGameRoom.cpp)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_include_directories(OnlineTetris PUBLIC ${PROJECT_SOURCE_DIR}/Commons)
target_link_libraries(OnlineTetris pthread)