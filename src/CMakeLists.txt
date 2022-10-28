set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES ${SOURCES})




# Añadimos las bibliotecas
add_library(common common/progargs.cpp common/progargs.h common/aux_functions.cpp common/aux_functions.h)
add_library(aos aos/imageaos.cpp)
add_library(soa soa/imagesoa.cpp)

# Generamos el ejecutable para AOS
add_executable(imgaos main_aos.cpp)
target_link_libraries(imgaos aos common)

# Generamos el ejecutable para SOA
add_executable(imgsoa main_soa.cpp)
target_link_libraries(imgsoa soa common)