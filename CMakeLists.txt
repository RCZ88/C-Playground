cmake_minimum_required(VERSION 3.20)

project(LEARN_abC
        VERSION 1.0
        LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(LEARN_abC
#        printMem.c
#        decimalBinary.c
#        bitFields.c
#        LW01IO.c
#        decimalBinary.c
#        psuedobullshit.c
#        TrackVault/bytes.h
#        TrackVault/flags.c
#        TrackVault/flags.h
#        TrackVault/serialization.h
#        TrackVault/serialization.c
#        TrackVault/tests.c
#        TrackVault/write.c
#        TrackVault/arena.h
#        TrackVault/arena.c
#        TrackVault/library.c
#        TrackVault/library.h
#        socs210926.c
#        TrackVault/shiftbits.c
#        socs280926.c
        socs051026.c
        #        TrackVault/index.c
#        TrackVault/index.h
#        TrackVault/format.h
#        TrackVault/format.c
#        TrackVault/record.h
#        TrackVault/record.c
)

if (UNIX AND NOT APPLE)
    target_link_libraries(LEARN_abC PRIVATE m)
endif()