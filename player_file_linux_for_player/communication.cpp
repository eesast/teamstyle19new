#include"communication.h"
#include<iostream>
#include<string>
#include<sstream>
#include<regex>
#include<vector>
#include"api_player.h"

using namespace std;

MyClient::MyClient()
{
	//����socket�Ļ�������
/*	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(9999);*/

    sockClient=socket(AF_INET,SOCK_STREAM,0);
    addrServer.sin_family=AF_INET;
    addrServer.sin_port=htons(9999);
    addrServer.sin_addr.s_addr=inet_addr("127.0.0.1");
}

void MyClient::change_map(char* map0)
{
	map = new bool*[200];
	for (int i = 0; i < _mapsize; i++)
		map[i] = new bool[_mapsize];
	for (int i = 0; i < _mapsize; i++)
	{
		for (int j = 0; j < _mapsize; j++)
			map[i][j] = map0[i*_mapsize + j] - '0';
	}
}

void MyClient::start_connection()  //�������������������
{
//	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));	
    connect(sockClient,(struct sockaddr*)&addrServer,sizeof(struct sockaddr_in));
    char cflag[1];
	recv(sockClient, cflag, 1, 0);
	string sflag(cflag);
	istringstream os(sflag);
	os >> flag;
	cout << "my flag is" << flag;
	int size = 200 * 200;  //size���Ե���
	smap = new char[size + 1];
	recv(sockClient, smap, size, 0);
	smap[size] = '\0';
	char can_start[3];
	recv(sockClient, can_start, 2, 0);
	can_start[2] = '\0';
	cout << can_start<<endl;
	fflag = flag;
	change_map(smap);

}

char* MyClient::change_command(bool _update, vector<command1> &v1, vector<command2>&v2)
{
	stringstream s;
	if (_update == true)
		s << 0;
	else
		s << 5;
	for (int i = 0; i < v1.size(); i++)
	{
		s << ',';
		s << v1[i].commandid << " " << v1[i].id;
	}
	for (int i = 0; i < v2.size(); i++)
	{
		s << ',';
		s << v2[i].commandid << " " << v2[i].building_type << " " << v2[i].bx << " " << v2[i].by << " " << v2[i].sx << " " << v2[i].sy;
	}
	string ss = s.str();
	if (ss.size() == 0)
		return NULL;
	char* c = new char[ss.size()];
	for (int i = 0; i < ss.size(); i++)
	{
		c[i] = ss[i];
	}
	c[ss.size()] = '\0';
	return c;
}

void MyClient::send_command(bool _update, vector<command1> &v1, vector<command2>&v2)
{
	char* msg = change_command(_update,v1,v2);
	if (msg == NULL)
		return;
	char* hello = "start";
	int len = strlen(msg);
	stringstream s;
	s << len;
	int count = 1;
	len /= 10;
	while (len > 0)
	{
		count++;
		len /= 10;
	}
	int left = 10 - len;
	for (; left > 0; left--)
		s << '#';
	const char* c = s.str().c_str();
	send(sockClient, hello, strlen(hello), 0);
	send(sockClient, s.str().c_str(), 10, 0);
	send(sockClient, msg, strlen(msg), 0);
}

State* MyClient::recv_state()
{
	char start[6];
	start[5] = '\0';
	char* cpstart = "start";
	//�ȴ�start���� һ�����յ�start����Ϳ�ʼ����״̬
	while (true) 
	{
		recv(sockClient, start, 5, 0);
		cout << start<<endl;
		bool flag = true;
		for(int i=0;i<5;i++)
			if (start[i] != cpstart[i])
			{
				flag = false;
				break;
			}
		if (flag)
			break;
	}

	//���ܽ����������state�ж��ٸ��ֽ� ����������һ����9λ ������λ��#����
	char number[10];
	for (int i = 0; i < 9; i++)
		number[i] = '#';
	number[9] = '\0';
	recv(sockClient, number, 9, 0);
	istringstream is(number);
	int len;
	is >> len;
	//cout << len << "!!!!"<<endl;
	//����״̬
	char *save;
	save = new char[len + 1];
	save[len] = '\0';
	recv(sockClient, save, len, 0);
	//cout << save << endl;

	//��byte��������ת����ʵ��
	regex reg0("(.*);(.*);(.*);(.*);#(.*);(.*);(.*);#");
	smatch m0;
	string s(save);
	regex_match(s, m0, reg0);
//m0.str(2/5) ������ʱ�� ��Դ �Ƽ�
//m0.str(3/6) �����˽�������Ϣ
//m0.str(4/7) ������soldier����Ϣ
	int w;
	istringstream iis(m0.str(1));
	State* state = new State;
	iis >> w;
//	cout << "!!!!!!!!!!!!!!!!!!!!!~~~~~~~~~~~!!1" << w << "!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	state->winner = w % 10;
	state->turn = w / 10;
//	cout << "Winner is" << state->winner << endl;
	//��resource��ageʵ����
	for (int i = 0; i < 2; i++)
	{
		istringstream iis(m0.str(2+3*i));
		int int_age;
		char temp;
		iis >> int_age;
		iis >> temp;
		int building_resource;
		iis >> building_resource;
		iis >> temp;
		int building_point;
		iis >> building_point;
		//cout << building_point;
		_resource temp_resource(building_point, building_resource);
		state->resource[i] = temp_resource;
		//cout << i<<"!!!"<<state->resource[i].building_point << state->resource[i].resource << endl;
		state->age[i] = (Age)int_age;
		//cout << i << "!!" << state->age[i] << endl;
	}
	
	//��buildingʵ����
	int unit_id, building_type, posx, posy, int_main;
	double hp;
	int levels;
	char temp;
	for (int i = 0; i < 2; i++)
	{
		istringstream builds(m0.str(3+i*3));
		while (true)
		{
			unit_id = -1;
			builds >> unit_id;
			if (unit_id == -1)
				break;
			builds >> building_type;
			builds >> hp;
			builds >> posx;
			builds >> posy;
			builds >> int_main;
			level = int_main;
			builds >> temp;
			BuildingType q;
			q = (BuildingType)building_type;
			state->building[i].push_back(Building(q, hp, Position(posx, posy), i, unit_id, level));
			//cout << q << " " << hp << " " << posx << " " << posy << " " <<i << " " << unit_id << " " << bool_main << endl;
		}
	}
	int soldier_name;
	for (int i = 0; i < 2; i++)
	{
		istringstream soldiers(m0.str(4 + i * 3));
		while (true)
		{
			unit_id = -1;
			soldiers >> unit_id;
			if (unit_id == -1)
				break;
			soldiers >> soldier_name;
			soldiers >> hp;
			soldiers >> posx;
			soldiers >> posy;
			soldiers >> temp;
			SoldierName q;
			q = (SoldierName)soldier_name;
			state->soldier[i].push_back(Soldier(q, hp, Position(posx, posy), i, unit_id));
		//	cout << q << " " << hp << " " << posx << " " << posy << " " << i << " " << unit_id << endl;
		}
	}
	//resource[2] building[2] soldier[2] ������0 1��Ҹ��Զ�Ӧ��ȫ����Ϣ
	//Winner ���浱ǰ��Ϸ��ʤ����
	return state;
}
