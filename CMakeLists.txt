
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(rsa)
#---USE AS LIBRARY---
ADD_LIBRARY(rsa src/rsa.cpp)
TARGET_INCLUDE_DIRECTORIES(rsa PUBLIC include/)

#---USE WITH MAIN---
#FIND_PACKAGE( Boost 1.76.0 COMPONENTS program_options REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
#SET (CMAKE_CXX_STANDARD 17)
#ADD_EXECUTABLE(rsa "src/rsa.cpp")
#TARGET_INCLUDE_DIRECTORIES(rsa PUBLIC include/)

