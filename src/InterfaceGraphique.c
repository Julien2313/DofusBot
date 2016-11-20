#include "dllScripting.h"
#include <windowsx.h>
#include <windows.h>

#include "bot.h"


LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);




int afficherPointsBle(void)
 {
  HWND hwnd;
  MSG msg;
  WNDCLASS wc;



  wc.style = 0;
  wc.lpfnWndProc = MainWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = GetModuleHandle(NULL);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
  wc.lpszMenuName =  NULL;
  wc.lpszClassName = "MaWinClass";

  if(!RegisterClass(&wc)) return FALSE;

  hwnd = CreateWindow("MaWinClass", "Titre", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1279, 1047, NULL, NULL, wc.hInstance, NULL);
  if(!hwnd) return FALSE;

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);


  while(GetMessage(&msg, NULL, 0, 0))
   {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   }

  return(scrOK);
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
  PAINTSTRUCT ps;
  HDC hdc;
  HBRUSH pinceauVert, pinceauRouge, pinceauBleu, pinceauNoir;
  char titre[200];
  int xPos, yPos;

  switch (uMsg)
   {
    case WM_CREATE:
         return(0);

    case WM_PAINT:
         hdc = BeginPaint(hwnd, &ps);

         pinceauRouge = CreateSolidBrush(RGB(255,   0,   0));
         pinceauVert  = CreateSolidBrush(RGB(  0, 255,   0));
         pinceauBleu  = CreateSolidBrush(RGB(  0,   0, 255));
         pinceauNoir  = CreateSolidBrush(RGB(  0,   0,   0));
/*
        while(images[IMAGE_EPI_BLE_1].nbrTrouvees > 0)
        {
            images[IMAGE_EPI_BLE_1].nbrTrouvees--;
            FillRect(hdc, &images[IMAGE_EPI_BLE_1].rect[images[IMAGE_EPI_BLE_1].nbrTrouvees],pinceauRouge);
        }
        while(images[IMAGE_EPI_BLE_2].nbrTrouvees > 0)
        {
            images[IMAGE_EPI_BLE_2].nbrTrouvees--;
            FillRect(hdc, &images[IMAGE_EPI_BLE_2].rect[images[IMAGE_EPI_BLE_2].nbrTrouvees],pinceauVert);
        }
        while(nbrPointsRecoltes > 0)
        {
            nbrPointsRecoltes--;
            FillRect(hdc, &pointsRecoltes[nbrPointsRecoltes].rect,pinceauNoir);
        }
        while(images[IMAGE_EPI_BLE_3].nbrTrouvees > 0)
        {
            images[IMAGE_EPI_BLE_3].nbrTrouvees--;
            FillRect(hdc, &images[IMAGE_EPI_BLE_3].rect[images[IMAGE_EPI_BLE_3].nbrTrouvees],pinceauBleu);
        }
*/
        RECT rect666;
/*
        int posX, posY;
        for(posX = 0; posX < LClient; posX++)
        {
            for(posY = 0; posY < HClient;posY++)
            {
                rect666.left = posX;
                rect666.top = posY;
                rect666.right = rect666.left + 1;
                rect666.bottom = rect666.top + 1;

                if(tab[posX][posY] == 1)
                {
                    FillRect(hdc, &rect666,pinceauRouge);
                }
                else if(tab[posX][posY] == 2)
                {
                    FillRect(hdc, &rect666,pinceauVert);
                }
                else if(tab[posX][posY] == 3)
                {
                    FillRect(hdc, &rect666,pinceauBleu);
                }
                else
                {
                    FillRect(hdc, &rect666,pinceauNoir);
                }
                FillRect(hdc, &pointsRecoltes[nbrPointsRecoltes].rect,pinceauBleu);
            }


        }*/
         DeleteObject(pinceauBleu);
         DeleteObject(pinceauVert);
         DeleteObject(pinceauRouge);
         DeleteObject(pinceauNoir);

         EndPaint(hwnd, &ps);
         return(0);

    case WM_MOUSEMOVE:
         xPos = GET_X_LPARAM(lParam);
         yPos = GET_Y_LPARAM(lParam);

         sprintf(titre, "Carte Dofus        Cellule : %d,%d", xPos, yPos);
         SetWindowText(hwnd, titre);
         return(0);

    case WM_DESTROY:
         PostQuitMessage(0);
         return(0);

    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
   }
 }
