# CMakeList.txt : CMake project for SwiftRock, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Add source to this project's executable.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(FastNet)

set(protocol
src/Packet.hxx
)

set(core
src/FastNet.hxx
src/FastNet.cxx
src/PeerConfig.hxx
src/Peer.hxx
src/Peer.cxx
src/NetVar.hxx
src/NetObject.hxx
src/NetObject.cxx
src/Globals.hxx

src/Channel.hxx
)


set(internal
src/Address.hxx
src/EndPoint.hxx
src/Socket.hxx
src/Packet.hxx
src/Packet.cxx
src/PacketBus.hxx
src/PacketBus.cxx
src/Connection.hxx
)

if(MSVC)
set(internal_platform
src/windows/Socket.cxx
)
elseif(UNIX)
set(internal_platform
src/linux/Socket.cxx
)
else()
set(internal_platform
src/darwin/Socket.cxx
)
endif()

source_group(protocol FILES ${protocol})
source_group(core FILES ${core})
source_group(internal FILES ${internal} ${internal_platform})

add_library (FastNetStatic STATIC ${core} ${internal} ${internal_platform} "src/Exceptions.hxx")
add_library (FastNetDynamic SHARED ${core} ${internal} ${internal_platform} "src/Exceptions.hxx")

add_executable(FastNetTest src/FastNet.hxx src/FastNet.cxx test/main.cxx "src/Exceptions.hxx")
target_link_libraries(FastNetTest PUBLIC FastNetStatic)