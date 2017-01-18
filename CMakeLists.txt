cmake_minimum_required(VERSION 3.2)

PROJECT( SEFES )

IF( NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )
  message( FATAL_ERROR "64 Bit is requiered." )
ENDIF( NOT CMAKE_SIZEOF_VOID_P EQUAL 8 )

INCLUDE_DIRECTORIES( api2 inc )

LINK_DIRECTORIES( lib )

FILE( GLOB SRC src/*.cpp src/*.h* )

ADD_EXECUTABLE( simulation ${SRC} )

TARGET_LINK_LIBRARIES( simulation debug RobotinoExtensiond )
TARGET_LINK_LIBRARIES( simulation optimized RobotinoExtension )
  
TARGET_LINK_LIBRARIES( simulation debug rec_robotino_api2d )
TARGET_LINK_LIBRARIES( simulation optimized rec_robotino_api2 )

TARGET_COMPILE_DEFINITIONS(simulation PRIVATE "ROBOTINO_IP=\"127.0.0.1\"" )
