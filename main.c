#include "hospital.h"

int main()
{
        int menu_op;
        
	menu_op = menu();
	switch(menu_op)
	{
    	case 1: dump_database();
                show_info();
                break;
        case 2: dump_database();
                med_by_spec();
                break;
        case 3: dump_database();
                pac_by_spec();
                break;
        case 4: printf("Função\n");
                break;
        case 5: free(head_m);
                free(head_p);
                free(head_c); 
                return 0;
                break;
	}
	return 0;
}