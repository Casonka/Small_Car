    /*!
    *   --------------------------------------------------------------------------
    *                       ///Regulators\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin, Caska
    *   @date 18/07/2022 - last update version Regulators
    *
    *       @note [RCR:Regulators] Configuration file Regulators
    */
#if(_configCALC_Regulators == 1)
    /*!
    *   @list P_Regulator Configuration
    */
    struct
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
    }Regulator;

    void P_Calc(Regulator *P_control);
#elif (_configCALC_Regulators == 2)
    /*!
    *   @list PI_Regulator Configuration
    */
    struct
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
    }Regulator;

    void PI_Calc(Regulator *PI_control);
#elif (_configCALC_Regulators == 3)
    /*!
    *   @list PID_Regulator Configuration
    */
    struct
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
    }Regulator;

    void PID_Calc(Regulator *PID_control);
#endif /*_configCALC_Regulators*/
