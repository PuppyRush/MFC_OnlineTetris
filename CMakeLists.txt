cmake_minimum_required(VERSION 3.7)
project(OnlineTetris)

set(CMAKE_CXX_STANDARD 14)



include_directories(Commons)
include_directories(Commons/Entity)
include_directories(Commons/Entity/Room)
include_directories(Server/Messenger)
include_directories(Server/Room)
include_directories(Server/Server)

add_executable(OnlineTetris
        Commons/Entity/Room/TIGameRoom.cpp
        Commons/Entity/Room/TIGameRoom.h
        Commons/Entity/Room/TIRoom.cpp
        Commons/Entity/Room/TIRoom.h
        Commons/Entity/Room/TIWaitingRoom.cpp
        Commons/Entity/Room/TIWaitingRoom.h
        Commons/Entity/TObject.h
        Commons/Entity/TObject.cpp
        Commons/Entity/TSocket.cpp
        Commons/Entity/TSocket.h
        Commons/Entity/TUser.cpp
        Commons/Entity/TUser.h
        Commons/DefineInfo.h
        Commons/ITObjectContainer.h
        Commons/Logger.h
        Commons/TProperty.h
        Commons/structs.h
        Commons/TAtomic.h
        Commons/TMessageStruct.h
        Commons/TObjectContainer.h
        Commons/TObjectContainerFactory.h
        Commons/TMessageThread.cpp
        Commons/TMessageThread.h
        Commons/TMessageSender.h
        Commons/TMessageSender.cpp
        Commons/TType.h
        Commons/TypeTraits.h
        Commons/Uncopyable.h
        Commons/Validator.cpp
        Commons/Validator.h
        Commons/TFunctional.h
        Commons/TMessageObject.cpp
        Commons/TMessageObject.h
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
        )

set(THREADS_PREFER_PTHREAD_FLAG ON -g -fno-omit-frame-pointer)
find_package(Threads REQUIRED)
target_include_directories(OnlineTetris PUBLIC ${PROJECT_SOURCE_DIR}/Commons)
target_link_libraries(OnlineTetris pthread)