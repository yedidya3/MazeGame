#include "RunPlayerStream.h"

namespace experis
{

RunPlayerStream::RunPlayerStream(CreatorPlayer_Base& a_creatorPlayers, std::function<void(Player&, std::unique_ptr<Reader>)> a_funcRun)
	:m_creatorPlayers{a_creatorPlayers}
	,m_funcRun{a_funcRun}
{
}

} //experis