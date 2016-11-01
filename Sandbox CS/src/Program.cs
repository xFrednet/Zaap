using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ZaapCLI;

namespace Sandbox_CS
{
	class CLITest : Application
	{
		public CLITest() : base("lol", 800, 600)
		{

		}
		
		
	}

	class Program
	{
		static void Main(string[] args)
		{
			CLITest test = new CLITest();
			test.start();
			test.cleanup();
		}
	}
}
