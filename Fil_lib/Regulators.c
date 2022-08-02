    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Regulators source file
    */
#include "FilConfig.h"

#if (_configCALC_Regulators == 1)
#include "Regulators.h"

/*!
*   @code PID Regulator Sector
*/
PID_Regulator EngineReg;
float EnginePWM = 0.0;
void init_PID_Regulator(void)  // инициализация регуляторов
{

  	EngineReg.p_k = 1.0;
  	EngineReg.i_k = 0.0;
  	EngineReg.d_k = 0.0;
  	EngineReg.pid_on = 1;
  	EngineReg.pid_error_end  = 5;
  	EngineReg.pid_output_end = 1000;
  	EngineReg.max_sum_error = 10.0;
  	EngineReg.max_output = 1.0;
  	EngineReg.min_output = 0.01;

}

static void PID_Calc(PID_Regulator *pid_control)
{
  float error, dif_error;
  error = pid_control->target - pid_control->current;
  dif_error = error - pid_control->prev_error;
  pid_control->prev_error = error;
  pid_control->sum_error += error;

  if (pid_control->sum_error > pid_control->max_sum_error)
    pid_control->sum_error = pid_control->max_sum_error;
  if (pid_control->sum_error < -pid_control->max_sum_error)
    pid_control->sum_error = -pid_control->max_sum_error;

  if (pid_control->pid_on)
  {
    pid_control->output = ((float)(pid_control->p_k * error)+(pid_control->i_k * pid_control->sum_error)+
            (pid_control->d_k * dif_error));

    if (pid_control->output > pid_control->max_output)
      pid_control->output = pid_control->max_output;
    else if (pid_control->output < -pid_control->max_output)
      pid_control->output = -pid_control->max_output;

    if (pid_control->output < pid_control->min_output && pid_control->output > -pid_control->min_output)
      pid_control->output = 0;

    if ((pid_control->output <= pid_control->pid_output_end) &&(
        pid_control->output >= -pid_control->pid_output_end) &&(
        error <= pid_control->pid_error_end) && (error >= -pid_control->pid_error_end))
      pid_control->pid_finish = 1;
    else
      pid_control->pid_finish = 0;
  }
  else
  {
    pid_control->output = 0;
    pid_control->pid_finish = 0;
  }
}

static void PID_Parse_EncoderData(int32_t encoderdata)
{



}


/*!
*   @brief PID_Low_Level(int32_t input) - General PID calculating engine
*/
void PID_Low_Level(void)
{
    if(EnginePWM > 1.0) EnginePWM = 1.0;
    if(EnginePWM < -1.0) EnginePWM = -1.0;
    EngineReg.target = EnginePWM;
    PID_Parse_EncoderData(*ENCODER1_CNT);
    *ENCODER1_CNT = 0;
    PID_Calc(&EngineReg);
    //SetVoltage(EngineReg.output);
}

#endif /*_configCALC_Regulators*/
