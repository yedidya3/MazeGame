// MazeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "UserInterfaceMaze.h"
#include "WriterStream.h"
#include "ReaderStream.h"
#include "WriterNet.h"
#include "ReadNet.h"
#include "UserInputParser.h"
#include "StructureRooms.h"
#include "Group.h"
#include "ProducesRoomsGroup.h"
#include <canvas.hpp>

#include <thread>
#include "ServerProj.h"
#include <conio.h>
#include "RunPlayerNet.h"
#include "RunPlayerStream.h"
#include <chrono>

#include "CreatorPlayersUniqueNames.h"
#include "DbNames_mt.h"
#include "CommandDrawRoom.h"
#include "ContentsRooms.h"
#include "CommandWalk.h"
#include "CommandAttack.h"
#include "ShoutState.h"
#include "TalkState.h"
#include "ActionState.h"

using namespace experis;

static constexpr unsigned char AMOUNT_DIRECTORY = 4;

std::unordered_map<Directions, std::string> DirectToStr
{
	{Directions::NORTH , "North"}
	,{Directions::EAST , "East"}
	,{Directions::SOUTH , "South"}
	,{Directions::WEST , "West"}
};

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

namespace start_data
{
    StateRoom OPEN = StateRoom::OPEN;
    StateRoom CLOSE = StateRoom::CLOSE;
    std::vector<StateRoom> roomsOpen{
        OPEN, OPEN, CLOSE, CLOSE
        ,CLOSE, OPEN, CLOSE, CLOSE
        ,CLOSE, OPEN, CLOSE, CLOSE
        ,CLOSE, OPEN, OPEN, CLOSE
        ,CLOSE, OPEN, OPEN, CLOSE
        ,CLOSE, OPEN, OPEN, CLOSE
        ,CLOSE, CLOSE, CLOSE, CLOSE
    };

    StructureRooms rooms{roomsOpen, 4};
    ContentsRooms contentsRooms{roomsOpen};


    CommandsMap commands{};

    CommandsMap commandsMang{};
    CommandAttack commandAttack{contentsRooms};


    DbNames_mt dbNames{};
    CreatorPlayersUniqueNames createUniquePlayers{dbNames, contentsRooms};
    
    CommandDrawRoom commandDrawRoom{rooms, contentsRooms};
    CommandWalk commandWalk{rooms, contentsRooms, commandDrawRoom};
}


int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
  //  size_t x = size_t(- 1);
    //std::cout << x << std::endl;
  // std::cout << std::abs(1 - 2) % 3 << std::endl;
    

    using namespace start_data;
    
    

    commands.Add("attack", commandAttack);


    commands.Add("collect", [&](Player& a_player){
        contentsRooms.Get(a_player.GetNumRoom()).BoxCollection(a_player);
        });

    auto facing = [&](Player& a_player){ a_player.GetWriter()->operator<<("You Are Facing ") <<
        DirectToStr[a_player.GetFacing().GetDirection()] << "\n";};

    commands.Add("facing", [&](Player& a_player){
         a_player.GetWriter()->operator<<("You Are Facing ") << DirectToStr[a_player.GetFacing().GetDirection()] << "\n";
         });

    commands.Add("left", [&](Player& a_player){
        Facing d = a_player.GetFacing();
	    d.Left();
	    a_player.SetFacing(d);     
        facing(a_player);
        });

    commands.Add("right", [&](Player& a_player){
        Facing d = a_player.GetFacing();
	    d.Right();
	    a_player.SetFacing(d);     
        facing(a_player);
        });


    commands.Add("help", [&](Player& a_player){
		for (const std::pair<std::string, CommandsMap::Action>& pair : commands)
		{
			a_player.GetWriter()->operator<<(pair.first) << "\n";
		}
	});
     UserInputParser parser{commands};
     std::unordered_map<std::string, std::shared_ptr<InputModeState>> m_mapStatesNext{};
    std::shared_ptr<ActionState> actionState = std::make_shared<ActionState>(parser, m_mapStatesNext, commands);
    std::shared_ptr<InputModeState> talkState = std::make_shared<TalkState>(contentsRooms, actionState);
    std::shared_ptr<InputModeState> shoutState = std::make_shared<ShoutState>(contentsRooms, actionState, rooms);
  
    m_mapStatesNext.insert(std::make_pair("talk", talkState));
    m_mapStatesNext.insert(std::make_pair("shout", shoutState));
    m_mapStatesNext.insert(std::make_pair("action", actionState));


     commands.Add("talk", [&](Player& a_player){
         a_player.GetWriter()->operator<<("what do you want to say?\n");
         });

     commands.Add("shout", [&](Player& a_player){
         a_player.GetWriter()->operator<<("what do you want to shout?\n");
         });


    commands.Add("exit", [&](Player& a_player)
        {
            a_player.GetWriter()->operator<<("game over\n Bye Bye...\n");
            throw std::invalid_argument("a or b negative"); //example
        });

    commands.Add("show", commandDrawRoom);

 
    commands.Add("walk", commandWalk);
    
    commandsMang.Add("start", [&](Player& a_player){
        std::string msgStart = "Hii " + a_player.GetName() + " welcome to the maze game\nFor the list of commands type \"help\"\n";
        MsgEnter(contentsRooms, a_player.GetNumRoom(), a_player.GetName());
        a_player.GetWriter()->operator<<(msgStart);
        facing(a_player);
        commandDrawRoom(a_player);
        });

    UserInterfaceMaze ui{actionState, commandsMang};

    std::unique_ptr<simplenet::SimpleNetMT> net;
    std::shared_ptr<simplenet::SimpleNetMT::Connection> connect;

    std::vector<std::unique_ptr<std::thread>> vectorTheards;
    std::unique_ptr<ServerProj<RunPlayerNet>> server;
    std::unique_ptr<RunPlayerNet> runPlayerNet;


    

    if (argc > 1 && is_number(argv[1]))
    {
        unsigned short port = static_cast<unsigned short>(std::stoul(argv[1]));
        std::cout << "try connect to net in port: " << port << "...\n";
        // unsigned short port = 4010;
        runPlayerNet.reset(new RunPlayerNet{createUniquePlayers, [&](Player& a_player, std::unique_ptr<Reader> a_reader){ui.Run(a_player, std::move(a_reader));}});
        server.reset(new ServerProj<RunPlayerNet>{*runPlayerNet, port, 50});
         std::cout << "connected\n";
    }

    std::unique_ptr<RunPlayerStream> runPlayerConsole;
    if (argc == 1 || (argc == 3 && std::string{argv[2]} == std::string{"console"}))
    {
        std::cout << "connect to console\n";
        runPlayerConsole.reset(new RunPlayerStream{
        createUniquePlayers, [&](Player& a_player, std::unique_ptr<Reader> a_reader){ui.Run(a_player, std::move(a_reader));}});
        vectorTheards.push_back(std::make_unique<std::thread>(&RunPlayerStream::operator()< std::istream , std::ostream>, std::ref(*runPlayerConsole),
        std::ref(std::cin), std::ref(std::cout)));
    }

    while(true)
    {
        std::this_thread::sleep_for(2000ms);
    }

  

}
