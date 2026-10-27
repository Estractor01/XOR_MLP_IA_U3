#include <stdio.h>
#include "MLP.h"
#include "esp_log.h"

static const char *TAG = "Neuron";

double w01 = -7.3870172501;
double w11 = 15.9740314484;
double w12 = 15.4625444412;
double w02 = -22.9216899872;
double w21 = 15.1479005814;
double w22 = 15.1510715485;
double w03 = -8.5453147888;
double v1  = 17.0284881592;
double v2  = -16.7011604309;


/* FUNCI�N ESCAL�N CON UMBRAL CERO */
static int escalon(double entrada_neta)
{
    if (entrada_neta >= 0.0)
        return 1;
    else
        return 0;
}

void process(bool IN1, bool IN2)
{
    double u1;
    double u2;
    double u3;

    int h1;
    int h2;
    int salida;

    ESP_LOGI(TAG, "RED NEURONAL XOR");
    ESP_LOGI(TAG, "FUNCION ESCALON CON UMBRAL CERO");

    /* NEURONA OCULTA 1 */
    u1 = w01 + w11*IN1 + w12*IN2;
    h1 = escalon(u1);

    /* NEURONA OCULTA 2 */
    u2 = w02 + w21*IN1 + w22*IN2;
    h2 = escalon(u2);

    /* NEURONA DE SALIDA */
    u3 = w03 + v1*h1 + v2*h2;
    salida = escalon(u3);

    ESP_LOGI(TAG,
        "Entrada: %d %d | "
        "Salida: %d\n",
        IN1,
        IN2,
        salida
    );
}

