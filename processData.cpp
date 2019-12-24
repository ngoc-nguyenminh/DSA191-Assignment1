/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;
#pragma region utility functions

int findCityID(TCity &city, void*& pPara)
{
	if (city.name == *(string*)pPara)
		return city.id;
	return-1;
}
int findLine(TLine& line, void*& pPara) {
	if (line.city_id == ((int*)pPara)[0])
		return line.id;
	return -1;
}
int findStation(TStation& station, void*& pPara) {						//process request LSC
	if (station.city_id == ((int*)pPara)[0])
		return station.id;
	return -1;
}
/*int findStationLineID(TStation_Line& staLine, void*& pPara) {	//process request ISL, check if linne_station is existed
	if (staLine.station_id == ((int*)pPara)[0] && staLine.line_id == ((int*)pPara)[1])
		return staLine.id;
	return -1;
}*/
int findLineIDInSLFile(TStation_Line& stationLine, void*& pPara) {
	if (stationLine.line_id == *((int*)pPara))
		return stationLine.station_id;
	return -1;
}
int findStationIDInSLFile(TStation_Line& stationLine, void*& pPara) {	//process request LSL
	if (stationLine.station_id == *(int*)pPara)
		return 0;
	return -1;
}

int findStationID(TStation& station, void*& pPara)						//process request FS
{
	if (station.name == *(string*)pPara)
		return station.id;
	return-1;
}
int checkStaID(TStation& station, void*& pPara) {	//check if stationID is existed
	if (station.id == *((int*)pPara))
		return 0;
	return -1;
}
int getSTaLine(TStation_Line& staLin, void*& pPara) {
	if (staLin.station_id == ((int*)pPara)[0] && staLin.line_id == ((int*)pPara)[1])
		return 0;
	return -1;
}
string getStationGeometry(TStation& station, void*& pPara) {
	if (station.id == *(int*)pPara)
		return station.geometry;
	return "";
}
int getStationID(TStation& station) {
	return station.id;
}
string getTrackGeometry(TTrack& track, void*& pPara) {
	if (track.id == *(int*)pPara)
		return track.geometry;
	return "";
}
int replace(TStation& station, void*& pPara) {
	if (station.id == stoi(((string*)pPara)[0])) {
		station.name = ((string*)pPara)[1];
		station.geometry = ((string*)pPara)[2];
		return 0;
	}
	return -1;
}

#pragma endregion


void Initialization() {
	int id_max = 0;
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
#pragma region Load Request
	TDataset* tmpData = static_cast<TDataset*>(pData);
	string temp,cmd,cmd_content;
	int i = 0;
	while (*(pRequest + i) != '\0') {
		temp.push_back(*(pRequest + i));
		i++;
	}
	if (temp.length() < 3)
	{
		cmd = temp;
		cmd_content = "";
	}
	else {
		for (int i = 0; i < temp.find(' '); ++i)
		{
			cmd.push_back(temp[i]);
		}
		for (int i = temp.find(' ') + 1; temp[i] != '\0'; ++i)
		{
			cmd_content.push_back(temp[i]);
		}
	}
#pragma endregion
	if (cmd == "CL")
	{
		if (cmd_content == "") {
			int* a = new int(tmpData->lineList->getSize() - 1);
			pOutput = a;
			N = 1;
		}
		else {
			void* pOut = new string(cmd_content);
			tmpData->cityList->traverse(findCityID,pOut);
			pOutput = new int(tmpData->lineList->traverse(findLine, pOut));
			N = 1;
		}
	}
	if (cmd == "LSC") {
		void* pOut = new string(cmd_content);
		tmpData->cityList->traverse(findCityID, pOut);
		N=tmpData->stationList->traverse(findStation, pOut);
		 //= tmpData->stationList->traverse(findStation, pOut);
		if (N == 0) {
			pOutput = new int(-1); N = 1;
		}
		else
		pOutput = pOut;
	}
	if (cmd == "LLC") {
		void* pOut = new string(cmd_content);
		tmpData->cityList->traverse(findCityID, pOut);
		N = tmpData->lineList->traverse(findLine, pOut);
		pOutput = pOut;
	}
	if (cmd == "LSL") {
		void* pOut = new int(stoi(cmd_content));
		N = tmpData->station_lineList->traverse(findLineIDInSLFile, pOut);;
		pOutput = pOut;
	}
	if (cmd == "FC") {
		void* pOut = new string(cmd_content);
		N = 1;
		if (tmpData->cityList->traverse(findCityID, pOut)== 0)
			pOutput=new int(-1);
		else pOutput = pOut;
	}
	if (cmd == "FS") {
		void* pOut = new string(cmd_content);
		N = 1;
		if (tmpData->stationList->traverse(findStationID, pOut)== 0)
			pOutput = new int(-1);
		else pOutput =pOut;
	}
	if (cmd == "SLP") {
		string st_id, t_id;
		int  staPos=0;
		for (int i = 0; i < cmd_content.find(' '); ++i) {
			st_id.push_back(cmd_content[i]);
		}
		for (int i = cmd_content.find(' ')+1; cmd_content[i]!='\0'; ++i) {
			t_id.push_back(cmd_content[i]);
		}
		void* pSta = new int(stoi(st_id));
		void* pTr = new int(stoi(t_id));
		string staGeo= tmpData->stationList->traverseFind(getStationGeometry, pSta);//retrive station geometry
		string traGeo= tmpData->trackList->traverseFind(getTrackGeometry, pTr);		//retrive track geometry
		if (staGeo != traGeo) {
			if (traGeo.find(staGeo) < traGeo.length()) {
				for (int i = 0; i < traGeo.find(staGeo); ++i) {
					if (traGeo[i] == ',')
						staPos++;
				}
				pOutput = new int(staPos);
			}
			else pOutput = new int(-1);
		}
		else pOutput=new int (-1);
		N = 1;
	}
	if (cmd == "IS") {
		string stname,stgeo;
		char* temp = &cmd_content[0];
		while (*temp != ',') {
			stname.push_back(*temp);
			temp = temp++;
		}
		temp = temp++;
		while (*temp != ',') {
			stgeo.push_back(*temp);
			temp = temp++;
		}
		TStation tmpStation ;
		int maxID = tmpData->stationList->traverseFindMax(getStationID);
		tmpStation.id=maxID+1;
		tmpStation.name = stname;
		tmpStation.geometry = stgeo;
		tmpStation.city_id = 0;
		tmpData->stationList->push_back(tmpStation);
		pOutput=new int( tmpStation.id);
		N = 1;
	}
	if (cmd == "ISL") {
		char* temp = &cmd_content[0];
#pragma region process content

		string idStation, idLine, id_x;
		int STA, LIN, pos;
		while(*temp!=' ') {
			idStation.push_back(*temp);
			temp=temp++;
		}
		STA = stoi(idStation);
		temp = temp++;
		while (*temp != ' ') {
			idLine.push_back(*temp);
			temp = temp++;
		}
		LIN = stoi(idLine);
		temp = temp++;
		while (*temp != '\0') {
			id_x.push_back(*temp);
			temp = temp++;
		}

#pragma endregion
		void* pOut = new int(LIN);
		int check = tmpData->station_lineList->traverse(findLineIDInSLFile, pOut);
		if (check!=0) {
			pos = stoi(id_x);
			int staAtidx = ((int*)pOut)[pos];
			pOut = new int[2];
			((int*)pOut)[0] = STA;
			((int*)pOut)[1] = LIN;
			int stationCount = tmpData->station_lineList->traverse(findStationIDInSLFile, pOut);//find if the given station is existed
			if ( stationCount ==0) {
				pOut = new int[2];
				((int*)pOut)[0] = staAtidx;
				((int*)pOut)[0] = STA;
				int filePos = tmpData->station_lineList->traverseFindPos(getSTaLine, pOut);
				TStation_Line tmp(STA, LIN);
				tmpData->station_lineList->insert(filePos, tmp);
				pOutput = new int(0);
			}
			else {
				pOutput = new int(-1);
			}
		}
		else {
			pOutput = new int(-1);
		}
		/*if (!isExisted) {
			if (stoi(id_x) <= tmpData->station_lineList->getSize() + 1) {
				TStation_Line tmpSta_Line(0, stoi(idStation), stoi(idLine));
				tmpData->station_lineList->insert(stoi(id_x), tmpSta_Line);
			}
			else pOutput = new int(-1);
		}
		else {
			pOutput = new int(-1);
		}*/
		N = 1;//cout << idStation << idLine << id_x;
	}
	if (cmd == "US") {
		string stID, stname, stgeo;
		int ID;
		char* temp = &cmd_content[0];
		while (*temp != ' ') {
			stID.push_back(*temp);
			temp = temp++;
		}
		ID = stoi(stID);
		void* pOut = new int(ID);
		int check = tmpData->stationList->traverse(checkStaID, pOut);
		if (check) {
			temp = temp++;
			while (*temp != ',') {
				stname.push_back(*temp);
				temp = temp++;
			}
			temp = temp++;
			while (*temp != ',') {
				stgeo.push_back(*temp);
				temp = temp++;
			}
			pOut = new string[3];
			((string*)pOut)[0] = stID;
			((string*)pOut)[0] = stname;
			((string*)pOut)[0] = stgeo;
			tmpData->stationList->traverseFindPos(replace, pOut);
			//TStation*station =tmpData->stationList->at()
			pOutput = new int(0);
		}
		else pOutput = new int(-1);
		N = 1;
	}
	if (cmd == "RSL") {
		string st_id, l_id;
		int  pos = 0,sta,lin;
		for (int i = 0; i < cmd_content.find(' '); ++i) {
			st_id.push_back(cmd_content[i]);
		}
		sta = stoi(st_id);
		for (int i = cmd_content.find(' ') + 1; cmd_content[i] != '\0'; ++i) {
			l_id.push_back(cmd_content[i]);
		}
		lin = stoi(l_id);
		void* pOut = new int[2];
		((int*)pOut)[0] = sta;
		((int*)pOut)[1] = lin;
		pos = tmpData->station_lineList->traverseFindPos(getSTaLine, pOut);
		if (pos!=-1) {
			tmpData->station_lineList->remove(pos);
			pOutput = new int(0);
		}
		else pOutput = new int(-1);
		N = 1;
	}
	if (cmd == "RS") {
		int ID = stoi(cmd_content);
		void* pOut = new int(ID);
		int posST = tmpData->stationList->traverseFindPos(checkStaID, pOut);
		if (posST != -1) {
			tmpData->stationList->remove(posST);
			pOut = new int(ID);
			int stCount = tmpData->station_lineList->traverse(findStationIDInSLFile, pOut);
			while (stCount) {
				pOut = new int(ID);
				int pos= tmpData->station_lineList->traverseFindPos(findStationIDInSLFile, pOut);
				tmpData->station_lineList->remove(pos);
				stCount--;
			}
			pOutput = new int(0);
		}
		else pOutput = new int(-1);
		N = 1;
	}
}