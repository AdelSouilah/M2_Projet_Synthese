cmake_minimum_required(VERSION 3.16)
project(M2_Projet_Synthese C)

set(CMAKE_C_STANDARD 11)

include_directories(headers)

add_executable(Executable src/main.c
        headers/aide.h
        headers/heur_EDD.h
        headers/heur_LPT.h
        headers/heur_MinCost.h
        headers/heur_Slack.h
        headers/heur_SPT.h
        headers/instance_gen.h
        headers/task.h
        src/aide.c
        src/algorithms/heur_EDD.c
        src/algorithms/heur_LPT.c
        src/algorithms/heur_MinCost.c
        src/algorithms/heur_Slack.c
        src/algorithms/heur_SPT.c
        src/instance_gen.c)