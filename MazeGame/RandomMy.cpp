#include "RandomMy.h"
namespace experis
{

namespace detail 
{
namespace random
{
static std::random_device rand{};
std::random_device::result_type Rand()
{
	return rand();
}

} //random
}//detail
} //experis