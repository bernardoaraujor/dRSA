cmake_minimum_required(VERSION 3.10)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(dopenssl DESCRIPTION "A deterministic implementation of some of the OpenSSL functionalities")

enable_language(C)
enable_testing()

option(TEST "Enable tests" OFF)

## ------------------------------------------------------------------------------------------------
## fetch ExternalProjects

include(FetchContent)
FetchContent_Declare(
		iota_common
		GIT_REPOSITORY http://github.com/iotaledger/iota_common.git
		GIT_TAG cf649803757abf48432d4fa60e9f27ac119bae5f
)

include(FetchContent)
FetchContent_Declare(
		trezor-firmware
		GIT_REPOSITORY https://github.com/bernardoaraujor/trezor-firmware.git
		GIT_TAG 0b3c205da877634eb348fe9dc11c7e9066f33b6f
)

message(STATUS "Fetching iota_common")
FetchContent_MakeAvailable(iota_common)

message(STATUS "Fetching trezor-firmware")
FetchContent_MakeAvailable(trezor-firmware)

## ------------------------------------------------------------------------------------------------
## set dopenssl lib properties
set(DOPENSSL_SRC_DIR "src/dopenssl")

set(DOPENSSL_HEADERS
	${DOPENSSL_SRC_DIR}/all.h
	${DOPENSSL_SRC_DIR}/bn.h
	${DOPENSSL_SRC_DIR}/rand.h
	${DOPENSSL_SRC_DIR}/rsa.h
)

include_directories(${DOPENSSL_SRC_DIR}/..)

set(DOPENSSL_SRC
	${DOPENSSL_SRC_DIR}/bn.c
	${DOPENSSL_SRC_DIR}/rand.c
	${DOPENSSL_SRC_DIR}/rsa.c
)

add_library(dopenssl STATIC ${DOPENSSL_SRC})

find_package(OpenSSL)
if (OPENSSL_FOUND)
	include_directories(${OPENSSL_INCLUDE_DIRS})
	target_link_libraries (dopenssl ${OPENSSL_LIBRARIES})
endif (OPENSSL_FOUND)

set_target_properties(dopenssl PROPERTIES OUTPUT_NAME "dopenssl")
target_include_directories(dopenssl PUBLIC
	${DOPENSSL_SRC_DIR}
)

install(TARGETS dopenssl DESTINATION lib)
install(FILES ${DOPENSSL_HEADERS} DESTINATION include/dopenssl)

if(TEST)
	set(TEST_DIR "tests/dopenssl")
	add_executable(bn_test ${TEST_DIR}/bn.c)
	add_executable(rand_test ${TEST_DIR}/rand.c)
	add_executable(rs_testa ${TEST_DIR}/rsa.c)

	target_include_directories(bn_test PRIVATE ${TEST_DIR})
	target_include_directories(rand_test PRIVATE ${TEST_DIR})
	target_include_directories(rsa_test PRIVATE ${TEST_DIR})

	target_link_libraries(bn_test dopenssl crypto)
	target_link_libraries(rand_test dopenssl crypto)
	target_link_libraries(rsa_test dopenssl crypto)
endif()

## ------------------------------------------------------------------------------------------------
## set iota2rsa lib properties
set(IOTA2RSA_SRC_DIR "src/iota/iota2rsa")
set(IOTA2RSA_HEADERS ${IOTA2RSA_SRC_DIR}/iota2rsa.h)

include_directories(${IOTA2RSA_SRC_DIR}/.. ${DOPENSSL_SRC_DIR})

set(IOTA2RSA_SRC ${IOTA2RSA_SRC_DIR}/iota2rsa.c)

add_library(iota2rsa STATIC ${IOTA2RSA_SRC})
target_include_directories(iota2rsa PUBLIC ${IOTA2RSA_SRC_DIR} ${iota_common_SOURCE_DIR} ${trezor_SOURCE_DIR})

set(IOTA2RSA_LINK_LIBS common trezor)
target_link_libraries(iota2rsa PUBLIC ${IOTA2RSA_LINK_LIBS})

install(TARGETS iota2rsa DESTINATION lib)
install(FILES ${IOTA2RSA_HEADERS} DESTINATION include/iota2rsa)

## ------------------------------------------------------------------------------------------------
## set iota2rsa_sample executable properties
add_executable(iota2rsa_sample src/iota/iota2rsa/sample.c)

set(SAMPLE_INCLUDE_DIRS
	${iota_common_SOURCE_DIR}
)

target_include_directories(iota2rsa_sample PUBLIC ${SAMPLE_INCLUDE_DIRS})

set(SAMPLE_LINK_DIRS
	${CMAKE_INSTALL_PREFIX}/lib
	${iota_common_BUILD_DIR}
)

target_link_directories(iota2rsa_sample PUBLIC ${SAMPLE_LINK_DIRS})

set(SAMPLE_LINK_LIBS
	dopenssl
	iota2rsa
	common # iota_common
)
target_link_libraries(iota2rsa_sample PUBLIC ${SAMPLE_LINK_LIBS})

install(TARGETS iota2rsa_sample DESTINATION bin)
