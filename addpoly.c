#include <stdio.h>

#define MAX 100


typedef struct {
    int coeff; 
    int exp;   
} Term;


void inputPoly(Term poly[], int *n) {
    printf("Enter number of terms: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Enter term %d (coefficient and exponent): ", i + 1);
        scanf("%d %d", &poly[i].coeff, &poly[i].exp);
    }
}


void displayPoly(Term poly[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%dx^%d", poly[i].coeff, poly[i].exp);
        if (i < n - 1)
            printf(" + ");
    }
    printf("\n");
}


int addPoly(Term poly1[], int n1, Term poly2[], int n2, Term result[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (poly1[i].exp == poly2[j].exp) {
            result[k].coeff = poly1[i].coeff + poly2[j].coeff;
            result[k].exp = poly1[i].exp;
            i++;
            j++;
        } else if (poly1[i].exp > poly2[j].exp) {
            result[k] = poly1[i];
            i++;
        } else {
            result[k] = poly2[j];
            j++;
        }
        k++;
    }

    // Copy remaining terms
    while (i < n1) {
        result[k++] = poly1[i++];
    }
    while (j < n2) {
        result[k++] = poly2[j++];
    }

    return k; 
}

int main() {
    Term poly1[MAX], poly2[MAX], sum[MAX];
    int n1, n2, nSum;

    printf("Enter first polynomial:\n");
    inputPoly(poly1, &n1);

    printf("\nEnter second polynomial:\n");
    inputPoly(poly2, &n2);

    nSum = addPoly(poly1, n1, poly2, n2, sum);

    printf("\nFirst Polynomial: ");
    displayPoly(poly1, n1);

    printf("Second Polynomial: ");
    displayPoly(poly2, n2);

    printf("Sum Polynomial: ");
    displayPoly(sum, nSum);

    return 0;
}
