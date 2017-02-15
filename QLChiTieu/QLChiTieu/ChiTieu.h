#pragma once
#include <string>
using namespace std;

class CChiTieu
{
private:
	wstring buffLoai;
	wstring buffNoiDung;
	long lSoTien;
public:
	CChiTieu();
	CChiTieu(wstring loai, wstring noiDung, long soTien);

	void setLoai(wstring loai);
	wstring getLoai();

	void setNoiDung(wstring noiDung);
	wstring getNoiDung();

	void setSoTien(long soTien);
	long getSoTien();

};

