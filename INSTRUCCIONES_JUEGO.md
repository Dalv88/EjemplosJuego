# Instrucciones para Ejecutar Galaga Invertido

## Pasos para compilar y ejecutar:

### Opción 1: Usar Make (Recomendado)
```bash
# 1. Limpiar archivos anteriores
make clean

# 2. Compilar y ejecutar
make run09_GalagaInvertido
```

### Opción 2: Compilación Manual
```bash
# 1. Eliminar ejecutable viejo
rm bin/09_GalagaInvertido.exe

# 2. Compilar
g++ src/09_GalagaInvertido.cpp -o bin/09_GalagaInvertido.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude

# 3. Ejecutar
./bin/09_GalagaInvertido.exe
```

## Controles del Juego:

### En el Menú Principal:
- **ENTER**: Iniciar el juego

### Durante el Juego:
- **Flecha Izquierda (←)**: Mover nave hacia la izquierda
- **Flecha Derecha (→)**: Mover nave hacia la derecha
- **ESPACIO**: Disparar

### En la Pantalla de Game Over:
- **R**: Reiniciar el juego
- **ESC**: Volver al menú principal

## Solución de Problemas:

Si el juego sigue mostrando "Game Over" al iniciar:

1. **Asegúrate de compilar de nuevo**:
   ```bash
   rm bin/09_GalagaInvertido.exe
   make bin/09_GalagaInvertido.exe
   ```

2. **Verifica que estás ejecutando el archivo correcto**:
   El ejecutable debe estar en: `bin/09_GalagaInvertido.exe`

3. **Verifica la fecha de modificación**:
   ```bash
   ls -l bin/09_GalagaInvertido.exe
   ```
   La fecha debe ser reciente (hoy).
