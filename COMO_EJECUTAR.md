# ¡IMPORTANTE! - Cómo Ejecutar el Juego

## Método 1: Usar el Archivo Batch (MÁS FÁCIL)

1. Ve a la carpeta del proyecto:
   ```
   C:\Users\diego\OneDrive\Documentos\GitHub\JuegoGalaga\EjemplosJuego
   ```

2. Haz **doble clic** en el archivo: `compilar_y_ejecutar.bat`

¡Eso es todo! El archivo batch se encargará de compilar y ejecutar el juego.

---

## Método 2: Desde la Terminal PowerShell

1. Abre PowerShell (Windows + X, luego selecciona "Windows PowerShell")

2. Navega a la carpeta del proyecto:
   ```powershell
   cd "C:\Users\diego\OneDrive\Documentos\GitHub\JuegoGalaga\EjemplosJuego"
   ```

3. Compila el juego:
   ```powershell
   g++ src/09_GalagaInvertido.cpp -o bin/09_GalagaInvertido.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude
   ```

4. Ejecuta el juego:
   ```powershell
   ./bin/09_GalagaInvertido.exe
   ```

---

## ¿Qué Deberías Ver?

### 1. Pantalla de Menú (al iniciar)
- Título "GALAGA INVERTIDO" en azul cyan
- Subtítulo "Humanos Atacan!"
- Instrucciones de controles
- Mensaje "Presiona ENTER para iniciar"

### 2. Al Presionar ENTER
- La pantalla del juego aparece
- Tu nave está abajo en el centro
- Los enemigos están arriba en formación
- Las estructuras de protección están en el medio
- Puedes moverte con las flechas
- Puedes disparar con ESPACIO

### 3. Controles del Juego
- **←** (Flecha Izquierda): Mover nave a la izquierda
- **→** (Flecha Derecha): Mover nave a la derecha
- **ESPACIO**: Disparar
- **R** (en Game Over): Reiniciar juego
- **ESC** (en Game Over): Volver al menú

---

## Si Sigue Sin Funcionar

1. Asegúrate de cerrar TODAS las ventanas del juego antes de compilar de nuevo
2. Ejecuta estos comandos en PowerShell:
   ```powershell
   cd "C:\Users\diego\OneDrive\Documentos\GitHub\JuegoGalaga\EjemplosJuego"
   rm bin/09_GalagaInvertido.exe
   g++ src/09_GalagaInvertido.cpp -o bin/09_GalagaInvertido.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude
   ./bin/09_GalagaInvertido.exe
   ```

3. Si te sigue apareciendo Game Over inmediatamente, toma una captura de pantalla y compártela.

---

## Bug Corregido

**Problema**: El juego mostraba "GAME OVER" inmediatamente al presionar ENTER.

**Causa**: La condición de victoria `if (enemigos.empty())` se activaba porque el vector empezaba vacío.

**Solución**: Ahora se verifica `if (enemigos.empty() && puntuacion > 0)`, así solo se considera victoria cuando realmente has destruido enemigos.
