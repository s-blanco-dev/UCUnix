# Configuración del Kernel

El kernel está compilado para permitir el arranque de un sistema básico usando `initramfs`, y ejecutar un programa `init` propio junto con algunas utilidades básicas provistas por `busybox`.

## Características principales habilitadas

- **/proc**: El sistema de archivos `/proc` está habilitado. Esto permite que el espacio de usuario pueda consultar información del kernel, como procesos, memoria, dispositivos, etc. Permite ejecutar `top`.
- **Initramfs**: El kernel puede cargar un filesystem inicial desde RAM (`initramfs`).
- **Terminal básica (TTY)**: Hay soporte para la consola básica (`tty`).
- **Soporte para logs del kernel**: El kernel guarda logs sobre su que pueden verse con `dmesg`.

Esto es suficiente para que el sistema arranque y se pueda ejecutar un shell mínimo, como `usdSh`.

## Características desactivadas

## ❌ Montaje de /sys desactivado

- El kernel no tiene activado el soporte para el sistema de archivos `/sys`.
- `/sys` contiene información sobre los dispositivos del sistema y es necesario para herramientas como `udev`.
- Como consecuencia, no es posible montar `/sys`, y algunas aplicaciones modernas del espacio de usuario no funcionarían.

## ❌ Creación automática de dispositivos en /dev

- El kernel no crea automáticamente archivos de dispositivo en `/dev`.
- Esto implica que si se quiere acceder, por ejemplo, a la consola o a un disco, los nodos correspondientes deben ser creados manualmente o con una herramienta como `mdev`.

## ❌ Sin terminales virtuales ni cambio entre TTYs

- No hay soporte para varias consolas (`tty1`, `tty2`, etc.).
- No se puede cambiar de terminal con `Alt + F1`, `Alt + F2`, etc.
- Limita el sistema a una única consola básica visible.

## ❌ Sin pseudoterminales

- El kernel no permite crear pseudoterminales (`/dev/pts`), que son necesarios para sesiones como `ssh`, `screen` o múltiples shells.
- Significa que el sistema es **MONOSESIÓN**

## ❌ Sin módulos

- No se pueden cargar ni descargar módulos del kernel de forma dinámica.
- Todos los drivers y funcionalidades deben estar compilados directamente dentro del kernel.

## ❌No soporta multiusuario 

- No hay archivos `/etc/passwd` o `login`, ni soporte para más de una sesión.
- Por lo tanto, el sistema es estrictamente **monousuario** y **monosesión**: se inicia directamente con el proceso `init` y una shell, sin necesidad de autenticación ni inicio de sesión.
