#include "main.h"
#include "dtb.h"
#include "apt.h"

int main()
{
        int menu_op = 0;
        struct medico *head_m = NULL;
        struct paciente *head_p = NULL;
        struct consulta *head_c = NULL;
        struct marcacao *head_apt = NULL;

        dump_med(&head_m);
        dump_pac(&head_p, &head_c);

	       do
        {
                menu_op = menu();
                switch(menu_op)
	               {
    	                case 1:  show_info(head_m, head_p, head_c);
                                      break;
                        case 2: med_by_spec(head_m);
                                      break;
                        case 3: pac_by_spec(head_p, head_c, head_m);
                                      break;
                        case 4: pac_by_t(head_p, head_c);
                                      break;
                        case 5:  check_schdl(head_m);
                                        break;
                        case 6: make_appointment(head_m, head_apt);
                                      break;
                        case 7: free_mem(head_m, head_p, head_c);
                                      daily_save(&head_apt, head_p, head_c);
                                      return 0;
                                      break;
	                }
        }while(1);
	return 0;
}
