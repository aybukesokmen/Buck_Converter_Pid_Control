#include "isr.h"
#include "can_receiver.h"
#include "deviceloop.h"
#include "control_pid_regulator.h"
#include "sensor_converter.h"
#include "f303_Init.h"


can_rx_msg_t s_can_rx_msg;
e_state_t system_state;
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR &= ~TIM_SR_UIF;
        if (system_state == RUN) {
            s_sys_state.vout = Sensor_ConvertToVoltage(a_adc1_data_u16[0]);
            s_sys_state.iout = Sensor_ConvertToCurrent(a_adc1_data_u16[1]);
            s_sys_state.pwm_duty = PID_Update(&pid_controller, s_sys_state.vout_target, s_sys_state.vout);
            if (s_sys_state.iout > 10.0f) {
                s_sys_state.pwm_duty = 0.0f;
                system_state = FAULT;
                s_can_state = SYS_STATE_OVERCURRENT;
                //saykal_io_set_fault_led(true);
            }
            TIM1->CCR1 = (uint16_t)(s_sys_state.pwm_duty * TIM1->ARR);
        }
    }
}

void USB_LP_CAN_RX0_IRQHandler(void)
{
    if (CAN->RF0R & CAN_RF0R_FMP0) {
        can_read_msg(&s_can_rx_msg);
        CAN->RF0R |= CAN_RF0R_RFOM0;
        can_receive_callback(&s_can_rx_msg);
    }
}
