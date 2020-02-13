#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <cstdlib>
#include <iostream>

using namespace std;
const char *nomFic = "crearProceso"; // "tiendas-virtuales.csv";
const int TAM_BUFF = 1024;

int
main() {

  int fd = ::open(nomFic, O_RDONLY);

  if (fd == -1) {
    cerr << "Error abriendo " << nomFic
	 << " debido a " <<  strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }

  char *buffer[TAM_BUFF];

  ssize_t nbl;

  while ((nbl = read(fd, buffer, TAM_BUFF)) == TAM_BUFF)
    write(STDOUT_FILENO,buffer,nbl);

  if (nbl < 0) {
    cerr << "Error leyendo de " << nomFic
	 << " debido a " << strerror(errno) << endl;
    _exit(EXIT_FAILURE);
  }
  else
    write(STDOUT_FILENO, buffer, nbl);

  close(fd);
  return EXIT_SUCCESS;
}
