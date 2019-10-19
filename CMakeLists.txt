cmake_minimum_required(VERSION 3.4.3)
project(face-morph)

function(download_file url filename hash_type hash)

if(NOT EXISTS ${filename})
  file(DOWNLOAD ${url} ${filename}
       TIMEOUT 60  # seconds
       EXPECTED_HASH ${hash_type}=${hash}
       TLS_VERIFY ON
      )
endif()

endfunction(download_file)

#find dependencies
find_package( OpenCV REQUIRED )
find_package(dlib REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${DLib_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-std=c++11")
add_library(face-morph SHARED
    src/AffineFactory.cpp
    src/DelaunayTriangles.cpp
    src/FaceFeatureExtract.cpp
    src/TriangleFactory.cpp
)

download_file(https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_alt2.xml
              ./haarcascade_frontalface_alt2.xml
              MD5
              bca0348056a6f8eca2c1b8f1c073d5c2
)
download_file(https://raw.githubusercontent.com/kurnianggoro/GSOC2017/master/data/lbfmodel.yaml
              ./lbfmodel.yaml
              MD5
              96034b93743e1f7f9748797fb8222dd9
)

target_link_libraries( face-morph ${OpenCV_LIBS} ${DLib_LIBRARIES} )
set_target_properties(face-morph PROPERTIES PUBLIC_HEADER "src/fmorph.h")
target_include_directories(face-morph PUBLIC "${PROJECT_SOURCE_DIR}/src/")
INSTALL(TARGETS face-morph 
        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/bin/
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/include/
)
add_executable(delaunay-ex examples/delaunayCam/main.cpp)
target_link_libraries(delaunay-ex PRIVATE face-morph ${OpenCV_LIBS})
add_executable(face-morph-ex examples/morphCli/main.cpp)
target_link_libraries(face-morph-ex PRIVATE face-morph ${OpenCV_LIBS})


