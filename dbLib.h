/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include "dsaLib.h"

#pragma region Structs
struct TCity {
	int id;
	string name;
	TCity():id(0), name(""){}
	TCity(int n,string str):id(n),name(str){}
};

struct TLine {
  	int id;
	int city_id;
	TLine():id(0),city_id(0){}
};

struct TTrack {
  	int id;
	string geometry;
	int city_id;
	TTrack():id(0),geometry(""),city_id(0) {}
};

struct TStation {
	int id;
	string name;
	string geometry;
	int city_id;
	TStation():id(0),name(""),geometry(""),city_id(0){}
};
struct TStation_Line {
	int station_id;
	int line_id;
	TStation_Line() : station_id(0),line_id(0){}
	TStation_Line(int b,int c): station_id(b), line_id(c) {}
};

class TDataset {
public:
	L1List<TCity>* cityList;
	L1List < TLine>* lineList;
	L1List < TTrack>* trackList;
	L1List < TStation>* stationList;
	L1List < TStation_Line>* station_lineList;
	TDataset():cityList(nullptr),lineList(nullptr),trackList(nullptr),stationList(nullptr),station_lineList(nullptr){}
	
    // This class can be a container that help you manage your tables
};
#pragma endregion


void LoadData(void* & pData);
void ReleaseData(void* & pData);

L1List<TCity>* LoadCityFile();
L1List<TLine>* LoadLinesFile();
L1List<TTrack>* LoadTracksFile();
L1List<TStation>* LoadStationFile();
L1List<TStation_Line>* LoadStation_LineFile();
#endif //DSA191_A1_DBLIB_H
