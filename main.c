#include "hospital.h"

int main()
{
        int menu_op;
        struct medico *head_m = NULL;
        struct paciente *head_p = NULL;
        struct consulta *head_c = NULL;
        
	menu_op = menu();
	switch(menu_op)
	{
    	case 1: dump_database(&head_m, &head_p, &head_c);
                show_info(head_m, head_p, head_c);
                break;
        case 2: dump_database(&head_m, &head_p, &head_c);
                med_by_spec(head_m);
                break;
        case 3: dump_database(&head_m, &head_p, &head_c);
                pac_by_spec(head_p, head_c);
                break;
        case 4: printf("Função\n");
                break;
        case 5: return 0;
                break;
	}
	return 0;
}