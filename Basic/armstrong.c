#include<stdio.h>
int main(){
    int num,res=0;
    printf("Enter a number");
    scanf("%d",&num);

    int original = num;
    while(num!=0){
        int rem= num%10;
         res= res+(rem*rem*rem);
        num=num/10;
    }
    if(original == res)
        printf("%d is Armstrong number",original);
    else
    printf("%d is Not Armstrong number",original);
    return 0;

}