# CMakeList.txt: CMake-Projekt für "retroBattle". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.20)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("retroBattle")

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (retroBattle "retroBattle.cpp" "retroBattle.h"  "headers/metrics.h" "source/metrics.cpp" "headers/entity.h" "source/entity.cpp" "source/vector2D.cpp" "vektor2D_test.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET retroBattle PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(retroBattle PUBLIC "${PROJECT_SOURCE_DIR}/")
target_include_directories(retroBattle PUBLIC "${PROJECT_SOURCE_DIR}/external_libraries/PDCurses")
target_link_libraries(retroBattle PRIVATE "${PROJECT_SOURCE_DIR}/external_libraries/PDCurses/wincon/pdcurses.lib")

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
