cmake_minimum_required(VERSION 3.26)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(simple_shell
        aid_err1.c
        aid_err2.c
        aid_assist.c
        aid_assist2.c
        aid_list.c
        aid_list2.c
        aid_memory.c
        aid_stardlib.c
        aid_conc.c
        aid_conc2.c
        aid_conc3.c
        build_cd.c
        build_cdir_shell.c
        all_error.c
        comand_exec.c
        env1.c
        env2.c
        is_execute.c
        dismiss_shell.c
        get_all_builtin.c
        get_err.c
        gassist.c
        get_line.c
        get_signt.c
        main.c
        main.h
        call_lines.c
        rep_var.c
        shell_loop.c
        split.c)
