#include <stdio.h>

struct Complex
{
    float real;
    float imag;
};

void input(struct Complex *c)
{
    scanf("%f%f", &c->real, &c->imag);
}

void output(struct Complex *c)
{
    if (c->imag >= 0)
        printf("%.6g + %.6gi", c->real, c->imag);
    else
        printf("%.6g - %.6gi", c->real, -c->imag);
}

void addto(struct Complex *c1, struct Complex *c2, struct Complex *c3)
{
    c3->real = c1->real + c2->real;
    c3->imag = c1->imag + c2->imag;
}

int main()
{
    struct Complex c1, c2, c3;

    input(&c1);
    input(&c2);

    output(&c1);
    printf("\n");

    output(&c2);
    printf("\n");

    addto(&c1, &c2, &c3);

    output(&c3);
    printf("\n");

    return 0;
}
