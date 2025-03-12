// Motor NEMA STM32 MBED


// RPM = 60/tiempo microsegundos*pasos vuelta ejemplo:   60/0.00004*400=375 RPM
// DIR- PUL- y ENABLE - a GND los demas son pines digitales.

#include "mbed.h"

// Definir pines
DigitalOut dirpin(PC_3); // Pines de dirección
DigitalOut steppin(PC_2); // Pines de pasos
DigitalOut enable(PH_1); // Pin de habilitación

// Variables para velocidad y vueltas
int velocidad; // En microsegundos entre pasos
int vueltas;   // Número de vueltas que quieres dar
int pasos_por_vuelta = 400; // Ajustar según el motor

void setup() {
    // Configuración inicial
    enable = 1; // Habilitar el motor

    // Ajustar la velocidad y número de vueltas
    velocidad = 400;  // Puedes modificar este valor para cambiar la velocidad
    vueltas = 10;    // Cambia este valor para ajustar el número de vueltas
}

void mover_motor(bool direccion, int total_pasos) {
    // Configuración de dirección
    dirpin = direccion;

    for (int i = 0; i < total_pasos; i++) {
        steppin = 0;
        wait_us(velocidad);
        steppin = 1;
        wait_us(velocidad);
    }
}

int main() {
    setup();
    
    int total_pasos = vueltas * pasos_por_vuelta; // Calcular el total de pasos

    while (true) {
        // Rotación en sentido horario
        mover_motor(1, total_pasos);
        thread_sleep_for(100); // Pausa de 100 ms

        // Rotación en sentido antihorario
        mover_motor(0, total_pasos);
        thread_sleep_for(100); // Pausa de 100 ms
    }
}
