# Galaga Invertido - Proyecto Final

Este proyecto es una implementación del juego " Space invaders" desarrollado en C++ utilizando la biblioteca SFML y Box2D. El desarrollo se realiza sobre MinGW64 utilizando Msys2 y Visual Studio Code.

---

## 📋 Tabla de Contenidos
1. [Estado Actual](#estado-actual)
2. [Instrucciones de Juego](#instrucciones-de-juego)
3. [Prerrequisitos](#prerrequisitos)
4. [Cómo Ejecutar](#cómo-ejecutar)
5. [Solución de Problemas](#solución-de-problemas)
6. [Estructura y Cambios](#estructura-y-cambios)
7. [Buenas Prácticas y Recursos](#buenas-prácticas-y-recursos)
8. [Pendientes (TODO)](#pendientes-todo)

---

## 🚀 Estado Actual <a name="estado-actual"></a>

El juego se encuentra **COMPLETAMENTE FUNCIONAL** con las siguientes características:

*   ✅ **Menú de Inicio**: Pantalla de bienvenida con instrucciones.
*   ✅ **Juego Principal**: 
    *   Nave del jugador controlable.
    *   Enemigos con movimiento horizontal (IA básica).
    *   Estructuras de protección destructibles.
    *   Sistema de disparos y colisiones.
    *   Puntuación y vidas (3 vidas iniciales).
    *   Condiciones de Victoria (destruir todos los enemigos) y Derrota (perder vidas).
*   ✅ **Estabilidad**: Se han corregido bugs de "Game Over" inmediato y problemas de renderizado.

---

## 🎮 Instrucciones de Juego <a name="instrucciones-de-juego"></a>

### Objetivo
**¡Destruye todos los enemigos antes de que te destruyan a ti!**
Acumula puntos por cada enemigo eliminado y utiliza las estructuras para protegerte de sus disparos.

### Controles

| Acción | Tecla |
| :--- | :--- |
| **Mover Izquierda** | `Flecha Izquierda (←)` |
| **Mover Derecha** | `Flecha Derecha (→)` |
| **Disparar** | `ESPACIO` |
| **Iniciar Juego** | `ENTER` (en el Menú) |
| **Reiniciar** | `R` (en Game Over) |
| **Salir al Menú** | `ESC` (en Game Over) |

---

## 🛠️ Prerrequisitos <a name="prerrequisitos"></a>

Antes de compilar, asegúrate de tener configurado el entorno:

*   [Instalar las herramientas necesarias](./docs/herramientas.md)
*   [Instalar las Extensiones VSCode](./docs/extensiones.md)
*   [Instalar las librerias](./docs/librerias.md)
*   [Clonar el repositorio](./docs/fork.md)

---

## 💻 Cómo Ejecutar <a name="cómo-ejecutar"></a>

Existen varios métodos para ejecutar el juego, desde el más sencillo hasta la compilación manual.

### Método 1: Archivo Batch (Recomendado / Más Fácil)
1. Navega a la carpeta `EjemplosJuego`.
2. Haz **doble clic** en el archivo `compilar_y_ejecutar.bat`.
   * _Este script compilará y ejecutará el juego automáticamente._

### Método 2: Usando Make (Terminal VSCode)
Si prefieres usar la terminal integrada de Visual Studio Code:
1. Abre la terminal en la carpeta `EjemplosJuego`.
2. Ejecuta el siguiente comando:
   ```bash
   make runJuegoProyecto252
   ```
   *(Nota: Asegúrate de que el Makefile esté configurado correctamente para este target).*

### Método 3: Compilación Manual (PowerShell)
Si necesitas recompilar manualmente:
1. Abre una terminal (PowerShell o CMD).
2. Navega a la carpeta del proyecto:
   ```powershell
   cd "ruta/a/EjemplosJuego"
   ```
3. Compila con g++:
   ```powershell
   g++ src/JuegoProyecto252.cpp -o bin/JuegoProyecto252.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude
   ```
4. Ejecuta:
   ```powershell
   ./bin/JuegoProyecto252.exe
   ```

---

## 🔧 Solución de Problemas <a name="solución-de-problemas"></a>

### Errores Comunes

**1. El juego se cierra o muestra "Game Over" inmediatamente:**
*   **Solución:** Asegúrate de estar ejecutando la versión más reciente (`JuegoProyecto252`). Versiones anteriores tenían un bug donde los enemigos tocaban el borde inferior muy rápido.
*   Recompila el proyecto (`make clean` seguido de `make...` o borra el `.exe` y recompila).

**2. No veo mi nave o las texturas:**
*   **Causa:** El ejecutable no encuentra la carpeta `assets`.
*   **Solución:** Asegúrate de ejecutar el juego desde la carpeta `EjemplosJuego`. Si ejecutas desde `bin/`, el programa buscará `assets` dentro de `bin/` y fallará. Siempre ejecuta desde la raíz del proyecto: `./bin/JuegoProyecto252.exe`.

**3. "No rule to make target":**
*   Verifica que el nombre del archivo en el comando `make` coincida con el target en el `makefile`.

**4. Los diagramas PUML no se ven:**
*   Revisa la sección de [Instalar Herramientas](./docs/herramientas.md) para configurar Java y Graphviz.

---

## 📂 Estructura y Cambios <a name="estructura-y-cambios"></a>

### Cambios Implementados Recientemente
*   **Sistema de Menú:** Se agregó un estado `MENU` inicial.
*   **Corrección de Bugs:** 
    *   Arreglado el Game Over inmediato.
    *   Inicialización correcta de enemigos.
    *   Lógica de victoria corregida (ahora requiere destruir enemigos).
*   **Mecánicas:** Movimiento de enemigos simplificado a horizontal para mejor jugabilidad.

---

## 📚 Buenas Prácticas y Recursos <a name="buenas-prácticas-y-recursos"></a>

### Guías de Desarrollo
*   [Cómo crear un buen README](https://www.makeareadme.com/)
*   [Patrones de diseño](https://refactoring.guru/es/design-patterns)
*   [Cómo hacer commits semánticos]()
*   [Cómo estructurar un proyecto]()
*   [Tipos de licencias]()

### Tutoriales Github
*   [Creación de un repositorio]()
*   [Cómo colaborar en un proyecto]()
*   [Solicitar GitHub Student Developer Pack]()

### Recursos Gratuitos
*   [Fuentes de texto (DaFont)](https://www.dafont.com/es/)
*   [Recursos de Videojuegos (OpenGameArt)](https://opengameart.org/)

---

## ✅ Pendientes (TODO) <a name="pendientes-todo"></a>

*   [ ] Agregar explicación de qué es el PATH.
*   [ ] Cómo activar autosave en VSCode.
*   [ ] Configurar perfil por defecto en terminal.
*   [ ] Documentar creación de repositorios y colaboración.
*   [ ] Guía para solicitar el Developer Pack.
*   [ ] Tutorial de instalación de Java para PlantUML.
*   [ ] Guía de diagramas de clases.
*   [ ] Agregar curso básico de navegación en código.
*   [ ] Enlazar videos de proyectos pasados.
*   [ ] Guía de formato y estilo de código.
