#pragma once
#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>
#include "serialib.h"
using namespace std;
using namespace cv;
serialib serial;
string incoming_msg;
string outgoing_msg;

#if defined (_WIN32) || defined(_WIN64)
#define SERIAL_PORT "COM1"
#endif
#if defined (__linux__) || defined(__APPLE__)
#define SERIAL_PORT "/dev/ttyS0"
#endif

static vector<string> splitstring(string str) {
	static vector<string> splitted;
	static string word = "";
	static int word_index = 0;
	for (auto c : str) {
		if (c == ',') {
			splitted.push_back(word);
			word_index++;
			word = "";
		}
		else {
			word += c;
		}
	}
	return splitted;
}

int ConnectSerial()
{
	char errorOpening = serial.openDevice(SERIAL_PORT, 115200);
	if (errorOpening != 1) return errorOpening;
	cout << "Successful connection to %s\n", SERIAL_PORT;
	serial.DTR(true);
	serial.RTS(false);
}

void ReadSerial() 
{
	incoming_msg = "";
	while (serial.available()) {
		char incoming_char;
		serial.readChar(&incoming_char);
		if (incoming_char == '\n' && serial.available()) {
			incoming_msg = "";
		}
		else {
			incoming_msg += incoming_char;
		}
	}
}

void WriteSerial(string outgoing_msg)
{
	char* char_arr;
	string str_obj(outgoing_msg);
	char_arr = &str_obj[0];
	serial.writeString(char_arr);
}