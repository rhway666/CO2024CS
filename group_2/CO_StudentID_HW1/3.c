#include<stdio.h>
int main()
{ 
    int f, i, j;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/3.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    int *p_x = &x[0] ;
    int *p_h = &h[0] ;
    int *p_y = &y[0] ;
    for (i = 0; i < 3; i++){ 
        for (j = 0; j < 2; j++){        	
            for (f = 0; f < 3; f++)
                asm volatile(
                    // read x[f][j]
                    "slli   t1, %[f], 1 \n"
                    "add    t1, t1, %[j] \n"
                    "slli   t1, t1, 2 \n"
                    "add    t1, t1, %[p_x] \n"
                    "lw     t4, 0(t1) \n"

                    // read h[i][f]
                    "slli   t2, %[i], 1 \n"
                    "add    t2, t2, %[i] \n"
                    "add    t2, t2, %[f] \n"
                    "slli   t2, t2, 2 \n"
                    "add    t2, t2, %[p_h] \n"
                    "lw     t5, 0(t2) \n"

                    // multilication
                    "mul    t6, t4, t5 \n"
                    
                    // read y[i][j]
                    "slli   t0, %[i], 1 \n"
                    "add    t0, t0, %[j] \n"
                    "slli   t0, t0, 2 \n"
                    "add    t0, t0, %[p_y] \n"
                    "lw     a0, 0(t0) \n"

                    // write y[i][j]
                    "add    a0, a0, t6 \n"
                    "sw     a0, 0(t0) \n"

                    : [p_y]"+r"(p_y)
                    : [i]"r"(i), [j]"r"(j), [f]"r"(f), [p_h]"r"(p_h), [p_x]"r"(p_x)
                    :
                );
    }
    }
    p_y = &y[0];
    for(i = 0; i < 6; i++)
    printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
