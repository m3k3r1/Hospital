#include "hospital.h"

int main()
{
        int menu_op = 0;
        struct medico *head_m = NULL;
        struct paciente *head_p = NULL;
        struct consulta *head_c = NULL;
        
	do
        {
                menu_op = menu();
                switch(menu_op)
	        {
    	                case 1: show_all(head_m, head_p, head_c);
                                break;
                        case 2: search_med(head_m, head_p, head_c);
                                break;
                        case 3: pac_by_speciality(head_m, head_p, head_c);
                                break;
                        case 4: pac_by_time(head_m, head_p, head_c);
                                break;
                        case 5: med_now(head_m, head_p, head_c);
                                break;
                        case 6: make_appointment();
                                break;
                        case 7: return 0;
                                break;
	        }
        }while(1);
	return 0;
}