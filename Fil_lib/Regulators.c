#include "Regulators.h"

#if (_configCALC_Regulators == 1)

void initRegulators(void)  // инициализация регуляторов
{
//PID Regulator settings________________________________________________________
  int i = 0;
  for (i = 0; i<=3; i++)  // пиды колес
  {
  	wheelsPidStruct[i].p_k = 2;
  	wheelsPidStruct[i].i_k = 0.295;
  	wheelsPidStruct[i].d_k = 0.18;
  	wheelsPidStruct[i].pid_on = 1;
  	wheelsPidStruct[i].pid_error_end  = 3;
  	wheelsPidStruct[i].pid_output_end = 1000;
  	wheelsPidStruct[i].max_sum_error = 10.0; //16.0;
  	wheelsPidStruct[i].max_output = 1;
  	wheelsPidStruct[i].min_output = 0.01;
  }

#endif /*_configCALC_Regulators*/
