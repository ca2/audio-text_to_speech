cmake_minimum_required(VERSION 3.16)
project(user_text_to_speech CXX)


message("PROJECT_NAME = ${PROJECT_NAME}")


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   berg
   )

list(APPEND library_source
   _.cpp
   platform.cpp
   platform.h
   _factory.cpp
   form_handler.cpp
   form_handler.h
   )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

# These providers are offered by the Options form and loaded dynamically.
# Build them with the form library without adding runtime link dependencies.
set(text_to_speech_provider_dependencies
   text_to_speech_azure
   text_to_speech_google
   text_to_speech_streamelements)
if(WIN32)
   list(APPEND text_to_speech_provider_dependencies text_to_speech_sapi)
endif()
add_dependencies(${PROJECT_NAME} ${text_to_speech_provider_dependencies})
add_dependencies(static_${PROJECT_NAME} ${text_to_speech_provider_dependencies})

if (NOT ${NO_PRECOMPILED_HEADER})

    target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
    target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${WIN32})
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})

elseif(${LINUX} OR ${__BSD__} OR ${__ANDROID__} OR ${__SUNOS__})
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
    #target_link_options(${PROJECT_NAME} PRIVATE "-Wl,-rpath=\$ORIGIN")
    #target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)






