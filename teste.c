
#include <stdio.h>
static void b();


static void a(){
    printf("chamou:a\n");
    b();
}
static void b(){
    printf("chamou:b\n");

}
int main(){
    a();
}
