using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZaapCLI;

namespace Sandbox_CS
{
	//public class CLITest : Application
	//{
	//	CLITest() : Application("CLI Test", 852, 480)
	//	{

	//	}
	//	public:
	//	virtual void update() override {
	//		}
	//}

	class Program
	{
		static void Main(string[] args)
		{
			Vector2 vec = new Vector2(1.0f, 2.0f);
			Console.WriteLine("Vector2 {0}, {1}", vec.X, vec.Y);
			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
		}
	}
}
