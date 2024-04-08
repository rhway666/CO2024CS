#include<stdio.h>
int main()
{ 
    int i = 0;
    int h[9] = {0}, x[6] = {0}, y[6] = {0}; 
    FILE *input = fopen("../input/4.txt", "r");
    for(i = 0; i < 9; i++) fscanf(input, "%d", &h[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &x[i]);
    for(i = 0; i < 6; i++) fscanf(input, "%d", &y[i]);
    fclose(input);
    
    int *p_x = &x[0];
    int *p_h = &h[0];
    int *p_y = &y[0];
    //  for (i = 0; i < 3; i++){ 
        // for (j = 0; j < 2; j++){        	
        //     for (f = 0; f < 3; f++) 
    asm volatile(/*Your code*/
        // s4, s5, s6: array sizes
        // s1, s2, s3: indices
        "li     s4, 3 \n"
        "li     s5, 2 \n"
        "li     s6, 3 \n"

        "li     s1, 0 \n"
        "bge    s1, s4, loop1_end \n"
        "loop1_start: \n"

        "li     s2, 0 \n"
        "bge    s2, s5, loop2_end \n"
        "loop2_start: \n"

        "li     s3, 0 \n"
        "bge    s3, s6, loop3_end \n"
        "loop3_start: \n"
        
        /**** Loop body start ****/
        // read x[f][j]
        "slli   t1, s3, 1 \n"
        "add    t1, t1, s2 \n"
        "slli   t1, t1, 2 \n"
        "add    t1, t1, %[p_x] \n"
        "lw     t4, 0(t1) \n"

        // read h[i][f]
        "slli   t2, s1, 1 \n"
        "add    t2, t2, s1 \n"
        "add    t2, t2, s3 \n"
        "slli   t2, t2, 2 \n"
        "add    t2, t2, %[p_h] \n"
        "lw     t5, 0(t2) \n"

        // multilication
        "mul    t6, t4, t5 \n"
        
        // read y[i][j]
        "slli   t0, s1, 1 \n"
        "add    t0, t0, s2 \n"
        "slli   t0, t0, 2 \n"
        "add    t0, t0, %[p_y] \n"
        "lw     a0, 0(t0) \n"

        // write y[i][j]
        "add    a0, a0, t6 \n"
        "sw     a0, 0(t0) \n"
        /**** Loop body end ****/

        "addi   s3, s3, 1 \n"
        "blt    s3, s6, loop3_start \n"
        "loop3_end: \n"

        "addi   s2, s2, 1 \n"
        "blt    s2, s5, loop2_start \n"
        "loop2_end: \n"

        "addi   s1, s1, 1 \n"
        "blt    s1, s4, loop1_start \n"
        "loop1_end: \n"

        : [p_y]"+r"(p_y)
        : [p_h]"r"(p_h), [p_x]"r"(p_x)
        :    
);

    p_y = &y[0];
    for(i = 0; i < 6; i++)
        printf("%d ", *p_y++);
    printf("\n");
    return 0; 
 
}
