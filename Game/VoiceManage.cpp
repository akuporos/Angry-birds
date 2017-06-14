#include "VoiceManage.h"

#include <iostream>

VoiceManage::VoiceManage()
{
}

void VoiceManage::send_request()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	ConnectionRequest proto_request;
	proto_request.set_speechkitversion("");
	proto_request.set_servicename("asr_dictation");
	proto_request.set_uuid("c4ab51e60edc40c88f6242e4a777a5a5");
	proto_request.set_apikey("ce0b1295-0fed-4336-a912-76398c0012c4");
	std::string sl = "ce0b1295-0fed-4336-a912-76398c0012c4";
	proto_request.set_applicationname("angry game");
	proto_request.set_device("laptop");
	proto_request.set_coords("0,0");
	proto_request.set_topic("queries");
	proto_request.set_lang("ru");
	proto_request.set_format("audio/x-wav");
	AdvancedASROptions* proto_adv = new AdvancedASROptions();
	//proto_adv->set_biometry("group");
	proto_adv->set_partial_results(false);
	proto_request.set_allocated_advancedasroptions(proto_adv);

	int array_size = proto_request.ByteSize();
	char* request_array = new char[array_size];
	proto_request.SerializeToArray(request_array, array_size);
	std::stringstream ss;
	ss << std::hex << array_size; // int decimal_value
	int s = ss.str().size();
	std::string str = ss.str();

	ConnectionResponse proto_response;
	char data;
	std::size_t received;

	status = socket.connect("asr.yandex.net", 80);
	
	std::string get_request = "GET /asr_partial HTTP/1.1\r\nUser-Agent: KeepAliveClient\r\nHost: asr.yandex.net:80\r\nUpgrade: dictation\r\n\r\n";
	socket.send(get_request.c_str(), get_request.size());
	bool flag_receive = false;
	while (true)
	{
		socket.receive(&data, 1, received);
		if (data == '\r')
		{
			socket.receive(&data, 1, received);
			flag_receive = true;
			socket.receive(&data, 1, received);
			if (data == '\r')
			{
				socket.receive(&data, 1, received);
				break;
			}
			flag_receive = false;
		}
	};

	socket.send(str.c_str(), s);
	socket.send("\r\n", 2);
	socket.send(request_array, array_size);

	std::size_t rcv;
	std::string size;
	char size_element;
	while (true)
	{
		socket.receive(&size_element, 1, rcv);
		if (size_element == '\r')
		{
			status  = socket.receive(&size_element, 1, rcv);
			break;
		}
		size += size_element;
	}
	// TCP socket:
	ss.str("");
	ss << size;
	int receive_answer;
	ss >> std::hex  >> receive_answer;
	std::vector<char> deserialised(receive_answer);
	socket.receive(&deserialised[0], receive_answer, received);

	proto_response.ParseFromArray(&deserialised[0], received);
	recorder.start();
}


std::vector<std::string> VoiceManage::new_audio()
{
	recorder.stop();
	const sf::SoundBuffer& buffer = recorder.getBuffer();
	std::string file_name = "my_record.wav";
	buffer.saveToFile(file_name);
	AddData add_audio;
	std::ifstream input("my_record.wav", std::ios::binary);
	// copies all data into buffer
	std::vector<char> bin_file((
		std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));
	add_audio.set_audiodata(&bin_file[0], bin_file.size());
	add_audio.set_lastchunk(false);
	int array_size = add_audio.ByteSize();
	char* request_array = new char[array_size];
	add_audio.SerializeToArray(request_array, array_size);

	std::stringstream ss;
	ss << std::hex << array_size; // int decimal_value
	int s = ss.str().size();
	std::string str = ss.str();

	socket.send(str.c_str(), s);
	socket.send("\r\n", 2);
	socket.send(request_array, array_size);
	
	recorder.start();

	AddDataResponse audio_recog;
	std::size_t rcv;
	std::string size;
	char size_element;
	while (true)
	{
		status = socket.receive(&size_element, 1, rcv);
		std::cout << status << std::endl;
		if (size_element == '\r')
		{
			status = socket.receive(&size_element, 1, rcv);
			break;
		}
		size += size_element;
	}
	// TCP socket:
	std::stringstream sss;
	sss << size;
	int receive_answer;
	sss >> std::hex >> receive_answer;
	std::vector<char> deserialised(receive_answer);
	socket.receive(&deserialised[0], receive_answer, rcv);
	std::vector<std::string> words;
	audio_recog.ParseFromArray(&deserialised[0], rcv);
	if (audio_recog.endofutt())
	{
		Result res = audio_recog.recognition(0);
		for (int i = 0; i <  res.words_size(); i++)
		{
			std::string val = Utf8_to_cp1251(res.words(i).value());
			words.push_back(val);
		}
	}
	return words;
}
std::string VoiceManage::Utf8_to_cp1251(const std::string& src)
{
	std::string res;
	int result_u, result_c;
	auto str = &src[0];


	result_u = MultiByteToWideChar(CP_UTF8,
		0,
		str,
		-1,
		0,
		0);

	if (!result_u)
		return 0;

	wchar_t *ures = new wchar_t[result_u];

	if (!MultiByteToWideChar(CP_UTF8,
		0,
		str,
		-1,
		ures,
		result_u))
	{
		delete[] ures;
		return 0;
	}


	result_c = WideCharToMultiByte(
		1251,
		0,
		ures,
		-1,
		0,
		0,
		0, 0);

	if (!result_c)
	{
		delete[] ures;
		return 0;
	}

	char *cres = new char[result_c];

	if (!WideCharToMultiByte(
		1251,
		0,
		ures,
		-1,
		cres,
		result_c,
		0, 0))
	{
		delete[] cres;
		return 0;
	}
	delete[] ures;
	res.append(cres);
	delete[] cres;
	return res;
}
VoiceManage::~VoiceManage()
{
}
