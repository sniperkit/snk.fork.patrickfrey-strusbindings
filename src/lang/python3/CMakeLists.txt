cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

# --------------------------------------
# PYTHON
# --------------------------------------
if( APPLE )
set( PYTHON3_MODULE_CXX_FLAGS "" )
set( PYTHON3_MODULE_LINK_FLAGS "-undefined dynamic_lookup" )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang" )
set( PYTHON3_MODULE_CXX_FLAGS "-g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security" )
set( PYTHON3_MODULE_LINK_FLAGS "-Xlinker -export-dynamic -Wl,-O1" )
else( APPLE )
set( PYTHON3_MODULE_CXX_FLAGS "-Wl,-Bsymbolic-functions -Wl,-z,relro -g -fstack-protector --param=ssp-buffer-size=4 -Wformat -Werror=format-security" )
set( PYTHON3_MODULE_LINK_FLAGS "-Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions" )
endif( APPLE )
message( STATUS "Python3 module compiler flags: ${PYTHON3_MODULE_CXX_FLAGS}" )
message( STATUS "Python3 module linker flags: ${PYTHON3_MODULE_LINK_FLAGS}" )

include_directories(
        ${PYTHON3_INCLUDE_DIRS}
	${Intl_INCLUDE_DIRS}
	${PAPUGA_INCLUDE_DIRS}
	${BINDINGS_INCLUDE_DIRS}
)

link_directories(
	${Boost_LIBRARY_DIRS}
        ${PYTHON3_LIBRARY_DIRS}
        ${PAPUGA_PYTHON3_LIBRARY_DIRS}
	${PAPUGA_LIBRARY_DIRS}
	${BINDINGS_LIBRARY_DIRS}
	${strusbase_LIBRARY_DIRS}
	${strusmodule_LIBRARY_DIRS}
	${strusrpc_LIBRARY_DIRS}
	${strus_LIBRARY_DIRS}
	${strusanalyzer_LIBRARY_DIRS}
	${strustrace_LIBRARY_DIRS}
)

add_custom_command(
    OUTPUT      strus.c
    DEPENDS    ${CMAKE_CURRENT_BINARY_DIR}/../../../include/strus/bindingObjects.h strusBindingsModuleGen strus_bindings_description
    COMMAND  strusBindingsModuleGen python3 module strus.c 
    COMMENT  "Generating Python3 module source strus.c"
    VERBATIM
 )
 
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py
    DEPENDS   ${CMAKE_CURRENT_BINARY_DIR}/../../../include/strus/bindingObjects.h strus_bindings_description strusBindingsModuleGen
    COMMAND  strusBindingsModuleGen python3 doc ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py
    COMMENT  "Generating bindings interface doc description file ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py"
    VERBATIM
 )

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.htm
    DEPENDS   papugaDoc  "${PROJECT_SOURCE_DIR}/src/lang/python3/strusPythonDoc.tpl"  ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py
    COMMAND  papugaDoc -o ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.htm "${PROJECT_SOURCE_DIR}/src/lang/python3/strusPythonDoc.tpl" ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py
    COMMENT  "Generating bindings interface doc html file ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.htm"
    VERBATIM
 )

configure_file( ${PROJECT_SOURCE_DIR}/src/lang/python3/pythonBindingsDoc.css  ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.css  COPYONLY )
configure_file( ${PROJECT_SOURCE_DIR}/src/lang/python3/pythonBindingsDoc.js  ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.js  COPYONLY )

add_custom_target(
    python3_mod ALL
    DEPENDS strus.c ${CMAKE_CURRENT_BINARY_DIR}/strusdoc.py papuga_python3_gen ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.htm ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.css ${CMAKE_BINARY_DIR}/doc/pythonBindingsDoc.js 
)

add_cppcheck( strus_bindings_python3 strus.c  )

add_library( strus_bindings_python3 MODULE strus.c )
add_dependencies( strus_bindings_python3 python3_mod )
set_target_properties( strus_bindings_python3 PROPERTIES 
				PREFIX "" 
				OUTPUT_NAME strus 
				LINK_FLAGS "${PYTHON3_MODULE_LINK_FLAGS}"
				COMPILE_FLAGS "${PYTHON3_MODULE_CXX_FLAGS}" )
target_link_libraries( strus_bindings_python3 ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} ${Intl_LIBRARIES} 
				strus_bindings
				papuga_python3_dev )

# FreeBSD needs kernel data access library for libuv (-libkvm)
find_library( LIBKVM_LIBRARIES kvm )
if(LIBKVM_LIBRARIES)
	target_link_libraries( strus_bindings_python3 ${LIBKVM_LIBRARIES} )
endif()

# Copy python3 module into a created directory easy relocatable by tests:
add_custom_command( TARGET strus_bindings_python3 POST_BUILD
					  COMMAND ${CMAKE_COMMAND} -E make_directory  ${CMAKE_BINARY_DIR}/modules/python3 )
add_custom_command( TARGET strus_bindings_python3 POST_BUILD
					  COMMAND ${CMAKE_COMMAND} -E copy_if_different  $<TARGET_FILE:strus_bindings_python3>  ${CMAKE_BINARY_DIR}/modules/python3/
					  COMMENT "Copy Python3 module built to ${CMAKE_BINARY_DIR}/modules/python3/" )

# ------------------------------
# INSTALLATION
# ------------------------------
install( TARGETS strus_bindings_python3
           LIBRARY DESTINATION ${PYTHON3_SITE_PACKAGES} )

