#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define oneLen 75

double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    return mat;
}



void zhdac ( HWND* hWnd )
{
    printf("\nWaiting for click");
    while (1)
    {
		if (_kbhit()) {
			char c = _getch();
			InvalidateRect(*hWnd, NULL, TRUE);
			break;
		}
	}
}

int nx[11] = { };
int ny[11] = { };
double** Amain = NULL;
void matGen (  )
{
    for ( int i = 0; i < 11; i++ ) {
        if ( i == 0 ) {
            nx[i] = oneLen*6;
            ny[i] = 800 - oneLen;
        }
        else if ( i < 3) {
            nx[i] = nx[i-1] - oneLen*2;
            ny[i] = ny[i-1];
        }
        else if ( i < 7 ) {
            nx[i] = nx[i-1] + oneLen;
            ny[i] = ny[i-1] - oneLen*2;
        }
        else {
            nx[i] = nx[i-1] + oneLen;
            ny[i] = ny[i-1] + oneLen*2;
        }
    }
    srand(0315);
    double** T = randmm(11, 11);
    double coef = 1.0 - 1*0.01 - 5*0.005 - 0.15;
    Amain = mulmr(coef, T, 11, 11);
}

void matout (  )
{
    printf("\nMatrix:\n");
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    printf("%.0f ", Amain[i][j]);
                }
                printf("\n");
            }
            //nenaprav graf matrix
            /*double B[11][11] = {};
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    B[i][j] = A[i][j];
                }
            }
            printf("\nMirror Matrix:\n");
            for ( int i = 0; i < 11; i++ )
            {
                for ( int j = 0; j < 11; j++ )
                {
                    if ( B[i][j] == 1 ){
                        B[j][i] = 1;
                    }
                    printf("%.0f ", B[i][j]);
                }
                printf("\n");
            }*/
}

double** dfs = NULL;
double dfsGraph[11][11];
int visited[11] = {};
int unvisited;
char *nume[11] = {};
int numeCheck = 0;
int last = 0;
int checker = 1;

void risovac ( HDC hdc, double** A, int* nx, int* ny )
{
            void arrow(float fi, int px,int py){
                    fi = 3.1416*(180.0 - fi)/180.0;
                    int lx,ly,rx,ry; //px,py,
                   // px=150; py=60;
                    lx = px+15*cos(fi+0.3);
                    rx = px+15*cos(fi-0.3);
                    ly = py+15*sin(fi+0.3);
                    ry = py+15*sin(fi-0.3);
                    MoveToEx(hdc, lx, ly, NULL);
                    LineTo(hdc, px, py);
                    LineTo(hdc, rx, ry);
                 //  return 0;
              }
            int i;
            char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b"};
            char *newnume[11] = {};
            if(numeCheck == 1) for ( int f = 0; f < 11; f++ ) newnume[f] = nume[f];
            int dx = 16, dy = 16, dtx = 7;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            HPEN NOTGGPen = CreatePen(PS_SOLID, 2, RGB(194, 210, 255));
            HPEN GGPen = CreatePen(PS_SOLID, 2, RGB(158, 194, 255));
            SelectObject(hdc, KPen);
            if( checker == 0 ) TextOut(hdc,100,100,"DFS graph",9);
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if ( A[i][j] == 1 && visited[i] != 0) {
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        if ( i != ( j + 1 ) && j != ( i + 1 ) ) {
                           if ( ( i <= 2 || i == 10 ) && ny[i] == ny[j] ) {
                                if ( i == j && i != 10) {
                                    Arc(hdc, nx[j], ny[j], nx[j]-50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( i == j && i == 10 ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]+50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( A[j][i] == 1 ) {
                                    if ( ( i - j ) < 0 ) {
                                        Arc(hdc, nx[j], ny[j]-60, nx[i], ny[i]+60, nx[i], ny[i], nx[j], ny[j]);
                                        arrow(50, nx[j]-dx+6, ny[j]+dy-2);
                                        Arc(hdc, nx[j], ny[j]-40, nx[i], ny[i]+40, nx[i], ny[i], nx[j], ny[j]);
                                        arrow(160, nx[i]+dx-4, ny[i]+dy-4);
                                    }
                                }
                                else {
                                    Arc(hdc, nx[i], ny[i]-40, nx[j], ny[j]+40, nx[j], ny[j], nx[i], ny[i]);
                                    arrow(-30, nx[j]-dx+4, ny[j]-dy+4);
                                }
                           }
                           else if ( ( i >= 2 && i < 7 ) && ( j >= 2 && j < 7 ) ) {
                                if ( i == j ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]-50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( A[j][i] != 1 ) {
                                    if( ( i-j ) == -2 || ( i-j ) == 2 ){
                                        Arc(hdc, nx[i]+10, ny[i]-110, nx[j]-50, ny[j]+40, nx[i], ny[i], nx[j], ny[j]);
                                        arrow(-70, nx[j]-11, ny[j]-dy+5);
                                    }
                                    else {
                                        Arc(hdc, nx[i]-100, ny[i]+75, nx[j]+100, ny[j]-70, nx[j], ny[j], nx[i], ny[i]);
                                        arrow(-50, nx[j]-12, ny[j]-dy+10);
                                    }
                                }
                           }
                            else if ( ( i >= 6 && i < 12 ) && ( j >= 6 && j < 12 ) ) {
                                if ( i == j ) {
                                    Arc(hdc, nx[j], ny[j], nx[j]+50, ny[j]-50, nx[j], ny[j], nx[j], ny[j]);
                                    arrow(-90, nx[j], ny[j]-dy);
                                }
                                else if ( A[j][i] == 1 ) {
                                    switch ( i - j ) {
                                    case 2: case -2:
                                        Arc(hdc, nx[i]+100, ny[i]+15, nx[j]-30, ny[j]-80, nx[i], ny[i], nx[j], ny[j]);
                                        arrow(-70, nx[j]-11, ny[j]-dy+5);
                                        break;
                                    case -3:
                                        Arc(hdc, nx[i]-50, ny[i]-100, nx[j]+70, ny[j]+70, nx[j], ny[j], nx[i], ny[i]);
                                        arrow(-110, nx[i]+6, ny[i]-dy);
                                        Arc(hdc, nx[i]-40, ny[i]-90, nx[j]+60, ny[j]+70, nx[j], ny[j], nx[i], ny[i]);
                                        arrow(-110, nx[j]+8, ny[j]-dy+5);
                                        break;
                                    case 4: case -4:
                                        Arc(hdc, nx[i]-50, ny[i]-70, nx[j]-50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                        break;
                                    }
                                }
                                else {
                                    switch ( i - j ) {
                                    case 2:
                                        Arc(hdc, nx[i]+100, ny[i]+15, nx[j]-30, ny[j]-80, nx[i], ny[i], nx[j], ny[j]);
                                        arrow(-120, nx[j]+5, ny[j]-dy+3);
                                        break;
                                    case -2:
                                        Arc(hdc, nx[j], ny[j]+200, nx[i]-100, ny[i]-10, nx[j], ny[j], nx[i], ny[i]);
                                        arrow(-90, nx[j]-1, ny[j]-dy+1);
                                        break;
                                    case 3: case -3:
                                        Arc(hdc, nx[i]-50, ny[i]-100, nx[j]+70, ny[j]+70, nx[j], ny[j], nx[i], ny[i]);
                                        arrow(-120, nx[j]+11, ny[j]-dy+8);
                                        break;
                                    }
                                }
                            //printf("\n%i\t%i\n",i,j);
                            }
                            else {
                                if ( A[j][i] == 1 ) {
                                    if ( ( i - j ) > 0 ) {
                                        POINT pt[3];
                                        pt[0].x = nx[i];
                                        pt[0].y = ny[i];

                                        pt[1].x = nx[i]+10;
                                        pt[1].y = ny[i]+200;

                                        pt[2].x = nx[j];
                                        pt[2].y = ny[j];

                                        Polyline(hdc,pt,3);
                                        LineTo(hdc, nx[j], ny[j]);

                                        if( i - j == 3 ){
                                            arrow(-230, nx[j]+10, ny[j]+dy-2);
                                            arrow(-270, nx[i]+2, ny[i]+dy);
                                        }
                                        else if( i - j == 5 ){
                                            arrow(-70, nx[j]-4, ny[j]-dy);
                                            arrow(-260, nx[i]+2, ny[i]+dy);
                                        }
                                        else {
                                            arrow(-30, nx[j]-12, ny[j]-dy+7);
                                            arrow(-240, nx[i]+8, ny[i]+dy);
                                        }

                                    }
                                }
                                else {
                                    //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                    LineTo(hdc, nx[j], ny[j]);
                                    if ( nx[i] == nx[j] ) {
                                        arrow(90,nx[j],ny[j]+dy);
                                    }
                                    else if ( ny[i] == ny[j] ){
                                        arrow(0,nx[j]-dx,ny[j]);
                                    }
                                    else if ( nx[i]-oneLen == nx[j] ) {
                                        arrow(-100,nx[j]+3,ny[j]-dy);
                                    }
                                    else if ( nx[i]-3*oneLen == nx[j] ) {
                                        if ( ny[j] > ny[i] ){
                                            arrow(-120,nx[j]+dx-9,ny[j]-dy);
                                        }
                                        else{
                                            arrow(140,nx[j]+dx,ny[j]+dy-7);
                                        }
                                    }
                                    else if ( nx[i]-5*oneLen == nx[j] ) {
                                        if( ny[j] > ny[i] ) {
                                            arrow(-160,nx[j]+dx,ny[j]-6);
                                        }
                                        else {
                                            arrow(140,nx[j]+dx-6,ny[j]+dy-2);
                                        }
                                    }
                                    else if ( nx[i]+3*oneLen == nx[j] ) {
                                        arrow(30,nx[j]-dx+3,ny[j]+9);
                                    }
                                    else if ( nx[i]+4*oneLen == nx[j] ) {
                                        arrow(50,nx[j]-dx+3,ny[j]+dy-3);
                                    }
                                    else if ( nx[i]+5*oneLen == nx[j] ) {
                                        arrow(-20,nx[j]-dx,ny[j]-6);
                                    }
                                    else if ( nx[i]+6*oneLen == nx[j] ) {
                                        arrow(40,nx[j]-dx+4,ny[j]+8);
                                    }
                                    else {
                                        if ( nx[i] > nx[j] )
                                            arrow(-220,nx[j]+dx,ny[j]+15);
                                        else{
                                            switch (ny[i] - ny[j]){
                                                case oneLen*4:
                                                    arrow(70,nx[j]-7,ny[j]+15);
                                                    break;
                                                case oneLen*6:
                                                    arrow(80,nx[j]-2,ny[j]+15);
                                                    break;
                                            }
                                        }
                                    }
                                }//printf("\n%i\t%i\n",i,j);
                            }
                        }
                        else {
                            if ( A[j][i] == 1 ) {
                                if ( ( i - j ) > 0 ) {
                                        POINT pt[3];
                                        pt[0].x = nx[i];
                                        pt[0].y = ny[i];

                                        pt[1].x = nx[i]-50;
                                        pt[1].y = ny[i]+50;

                                        pt[2].x = nx[j];
                                        pt[2].y = ny[j];

                                        Polyline(hdc,pt,3);
                                        LineTo(hdc, nx[j], ny[j]);

                                        arrow(-100, nx[j]+4, ny[j]-dy);
                                        arrow(70, nx[i]-8, ny[i]+dy);
                                    }
                            }
                            else {
                                LineTo(hdc, nx[j], ny[j]);
                                if ( nx[j] > nx[i] ) {
                                    if(ny[i] != ny[j])arrow(70, nx[j]-8, ny[j]+dy);
                                    else arrow(0, nx[j]-dx, ny[j]);
                                }
                                else {
                                    arrow(120, nx[j]+8, ny[j]+dy);

                                }
                            }
                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            for ( i = 0; i <= 10; i++ ){
                if( visited[i] == 0 )
                {
                   SelectObject(hdc, BPen);
                }
                else if ( visited[i] == 1 )
                {
                    SelectObject(hdc, NOTGGPen);
                }
                else
                {
                    SelectObject(hdc, GGPen);
                }
                Ellipse ( hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy );
                if(numeCheck == 0) TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1 );
                else{
                    printf("\nthis - %c",newnume[i]);
                    TextOut ( hdc, nx[i]-dtx, ny[i]-dy/2, newnume[i], 1 );
                }


            };
}



void dfsout (  )
{
    printf("\n\ndfs:\n");
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    printf("%.0f ", dfs[i][j]);
                }
                printf("\n");
            }
}

//potok


DWORD WINAPI somethingcool (LPVOID lpParam)
{
    matGen ( );
    matout ( );

    //int queu[11] = {};
    int a = 0;
    for ( int i = 0; i < 11; i++ )
    {
        visited[i] = 0;
        for ( int j = 0; j < 11; j++ ) dfsGraph[i][j] = 0;
    }

    while (1)
    {
        unvisited = -1;
        for ( int i = 0; i < 11; i++ )
            if ( visited[i] == 0 )
            {
                unvisited = i;
                break;
            }
        if ( unvisited == -1 ) break;
        else
        {
            nume[last] = "a";
            last = last + 1;
            dfcheck(lpParam, unvisited);
        }
    }

    dfs = randmm(11, 11);
    for ( int i = 0; i < 11; i++ )
        for ( int j = 0; j < 11; j++ )
            dfs[i][j] = dfsGraph[i][j];
    dfsout();

    printf("\n\nSwitch number");
    zhdac(lpParam);
    numeCheck = 1;
    checkanddraw(lpParam);

    printf("\n\nBuild dfs graph");
    zhdac(lpParam);
    numeCheck = 0;
    checker = 0;
    printf("\n\nHere it is:");
    checkanddraw(lpParam);

    printf("\n\nBuild dfs graph with new numbers");
    zhdac(lpParam);
    numeCheck = 1;
    printf("\n\nHere it is:");
    checkanddraw(lpParam);

}

void dfcheck ( HWND hWnd, int calledFor )
{

    printf("\ncalledFor = %i\n", calledFor);
    visited[calledFor] = 1;
    zhdac(hWnd);
    for ( int i = 0; i < 11; i++ )
    {
        if ( Amain[calledFor][i] && !visited[i] )
        {
            switch(i){
            case 1:
                nume[last] = "b";
                break;
            case 2:
                nume[last] = "c";
                break;
            case 3:
                nume[last] = "d";
                break;
            case 4:
                nume[last] = "e";
                break;
            case 5:
                nume[last] = "f";
                break;
            case 6:
                nume[last] = "g";
                break;
            case 7:
                nume[last] = "h";
                break;
            case 8:
                nume[last] = "j";
                break;
            case 9:
                nume[last] = "k";
                break;
            case 10:
                nume[last] = "l";
                break;
            }
            last++;
            dfsGraph[calledFor][i] = 1;
            dfcheck(hWnd,i);
        }
    }

}

void checkanddraw ( HDC hdc )
{
    if( checker ) risovac ( hdc, Amain, nx, ny );
    else risovac ( hdc, dfs, nx, ny );
}

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//объявляем строку-имя программы
char ProgName[] = "Лабораторна робота 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style = CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if( !RegisterClass(&w) )
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd=CreateWindow(ProgName, //Имя программы
        "Лабораторна робота 3", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        0, //положение окна на экране по х
        0, //положение по у
        1920, //ширина
        1080, //висота
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
 //   UpdateWindow(hWnd);

        DWORD dwThreadId = 1;

        HANDLE cool;
        cool = CreateThread(NULL, 0, somethingcool, &hWnd, 0, &dwThreadId);
//Цикл одержання повідомлень

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
            TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
            DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
        }
    return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода


//Цикл обработки сообщений
    switch ( messg )
    {
    //сообщение рисования
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);

            checkanddraw( hdc );

            EndPaint(hWnd, &ps);
            break;

        case WM_KEYDOWN:
            InvalidateRect(hWnd, NULL, TRUE);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
