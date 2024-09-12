#include <stdio.h> //entrada y salida estandar
#include <stdlib.h> //libreria estandar
#include <unistd.h> //llamadas al sistema
#include <sys/types.h> //tipos de datos
#include <sys/wait.h> //llamadas al sistema

int main() {
    pid_t pid;

    // Crear un proceso hijo utilizando fork()
    pid = fork();

    if (pid < 0) {
        // Error al crear el proceso hijo
        perror("fallo en el fork");
        exit(1);
    }

    if (pid == 0) {
        // Este es el código del proceso hijo
        printf("Proceso hijo (PID: %d) ha finalizado.\n", getpid());
        // El hijo termina inmediatamente
        exit(0);
    } else {
        // Este es el código del proceso padre

        // Imprimir el PID del proceso hijo
        printf("Proceso padre (PID: %d) creo un proceso hijo (PID: %d).\n", getpid(), pid);

        // Dormir 60 segundos para estado zombie del proceso hijo
        sleep(60);

        // Ahora el padre espera a que el hijo termine (esto limpia el proceso zombie)
        wait(NULL);

        printf("Proceso hijo (PID: %d) limpiado (no zombie).\n", pid);
    }

    return 0;
}