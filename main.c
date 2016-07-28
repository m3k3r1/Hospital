#include "hospital.h"

int main()
{
	int menu_op;

	menu_op = menu();
	switch(menu_op)
	{
    	case 1: save_file_info();
				show_info();
                break;
        case 2: printf("Função\n");
                break;
        case 3: printf("Função\n");
                break;
        case 4: printf("Função\n");
                break;
        case 5: return 0;
                break;
	}
    
}