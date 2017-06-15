#pragma once

#include "SFML/Network.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <Windows.h>
#include "request.pb.h"
#include "response.pb.h"
#include "add_audio.pb.h"
#include "audio_recognition.pb.h"
#define PROTOBUF_USE_DLLS

class VoiceManage
{
	sf::SoundBufferRecorder recorder;
	sf::TcpSocket socket;
	sf::Socket::Status status;
public:
	
	VoiceManage();
	void send_request();
	void record_audio();
	std::vector<std::string> new_audio();
	std::string Utf8_to_cp1251(const std::string & src);
	~VoiceManage();
};

