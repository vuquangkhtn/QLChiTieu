// QLChiTieu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QLChiTieu.h"
#include "DSChiTieu.h"
#include <string>
#include <Shellapi.h> //Shell object
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
using namespace std;

#define MAX_LOADSTRING 100
#define SO_LOAI_CHI 6

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);

void createCol();
void loadListView();
void taoChuThich(HWND hWnd, HDC hdc, PAINTSTRUCT ps);
void rePaint(HWND hWnd);
void loadRate();
bool isInteger(WCHAR* buffer,int length);

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QLCHITIEU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QLCHITIEU));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QLCHITIEU));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_QLCHITIEU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

HWND lvDSChi;
HWND comboBoxLoaiChiTieu;
HWND txtNoiDungChi;
HWND txtSoTien;
HWND txtTongTien;
CDSChiTieu dsChiTieu;

HWND rateAnUong;
HWND rateDiChuyen;
HWND rateXeCo;
HWND rateNhaCua;
HWND rateNhuYeuPham;
HWND rateDichVu;

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	RECT main; 
	GetWindowRect(hWnd, &main);
	InitCommonControls();
	
	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	
	HWND boxNhap = CreateWindowEx(0,L"BUTTON",L"Thêm chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,50, 30, 350, 220,hWnd, NULL,hInst,NULL);
	SendMessage(boxNhap, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	//Tao combobox va cac thuoc tinh
	comboBoxLoaiChiTieu = CreateWindowEx(0, WC_COMBOBOX, TEXT(""),CBS_DROPDOWNLIST |  WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 150, 50, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(comboBoxLoaiChiTieu, WM_SETFONT, WPARAM(hFont), TRUE);
	const TCHAR* ComboBoxItems[6] = { _T("Ăn uống"), _T("Di chuyển"), _T("Nhà cửa"),_T("Xe cộ"), _T("Nhu yếu phẩm"), _T("Dịch vụ") };
	for(int i=0;i<SO_LOAI_CHI;i++)
	{
		SendMessage(comboBoxLoaiChiTieu, CB_INSERTSTRING, i, (LPARAM) ComboBoxItems[i]);
	}

	SendMessage(comboBoxLoaiChiTieu, CB_SETCURSEL, 0, 0);
	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung chi:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 90, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	txtNoiDungChi = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 150, 90, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(txtNoiDungChi, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 130, 100, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	txtSoTien = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER| SS_RIGHT| WS_TABSTOP, 150, 130, 150, 20, boxNhap, NULL, hInst, NULL);
	SendMessage(txtSoTien, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND boxList = CreateWindowEx(0,L"BUTTON",L"Danh Sách chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,450, 30, 520, 220,hWnd, NULL,hInst,NULL);
	SendMessage(boxList, WM_SETFONT, WPARAM(hFont), TRUE);
	//tao listview
	lvDSChi = CreateWindowEx(0, WC_LISTVIEW, L"Danh sách chi", WS_CHILD | WS_VISIBLE | WS_VSCROLL,10,20, 500, 175,boxList, NULL,hInst,NULL);
	SendMessage(lvDSChi, WM_SETFONT, WPARAM(hFont), TRUE);
	//Đổi sang kiểu details
	SetWindowLong(lvDSChi, GWL_STYLE, GetWindowLong(lvDSChi, GWL_STYLE) | LVS_REPORT);
	createCol();

	hwnd = CreateWindowEx(0,L"BUTTON",L">", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,410, 35, 30, 215,hWnd, (HMENU)IDC_BTNTHEM,hInst,NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	HWND boxDraw = CreateWindowEx(0,L"BUTTON",L"Thống kê chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,50, 280, 920, 180,hWnd, NULL,hInst,NULL);
	SendMessage(boxDraw, WM_SETFONT, WPARAM(hFont), TRUE);
	
	hwnd = CreateWindowEx(0, L"STATIC", L"Tổng tiền:", WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 100, 20, boxDraw, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtTongTien = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT, 120, 50, 100, 20, boxDraw, NULL, hInst, NULL);
	SendMessage(txtTongTien, WM_SETFONT, WPARAM(hFont), TRUE);

	//Danh sach chu thich
	rateAnUong = CreateWindowEx(0, L"STATIC", L"Ăn uống", WS_CHILD | WS_VISIBLE | SS_LEFT, 380, 300, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateAnUong, WM_SETFONT, WPARAM(hFont), TRUE);

	rateDiChuyen = CreateWindowEx(0, L"STATIC", L"Di chuyển", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 300, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateDiChuyen, WM_SETFONT, WPARAM(hFont), TRUE);

	rateNhaCua = CreateWindowEx(0, L"STATIC", L"Nhà cửa", WS_CHILD | WS_VISIBLE | SS_LEFT, 780, 300, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateNhaCua, WM_SETFONT, WPARAM(hFont), TRUE);

	rateXeCo = CreateWindowEx(0, L"STATIC", L"Xe cộ", WS_CHILD | WS_VISIBLE | SS_LEFT, 380, 350, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateXeCo, WM_SETFONT, WPARAM(hFont), TRUE);

	rateNhuYeuPham = CreateWindowEx(0, L"STATIC", L"Nhu yếu phẩm", WS_CHILD | WS_VISIBLE | SS_LEFT, 580, 350, 150, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateNhuYeuPham, WM_SETFONT, WPARAM(hFont), TRUE);

	rateDichVu = CreateWindowEx(0, L"STATIC", L"Dịch vụ", WS_CHILD | WS_VISIBLE | SS_LEFT, 780, 350, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(rateDichVu, WM_SETFONT, WPARAM(hFont), TRUE);

	dsChiTieu.getDSChiTieu("DSChiTieu.txt");
	loadListView();
	loadRate();
	return true;
}


void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int stSoTien = 0;
	int stNoiDung = 0;
	int stLoai = 0;

	WCHAR* buffSoTien =NULL;
	WCHAR* buffNoiDung =NULL;
	WCHAR* buffLoai =NULL;
	WCHAR* buffTongTien = NULL;

	wstring noiDung;
	wstring loai;
	long valSoTien = 0;

	CChiTieu chiTieu;

	switch(id)
	{
		case IDM_ABOUT:
			MessageBox(hWnd,L"1412430 Nguyễn Vũ Quang\nvuquangkhtn@gmail.com",L"My information",MB_OK|MB_ICONINFORMATION|MB_SETFOREGROUND);
			break;
		case ID_HELP_INSTRUCTION:
			ShellExecute(NULL, _T("open"), L"Readme.docx", NULL, NULL, SW_SHOWNORMAL);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDC_BTNTHEM:
			stSoTien = GetWindowTextLength(txtSoTien);
			buffSoTien = new WCHAR[stSoTien+1];
			GetWindowText(txtSoTien, buffSoTien, stSoTien+1);
			valSoTien = _wtol(buffSoTien);

			if(!isInteger(buffSoTien,stSoTien) || valSoTien < 1000)
			{
				MessageBox(hWnd,L"Số tiền phải lớn hơn 1000VNĐ",L"Nhập lỗi",MB_OK | MB_ICONERROR);
				return;
			}

			stNoiDung = GetWindowTextLength(txtNoiDungChi);
			buffNoiDung = new WCHAR[stNoiDung+1];
			GetWindowText(txtNoiDungChi, buffNoiDung, stNoiDung+1);
			
			if(stNoiDung == 0)
			{
				int i = MessageBox(hWnd,L"Bạn thật sự không nhập nội dung cho chi tiêu?",L"Xác nhận",MB_YESNO | MB_ICONQUESTION);
				if(i == IDNO)
				{
					return;
				}
				else
				{
					//Nothing
				}

			}


			stLoai = GetWindowTextLength(comboBoxLoaiChiTieu);
			buffLoai = new WCHAR[stLoai+1];
			GetWindowText(comboBoxLoaiChiTieu,buffLoai,stLoai+1);


			LV_ITEM lv;
			lv.mask = LVIF_TEXT;
			lv.iItem = dsChiTieu.getCountItem()+1;
			lv.iSubItem = 0;
			lv.pszText = buffLoai;
			ListView_InsertItem(lvDSChi, &lv);
			ListView_SetItemText(lvDSChi, dsChiTieu.getCountItem(), 1, buffNoiDung);
			ListView_SetItemText(lvDSChi, dsChiTieu.getCountItem(), 2, buffSoTien);
			

			loai = wstring(buffLoai);
			noiDung = wstring(buffNoiDung);
			chiTieu = CChiTieu(loai,noiDung,valSoTien);

			dsChiTieu.them(chiTieu);
			buffTongTien = new WCHAR[20];
			swprintf(buffTongTien,20,L"%ld",dsChiTieu.getTongTien());
			SetWindowText(txtTongTien,buffTongTien);
			rePaint(hWnd);
			loadRate();

			break;
	}
	if(!buffLoai)
		delete[]buffLoai;
	if(!buffNoiDung)
		delete[]buffNoiDung;
	if(!buffSoTien)
		delete[]buffSoTien;
	return;
}
void loadListView()
{
	LV_ITEM lv;
	lv.mask =LVIF_TEXT;
	lv.iItem = dsChiTieu.getCountItem();
	WCHAR* buffSoTien = new WCHAR[20];
	WCHAR* buffNoiDung = new WCHAR[20];
	WCHAR* buffLoai = new WCHAR[20];
	for(int i=0;i<dsChiTieu.getCountItem();i++)
	{
		CChiTieu chiTieu = dsChiTieu.getChiTieu(i);
		lv.iSubItem = 0;
		chiTieu.getNoiDung().c_str();
		swprintf(buffLoai,20,L"%s",chiTieu.getLoai().c_str());
		lv.pszText = buffLoai;
		ListView_InsertItem(lvDSChi, &lv);
		swprintf(buffNoiDung,20,L"%s",chiTieu.getNoiDung().c_str());
		ListView_SetItemText(lvDSChi, i, 1,buffNoiDung);
		swprintf(buffSoTien,20,L"%ld",chiTieu.getSoTien());
		ListView_SetItemText(lvDSChi, i, 2, buffSoTien);
	}

	//lấy tổng tiền
	swprintf(buffSoTien,20,L"%ld",dsChiTieu.getTongTien());
	SetWindowText(txtTongTien,buffSoTien);
	if(!buffLoai)
		delete[]buffLoai;
	if(!buffNoiDung)
		delete[]buffNoiDung;
	if(!buffSoTien)
		delete[]buffSoTien;

}

void OnPaint(HWND hWnd)
{
	int length = 890;
	int lengthDiChuyen = length * dsChiTieu.getTiLeMotLoai(1);
	int lengthNhaCua = length * dsChiTieu.getTiLeMotLoai(2);
	int lengthXeCo = length * dsChiTieu.getTiLeMotLoai(3);
	int lengthNhuYeuPham = length * dsChiTieu.getTiLeMotLoai(4);
	int lengthDichVu = length * dsChiTieu.getTiLeMotLoai(5);
	int lengthAnUong = length - lengthDiChuyen - lengthDichVu - lengthNhaCua - lengthNhuYeuPham - lengthXeCo;
	HDC hdc;

	int nextLength = 60;
	int preLength = 60;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	nextLength+=lengthAnUong;
	HRGN anUong = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushAnUong = CreateSolidBrush(RGB(250,75, 45));	
	FillRgn(hdc,anUong,hbrushAnUong);

	preLength = nextLength;
	nextLength += lengthDiChuyen;	
	HRGN diChuyen = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushDiChuyen = CreateSolidBrush(RGB(255,160, 25));	
	FillRgn(hdc,diChuyen,hbrushDiChuyen);

	preLength = nextLength;
	nextLength += lengthNhaCua;
	HRGN nhaCua = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushnhaCua = CreateSolidBrush(RGB(240,255, 100));	
	FillRgn(hdc,nhaCua,hbrushnhaCua);

	preLength = nextLength;
	nextLength += lengthXeCo;
	HRGN xeCo = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushxeCo = CreateSolidBrush(RGB(85,250, 60));	
	FillRgn(hdc,xeCo,hbrushxeCo);

	preLength = nextLength;
	nextLength += lengthNhuYeuPham;
	HRGN nhuYeuPham = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushnhuYeuPham = CreateSolidBrush(RGB(60,235, 250));	
	FillRgn(hdc,nhuYeuPham,hbrushnhuYeuPham);

	preLength = nextLength;
	nextLength += lengthDichVu;
	HRGN dichVu = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushdichVu = CreateSolidBrush(RGB(60,65, 250));	
	FillRgn(hdc,dichVu,hbrushdichVu);

	taoChuThich(hWnd,hdc,ps);
	EndPaint(hWnd, &ps);
	return;
}
#define MAX_CHAR 30
void loadRate()
{
	WCHAR* buffer = new WCHAR[MAX_CHAR];
	float tiLe = 100;
	float tiLeDiChuyen = 100*dsChiTieu.getTiLeMotLoai(1);
	float tiLeNhaCua = 100*dsChiTieu.getTiLeMotLoai(2);
	float tiLeXeCo = 100*dsChiTieu.getTiLeMotLoai(3);
	float tiLeNhuYeuPham = 100*dsChiTieu.getTiLeMotLoai(4);
	float tiLeDichVu = 100*dsChiTieu.getTiLeMotLoai(5);
	float tiLeAnUong = tiLe - tiLeDiChuyen - tiLeDichVu - tiLeNhaCua - tiLeNhuYeuPham - tiLeXeCo;
	swprintf(buffer,MAX_CHAR,L"Ăn uống: %.2f%%",tiLeAnUong);
	SetWindowText(rateAnUong,buffer);

	swprintf(buffer,MAX_CHAR,L"Di chuyển: %.2f%%",tiLeDiChuyen);
	SetWindowText(rateDiChuyen,buffer);

	swprintf(buffer,MAX_CHAR,L"Nhà cửa: %.2f%%",tiLeNhaCua);
	SetWindowText(rateNhaCua,buffer);

	swprintf(buffer,MAX_CHAR,L"Xe cộ: %.2f%%",tiLeXeCo);
	SetWindowText(rateXeCo,buffer);

	swprintf(buffer,MAX_CHAR,L"Nhu yếu phẩm: %.2f%%",tiLeNhuYeuPham);
	SetWindowText(rateNhuYeuPham,buffer);

	swprintf(buffer,MAX_CHAR,L"Dịch vụ: %.2f%%",tiLeDichVu);
	SetWindowText(rateDichVu,buffer);
}

void rePaint(HWND hWnd)
{
	int length = 890;
	int lengthDiChuyen = length * dsChiTieu.getTiLeMotLoai(1);
	int lengthNhaCua = length * dsChiTieu.getTiLeMotLoai(2);
	int lengthXeCo = length * dsChiTieu.getTiLeMotLoai(3);
	int lengthNhuYeuPham = length * dsChiTieu.getTiLeMotLoai(4);
	int lengthDichVu = length * dsChiTieu.getTiLeMotLoai(5);
	int lengthAnUong = length - lengthDiChuyen - lengthDichVu - lengthNhaCua - lengthNhuYeuPham - lengthXeCo;
	HDC hdc;

	int nextLength = 60;
	int preLength = 60;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	nextLength+=lengthAnUong;
	HRGN anUong = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushAnUong = CreateSolidBrush(RGB(250,75, 45));	
	FillRgn(hdc,anUong,hbrushAnUong);

	preLength = nextLength;
	nextLength += lengthDiChuyen;	
	HRGN diChuyen = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushDiChuyen = CreateSolidBrush(RGB(255,160, 25));	
	FillRgn(hdc,diChuyen,hbrushDiChuyen);

	preLength = nextLength;
	nextLength += lengthNhaCua;
	HRGN nhaCua = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushnhaCua = CreateSolidBrush(RGB(240,255, 100));	
	FillRgn(hdc,nhaCua,hbrushnhaCua);

	preLength = nextLength;
	nextLength += lengthXeCo;
	HRGN xeCo = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushxeCo = CreateSolidBrush(RGB(85,250, 60));	
	FillRgn(hdc,xeCo,hbrushxeCo);

	preLength = nextLength;
	nextLength += lengthNhuYeuPham;
	HRGN nhuYeuPham = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushnhuYeuPham = CreateSolidBrush(RGB(60,235, 250));	
	FillRgn(hdc,nhuYeuPham,hbrushnhuYeuPham);

	preLength = nextLength;
	nextLength += lengthDichVu;
	HRGN dichVu = CreateRectRgn(preLength, 400, nextLength, 450);
	HBRUSH hbrushdichVu = CreateSolidBrush(RGB(60,65, 250));	
	FillRgn(hdc,dichVu,hbrushdichVu);

	//Vẽ lại mỗi lần thêm chi tiêu
	InvalidateRgn(hWnd,anUong,TRUE);
	InvalidateRgn(hWnd,diChuyen,TRUE);
	InvalidateRgn(hWnd,dichVu,TRUE);
	InvalidateRgn(hWnd,xeCo,TRUE);
	InvalidateRgn(hWnd,nhuYeuPham,TRUE);
	InvalidateRgn(hWnd,nhaCua,TRUE);

	taoChuThich(hWnd,hdc,ps);
	EndPaint(hWnd, &ps);
	return;
}

void taoChuThich(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{

	HRGN anUong = CreateRectRgn(350, 300, 370, 320);
	HBRUSH hbrushAnUong = CreateSolidBrush(RGB(250,75, 45));	
	FillRgn(hdc,anUong,hbrushAnUong);

	HRGN diChuyen = CreateRectRgn(550, 300, 570, 320);	
	HBRUSH hbrushDiChuyen = CreateSolidBrush(RGB(255,160, 25));	
	FillRgn(hdc,diChuyen,hbrushDiChuyen);

	HRGN nhaCua = CreateRectRgn(750, 300, 770, 320);
	HBRUSH hbrushnhaCua = CreateSolidBrush(RGB(240,255, 100));	
	FillRgn(hdc,nhaCua,hbrushnhaCua);

	HRGN xeCo = CreateRectRgn(350, 350, 370, 370);
	HBRUSH hbrushxeCo = CreateSolidBrush(RGB(85,250, 60));	
	FillRgn(hdc,xeCo,hbrushxeCo);

	HRGN nhuYeuPham = CreateRectRgn(550, 350, 570, 370);
	HBRUSH hbrushnhuYeuPham = CreateSolidBrush(RGB(60,235, 250));	
	FillRgn(hdc,nhuYeuPham,hbrushnhuYeuPham);

	HRGN dichVu = CreateRectRgn(750, 350, 770, 370);
	HBRUSH hbrushdichVu = CreateSolidBrush(RGB(60,65, 250));	
	FillRgn(hdc,dichVu,hbrushdichVu);

	
}


void OnDestroy(HWND hwnd)
{
	dsChiTieu.setDSChiTieu("DSChiTieu.txt");
	PostQuitMessage(0);
	return;
}

void createCol()
{
	LVCOLUMN lvCol;

	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;
	lvCol.cx = 150;
	lvCol.pszText = _T("Loại chi tiêu");
	ListView_InsertColumn(lvDSChi, 0, &lvCol);
	
	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;
	lvCol.cx = 200;
	lvCol.pszText = _T("Nội dung chi");
	ListView_InsertColumn(lvDSChi, 1, &lvCol);
	
	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvCol.fmt = LVCFMT_LEFT;
	lvCol.cx = 130;
	lvCol.pszText = _T("Số tiền (VNĐ)");
	ListView_InsertColumn(lvDSChi, 2, &lvCol);
}

bool isInteger(WCHAR* buffer,int length)
{
	if(buffer == NULL && length == 0)
		return true;
	for(int i=0;i<length;i++)
	{
		if(buffer[i] == '\0')
			break;
		if(buffer[i] < '0' || buffer[i] > '9' )
		{
			return false;
		}

	}
	return true;

}