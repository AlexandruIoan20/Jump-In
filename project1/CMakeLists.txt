cmake_minimum_required(VERSION 3.29.5)
project(project1)

# Setează standardul de compilare
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Adaugă toate fișierele sursă
add_executable(project1
        main.cpp
        global/global.cpp
        afis/afis.cpp
        logica-joc/miscare-iepure/miscare-iepure.cpp
        logica-joc/miscare-vulpe/miscare-vulpe.cpp
        utils/utils.cpp
        miscari/miscari.cpp
        utilizatori/utilizatori.cpp
)

#[[
# Activează compabilitatea ANSI în MinGW pentru stdio
add_definitions(-D__USE_MINGW_ANSI_STDIO=1)
add_definitions(-D__MINGW_HAVE_STD_C99) # Pentru ISO C99 suportat în MinGW
add_definitions(-D__MINGW_EXTENSION=)   # Elimină problema macro-urilor

# Adaugă directory include pentru graphics.h
target_include_directories(project1 PRIVATE "C:/compiler_graphics/include" -std=c++17 -std=gnu++17)

# Adaugă directorul unde se află librăria grafică WinBGIm
link_directories("C:/compiler_graphics/lib")

# Opțiuni adiționale pentru compilare
target_compile_options(project1 PRIVATE -std=c++17 -std=c11)

# Leagă librăria BGI și alte librării Windows
target_link_libraries(project1 PRIVATE -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32)]]
