#include <Windows.h>
#include <stdio.h>
int main()
{
    HANDLE hcom;
    BOOL status;
    DWORD bytesWritten = 0;
    DWORD bytesRead;
    DCB serialparams;
    COMMTIMEOUTS timeout;
    char buffer[10];
    char square[10];
    char square2[10];
    char Temptchar;
    int i ,j;
    hcom = CreateFile("COM6", GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if(hcom == INVALID_HANDLE_VALUE)
    printf("Error in opening port");
    else
    printf("Port succesfully opened");

    serialparams.DCBlength = sizeof(serialparams);
    status = GetCommState(hcom,&serialparams);
    if(status == FALSE)
    printf("Can not get comm states");
    serialparams.BaudRate = CBR_9600;
    serialparams.ByteSize = 8;
    serialparams.StopBits = ONESTOPBIT;
    serialparams.Parity = NOPARITY;
    status = SetCommState(hcom,&serialparams);
    if(status == FALSE)
    printf("Cant set comm states");

    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 10;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hcom,&timeout) == FALSE)
    printf("cant set timeouts");

    while(1)
    {
        printf("\nEnter your number: ");
        scanf("%s", buffer, (unsigned)_countof(buffer));
        if(buffer[0] == '0')
        break;
        status = WriteFile(hcom,buffer,sizeof(buffer),&bytesWritten,NULL);
        if(buffer[0] == '4')
        {
            i = 0;
            printf("Your other number: ");
            scanf("%s", square,(unsigned)_countof(square));
            WriteFile(hcom, square,sizeof(square),&bytesWritten,NULL);
            status = SetCommMask(hcom, EV_RXCHAR);
            status = WaitCommEvent(hcom, EV_RXCHAR,NULL);
            do
            {
                status = ReadFile(hcom, &Temptchar, sizeof(Temptchar), &bytesRead,NULL);
                square2[i] = Temptchar;
                i++;
            } while (bytesRead > 0);
            
            printf("\nSquare of your number is: ");
            for(j = 0; j < i-1; j++)
            printf("%c",square2[j]);
            memset(square2, '0' , sizeof(square2));
        }
         memset(buffer, '0' , sizeof(buffer));
        /*for(i = 0; i<= j; i++)
        printf("%c,", buffer[i]);
        printf("\n%d", j);
        j++;*/
       
    }
     CloseHandle(hcom);
}