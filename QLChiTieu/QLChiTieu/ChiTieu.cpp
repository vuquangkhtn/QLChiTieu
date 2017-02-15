#include "stdafx.h"
#include "ChiTieu.h"


CChiTieu::CChiTieu()
{
	buffLoai.clear();
	buffNoiDung.clear();
	lSoTien = 0;
}

CChiTieu::CChiTieu(wstring loai, wstring noiDung, long soTien)
{
	buffLoai = loai;
	buffNoiDung = noiDung;
	this->lSoTien = soTien;
}

void CChiTieu:: setLoai(wstring loai)
{
	buffLoai = loai;
}

wstring CChiTieu::getLoai()
{
	return this->buffLoai;
}


void CChiTieu::setNoiDung(wstring noiDung)
{		
	buffNoiDung = noiDung;
}

wstring CChiTieu::getNoiDung()
{
	return this->buffNoiDung;
}

void CChiTieu::setSoTien(long soTien)
{	
	this->lSoTien = soTien;
}

long CChiTieu::getSoTien()
{
	return this->lSoTien;
}