#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// función que se ejecutará en el hilo
void* thread_function(void* arg) {
    printf("Hilo creado\n");
    return NULL;
}

int main() { // Se crean 3 procesos y 1 hilo main es el proceso padre
    pid_t pid;

    pid = fork();  // Primer fork, crea un hijo
    if (pid == 0) {  /* Proceso hijo */
        fork();  // Segundo fork (crea un nieto, de main, en el hijo del primer fork)
        pthread_t thread; // Declaración de un hilo
        pthread_create(&thread, NULL, thread_function, NULL);  // Crea un hilo en el proceso hijo del primer fork
        pthread_join(thread, NULL);  // Espera a que el hilo termine
    }
    
    fork();  // Tercer fork (puede crear un proceso nuevo en el hijo(primer fork) o padre original(proceso main))

    return 0;
}
