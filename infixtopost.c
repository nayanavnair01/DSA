#include<stdio.h>
#define MAX 100
int main()
{
 char infix[MAX], postfix[MAX], stack[MAX];
 int k=0,top=-1;
 printf("Enter infix expression: ");
 scanf("%s", infix);
  for (int i = 0; infix[i] != '\0'; i++) 
  {
        char c = infix[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        {
        postfix[k] = c;
        k++;
        }
         else if (c == '(') {
            if ( top == MAX - 1) {
                printf("Stack overflow\n");
                return 0;
            }
            top++;
            stack[top] = c;
            }
            else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            if (top != -1 && stack[top] == '(') {
                top--;
            } else {
                printf("Invalid expression\n");
                return 0;
            }
        }
        else{
             int prec;
            if (c == '^') prec = 3;
            else if (c == '*' || c == '/') prec = 2;
            else if (c == '+' || c == '-') prec = 1;
            else prec = 0;
            
            while (top != -1) {
                char topOp = stack[top];
                int topPrec;
                if (topOp == '^') topPrec = 3;
                else if (topOp == '*' || topOp == '/') topPrec = 2;
                else if (topOp == '+' || topOp == '-') topPrec = 1;
                else topPrec = 0;
       
           if ((prec < topPrec) || (prec == topPrec && c != '^')) {
                    postfix[k++] = stack[top--];
                } else {
                    break;
                }
            }

            stack[++top] = c;
            }
            }
    
     while (top != -1) {
        if (stack[top] == '(') {
            printf("Invalid expression");
            return 0;
        }
        postfix[k++] = stack[top--];
}
    postfix[k] = '\0';
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
