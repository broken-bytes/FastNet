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
protocol/Packet.hxx
)

set(core
core/FastNet.hxx
core/FastNet.cxx
core/PeerConfig.hxx
core/Peer.hxx
core/Peer.cxx
core/NetVar.hxx
core/NetObject.hxx
core/NetObject.cxx
Globals.hxx
)


set(internal
network/Address.hxx
network/EndPoint.hxx
network/Socket.hxx
network/Packet.hxx
network/Packet.cxx
network/PacketBus.hxx
network/PacketBus.cxx
network/Connection.hxx
)

if(MSVC)
set(internal_platform
network/windows/Socket.cxx
)
elseif(UNIX)
set(internal_platform
network/linux/Socket.cxx
)
else()
set(internal_platform
network/darwin/Socket.cxx
)
endif()

source_group(protocol FILES ${protocol})
source_group(core FILES ${core})
source_group(internal FILES ${internal} ${internal_platform})

add_library (FastNetStatic STATIC ${core} ${internal} ${internal_platform})
add_library (FastNetDynamic SHARED ${core} ${internal} ${internal_platform})

add_executable(FastNetTest core/FastNet.hxx core/FastNet.cxx test/main.cxx)
target_link_libraries(FastNetTest PUBLIC FastNetStatic)