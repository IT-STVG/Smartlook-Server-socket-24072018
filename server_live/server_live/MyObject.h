/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyObject.h
 * Author: Thong_Laptop
 *
 * Created on July 13, 2018, 6:03 PM
 */

#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>
#include <string.h>
#include "base64.h"

using namespace std;

class MyObject {
public:
	MyObject();
	MyObject(const MyObject& orig);
	virtual ~MyObject();
	MyObject& operator=(const MyObject& other);

	string name;
	string type;
	int size;
	void* data;

	//template <typename T> bool set(string name, T& data);
	//template <typename T, size_t N> bool set(string name, T (&data)[N]);
	//template <typename T> bool set(string name, T* p_data, int size);

	string convertToData();
	bool convertFromData(string& data, int &index);
private:
	bool checkData(string& input, int& index, string comp);
	bool findData(string& input, int& index, char data);

	Base64 m_base64;
public:


	template <typename T> bool set(string name, T& data) {
		this->name = name;
		this->type = getType(data);
		if (this->type.empty()) {
			return false;
		}
		this->size = 1;
		//boost::scoped_array<T>(this->data)(new T(data));
		//this->data = new T(data);
		this->data = (void*)(&data);
		return true;
	}

	template <typename T, size_t N> bool set(string name, T(&data)[N]) {
		this->name = name;
		this->type = getType(data[0]);
		if (this->type.empty()) {
			return false;
		}
		this->size = N;
		cout << this->type << endl;
		if (this->type.compare("string") == 0) {
			//this->data = new T[N];
			//boost::scoped_array<T>(this->data)(new T[N]);
			this->data = (void*)data;
			//for (int i = 0; i < N; i++) {
				//((T*)(this->data))[i] = T(data[i]);
			//}
		}
		else if (this->type.compare("object") == 0) {
			//this->data = new T[N];
			//boost::scoped_array<T>(this->data)(new T[N]);
			//for (int i = 0; i < N; i++) {
				//((T*)(this->data))[i] = T(data[i]);
			//}
			this->data = (void*)data;
		}
		else {
			//this->data = new T[N];
			//boost::scoped_array<T>(this->data)(new T[N]);
			//memcpy(this->data, data, this->size * sizeof(T));
			this->data = (void*)data;
		}
		return true;
	}

	template <typename T> bool set(string name, T* p_data, int size) {
		this->name = name;
		this->type = getType(p_data[0]);
		if (this->type.empty()) {
			return false;
		}
		this->size = size;
		
		//this->data = new T(size);
		//boost::scoped_array<T>(this->data)(new T[size]);
		if (this->type.compare("string") == 0) {
			//this->data = new T(size);
			//for (int i = 0; i < size; i++) {
                //((T*)(this->data))[i] = T(p_data[i]);
			//}
			this->data = p_data;
		}
		else if (this->type.compare("object") == 0) {
			//this->data = new T(size);
			//for (int i = 0; i < size; i++) {
                //((T*)(this->data))[i] = T(p_data[i]);
			//}
			this->data = p_data;
		}
		else {
            //this->data = new T(size);
            //memcpy(this->data, p_data, size * sizeof(T));
            //cout << "size copy" << this->size * sizeof(T) << "-" << sizeof(T)<<endl;
			this->data = p_data;
		}
		return true;
	}

	template <typename T> string getType(T& data) {
		if (typeid(T) == typeid(char))
			return "char";
		else if (typeid(T) == typeid(unsigned char))
			return "char";
		else if (typeid(T) == typeid(short))
			return "short";
		else if (typeid(T) == typeid(unsigned short))
			return "short";
		else if (typeid(T) == typeid(int))
			return "int";
		else if (typeid(T) == typeid(unsigned int))
			return "int";
		else if (typeid(T) == typeid(long))
			return "long";
		else if (typeid(T) == typeid(unsigned long))
			return "long";
		else if (typeid(T) == typeid(float))
			return "float";
		else if (typeid(T) == typeid(double))
			return "double";
		else if (typeid(T) == typeid(string))
			return "string";
		else if (typeid(T) == typeid(MyObject))
			return "object";
		else
			return string();
	}
};

#endif /* MYOBJECT_H */

