cmake_minimum_required(VERSION 2.8)
set(libFakeInput)
project(libFakeInput)

set(VERSION 1)
set(SUBVERSION 0)


if(${UNIX})
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(X11 REQUIRED x11)
    pkg_check_modules(XTest REQUIRED xtst)
endif(${UNIX})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/FakeInput)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/FakeInput/actions)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/bin/lib)




# headers
set(HDRS_COMMON
        include/FakeInput/key.hpp
        include/FakeInput/key_base.hpp
        include/FakeInput/keyboard.hpp
        include/FakeInput/mapper.hpp
        include/FakeInput/mouse.hpp
        include/FakeInput/system.hpp
        include/FakeInput/types.hpp
        include/FakeInput/actions/actions.hpp
        include/FakeInput/actions/action.hpp
        include/FakeInput/actions/actionsequence.hpp
        include/FakeInput/actions/commandaction.hpp
        include/FakeInput/actions/keyaction.hpp
        include/FakeInput/actions/mouseaction.hpp
        include/FakeInput/actions/waitaction.hpp
        )

set(HDRS_UNIX
        include/FakeInput/display_unix.hpp
        include/FakeInput/key_unix.hpp
        )

set(HDRS_WIN
        include/FakeInput/key_win.hpp
        )

# sources
set(SRCS_COMMON
        src/key_base.cpp
        src/keyboard.cpp
        src/actions/actionsequence.cpp
        src/actions/commandaction.cpp
        src/actions/keyaction.cpp
        src/actions/mouseaction.cpp
        src/actions/waitaction.cpp
        )

set(SRCS_UNIX
        src/display_unix.cpp
        src/mouse_unix.cpp
        src/mapper_unix.cpp
        src/system_unix.cpp
        src/keyboard_unix.cpp
        src/key_unix.cpp
        )

set(SRCS_WIN
        src/mouse_win.cpp
        src/mapper_win.cpp
        src/system_win.cpp
        src/keyboard_win.cpp
        src/key_win.cpp
        )

if(${UNIX})
    set(HDRS
            ${HDRS_COMMON}
            ${HDRS_UNIX}
            )

    set(SRCS
            ${SRCS_COMMON}
            ${SRCS_UNIX}
            )

    set(LIBS
            ${X11_LIBRARIES}
            ${XTest_LIBRARIES}
            )
endif(${UNIX})

if(${WIN32})
    set(HDRS
            ${HDRS_COMMON}
            ${HDRS_WIN}
            )

    set(SRCS
            ${SRCS_COMMON}
            ${SRCS_WIN}
            )
endif(${WIN32})


add_library(fakeInputStatic STATIC ${SRCS})
target_link_libraries(fakeInputStatic ${LIBS})
set_target_properties(fakeInputStatic
        PROPERTIES
        OUTPUT_NAME fakeInput
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib
        )

add_library(fakeInputShared SHARED ${SRCS})
target_link_libraries(fakeInputShared ${LIBS})
set_target_properties(fakeInputShared
        PROPERTIES
        OUTPUT_NAME fakeInput
        VERSION ${VERSION}.${SUBVERSION}.0
        SOVERSION ${VERSION}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib # needed on Unix
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/lib # needed on Windows
        )

install(TARGETS fakeInputStatic fakeInputShared
        ARCHIVE DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
        LIBRARY DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
        RUNTIME DESTINATION ${INSTALL_PREFIX}/${INSTALL_LIBRARY_DIR}
        )

install(FILES fakeinput.hpp
        DESTINATION ${INSTALL_PREFIX}/${INSTALL_HEADER_DIR}
        )

install(FILES ${HDRS}
        DESTINATION ${INSTALL_PREFIX}/${INSTALL_HEADER_DIR}/fakeinput
        )




target_include_directories(fakeInputStatic PUBLIC include)
target_include_directories(fakeInputShared PUBLIC include)
