#include "deviceloop.h"
#include "sensor_converter.h"
#include "control_pid_regulator.h"
#include "protocol.h"
#include "saykal_io.h"
#include "f303_Init.h"

extern uint16_t a_adc1_data_u16[4];
extern PID_Controller_t pid_controller;

SystemState_t s_sys_state = {0};
SystemCANState_t s_can_state = SYS_STATE_IDLE;
e_state_t state = INIT;

void sensor_monitoring(){
    s_sys_state.vout = Sensor_ConvertToVoltage(a_adc1_data_u16[0]);
    s_sys_state.iout = Sensor_ConvertToCurrent(a_adc1_data_u16[1]);
    s_sys_state.temperature = Sensor_ConvertToVoltage(a_adc1_data_u16[2]);
}

void DeviceMainLoop(void)
{
    switch(state)
    {
        case INIT:
            // Donanım başlatma
            gpio_init();
            adc1_init();
            tim1_init();
            tim4_init();
            can_receiver_init();
            can_transmitter_init();

            // PID başlangıç parametreleri
            PID_Init(&pid_controller, 0.5f, 0.1f, 0.01f, 0.0001f, 0.0f, 0.95f);
            s_sys_state.vout_target = 24.0f; // Hedef voltaj 24V

            state = MODE_EN;
            break;

        case MODE_EN:
            // Sensör ve girişleri oku
            sensor_monitoring();
            saykal_io_monitoring();
            saykal_io_toggle_status_led(5000); // Yavaş yanıp sönen LED

            // Enable koşulu (örneğin bir buton kontrolü)
            if(s_inputs.a_service_enable_b[0]) {
                state = CONTROL;
            }
            break;

        case CONTROL:
            // Sensör ve girişleri oku
            saykal_io_monitoring();
            sensor_monitoring();

            // Başlangıç kontrolü yap
            if(s_sys_state.vout > 5.0f) { // Minimum başlama voltajı
                state = RUN;
            }
            break;

        case RUN:
            // 1. Sensör ve girişleri oku
            saykal_io_monitoring();
            sensor_monitoring();

            // 2. PID ile duty hesapla
            s_sys_state.pwm_duty = PID_Update(&pid_controller,
                                            s_sys_state.vout_target,
                                            s_sys_state.vout);

            // 3. Aşırı akım kontrolü
            if (s_sys_state.iout > 10.0f) {
                s_sys_state.overcurrent = 1;
                s_can_state = SYS_STATE_OVERCURRENT;
                saykal_io_set_fault_led(true);
                state = FAULT;
            } else {
                s_sys_state.overcurrent = 0;
                s_can_state = SYS_STATE_RUNNING;
                saykal_io_set_fault_led(false);

                // PWM çıkışını güncelle
                TIM1->CCR1 = (uint16_t)(s_sys_state.pwm_duty * TIM1->ARR);
            }

            // 4. Telemetriyi CAN ile gönder
            protocol_init(&s_sys_state, s_can_state);
            break;

        case FAULT:
            // PWM çıkışını sıfırla
            TIM1->CCR1 = 0;

            // Reset butonunu bekle
            if(s_inputs.a_service_enable_b[1]) {
                pid_controller.integral = 0; // Integral terimini sıfırla
                state = INIT;
            }
            break;

        default:
            state = INIT;
            break;
    }
}
