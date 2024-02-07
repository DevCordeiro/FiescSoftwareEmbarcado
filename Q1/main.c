#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

float temperatura = 25.0;

SemaphoreHandle_t mutex;

float celsius_para_fahrenheit(float celsius) {
    return (celsius * 9 / 5) + 32;
}

// Tarefa 1: leia a variável compartilhada, adicione 1.5 °C ao seu valor, imprima o resultado na serial com uma frequência de 1 Hz e salve a variável com seu novo valor
void task1(void* pvParameters) {
    while (1) {
        // Adquirir o mutex
        xSemaphoreTake(mutex, portMAX_DELAY);
        temperatura += 1.5;

        printf("Temperatura atualizada: %.2f °C\n", temperatura);

        xSemaphoreGive(mutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Tarefa 2: leia a variável compartilhada, converta seu valor para Fahrenheit, imprima o resultado na serial com uma frequência de 2 Hz e salve a variável com seu novo valor
void task2(void* pvParameters) {
    while (1) {
        xSemaphoreTake(mutex, portMAX_DELAY);
        float temp_celsius = temperatura;
        float temp_fahrenheit = celsius_para_fahrenheit(temp_celsius);

        printf("Temperatura em Fahrenheit: %.2f °F\n", temp_fahrenheit);

        xSemaphoreGive(mutex);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main() {
    mutex = xSemaphoreCreateMutex();

    xTaskCreate(task1, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(task2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    vTaskStartScheduler();

    return 0;
}