# Actividad 3 - Control de Accesos.

## Parte 1: Gestión de Usuarios

1. **Creación de Usuarios: Crea tres usuarios llamados `usuario1`, `usuario2` y `usuario3`.**

    **Comando utilizado:**

        sudo adduser usuario1
        sudo adduser usuario2
        sudo adduser usuario3

    **Nota:El comando adduser nos permite agregarle una contrasena al crear el usuario.**
    
- `usuario1` = pass1user1
- `usuario2` = pass2user2
- `usuario3` = pass3user3

2. **Asignacion de contrasena:**

    **Comando utilizado:**

        sudo passwd usuario1
        sudo passwd usuario2
        sudo passwd usuario3

    **Nota:La nueva contrasena es la siguiente:**
- `usuario1` = cambiouser1
- `usuario2` = cambiouser2
- `usuario3` = cambiouser3

3. **Información de Usuarios:**

    **Comando utilizado:**

        id usuario1

4. **Eliminacion de Usuarios:**

    **Comando utilizado:**

        sudo userdel usuario3

    **Nota: El comando usado conserva su directorio principal /home/usuario3**

## Parte 2: Gestión de Grupos

1. **Creación de Grupos: Crea dos grupos llamados `grupo1` y `grupo2`.**

    **Comando utilizado:**

        sudo groupadd grupo1
        sudo groupadd grupo2

2. **Agregar Usuarios a Grupos: Agrega `usuario1` a `grupo1` y `usuario2` a `grupo2`.**

        sudo usermod -aG grupo1 usuario1
        sudo usermod -aG grupo2 usuario2

3. **Verificar Membresía: Verifica que los usuarios han sido agregados a los grupos utilizando el comando `groups`.**

        groups usuario1
        groups usuario2

4. Eliminar Grupo: Elimina `grupo2`.

        sudo groupdel grupo2

    **Nota: Si había usuarios en grupo2, ya no serán miembros de ese grupo.**

## Parte 3: Gestión de Permisos

1. **Creación de Archivos y Directorios:**

    Primero tenemos que cambiar al `usuario1` para hacer la tarea como ese usuario.

        su - usuario1

    Estando como `usuario1` se crea el archivo `archivo1.txt` en su directorio principal y escribimos en el.

        echo "Hola desde usuario1, archivo1.txt" > ~/archivo1.txt

    Creamos un directorio llamado `directorio1` y dentro de dicho directorio, un archivo llamado `archivo2.txt`

        mkdir `~/directorio1`

        echo "Hola desde /directorio1, archivo2.txt" > ~/directorio1/archivo2.txt

2. **Verificar Permisos:** 
    
    Verifica los permisos del archivo y directorio usando el comando `ls -l` y `ls -ld` respectivamente.

        ls -l

        -rw-rw-r-- 1 usuario1 usuario1   34 ago  4 21:35 archivo1.txt
        drwxrwxr-x 2 usuario1 usuario1 4096 ago  4 21:51 directorio1

        ls -ld
        drwxr-x--- 3 usuario1 usuario1 4096 ago  4 21:50 .

3. **Modificar Permisos usando `chmod` con Modo Numérico:** 

    Cambia los permisos del `archivo1.txt` para que sólo `usuario1` pueda leer y escribir (permisos `rw-`), el grupo pueda leer (permisos `r--`) y nadie más pueda hacer nada.

        chmod 640 ~/archivo1.txt

    luego de ejecutar el comando queda lo siguiente:

        ls -l ~/archivo1.txt
        -rw-r----- 1 usuario1 usuario1 34 ago  4 21:35 /home/usuario1/archivo1.txt

4. **Modificar Permisos usando `chmod` con Modo Simbólico:**
    
     Agrega permiso de ejecución al propietario del `archivo2.txt`.

     primero veremos como estan los permisos del archivo2.txt

        ls -l ~/directorio1/archivo2.txt

    nos da la siguiente salida:

        -rw-rw-r-- 1 usuario1 usuario1 38 ago  4 21:51 /home/usuario1/directorio1/archivo2.txt

    procedemos a agregar permisos de ejecucion al propietario representado en los primero 3 espacios de los permisos, con el siguiente comando:

        chmod u+x ~/directorio1/archivo2.txt

    vemos nuevamente el estado de los permisos:

        ls -l ~/directorio1/archivo2.txt

    nos da la siguiente salida:

        -rwxrw-r-- 1 usuario1 usuario1 38 ago  4 21:51 /home/usuario1/directorio1/archivo2.txt

5. **Cambiar el Grupo Propietario:** 
    
    Cambia el grupo propietario de `archivo2.txt` a `grupo1`. 
    
    Para esto utilizaremos el comando chown con el uso de `:nombregrupo` seguido de la ruta del archivo.

        chown :grupo1 ~/directorio1/archivo2.txt
    
    Verificamos el cambio:

        ls -l ~/directorio1/archivo2.txt

    nos da la salida:

        -rwxrw-r-- 1 usuario1 grupo1 38 ago  4 21:51 /home/usuario1/directorio1/archivo2.txt

6. **Configurar Permisos de Directorio:** 

    Cambia los permisos del `directorio1` para que sólo el propietario pueda entrar (permisos `rwx`), el grupo pueda listar contenidos pero no entrar (permisos `r--`), y otros no puedan hacer nada.

    para esto usaremos el comando chmod en modo numerico, el comando sera:

        chmod 740 ~/directorio1
    
    procedemos a ver los permisos del directorio:

        ls -ld directorio1/
        drwxr----- 2 usuario1 usuario1 4096 ago  4 21:51 directorio1/

7. **Comprobación de Acceso:** 
    
    Intenta acceder al `archivo1.txt` y `directorio1/archivo2.txt` como `usuario2`. Nota cómo el permiso de directorio afecta el acceso a los archivos dentro de él.

    Primero debemos de cambiar de usuario
        
        su - usuario2

    ya como usuario2 intentamos acceder al archivo1.txt

        cat /home/usuario1/archivo1.txt
        cat: /home/usuario1/archivo1.txt: Permiso denegado

    ahora intentamos acceder al directorio1/archivo2.txt

        cat /home/usuario1/directorio1/archivo2.txt
        cat: /home/usuario1/directorio1/archivo2.txt: Permiso denegado

    Se nos niega el acceso debido a que usuario2 no pertenece a grupo1. Esto se puede comprobar con el comando:
            
            groups usuario2
    
    8. **Verificación Final:** 
        
        Verifica los permisos y propietario de los archivos y directorio nuevamente con `ls -l` y `ls -ld`.

        primero regresamos a usuario1:
            su - usuario1

        luego de loguearnos, usamos el comando y vemos la salida:

            ls -l
            total 8
            -rw-r----- 1 usuario1 usuario1   34 ago  4 21:35 archivo1.txt
            drwxr----- 2 usuario1 usuario1 4096 ago  4 21:51 directorio1
        
        analizamos el del archivo2.txt

            ls -l directorio1/archivo2.txt
            -rwxrw-r-- 1 usuario1 grupo1 38 ago  4 21:51 directorio1/archivo2.txt

        ejecutamos el analisis de directorios:

            ls -ld
            drwxr-x--- 3 usuario1 usuario1 4096 ago  4 21:50 .

        nos movemos al directorio1 y analizamos sus permisos:

            ls -ld
            drwxr----- 2 usuario1 usuario1 4096 ago  4 21:51 .

## **Reflexión:**

**¿Por qué es importante gestionar correctamente los usuarios y permisos en un sistema operativo?**
    
*R//* Esto es muy importante debido a varias razones, entre ellas esta la integridad del sistema debido que al tener permisos limitados para cada usuario, se evita que se haga un cambio ya sean intencionalmente o no, afectando al sistema.

Otro punto importante es que se crea confidencialidad en un entorno multiusuario, asegurando que la informacion de un usuario no este accesible para otros, a menos que exista una configuracion que lo permita.

**¿Qué otros comandos o técnicas conocen para gestionar permisos en Linux?**

*R//* De momento los vistos en clase de Sistemas Operativos 1:

- setuid/setgid (s)
- Sticky bit (t)


    
