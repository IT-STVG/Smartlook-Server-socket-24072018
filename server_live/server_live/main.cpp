#include <cstdio>


#include "MyObject.h"
#include "server_ws.hpp"
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;
using namespace cv;

static Mat buffer_src;

static bool flag_buffer_ready = true;

static VideoCapture play_clip;

static void *thread_server(void *threadid) {
	WsServer* server = (WsServer*)threadid;
	cout << "Server running ..." << endl;
	server->start();
	pthread_exit(NULL);
}

int main()
{
	printf("hello from server_live!\n");
	WsServer server;
	server.config.port = 8080;

	auto &echo = server.endpoint["^/live_stream/?$"];


	echo.on_message = [](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
		string msg = message->string();
		cout << "msg : " << msg << endl;
		MyObject obj_msg;
		int index = 0;
		//cout << obj_msg.convertFromData(msg, index) << endl;
		if (obj_msg.convertFromData(msg, index)) {
			cout << "Have data" << endl;
			if (obj_msg.name.compare("start") == 0) {
				play_clip = VideoCapture("/root/Workspace/ImageTest/video_test.mp4");
				if (play_clip.isOpened()) {
					MyObject obj_msg;
					string tmp = "OK";
					obj_msg.set("result", tmp);
					string buffer_msg = obj_msg.convertToData();
					auto send_stream = make_shared<WsServer::SendStream>();
					*send_stream << buffer_msg;
					cout << "Sending data" << endl;
					connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
						if (ec) {
							cout << "Server: Error sending message. " <<
								// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
								"Error: " << ec << ", error message: " << ec.message() << endl;
						}
					});
				}
				else {
					MyObject obj_msg;
					string tmp = "Error";
					obj_msg.set("result", tmp);
					string buffer_msg = obj_msg.convertToData();
					auto send_stream = make_shared<WsServer::SendStream>();
					*send_stream << buffer_msg;
					cout << "Sending data" << endl;
					connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
						if (ec) {
							cout << "Server: Error sending message. " <<
								// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
								"Error: " << ec << ", error message: " << ec.message() << endl;
						}
					});
				}
			}
			if (obj_msg.name.compare("view") == 0) {
				if (play_clip.isOpened()) {
					Mat src;
					play_clip >> src;
					if (src.empty()) {
						MyObject obj_msg;
						string tmp = "Error";
						obj_msg.set("result", tmp);
						string buffer_msg = obj_msg.convertToData();
						auto send_stream = make_shared<WsServer::SendStream>();
						*send_stream << buffer_msg;
						cout << "Sending data" << endl;
						connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
							if (ec) {
								cout << "Server: Error sending message. " <<
									// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
									"Error: " << ec << ", error message: " << ec.message() << endl;
							}
						});
					}
					else {
						vector<int> params;
						params.push_back(CV_IMWRITE_JPEG_QUALITY);
						params.push_back(50);
						vector<uchar> temp_buffer;
						imencode(".jpg", src, temp_buffer, params);
						cout << temp_buffer.size() << endl;
						MyObject obj_image;
						obj_image.set("image", (char*)(temp_buffer.data()), temp_buffer.size());
						cout << "Type obj : " << obj_image.type << endl;
						string buffer_msg = obj_image.convertToData();
						auto send_stream = make_shared<WsServer::SendStream>();
						*send_stream << buffer_msg;
						cout << "Sending data" << endl;
						connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
							if (ec) {
								cout << "Server: Error sending message. " <<
									// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
									"Error: " << ec << ", error message: " << ec.message() << endl;
							}
						});
					}
					
				}
				else {
					MyObject obj_msg;
					string tmp = "Error";
					obj_msg.set("result", tmp);
					string buffer_msg = obj_msg.convertToData();
					auto send_stream = make_shared<WsServer::SendStream>();
					*send_stream << buffer_msg;
					cout << "Sending data" << endl;
					connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
						if (ec) {
							cout << "Server: Error sending message. " <<
								// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
								"Error: " << ec << ", error message: " << ec.message() << endl;
						}
					});
				}
				/*
				while (!flag_buffer_ready) {
					cout << "Waiting" << endl;
					usleep(1000);
				}
				buffer_src = imread("/root/Workspace/ImageTest/file_1.jpg", 1);
				vector<int> params;
				params.push_back(CV_IMWRITE_JPEG_QUALITY);
				params.push_back(100);
				vector<uchar> temp_buffer;
				imencode(".jpg", buffer_src, temp_buffer, params);
				cout << temp_buffer.size() << endl;
				MyObject obj_image;
				obj_image.set("image", (char*)(temp_buffer.data()), temp_buffer.size());
				cout << "Type obj : " << obj_image.type << endl;
				string buffer_msg = obj_image.convertToData();
				auto send_stream = make_shared<WsServer::SendStream>();
				*send_stream << buffer_msg;
				cout << "Sending data" << endl;
				connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
					if (ec) {
						cout << "Server: Error sending message. " <<
							// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
							"Error: " << ec << ", error message: " << ec.message() << endl;
					}
				});

				flag_buffer_ready = true;
				*/
			}
		}
	};

	echo.on_open = [](shared_ptr<WsServer::Connection> connection) {
		cout << "Server: Opened connection " << connection.get() << endl;
	};

	// See RFC 6455 7.4.1. for status codes
	echo.on_close = [](shared_ptr<WsServer::Connection> connection, int status, const string & /*reason*/) {
		cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
	};

	// See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
	echo.on_error = [](shared_ptr<WsServer::Connection> connection, const SimpleWeb::error_code &ec) {
		cout << "Server: Error in connection " << connection.get() << ". "
			<< "Error: " << ec << ", error message: " << ec.message() << endl;
	};

	pthread_t pthread_server;
	pthread_create(&pthread_server, NULL, thread_server, &server);

	while (1) {
		sleep(1);
	}
	return 0;
}