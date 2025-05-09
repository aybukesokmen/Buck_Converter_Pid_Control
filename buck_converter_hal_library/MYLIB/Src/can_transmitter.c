#include "can_transmitter.h"
#include "stm32f4xx_hal.h"

// HAL'de tanımlı CAN handle
extern CAN_HandleTypeDef hcan1;

// Yardımcı dönüşüm: float → uint16 (0.01 çözünürlük)
static uint16_t FloatToRaw100(float val)
{
    return (uint16_t)(val * 100.0f);
}

void CAN_Transmitter_Init(void)
{
    // CAN init işlemi burada yapılabilir, genellikle main.c'de yapılır
    // Buraya özel bir işlem gerekirse eklenebilir
}

// Telemetri mesajı gönderir
void CAN_Transmitter_SendTelemetry(const SystemState_t *state, SystemCANState_t status)
{
    CAN_TxHeaderTypeDef txHeader;
    uint8_t txData[8];
    uint32_t txMailbox;

    // CAN ID: 0x555, standard ID
    txHeader.StdId = 0x555;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = 8;
    txHeader.TransmitGlobalTime = DISABLE;

    // Verileri DBC uyumlu sırayla koy
    uint16_t vout_raw = FloatToRaw100(state->vout);
    uint16_t iout_raw = FloatToRaw100(state->iout);
    uint16_t temp_raw = FloatToRaw100(state->temperature);

    txData[0] = (vout_raw >> 8) & 0xFF;
    txData[1] = (vout_raw) & 0xFF;

    txData[2] = (iout_raw >> 8) & 0xFF;
    txData[3] = (iout_raw) & 0xFF;

    txData[4] = (temp_raw >> 8) & 0xFF;
    txData[5] = (temp_raw) & 0xFF;

    txData[6] = (uint8_t)status;  // System enum
    txData[7] = 0x00;             // Reserved (boş)

    HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox);
}
