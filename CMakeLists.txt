cmake_minimum_required(VERSION 3.10)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(drsa DESCRIPTION "A deterministic implementation of some of the OpenSSL functionalities")

enable_language(C)
enable_testing()

option(TEST "Enable tests" OFF)
## ------------------------------------------------------------------------------------------------
## set DRSA_SRC lib properties
set(DRSA_SRC_DIR "src")

set(DRSA_HEADERS
	${DRSA_SRC_DIR}/all.h
	${DRSA_SRC_DIR}/bn.h
	${DRSA_SRC_DIR}/rand.h
	${DRSA_SRC_DIR}/rsa.h
)

include_directories(${DRSA_SRC_DIR}/..)

set(DRSA_SRC
	${DRSA_SRC_DIR}/bn.c
	${DRSA_SRC_DIR}/rand.c
	${DRSA_SRC_DIR}/rsa.c
)

add_library(drsa STATIC ${DRSA_SRC})

find_package(OpenSSL)
if (OPENSSL_FOUND)
	include_directories(${OPENSSL_INCLUDE_DIRS})
	target_link_libraries (drsa ${OPENSSL_LIBRARIES})
endif (OPENSSL_FOUND)

set_target_properties(drsa PROPERTIES OUTPUT_NAME "drsa")
target_include_directories(drsa PUBLIC
	${DRSA_SRC_DIR}
)

install(TARGETS drsa DESTINATION lib)
install(FILES ${DRSA_HEADERS} DESTINATION include/drsa)

if(TEST)
	set(TEST_DIR "tests/drsa")
	add_executable(bn_test ${TEST_DIR}/bn.c)
	add_executable(rand_test ${TEST_DIR}/rand.c)
	add_executable(rs_testa ${TEST_DIR}/rsa.c)

	target_include_directories(bn_test PRIVATE ${TEST_DIR})
	target_include_directories(rand_test PRIVATE ${TEST_DIR})
	target_include_directories(rsa_test PRIVATE ${TEST_DIR})

	target_link_libraries(bn_test drsa crypto)
	target_link_libraries(rand_test drsa crypto)
	target_link_libraries(rsa_test drsa crypto)
endif()

## ------------------------------------------------------------------------------------------------
## set sample executable properties
add_executable(sample src/sample.c)

set(SAMPLE_INCLUDE_DIRS)

target_include_directories(sample PUBLIC ${SAMPLE_INCLUDE_DIRS})

set(SAMPLE_LINK_DIRS
	${CMAKE_INSTALL_PREFIX}/lib
)

target_link_directories(sample PUBLIC ${SAMPLE_LINK_DIRS})

set(SAMPLE_LINK_LIBS drsa)

target_link_libraries(sample PUBLIC ${SAMPLE_LINK_LIBS})

install(TARGETS sample DESTINATION bin)
