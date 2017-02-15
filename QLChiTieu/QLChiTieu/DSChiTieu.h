#pragma once
#include "ChiTieu.h"
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
using namespace std;
class CDSChiTieu
{
	vector<CChiTieu> dsChiTieu;
	int countItem;
public:
	CDSChiTieu();
	void setCountItem(int count);
	int getCountItem();
	void them(CChiTieu chiTieu);
	long getTongTien();
	float getTiLeMotLoai(int idType);
	CChiTieu getChiTieu(int pos);
	void getDSChiTieu(string path);
	void setDSChiTieu(string path);
};

