#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
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

    std::cout << "Proceso identificador hijo: " << hijo << std::endl;
    std::cout << "Identificador proceso actual: " << getpid() << std::endl;
    std::cout << "Identificador de proceso padre: " << getppid() << std::endl;
    
    // ::sleep(5);
    return 10;
  }
  else {  // El proceso padre
    int status;
    
    std::cout << "Identificador proceso hijo: " << hijo << std::endl;

    ::sleep(5);
    ::kill(hijo, SIGKILL);
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
