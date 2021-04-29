#include <stdio.h>

#include "lab1.h"

int main() {

    float polynom[] = {1, -105, 206};
    init_coeffs(polynom, sizeof(polynom) / sizeof(polynom[0]));

    float lims[sizeof(limits) / sizeof(limits[0])];

    for (int i = 0; i < sizeof(limits) / sizeof(limits[0]); i++) {
        lims[i] = limits[i]();
        printf("%s: %.6f\n", limits_names[i], lims[i]);
    }
    printf("\n");
    printf("%f\n", secant(0, 1.5, 0.0000001, transcendental));

    float eps = 1;
    float a = 2, b = 0.739085;

    FILE* p_bisect, *p_secant, *t_bisect, *t_secant;

    if ((p_bisect = fopen("../p_bisect.txt", "w")) == NULL)
        return 0;
    if ((p_secant = fopen("../p_secant.txt", "w")) == NULL)
        return 0;
    if ((t_bisect = fopen("../t_bisect.txt", "w")) == NULL)
        return 0;
    if ((t_secant = fopen("../t_secant.txt", "w")) == NULL)
        return 0;

    for (int i = 1; i < 7; i++) {
            eps /= 10;
        float offset = 50;
        for (int j = 13; j >= 0; j--) {

            fprintf(p_bisect, "%.*f;%f;%.*f;", i + 1, eps, offset, i + 1,
                    bisect(a - offset, a + offset, eps, polynomial));
            fprintf(p_bisect, "%ld\n", get_bisect_iter());

            null_bisect_iter();

            fprintf(t_bisect, "%.*f;%f;%.*f;", i + 1, eps, offset, i + 1,
                    bisect(b - offset, b + offset, eps, transcendental));
            fprintf(t_bisect, "%ld\n", get_bisect_iter());

            null_bisect_iter();

            fprintf(p_secant, "%.*f;%f;%.*f;", i + 1, eps, offset, i + 1,
                    secant(a - offset, a + offset, eps, polynomial));
            fprintf(p_secant, "%ld\n", get_secant_iter());

            null_secant_iter();

            fprintf(t_secant, "%.*f;%f;%.*f;", i + 1, eps, offset, i + 1,
                    secant(b - offset, b + offset, eps, transcendental));
            fprintf(t_secant, "%ld\n", get_secant_iter());

            null_secant_iter();

            printf("poly\n");
            printf("Bisect(e=%.*f, offset=%f) %.*f ", i + 1, eps, offset, i + 1,
                   bisect(a - offset, a + offset, eps, polynomial));
            printf("%ld  ", get_bisect_iter());
            printf("Secant(e=%.*f, offset=%f) %.*f ", i + 1, eps, offset, i + 1,
                   secant(a - offset, a + offset, eps, polynomial));
            printf("%ld\n", get_secant_iter());

            null_bisect_iter();
            null_secant_iter();
            printf("trans\n");
            printf("Bisect(e=%.*f, offset=%f) %.*f ", i + 1, eps, offset, i + 1,
                   bisect(b - offset, b + offset, eps, transcendental));
            printf("%ld  ", get_bisect_iter());
            printf("Secant(e=%.*f, offset=%f) %.*f ", i + 1, eps, offset, i + 1,
                   secant(b - offset, b + offset, eps, transcendental));
            printf("%ld\n\n", get_secant_iter());
            offset -= offset > 10 ? 10 : 1;

            null_bisect_iter();
            null_secant_iter();
        }
        printf("\n");
    }

    fflush(p_bisect);
    fclose(p_bisect);
    fflush(t_bisect);
    fclose(t_bisect);
    fflush(t_secant);
    fclose(t_secant);
    fflush(p_secant);
    fclose(p_secant);

    return 0;
}