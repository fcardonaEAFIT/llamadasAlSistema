/*
 * crearProceso se encarga de crear un proceso
 *
 * Programador: Juan Francisco Cardona Mc'Cormick
 */
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>

const char* EMACSNAME     = "emacs";
const char* NOWINDOW      = "-nw";
const char* FILEPOS       = "+29:4";
const char* FILEOPEN      = "crearProceso.cpp";

int
main(int argc, char *argv[], char *arge[]) {
  pid_t hijo;

  std::cout << "PID (Process ID): " << getpid() << std::endl;

  hijo = ::fork();

  if (hijo == -1) {
    std:: cout << "Error: " << errno << std::endl;

    if (errno == EAGAIN) {
      std::cerr << "Error manejar el error aqui" << std::endl;
    }

    ::exit(0);
  }

  if (hijo == 0) { // El proceso hijo

    char *args[5];

    args[0] = new char[::strlen(EMACSNAME)];
    ::strcpy(args[0], EMACSNAME);
    args[1] = new char[::strlen(NOWINDOW)];
    ::strcpy(args[1], NOWINDOW);
    args[2] = new char[::strlen(FILEPOS)];
    ::strcpy(args[2], FILEPOS);
    args[3] = new char[::strlen(FILEOPEN)];
    ::strcpy(args[3], FILEOPEN);
    args[4] = NULL;

    ::execve("/usr/bin/emacs",
             args,
             arge);
    ::exit(10);
  }
  else {  // El proceso padre
    int status;

    ::wait(&status);

    if (WIFEXITED(status)) {
      std::cout << "Mi proceso hijo termina con:"  << WEXITSTATUS(status)
                << std::endl;
    }
    else {
      std::cout << "Mi proceso fue asesinado con la senal: "
                << WTERMSIG(status) << std::endl;
    }
  }

  return 0;
}
