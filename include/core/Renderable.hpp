#include <cstdlib>

namespace MSQ 
{
	class Renderable 
	{
		unsigned long int id_;
	public:
		virtual void render() = 0;
		Renderable():id_(rand()){};
	};
}
