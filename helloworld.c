//Simple HelloWorld with WindowsAPI

#include <windows.h>




void main(){
    const char * message = "Hello World";
    const char * title = "My First Windows API usage";
    MessageBox(NULL, message, title, MB_OK);
}