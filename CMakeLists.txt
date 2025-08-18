cmake_minimum_required(VERSION 3.16)
project(LibraryManagementSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets libraries
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

# Recursively find all source and header files from all subdirectories
file(GLOB_RECURSE SRCS
    "Core/*.cpp" "Dashboard/*.cpp" "Data/*.cpp" "Data_Models/*.cpp" "Utility/*.cpp"
    "Core/*.hpp" "Dashboard/*.hpp" "Data/*.hpp" "Data_Models/*.hpp" "Utility/*.hpp"
    "App.cpp"
)

# Create a single executable from all source files
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SRCS})
else()
    add_executable(${PROJECT_NAME} ${SRCS})
endif()

# Automatically organize files into folders in the IDE
foreach(FILE ${SRCS})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
        set(GROUP "${GROUP}\\Source Files")
    elseif("${FILE}" MATCHES ".*\\.hpp")
        set(GROUP "${GROUP}\\Header Files")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

# Set include directories for the entire project
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    Core
    Dashboard
    Data
    Data_Models
    Utility
)

# Link to wxWidgets libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

# Copy the text files to the build output directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Data/admins_text.txt"
     "${CMAKE_CURRENT_SOURCE_DIR}/Data/books_text.txt"
     "${CMAKE_CURRENT_SOURCE_DIR}/Data/students_text.txt"
     DESTINATION "${CMAKE_BINARY_DIR}/Data")