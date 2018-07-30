/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyObject.cpp
 * Author: Thong_Laptop
 * 
 * Created on July 13, 2018, 6:03 PM
 */

#include <ostream>

#include "MyObject.h"

MyObject::MyObject() {
}

MyObject::MyObject(const MyObject& orig) {
    this->name = orig.name;
    this->type = orig.type;
	this->size = orig.size;
	if (!this->type.empty()) {
		if (this->type.compare("char") == 0) {
			this->data = new char[this->size];
			memcpy(this->data, orig.data, this->size);
		}
		else if (this->type.compare("short") == 0) {
			this->data = new short[this->size];
			memcpy(this->data, orig.data, 2 * this->size);
		}
		else if (this->type.compare("int") == 0) {
			//cout << "2" << endl;
			this->data = new int[this->size];
			memcpy(this->data, orig.data, 4 * this->size);
		}
		else if (this->type.compare("long") == 0) {
			this->data = new long[this->size];
			memcpy(this->data, orig.data, 8 * this->size);
		}
		else if (this->type.compare("float") == 0) {
			this->data = new float[this->size];
			memcpy(this->data, orig.data, 4 * this->size);
		}
		else if (this->type.compare("double") == 0) {
			this->data = new double[this->size];
			memcpy(this->data, orig.data, 8 * this->size);
		}
		else if (this->type.compare("string") == 0) {
			if (this->size == 1) {
				this->data = new string(*((string*)orig.data));
			}
			else {
				this->data = new string[this->size];
				for (int i = 0; i < this->size; i++) {
					((string*)(this->data))[i] = string(((string*)(orig.data))[i]);
				}
			}
		}
		else if (this->type.compare("object") == 0) {
			if (this->size == 1) {
				//cout << "1-a" << endl;
				this->data = new MyObject(*((MyObject*)orig.data));
			}
			else {
				//cout << "1-b" << endl;
				this->data = new MyObject[this->size];
				for (int i = 0; i < this->size; i++) {
					((MyObject*)(this->data))[i] = MyObject(((MyObject*)(orig.data))[i]);
				}
			}
		}
	}
}

MyObject::~MyObject() {
}

MyObject& MyObject::operator=(const MyObject& orig) {
	//cout << "func =" << endl;
	this->name = orig.name;
	this->type = orig.type;
	this->size = orig.size;
	if (!this->type.empty()) {
		if (this->type.compare("char") == 0) {
			this->data = new char[this->size];
			memcpy(this->data, orig.data, this->size);
		}
		else if (this->type.compare("short") == 0) {
			this->data = new short[this->size];
			memcpy(this->data, orig.data, 2 * this->size);
		}
		else if (this->type.compare("int") == 0) {
			this->data = new int[this->size];
			memcpy(this->data, orig.data, 4 * this->size);
		}
		else if (this->type.compare("long") == 0) {
			this->data = new long[this->size];
			memcpy(this->data, orig.data, 8 * this->size);
		}
		else if (this->type.compare("float") == 0) {
			this->data = new float[this->size];
			memcpy(this->data, orig.data, 4 * this->size);
		}
		else if (this->type.compare("double") == 0) {
			this->data = new double[this->size];
			memcpy(this->data, orig.data, 8 * this->size);
		}
		else if (this->type.compare("string") == 0) {
			if (this->size == 1) {
				this->data = new string(*((string*)orig.data));
			}
			else {
				this->data = new string[this->size];
				for (int i = 0; i < this->size; i++) {
					((string*)(this->data))[i] = string(((string*)(orig.data))[i]);
				}
			}
		}
		else if (this->type.compare("object") == 0) {
			if (this->size == 1) {
				this->data = new MyObject(*((MyObject*)orig.data));
			}
			else {
				this->data = new MyObject[this->size];
				for (int i = 0; i < this->size; i++) {
					((MyObject*)(this->data))[i] = MyObject(((MyObject*)(orig.data))[i]);
				}
			}
		}
	}
}

string MyObject::convertToData() {
	stringstream ss;
	ss << "{name:\"";
	cout << name << endl;
	ss << name;
	ss << "\";type:\"";
	ss << type;
	cout << type << endl;
	ss << "\";length:\"";
	if (type.compare("string") == 0) {
		if (this->size == 1) {
			ss << std::to_string(((string*)(this->data))->length());
			ss << "\";data:";
			ss << "\"";
			ss << *((string*)(this->data));
			ss << "\"" << "}";
		}
		else {
			int tmp_length = 0;
			for (int i = 0; i < this->size; i++) {
				tmp_length += ((string*)(this->data)+i)->length();
			}
			tmp_length += this->size * 2;
			ss << std::to_string(tmp_length);
			ss << "\";data:";
			for (int i = 0; i < this->size; i++) {
				ss << "\"" << ((string*)(this->data))[i] << "\"";
			}
			//ss.seekp(ss.str().length() - 1);
			ss << "}";
		}
	}
	else if (type.compare("object") == 0) {
		if (this->size == 1) {
			string tmp = ((MyObject*)(this->data))->convertToData();
			ss << std::to_string(tmp.length());
			ss << "\";data:";
			ss << "\"";
			ss << tmp;
			ss << "\"" << "}";
		}
		else {
			string tmp[this->size];
			int tmp_length = 0;
			for (int i = 0; i < this->size; i++) {
				tmp[i] = ((MyObject*)(this->data))[i].convertToData();
				tmp_length += tmp[i].length();
			}
			ss << std::to_string(tmp_length);
			ss << "\";data:";
			for (int i = 0; i < this->size; i++) {
				ss << tmp[i];
			}
			ss << "}";
		}
	}
	else {
		int tmp_member_size = 0;
		if (this->type.compare("char") == 0)
			tmp_member_size = 1;
		else if (this->type.compare("short") == 0)
			tmp_member_size = 2;
		else if (this->type.compare("int") == 0)
			tmp_member_size = 4;
		else if (this->type.compare("long") == 0)
			tmp_member_size = 8;
		else if (this->type.compare("float") == 0)
			tmp_member_size = 4;
		else if (this->type.compare("double") == 0)
			tmp_member_size = 8;
		if (this->size == 1) {
			string tmp = m_base64.encode((char*)this->data, tmp_member_size);
			ss << std::to_string(tmp.length());
			ss << "\";data:";
			ss << tmp;
			ss << "}";
		}
		else {
			int t_length = tmp_member_size * this->size;
			string tmp = m_base64.encode((char*)this->data, t_length);
			ss << std::to_string(tmp.length());
			ss << "\";data:";
			ss << tmp;
			ss << "}";
		}
	}
	return ss.str();
}

bool MyObject::convertFromData(string& input_data, int &index) {
	std::stringstream ss;
	int temp_index = index;
	int store_index = index;
	if (checkData(input_data, temp_index, "{name:\"") == false) {
		return false;
	}
	index = temp_index;
	if (findData(input_data, temp_index, '\"') == false) {
		return false;
	}
	this->name = input_data.substr(index, temp_index - index - 1);
	index = temp_index;
	
	if (checkData(input_data, temp_index, ";type:\"") == false) {
		return false;
	}
	index = temp_index;
	if (findData(input_data, temp_index, '\"') == false) {
		return false;
	}
	this->type = input_data.substr(index, temp_index - index - 1);
	
	index = temp_index;
	if (checkData(input_data, temp_index, ";length:\"") == false) {
		return false;
	}
	index = temp_index;
	if (findData(input_data, temp_index, '\"') == false) {
		return false;
	}
	int m_length = atoi(input_data.substr(index, temp_index - index - 1).c_str());
	index = temp_index;
	if (checkData(input_data, temp_index, ";data:") == false) {
		return false;
	}
	index = temp_index;
	if (input_data.length() <= index + m_length) {
		return false;
	}
	if (input_data.at(index + m_length) != '}') {
		return false;
	}
	index += m_length;
	index++;
	if (this->type.compare("object") == 0) {
		vector<MyObject> m_buffer;
		for (;;) {
			m_buffer.push_back(MyObject());
			if (!m_buffer.at(m_buffer.size() - 1).convertFromData(input_data, temp_index)) {
				this->size = m_buffer.size() - 1;
				this->data = new MyObject[this->size];
				for (int i = 0; i < this->size; i++) {
					((MyObject*)(this->data))[i] = MyObject(m_buffer.at(i));
				}
				return true;
			}
		}	
	}
	else if (this->type.compare("string") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		if (input_data.at(temp_index) != '\"') {
			return false;
		}
		vector<string> m_buffer;
		temp_index++;
		int tmp_index = temp_index;
		for (;;) {
			if (findData(input_data, temp_index, '\"')) {
				m_buffer.push_back(input_data.substr(tmp_index, temp_index - tmp_index - 1));
				if (input_data.at(temp_index) != '\"') {
					this->size = m_buffer.size();
					this->data = new string[this->size];
					for (int i = 0; i < this->size; i++) {
						((string*)(this->data))[i] = string(m_buffer.at(i));
					}
					m_buffer.clear();
					return true;
				}
				else {
					temp_index++;
					tmp_index = temp_index;
				}
			}
			else {
				return false;
			}
		}
	}
	else if (this->type.compare("char") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size();
		this->data = new char[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	else if (this->type.compare("short") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size()/2;
		this->data = new short[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	else if (this->type.compare("int") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size() / 4;
		this->data = new int[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	else if (this->type.compare("long") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size() / 8;
		this->data = new long[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	else if (this->type.compare("float") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size() / 4;
		this->data = new long[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	else if (this->type.compare("double") == 0) {
		string tmp = input_data.substr(temp_index, m_length);
		vector<char> buffer;
		buffer = m_base64.decode(tmp);
		this->size = buffer.size() / 4;
		this->data = new long[this->size];
		memcpy(this->data, buffer.data(), buffer.size());
		//index += m_length;
		return true;
	}
	return false;
}


bool MyObject::checkData(string& input, int& index, string comp) {
    bool flag = true;
    int length = comp.length();

    if(index + length >= input.size()) {
        return false;
    }
    string::iterator pointer_1 = input.begin() + index;
    string::iterator pointer_2 = comp.begin();
    for(pointer_2 = comp.begin(); pointer_2 < comp.end(); pointer_2++) {
        if(pointer_1[0] != pointer_2[0]) {
            return false;
        } else {
            pointer_1++;
        }
    }
    index += length;
    return true;
}

bool MyObject::findData(string& input, int& index, char data) {
	for (string::iterator pointer = input.begin() + index; pointer < input.end(); pointer++) {
		if (pointer[0] == data) {
			index = pointer - input.begin() + 1;
			return true;
		}
	}
	return false;
}