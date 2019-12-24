/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */
#include "dbLib.h"
L1List<TCity>* LoadCityFile()		//L1List<int>* &cityIDList)
{
	fstream cityFile;
	L1List<TCity>* cityList = new L1List<TCity>();
	cityFile.open("cities.csv", ios::in);	
	string line, trash;
	getline(cityFile, line);				//pass the first line
	while (cityFile.good()) {
		char temp;
		TCity city;
		cityFile >> city.id;
		cityFile >> temp;
		getline(cityFile, city.name,',');
		getline(cityFile, trash);
		cityList->push_back(city);
	}
	cityFile.close();
	return cityList;
}

L1List<TLine>* LoadLinesFile()
{
	fstream lineFile;
	L1List<TLine>* lineList = new L1List<TLine>();
	lineFile.open("lines.csv", ios::in);
	string line, trash;
	//getline(lineFile, line);				//pass the first line
	while (lineFile.good()) {
		char temp;
		getline(lineFile, trash);
		TLine line;
		lineFile >> line.id; 
		lineFile >> temp;
		lineFile >> line.city_id;
		lineList->push_back(line);
	}
	 
	lineFile.close();
	return lineList;
}

L1List<TTrack>* LoadTracksFile() {
	fstream trackFile;
	L1List<TTrack>* trackList = new L1List<TTrack>();
	trackFile.open("tracks.csv", ios::in);
	string line, trash;
	getline(trackFile, line);				//pass the first line
	//int bugline = 1;
	while (trackFile.good()) {
		char temp;
		TTrack track;
		trackFile >> track.id;
		trackFile >> temp;
		//if(temp.)
		getline(trackFile, track.geometry, ')');
		getline(trackFile, trash, ',');
		for (int i = 0; i < 4; ++i) {
			getline(trackFile, trash, ',');
		}
		trackFile >> track.city_id; //cout << track.city_id << ' ' << bugline << endl;
		trackList->push_back(track);
		//bugline++;
	}
	trackFile.close();
	return trackList;
}

L1List<TStation>* LoadStationFile() {
	fstream staFile;
	L1List<TStation>* staList = new L1List<TStation>();
	staFile.open("stations.csv", ios::in);
	string line, trash;
	getline(staFile, line);				//pass the first line
	while (staFile.good()) {
		char temp;
		TStation station;
		staFile >> station.id;
		staFile >> temp;
		getline(staFile, station.name, ',');
		getline(staFile, trash, '(');
		getline(staFile, station.geometry, ')'); 
		staFile >> temp;
		for (int i = 0; i < 3; ++i){
			getline(staFile, trash, ',');
		}
		staFile >> station.city_id; 
		staList->push_back(station);
	}
	staFile.close();
	return staList;
}

L1List<TStation_Line>* LoadStation_LineFile()
{
	fstream sta_lineFile;
	L1List<TStation_Line>* sta_lineList = new L1List<TStation_Line>();
	sta_lineFile.open("station_lines.csv", ios::in);
	string line, trash;
	getline(sta_lineFile, line);				//pass the first line
	while (sta_lineFile.good()) {
		char temp;
		TStation_Line obj;
		getline(sta_lineFile, trash, ',');
		//sta_lineFile >> temp;
		sta_lineFile >> obj.station_id; 
		sta_lineFile >> temp;
		sta_lineFile >> obj.line_id; 
		getline(sta_lineFile, trash);
		sta_lineList->push_back(obj);
	}
	sta_lineFile.close();
	return sta_lineList;
}

void LoadData(void*& pData)
{
	TDataset* pDataSet = new TDataset();
	pDataSet->cityList = LoadCityFile();
	pDataSet->lineList = LoadLinesFile();
	pDataSet->stationList = LoadStationFile();
	pDataSet->trackList = LoadTracksFile();
	pDataSet->station_lineList = LoadStation_LineFile();
	pData= pDataSet;
}

void ReleaseData(void*& pData) {
	delete pData;
}