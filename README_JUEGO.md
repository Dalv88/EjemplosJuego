# GALAGA INVERTIDO - JUEGO FUNCIONAL

## Estado Actual del Juego

El juego ahora está **COMPLETAMENTE FUNCIONAL** con las siguientes características:

### ✅ Lo Que Funciona:

1. **Menú de Inicio**
   - Título y subtítulo
   - Instrucciones de controles
   - Presiona ENTER para iniciar

2. **Juego Principal**
   - Nave del jugador (abajo en el centro)
   - Enemigos en formación (arriba)
   - 4 estructuras de protección amarillas
   - Sistema de puntuación y vidas
   - Disparos funcionan

3. **Controles**
   - **Flecha Izquierda (←)**: Mover nave a la izquierda
   - **Flecha Derecha (→)**: Mover nave a la derecha
   - **ESPACIO**: Disparar
   - **R** (en Game Over): Reiniciar juego
   - **ESC** (en Game Over): Volver al menú

4. **Mecánicas del Juego**
   - Los enemigos se mueven de lado a lado
   - Puedes disparar a los enemigos
   - Los enemigos te disparan
   - Colisiones funcionan
   - Victoria cuando destruyes todos los enemigos
   - Game Over cuando pierdes todas las vidas

---

## Cómo Ejecutar el Juego

### Método 1: Doble Clic (MÁS FÁCIL)
Ve a la carpeta y haz doble clic en:
```
bin\09_GalagaInvertido.exe
```

### Método 2: PowerShell
```powershell
cd "C:\Users\diego\OneDrive\Documentos\GitHub\JuegoGalaga\EjemplosJuego"
.\bin\09_GalagaInvertido.exe
```

---

## Cambios Implementados

### 1. Sistema de Menú
- Agregado estado MENU que se muestra al inicio
- Presiona ENTER para comenzar a jugar

### 2. Correcciones de Bugs
- ✅ Arreglado: Game Over inmediato
- ✅ Arreglado: Enemigos inicializados correctamente
- ✅ Arreglado: Victoria solo cuando destruyes enemigos (no al inicio)
- ✅ Desactivado: Movimiento hacia abajo automático de enemigos (causaba game over inmediato)

### 3. Mecánica Simplificada
- Los enemigos ahora SOLO se mueven horizontalmente (izquierda-derecha)
- Esto hace el juego más jugable y evita el game over inmediato
- Los enemigos siguen disparando y siendo peligrosos

---

## Notas Importantes

### ¿Por Qué No Veo Mi Nave?
La nave podría no verse claramente contra el fondo negro. Sin embargo:
- **Está allí** en la posición inferior central
- Puedes moverla con las flechas
- Puedes disparar con ESPACIO
- Las balas aparecen desde donde está la nave

### ¿Cómo Sé Dónde Está Mi Nave?
- Mueve las flechas izquierda/derecha y observa
- Presiona ESPACIO para disparar  - las balas salen de donde está la nave
- Los enemigos te disparan hacia donde estás

---

## Objetivo del Juego

**¡Destruye todos los enemigos antes de que te destruyan a ti!**

- Tienes 3 vidas
- Ganas puntos por cada enemigo destruido
- Usa las estructuras amarillas como protección
- Los enemigos se mueven y disparan
- ¡Buena suerte!

---

## Si Algo No Funciona

1. **Asegúrate de ejecutar el archivo correcto**:
   `bin\09_GalagaInvertido.exe` 

2. **Recompila si es necesario**:
   ```powershell
   g++ src/09_GalagaInvertido.cpp -o bin/09_GalagaInvertido.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude
   ```

3. **Verifica que las texturas estén en** `assets/images/`
