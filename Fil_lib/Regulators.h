    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 02/08/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Configuration file Regulators
    */
#pragma once
#include "RCR_DevBoard_3_Setup.h"
#if(_configCALC_Regulators == 1)

    /*!
    *   @list P_Regulator Settings
    */
    typedef struct
    {
          float p_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float output; //��������, ��������� ������ �
          char p_on; //���/���� � ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
          char p_finish;
          float error_dir;
          float p_error_end;
          float p_output_end;
    }P_Regulator;

void init_P_Regulator(P_Regulator Regulator);

    /*!
    *   @list PI_Regulator Settings
    */
    typedef struct
    {
          float p_k; //� ����������
          float i_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float sum_error; //��������� ������ (��� � ����������)
          float max_sum_error; //������������ ��������� ������ (��� �� � ��������� �� ������ �� ��������� ���� ���������� �������� ���������� ��������)
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float cut_output;
          float output; //��������, ��������� ������ ��
          char pi_on; //���/���� �� ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
          char pi_finish;
          float error_dir;
          float pi_error_end;
          float pi_output_end;
    }PI_Regulator;

void init_PI_Regulator(PI_Regulator Regulator);

    /*!
    *   @list PID_Regulator Settings
    */
    typedef struct
    {
          float p_k; //� ����������
          float i_k; //� ����������
          float d_k; //� ����������
          float target; //������� ��������
          float current; //������� (���������� ��������� ����� ����� ������ ��������)
          float prev_error; //���������� �������� ������ (��� � ����������)
          float sum_error; //��������� ������ (��� � ����������)
          float max_sum_error; //������������ ��������� ������ (��� �� � ��������� �� ������ �� ��������� ���� ���������� �������� ���������� ��������)
          float max_output; //������������ �����, ��� �� �������� �� �������� �� �����
          float min_output;
          float cut_output;
          float output; //��������, ��������� ������ ���
          char pid_on; //���/���� ��� ���� ���� �� output ������ ����� 0, ������ ��� ��������� ���������� �������������
          char pid_finish;
          float error_dir;
          float pid_error_end;
          float pid_output_end;
    }PID_Regulator;

    float EnginePWM;
    PID_Regulator EngineReg;
    void init_PID_Regulator(void);

    void PID_Low_Level(void);

#endif /*_configCALC_Regulators*/
