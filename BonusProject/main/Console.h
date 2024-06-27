﻿#ifndef Console_h
#define Console_h
#include "Struct.h"
//.Console la luu nhung ham thao tac hien thi tren man hinh console va cac ham xu li ngay(Date) thi luu luon trong nay
void hideCursor(bool isHiden);
void getConsoleSize(int& width, int& height);
void gotoXY(int x, int y);
void drawBox(int width, int height, int left, int top);
void notifyBox(string noti);
void textAlignCenter(string s, int left, int width, int y);
void printMenu(const vector<string>& options, int currentOption, int k);
void headerBackGround(int x, int y);
void bodyBackground(int x, int y);
void footerBackground();
//giao diện chờ
void waittingscreen();
//phần xử lí ngày tháng năm
Date CurrentDate();
wstring strToWstr(string s);

#endif
