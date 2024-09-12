# Tipos de Kernel y sus diferencias

Existen diferentes tipos de kernels, cada uno con sus propias características y enfoques de diseño. Los tres tipos principales son: 

**Kernel monolítico**: En este diseño, todas las funciones del kernel se implementan como un único programa en espacio de kernel. Ejemplos de sistemas operativos con kernels monolíticos son Linux y Windows (aunque Windows también incorpora aspectos de diseño híbrido). 

- **Ventajas:**
    - Rendimiento: Al estar todo en un solo espacio de memoria, la comunicación entre componentes es rápida.
    - Simplicidad en diseño: Aunque es grande y complejo, la interacción entre los componentes es directa.

- **Desventajas:**
    - Tamaño: Es grande y cualquier cambio requiere recompilar todo el kernel.
    - Estabilidad: Un fallo en un módulo puede afectar todo el sistema.

- **Ejemplos:** Linux, Unix, BSD.

**Microkernel**: En contraste con el enfoque monolítico, un microkernel delega la mayoría de las funciones del kernel a procesos separados que se ejecutan en espacio de usuario. Esto reduce la complejidad del núcleo y facilita la extensibilidad y la modularidad del sistema operativo. Ejemplos de sistemas con microkernels son GNU Hurd y QNX. 

- **Ventajas:**
    - Modularidad: Los servicios adicionales se ejecutan en el espacio de usuario, por lo que el kernel es menos susceptible a fallos.
    - Estabilidad: Si un módulo falla, no afecta al kernel completo.
    - Facilidad de extensión: Agregar nuevas funciones es más sencillo y no requiere modificar el kernel.

- **Desventajas:**
    - Rendimiento: Puede ser más lento debido a la sobrecarga en la comunicación entre módulos en espacios separados.
    - Complejidad: Requiere más mecanismos de comunicación entre módulos.

**Ejemplos:** Minix, QNX, L4.

**Kernel híbrido**: Como su nombre sugiere, un kernel híbrido combina características de los kernels monolíticos y microkernels. Algunas funciones críticas se implementan en espacio de kernel, mientras que otras se ejecutan como procesos en espacio de usuario. Este enfoque busca combinar la eficiencia del kernel monolítico con la flexibilidad del microkernel. macOS es un ejemplo de sistema operativo que utiliza un kernel híbrido. 

- **Ventajas:**
    - Flexibilidad: Combina rendimiento y modularidad.
    - Compatibilidad: Permite que los sistemas operativos sean más modulares sin sacrificar demasiada velocidad.

- **Desventajas:**
    - Complejidad en el diseño: La implementación puede volverse complicada, al tratar de equilibrar rendimiento y modularidad.
    - Dependencia en componentes críticos: A pesar de la modularidad, algunos componentes críticos siguen siendo monolíticos, lo que puede limitar la estabilidad.

**Ejemplos:** Windows NT, macOS, BeOS

**Exokernel**: Un exokernel es un tipo de kernel extremadamente minimalista que permite a las aplicaciones gestionar los recursos del hardware directamente, sin abstraerlos a través del kernel.

- **Ventajas:**
    - Rendimiento: Al permitir acceso directo al hardware, las aplicaciones pueden optimizar su uso.
    - Flexibilidad: Las aplicaciones pueden personalizar cómo interactúan con el hardware.

- **Desventajas:**
    - Complejidad en el desarrollo: Las aplicaciones deben implementar sus propios gestores de recursos.
    - Seguridad y estabilidad: Al tener menos control centralizado, es más difícil asegurar el sistema y prevenir errores.

**Ejemplos:** ExOS, Xok.

**Nanokernel:** Un nanokernel es un tipo de kernel extremadamente simple que solo proporciona los mecanismos más básicos para la sincronización y la gestión del hardware, delegando casi todas las demás funciones a los sistemas de nivel superior.

- **Ventajas:**
    - Extremadamente ligero: Reduce la sobrecarga del sistema.
    - Especialización: Permite la creación de sistemas operativos muy específicos.

- **Desventajas:**
    - Funcionalidad limitada: No gestiona directamente muchos aspectos esenciales del sistema.
    - Dificultad en la integración: Puede requerir mucho trabajo adicional para implementar funciones que son estándar en otros tipos de kernels.

**Ejemplos:** Los nanokernels no son comúnmente usados en sistemas generales, pero se emplean en sistemas altamente especializados.

Además de gestionar recursos y proporcionar servicios básicos, el kernel también juega un papel crucial en la seguridad del sistema. Implementa mecanismos de control de acceso, gestión de usuarios y protección contra amenazas como malware y ataques de seguridad. 

# User Mode vs Kernel Mode

## **¿Qué es el modo de usuario?**

Cuando se inicia un programa en un sistema operativo, digamos Windows, se inicia el programa en modo de usuario. Cuando un programa en modo de usuario solicita ejecutarse, Windows crea un proceso y un espacio de direcciones virtuales (espacio de direcciones para ese proceso). Los programas en modo de usuario tienen menos privilegios que las aplicaciones en modo de usuario y no pueden acceder a los recursos del sistema directamente. Por ejemplo, si una aplicación en modo usuario desea acceder a los recursos del sistema, primero deberá pasar por el kernel del sistema operativo mediante llamadas al sistema.  

## **¿Qué es el modo kernel?**

El núcleo es el programa central del que dependen todos los demás componentes del sistema operativo. Se utiliza para acceder a los componentes de hardware y programar qué procesos deben ejecutarse en un sistema informático y cuándo, y también administra la interacción entre el software de aplicación y el hardware. Por lo tanto, es el programa más privilegiado; a diferencia de otros programas, puede interactuar directamente con el hardware. Cuando los programas que se ejecutan en modo de usuario necesitan acceso al hardware, por ejemplo, una cámara web, primero deben pasar por el núcleo mediante una llamada al sistema y, para llevar a cabo estas solicitudes, la CPU cambia del modo de usuario al modo de núcleo en el momento de la ejecución. Después de completar finalmente la ejecución del proceso, la CPU vuelve a cambiar al modo de usuario .

## **Diferencia entre el modo de usuario y el modo kernel:**

**¿Cuáles son algunos ejemplos de operaciones que requieren el modo kernel?**

- Las operaciones que requieren el modo kernel incluyen control de memoria, programación de procesos, manejo de interrupciones de hardware e interacción directa con dispositivos de hardware.

**¿Cómo varía el acceso a la memoria entre el modo de usuario y el modo kernel?**
- En el modo de usuario, el acceso a la memoria está restringido para evitar que las aplicaciones interfieran entre sí o con el sistema operativo. En modo kernel, el sistema operativo tiene acceso ilimitado a todas las áreas de la memoria, lo que le permite controlar correctamente los recursos del dispositivo.

**¿Pueden las aplicaciones ejecutarse directamente en modo kernel?**
- Normalmente, las aplicaciones no se ejecutan directamente en modo kernel. La ejecución de programas en modo kernel puede plantear importantes problemas de seguridad y estabilidad.

# **Interruptions vs traps**

## ¿Que es Traps o Trampas?

El programa de usuario produce trampas para invocar la funcionalidad del sistema operativo. Supongamos que la aplicación del usuario requiere que se imprima algo en la pantalla, se activaría una trampa y el sistema operativo escribiría los datos en la pantalla.

Una trampa es una interrupción producida por software que puede ser causada por varios factores, incluido un error en la instrucción, como la división por cero o el acceso ilegal a la memoria. También se puede generar una trampa cuando un programa de usuario realiza una solicitud de servicio definitiva desde el sistema operativo.

Las trampas se denominan eventos sincrónicos porque es mucho más probable que la ejecución de las instrucciones presentes provoque trampas. Las llamadas al sistema son otro tipo de trampa en la que el programa le pide al sistema operativo que busque un determinado servicio y, posteriormente, el sistema operativo genera una interrupción para permitir que el programa acceda a los servicios. Las trampas son más activas como interrupción porque el código dependerá en gran medida del hecho de que la trampa pueda usarse para interactuar con el sistema operativo. Por lo tanto, las trampas repetirían la función de la trampa para acceder a cualquier servicio del sistema.

## Mecanismo de trampa en el sistema operativo

El programa de usuario de la CPU suele utilizar llamadas a la biblioteca para realizar llamadas al sistema. El trabajo de la verificación de rutina de la biblioteca es validar los parámetros del programa, crear una estructura de datos para transferir los argumentos de la aplicación al kernel del sistema operativo y luego ejecutar instrucciones especiales conocidas como trampas o interrupciones de software.

Estas instrucciones especiales o trampas tienen operandos que ayudan a determinar qué servicio del kernel requieren las entradas de la aplicación. Como resultado, cuando el proceso está configurado para ejecutar las trampas, la interrupción guarda el estado del código de usuario, cambia al modo supervisor y luego envía el procedimiento del núcleo relevante que puede ofrecer el servicio solicitado.

## ¿Qué es la interrupción?

Las interrupciones son señales emitidas por software o hardware cuando un proceso o evento requiere atención inmediata. Debido a que tanto el hardware como el software generan estas señales, se les denomina hardware y el software interrumpe. Un dispositivo de hardware produce una interrupción. Las interrupciones pueden deberse a un dispositivo USB, una tarjeta NIC o un teclado. Las interrupciones ocurren de forma asincrónica y pueden ocurrir en cualquier momento.

Un pin de interrupción es un pin dedicado en una CPU. También se le conoce como pin INT. El pin de interrupción conecta dispositivos como teclados al procesador. Cuando se hace clic en una tecla, se produce la interrupción. La CPU pasará del proceso actual a una rutina de manejo de interrupciones. En este caso, se está produciendo la rutina del controlador de interrupciones del teclado. Después de finalizar el código del controlador de interrupciones, la CPU regresa al programa original que se estaba ejecutando. Cuando llega una interrupción, la CPU cambia el contexto y ejecuta el controlador de interrupciones. Vuelve al estado anterior una vez finalizado.

La CPU tiene un único pin de interrupción, pero hay varios dispositivos de hardware. El controlador de interrupciones permite que varios pines compartan un único pin de interrupción. Para identificar qué dispositivo causó la interrupción, el procesador interactuaría con el controlador de interrupciones, ejecutando el procedimiento de manejo de interrupciones apropiado. Podría ser un método para manejar interrupciones del temporizador, USB o teclado.

## Mecanismo de interrupción en el sistema operativo

Veamos cómo funciona la interrupción. Se ejecutan varias instrucciones en un programa y el tiempo que tarda un programa en ejecutar una instrucción del programa se denomina ciclo de instrucción. Los dispositivos de I/O o los programas de usuario pueden generar interrupciones mientras la CPU está ejecutando las instrucciones del programa. Estas interrupciones se le pasarían como entrada mientras la CPU está ejecutando las instrucciones del programa.

El procesador administra las interrupciones verificando si hay una interrupción pendiente o no para realizar una acción después de cada ciclo de instrucción. Si la CPU no identifica ninguna interrupción pendiente, procederá a la siguiente instrucción del programa. Si la CPU identifica una interrupción pendiente, detendrá la ejecución de la instrucción e invocará el programa de manejo de interrupciones para atender la interrupción pendiente.

## Diferencias principales entre la trampa y la interrupción

1. La trampa es una señal emitida por un programa de usuario que indica al sistema operativo que realice alguna función inmediatamente. Por el contrario, la interrupción es una señal a la CPU emitida por el hardware que indica un evento que requiere atención inmediata.

2. Una trampa también activa la funcionalidad del sistema operativo. Le da control al controlador de trampas. Por el contrario, una interrupción activa la CPU para que realice la rutina del controlador de interrupciones.

3. Una trampa es sincrónica y puede ocurrir después de la ejecución de la instrucción. Por el contrario, una interrupción es asincrónica y puede ocurrir en cualquier momento.

4. Una trampa es generada por una instrucción del programa de usuario. Por el contrario, los dispositivos de hardware generan una interrupción.
   
5. Una trampa también se conoce como una interrupción de software. Por el contrario, una interrupción se conoce como una interrupción de hardware.

6. La trampa es un proceso sincrónico. Por el contrario, la interrupción es un proceso asincrónico.