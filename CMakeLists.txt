cmake_minimum_required(VERSION 3.10)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(dopenssl DESCRIPTION "A deterministic implementation of some of the OpenSSL functionalities")

enable_language(C)
enable_testing()

option(TEST "Enable tests" OFF)

set(SRC_DIR "src/dopenssl")

set(HEADER_FILES
	${SRC_DIR}/all.h
	${SRC_DIR}/bn.h
	${SRC_DIR}/rand.h
	${SRC_DIR}/rsa.h
)

include_directories(${SRC_DIR}/..)

set(SRC_FILES
	${SRC_DIR}/bn.c
	${SRC_DIR}/rand.c
	${SRC_DIR}/rsa.c
)

add_library(dopenssl STATIC ${SRC_FILES})

find_package(OpenSSL)
if (OPENSSL_FOUND)
	include_directories(${OPENSSL_INCLUDE_DIRS})
	target_link_libraries (dopenssl ${OPENSSL_LIBRARIES})
endif (OPENSSL_FOUND)

set_target_properties(dopenssl PROPERTIES OUTPUT_NAME "dopenssl")
target_include_directories(dopenssl PUBLIC
	${SRC_DIR}
)

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

install(TARGETS dopenssl DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include/dopenssl)

add_executable(dopenssl_sample src/sample.c)
target_include_directories(dopenssl_sample PUBLIC ${HEADER_FILES})
target_link_libraries(dopenssl_sample PUBLIC dopenssl)

install(TARGETS dopenssl_sample DESTINATION bin)
