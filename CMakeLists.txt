# Минимальная версия CMake
cmake_minimum_required(VERSION 3.16)

# Название проекта и его версия
project(Translator VERSION 0.1 LANGUAGES CXX)

# Включаем автогенерацию для UI, MOC и RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем необходимые библиотеки Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# Список исходных файлов
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    translator.cpp
    translator.h
)

# Создаём цель для приложения
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Translator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        database.h database.cpp
        quise.h quise.cpp
        enum.h
    )
else()
    if(ANDROID)
        add_library(Translator SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Translator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Подключаем библиотеки
target_link_libraries(Translator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# Указываем свойства для макета (для macOS)
set_target_properties(Translator PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Устанавливаем директории для установки
include(GNUInstallDirs)
install(TARGETS Translator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Завершаем сборку для Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Translator)
endif()
